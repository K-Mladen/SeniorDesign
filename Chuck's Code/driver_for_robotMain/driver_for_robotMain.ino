/*

  This is a driver program for robotMain.py

*/

int pin4 = 4;    // take a picture? (T/F)
int pin7 = 7;    // maze finished?  (T/F)
int pin8 = 8;    // indicate maze finished
const int dataRate = 9600;
bool done = false;
int driveTime = 5000;
int pulseWidth = 250;

void setup()
{
  pinMode(pin4, OUTPUT);
  pinMode(pin7, OUTPUT);
  pinMode(pin8, OUTPUT);   // LED goes off when maze is done
  Serial.begin(dataRate);
}

void loop()
{
  delay(5000);              // wait 5 sec to run robotMain.py
  
  digitalWrite(pin4, LOW);  // initialize, picture control
  digitalWrite(pin7, LOW);  // tell Rpi that we NOT finished with the maze
  digitalWrite(pin8, LOW);  // tell user with LED that we ARE finished
  
  digitalWrite(pin4, HIGH);  // Take a picture 1
  delay(pulseWidth);
  digitalWrite(pin4, LOW);   // creates a pulse
  Serial.print(1);
  Serial.println(); 
  delay(driveTime);           
  
  digitalWrite(pin4, HIGH);  // Take a picture 2
  delay(pulseWidth);
  digitalWrite(pin4, LOW);   // creates a pulse
  Serial.print(4);
  Serial.println(); 
  delay(driveTime);
  
  digitalWrite(pin4, HIGH);  // Take a picture 3
  delay(pulseWidth);
  digitalWrite(pin4, LOW);   // creates a pulse
  Serial.print(12);
  Serial.println(); 
  delay(driveTime);
  
  digitalWrite(pin4, HIGH);  // Take a picture 4
  delay(pulseWidth);
  digitalWrite(pin4, LOW);   // creates a pulse
  Serial.print(8);
  Serial.println(); 
  delay(driveTime);
  
  digitalWrite(pin4, HIGH);  // Take a picture 5
  delay(pulseWidth);
  digitalWrite(pin4, LOW);   // creates a pulse
  Serial.print(42);
  Serial.println(); 
  delay(driveTime);
  
  digitalWrite(pin7, HIGH);  // tell the Rpi that we are done
  
  do
  {
    done = true;
    digitalWrite(pin8, HIGH); // LED lights up to signal maze is finished
    // stay here to see what happens
    delay(1000);
  }while(done == true);

}

