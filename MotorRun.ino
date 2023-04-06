#include // LCD
#include // Motors
#include // IR Recv.

LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD Initialization adn Setup on 0x27 default 
// We may want to switch this to a 7 segment display, much cheaper

// USS Pins and Vars
const int trigPin = ; // USS Trig Pin for all Sensors
const int echoPinL = ; // USS recvPin L
const int echoPinR = ; // USS recvPin R
const int echoPinF = ; // USS recvPin F
int distanceL; 
int distanceR;
int distanceF; 
long durationL;
long durationR;
long durationF;

// Restriction Variables
const int minDistFront = 15; // Minimum distance before it will redirect
const int minDistSide = 15; // Minimum distance before it will redirect

// IR Receiver Pins and Vars
const int irRecvPin = ; // IR Recieve Pin
int cmd;

// Motor Pins and Vars
const int motorLPin = ; // Left Motor Pin
const int motorLRev = ; // Left Motor Reverse Pin
const int motorRPin = ; // Right Motor Pin
const int motorRRev = ; // Right Motor Reverse Pin

void setup() {
    serial.begin(9600); // Serial Readout is 9600

    pinMode(trigPin, OUTPUT); // Sensor Reception
    pinMode(echoPinL, INPUT); // Reception pin from Sens L
    pinMode(echoPinR, INPUT); // Reception pin from Sens R
    pinMode(echoPinF, INPUT); // Reception pin from Sens F

    lcd.init(); // LCD Initialization 
    lcd.backlight(); // Turning on Backlight
    lcd.clear(); // Clearing LCD

    IrReceiver.begin(irRecvPin); // Receiver enables

    digitalWrite(motorLRev, LOW); // Ensuring Motor Movement is Forward
    digitalwrite(motorRRev, LOW);

    lcd.print('Strt Cmplt'); // May switch to 7 segment
}

void sensDist(){ // Sensor reading

digitalWrite(trigPin, LOW); 
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
durationL = pulseIn(echoPinL, HIGH);
durationR = pulseIn(echoPinR, HIGH);
durationF = pulseIn(echoPinF, HIGH);


distanceL = durationL * 0.034 / 2;
distanceR = durationR * 0.034 / 2;
distanceF = durationF * 0.034 / 2;

}


void forward() {
digitalWrite()
}

void turnRight() {

}

void turnLeft() {

}

void reverse() {

}

void shift (){
    lcd.print("Shifting Path");
    if (distanceF > distanceL && distanceF > distanceR) {
        forward();
    } else if (distanceF < distanceL && distanceR < distanceL) {
        turnLeft();
    } else {
        turnRight();
    }
    return;
}

void drive() {
    if (distanceF <= minDistFront || distanceL <= minDistSide || distanceL <= minDistSide) {
        shift();
    } else {
        forward();
    }
}


void loop() {
    if (IrReceiver.decode()) { // On IR Receive, decode
        IrReceiver.resume(); // resume reception
        serial.print(IrReceiver.decodedIRData.command); // Print Reception
        cmd = IrReceiver.decodedIRData.command; // Set as CMD
        if (cmd == 70) { // Check CMD for Mode Button
            while true {  // Infinite loop to be broken if Power is pressed
                if (IrReceiver.decode()){ // IR Receiver for shutdown
                    IrReceiver.resume();
                    serial.print(IrReceiver.decodedIRData.command);
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
