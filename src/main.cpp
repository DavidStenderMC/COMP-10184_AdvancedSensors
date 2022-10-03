// library for Arduino framework  
#include <Arduino.h> 
// 1-Wire sensor communication libary 
#include <OneWire.h> 
// DS18B20 sensor library 
#include <DallasTemperature.h>

/*
  I, David Stender, 000828140 certify that this material is my original work.
  No other person's work has been used without due acknowledgement.
*/
 
// Pin that the  DS18B20 is connected to 
const int oneWireBus = D3;      
 
// Setup a oneWire instance to communicate with any OneWire devices 
OneWire oneWire(oneWireBus); 
 
// Pass our oneWire reference to Dallas Temperature sensor  
DallasTemperature DS18B20(&oneWire);

// The address of the DS18B20 as a string
String DS18B20DeviceAddressString;

// Holds the temperature from the DS18B20 sensor 
float tempurature = 0;

// A function that takes in a variable of type DeviceAddress
// and returns a string interpretation
String printAddress(DeviceAddress deviceAddress){ 
  String deviceAddressString = "";

  for (uint8_t i = 0; i < 8; i++){
    
    if (deviceAddress[i] < 0x10){
      deviceAddressString += "0";
    }
    deviceAddressString += String(deviceAddress[i], HEX);
  }
  return deviceAddressString;
}
 
void setup() { 
  // configure the USB serial monitor 
  Serial.begin(115200);
  // Start the DS18B20 sensor 
  DS18B20.begin();
  
  Serial.println("Temperature Application");

  // ask DS18B20 for the current temperature 
  DS18B20.requestTemperatures(); 
  // fetch the temperature.  We only have 1 sensor, so the index is 0. 
  tempurature = DS18B20.getTempCByIndex(0);

  // If the senosr is reading -127.00 that means it is not connected
  if(tempurature != -127.00){
    DeviceAddress DS18B20Sensor;
    DS18B20.getAddress(DS18B20Sensor, 0);
    DS18B20DeviceAddressString = printAddress(DS18B20Sensor);
    Serial.println("Found DS18B20 sensor with address: " + DS18B20DeviceAddressString);
  } else{
    Serial.println("No DS18B20 sensor are installed");
  }
} 
 
void loop() {
  // Gets the Temperature
  DS18B20.requestTemperatures(); 
  tempurature = DS18B20.getTempCByIndex(0);

  // If the senosr is reading -127.00 that means it is not connected
  if(tempurature > -127.00){
    // Holds the judgement based on the temperature output from the DS18B20 sensor 
    String judgement = "";

    // print the temp to the USB serial monitor
    if(tempurature > 35) {
      judgement = "Too Hot!";
    } else if(tempurature >= 30) {
      judgement = "Hot";
    } else if(tempurature >= 25) {
      judgement = "Warm";
    } else if(tempurature >= 15) {
      judgement = "Perfect";
    } else if(tempurature >= 10) {
      judgement = "Cool";
    } else {
      judgement = "Cold!";
    }
    Serial.println("Current temperature is: " + String(tempurature) + " or "+judgement); 
  
    delay(5000);
  }
}


