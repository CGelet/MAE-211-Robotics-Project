//#include <LiquidCrystal_I2C.h> // LCD
//#include // Motors
#include <IRremote.h> // IR Recv.

//LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD Initialization adn Setup on 0x27 default 
// We may want to switch this to a 7 segment display, much cheaper

// USS Pins and Vars
const int trigPinL = ; // USS Trig Pin L
const int trigPinR = 4; // USS Trig Pin R
const int trigPinF = 6; // USS Trig Pin F
const int echoPinL = ; // USS recvPin L
const int echoPinR = 3; // USS recvPin R
const int echoPinF = 5; // USS recvPin F
long int distance, duration;


// Restriction Variables
const int minDistFront = 15; // Minimum distance before it will redirect
const int minDistSide = 15; // Minimum distance before it will redirect

// IR Receiver Pins and Vars
const int irRecvPin = 13; // IR Recieve Pin
int cmd;

// Motor Pins and Vars
const int motorLPin = 9; // Left Motor Pin (IN1)
const int motorLRev = 10; // Left Motor Reverse Pin (IN2)
const int motorRPin = 11; // Right Motor Pin (IN3)
const int motorRRev = 12; // Right Motor Reverse Pin (IN4)

void setup() {
    Serial.begin(9600); // Serial Readout is 9600
    pinMode(motorRRev,OUTPUT);
    pinMode(motorLRev,OUTPUT);
    pinMode(motorRPin,OUTPUT);
    pinMode(motorLPin,OUTPUT);

    pinMode(trigPinL, OUTPUT); // Sensor Reception
    pinMode(trigPinR, OUTPUT); // Sensor Reception
    pinMode(trigPinF, OUTPUT); // Sensor Reception
    pinMode(echoPinL, INPUT); // Reception pin from Sens L
    pinMode(echoPinR, INPUT); // Reception pin from Sens R
    pinMode(echoPinF, INPUT); // Reception pin from Sens F

    //lcd.init(); // LCD Initialization 
    //lcd.backlight(); // Turning on Backlight
    //lcd.clear(); // Clearing LCD

    IrReceiver.begin(irRecvPin); // Receiver enables

    digitalWrite(motorLRev, LOW); // Ensuring Motor Movement is Forward
    digitalWrite(motorRRev, LOW);

    //lcd.print('Strt Cmplt'); // May switch to 7 segment
}

void loop() {
    if (IrReceiver.decode()) { // On IR Receive, decode
        IrReceiver.resume(); // resume reception
        Serial.print(IrReceiver.decodedIRData.command); // Print Reception
        cmd = IrReceiver.decodedIRData.command; // Set as CMD
        if (cmd == 70) { // Check CMD for Mode Button
            while (true) {  // Infinite loop to be broken if Power is pressed
                if (IrReceiver.decode()){ // IR Receiver for shutdown
                    IrReceiver.resume();
                    Serial.print(IrReceiver.decodedIRData.command);
                    cmd = IrReceiver.decodedIRData.command;
                    if (cmd == 69) {
                        break;
                    }
                }

                drive(); // Drive Function
            }
        }
    }
}

void drive() {
    long distanceF = sensDist(echoPinF,trigPinF);
    long distanceL = sensDist(echoPinL,trigPinL);
    long distanceR = sensDist(echoPinR,trigPinR);

    if (distanceF <= minDistFront || distanceL <= minDistSide || distanceL <= minDistSide) {
        shift();
    } else {
        forward();
    }
}

long sensDist(int echo, int trigger){ // Sensor reading
    int maxDist = 5000;
    digitalWrite(trigger, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger, LOW);

    duration = pulseIn(echo, HIGH);
    distance = duration * 0.034 / 2;

    if (distance > maxDist)
    {
        distance = maxDist;
    }
    return distance;
}

void shift (){
    //lcd.print("Shifting Path");
    long distanceF = sensDist(echoPinF,trigPinF);
    long distanceL = sensDist(echoPinL,trigPinL);
    long distanceR = sensDist(echoPinR,trigPinR);

    if (distanceF > distanceL && distanceF > distanceR) {
        forward();
    } else if (distanceF < distanceL && distanceR < distanceL) {
        turnLeft();
    } else {
        turnRight();
    }
    return;
}


void forward() {
    digitalWrite(motorLPin, HIGH);
    digitalWrite(motorRPin, HIGH);
    return;
}

void turnRight() {
    digitalWrite(motorLPin, LOW);
    digitalWrite(motorRPin, HIGH);
    return;
}

void turnLeft() {
    digitalWrite(motorRPin, LOW);
    digitalWrite(motorLPin, HIGH);
    return;
}

void reverse() {
    stop();
    digitalWrite(motorRRev, HIGH);
    digitalWrite(motorLRev, HIGH);
    delay(1000);
    shift();
    delay(1000);
    digitalWrite(motorRRev, LOW);
    digitalWrite(motorLRev, LOW);
    return;
}

void stop(){
    Serial.print('Stopped');
    digitalWrite(motorLPin, LOW);
    digitalWrite(motorRPin, LOW);
    return;
}

