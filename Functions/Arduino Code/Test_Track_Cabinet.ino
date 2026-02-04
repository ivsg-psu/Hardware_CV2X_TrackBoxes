//Libraries
#include <dht.h>;
dht DHT;
//Constants
#define DHT22_PIN 2 


//Variables
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value
float light;
int waterSensorPin = A0;  // Water level sensor connected to analog pin A0
int ledPin = 13;          // LED connected to digital pin 13

void setup() {
  pinMode(8,INPUT);
  pinMode(9,OUTPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);  //initialise serial monitor
}

void loop() {
  light=digitalRead(8);      //assign value of LDR sensor to a temporary variable
  Serial.print("Intensity=");  //print on serial monitor using ""
  Serial.println(light);         //display  output on serial monitor
  if(light==HIGH) {
  digitalWrite(9,HIGH);        //if light is not present,LED  on
  Serial.println("Cabinet's Lights On");
  }              //HIGH  means,light got blocked
  else {
  digitalWrite(9,LOW);         //if light is present,LED off
  Serial.println("Cabinet's Lights Off");
  }

  int chk = DHT.read22(DHT22_PIN);
  //Read data and store it to variables hum and temp
  hum = DHT.humidity;
  temp= DHT.temperature;
  //Print temp and humidity values to serial monitor
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.print(" %, Temp: ");
  Serial.print(temp);
  Serial.println(" Celsius");

  // Read the input on analog pin 0
  int sensorValue = analogRead(waterSensorPin);

  // Print out the value you read
  Serial.print("Water Level: ");
  Serial.println(sensorValue);

  // Check if the water level is above a threshold
  if (sensorValue > 50) {  // Adjust the threshold as necessary
    digitalWrite(ledPin, HIGH);  // Turn the LED on
  } else {
    digitalWrite(ledPin, LOW);   // Turn the LED off
  }
  delay(1000); //Delay 1 sec.
}