//#include <Wire.h>
//#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
Adafruit_BME280 bme; // I2C


const int potiPin = A0;         //Poti?
int potiSet = 0;                //Poti?

int relaisPin = 13;             //set pin 13 to be the Relais switch
int relaisVCC = 12;             //set pin 12 to be VCC for Relais
        
float tempT = 0.0;         //target temp set by poti, compared with bme280
float tempM = 0.00;



void setup() {
  Serial.begin(9600);           //start serial output
 
  ////START-BME280////
  // default address from library is 0x77
  // bool communication = bme.begin();
  bool communication = bme.begin(0x76);
  if (!communication) {
  Serial.println("Could not find a valid BME280 sensor");
  Serial.println("check wiring, address, sensor ID!");
  Serial.print("SensorID was: 0x");
  Serial.println(bme.sensorID(), 16);
  Serial.println("ID of 0xFF probably means a bad address\n");
  while (true) { };
  delay(10);
  }
  else {
  Serial.println("Communication established!\n");
  }
  ////END-BME280////


  ////Relais Setup////
  digitalWrite(relaisPin, LOW);     //relais control pin set to low to avoid jumps and 
  pinMode(13, OUTPUT);   
  pinMode(8, OUTPUT); 
  pinMode(12, OUTPUT);               //5V DC VCC for relais
  pinMode(A1, OUTPUT);               //5V DC VCC for poti
  digitalWrite(12, LOW);            //set the relais VCC to ON
  digitalWrite(7, HIGH);            //set the relais VCC to ON
  digitalWrite(A1, HIGH);            //set the poti VCC to ON

}

void loop() {
  ////BME280 Reading ////
  float tempM = bme.readTemperature();
  Serial.print("Temperature = ");
  Serial.print(tempM);
  Serial.println(" *C");
  delay(100);

  if(tempM < tempT){
    digitalWrite(8,HIGH);
    delay(5000);
    }
    else{
    digitalWrite(8,LOW);
      };
    
  //potentiometer and mapping
  potiSet = analogRead(potiPin);   //sets the varialbe "potiSet" to be driven with the analog read from "potiPin"
  tempT = (potiSet / 25.575)+10;    //tempT as variable is driven by potiSet/X+minTemperature so that it will be a range from 10-50°C

//  analogWrite(analogOutPin, potiSet);

  Serial.print("potiSet = ");
  Serial.print(potiSet);
  Serial.print("\t tempTarget = ");
  Serial.print(tempT);
  Serial.println(" ");

/*
  //relais
  if (potiSet <= 25) {
    digitalWrite(relaisPin, LOW);
    Serial.println("relais ON");
  }
  else {
    digitalWrite(relaisPin, LOW);
    Serial.println("relais Off");
  }
  */

  delay(20);
}
