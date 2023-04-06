#include // LCD
#include // Motors
#include // IR Recv.

LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD Initialization adn Setup on 0x27 default 
// We may want to switch this to a 7 segment display, much cheaper

const int trigPin = ; // USS Trig Pin for all Sensors
const int echoPin1 = ; // USS recvPin 1
const int echoPin2 = ; // USS recvPin 2
const int echoPin3 = ; // USS recvPin 3
int distance1;
int distance2;
int distance3; 
long duration1;
long duration2;
long duration3;


const int irRecvPin = ; // IR Recieve Pin
int cmd;

const int motorLPin = ; // Left Motor Pin
const int motorLRev = ; // Left Motor Reverse Pin

const int motorRPin = ; // Right Motor Pin
const int motorRRev = ; // Right Motor Reverse Pin

void setup() {
    serial.begin(9600); // Serial Readout is 9600

    pinMode(trigPin, OUTPUT); // Sensor Reception
    pinMode(echoPin1, INPUT); // Reception pin from Sens 1
    pinMode(echoPin2, INPUT); // Reception pin from Sens 2
    pinMode(echoPin3, INPUT); // Reception pin from Sens 3

    lcd.init(); // LCD Initialization 
    lcd.backlight(); // Turning on Backlight
    lcd.clear(); // Clearing LCD

    IrReceiver.begin(irRecvPin); // Receiver engables

    digitalWrite(trigPin, LOW); // Find distances at start
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration1 = pulseIn(echoPin1, HIGH);
    duration2 = pulseIn(echoPin2, HIGH);
    duration3 = pulseIn(echoPin3, HIGH);
    distance1f = duration1 * 0.034 / 2;
    distance2f = duration2 * 0.034 / 2;
    distance3f = duration3 * 0.034 / 2; // End of Distances at Start

    lcd.print('Strt Cmplt');
}

void sensRead(){ // Sensor reading

digitalWrite(trigPin, LOW); 
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration1 = pulseIn(echoPin1, HIGH);
duration2 = pulseIn(echoPin2, HIGH);
duration3 = pulseIn(echoPin3, HIGH);

distance1i = distance1f;
distance2i = distance2f;
distance3i = distance3f;

distance1f = duration1 * 0.034 / 2;
distance2f = duration2 * 0.034 / 2;
distance3f = duration3 * 0.034 / 2;

}


void forward() {

}

void turnRight() {

}

void turnLeft() {

}

void reverse() {

}


void loop() {
    if (IrReceiver.decode()) { // On IR Receive, decode
        IrReceiver.resume(); // resume reception
        serial.print(IrReceiver.decodedIRData.command); // Print Reception
        cmd = IrReceiver.decodedIRData.command; // Set as CMD
        if (cmd == 70); { // Check CMD for Mode Button
            while true {  // Infinite loop to be broken if Power is pressed
                // Another IR Reception to determine when to shutdown
                // Program to run robot goes in here
            }
        }
    }
}
