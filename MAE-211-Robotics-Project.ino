#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C Address is 0x27, 16 columns and 2 rows
#include <IRremote.h>

const int RECV_PIN = 12;

const int trigPin = 4;
const int echoPin = 3;

// defines variables
long duration;
int distance;
void setup()
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
  Serial.begin(9600);       // Starts the serial communication
  lcd.init();               // Initializing LCD Display
  lcd.backlight();          // Turning Backlight on

  IrReceiver.begin(RECV_PIN);
  lcd.print("Ready!");
}

void loop()
{
  if (IrReceiver.decode())
  {
    IrReceiver.resume();
    Serial.println(IrReceiver.decodedIRData.command);
    int cmd = IrReceiver.decodedIRData.command;
    if (cmd == 70)
    {
      Serial.print("Received");
      while (true)
      {
        if (IrReceiver.decode())
        {
          IrReceiver.resume();
          Serial.println(IrReceiver.decodedIRData.command);
          int cmd = IrReceiver.decodedIRData.command;
          if (cmd == 69)
          {
            lcd.clear();
            lcd.print("Completed");
            break;
          }
        }
        lcd.clear();
        lcd.setCursor(0, 0);
        // Clears the trigPin
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        // Sets the trigPin on HIGH state for 10 micro seconds
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        // Reads the echoPin, returns the sound wave travel time in microseconds
        duration = pulseIn(echoPin, HIGH);
        // Calculating the distance
        distance = duration * 0.034 / 2;
        // Prints the distance on the Serial Monitor
        lcd.print("Distance: ");
        lcd.print(distance);
        delay(500);
      }
    }
  }
  delay(1000);
}
