// Basic demo for configuring the MCP4728 4-Channel 12-bit I2C DAC
#include <Adafruit_MCP4728.h>
#include <Wire.h>

const int numReadings = 64 ;      //number of readings for the calibration phase
int SensorValue[numReadings];     // array of calibration values 
char j, k;
long result;
long average;                     // average value for the given number of readings
long average_pressure;


int SensorPin = A2;               // pressure sensor pin
int connectionLed = 2;            // LED 2 (rechts vom Power)
int errorLed = 3;                 // LED 3 (ganz rechts)



long read_input_pressure = 1;
long calibration_pressure; 
String set_pressure;
long pressure_read; 
int set_pressure_value;
String set_pressure_string;
int set_pressure_value_mapped;

Adafruit_MCP4728 mcp;


int calibration(){
    mcp.setChannelValue(MCP4728_CHANNEL_A, 0, MCP4728_VREF_INTERNAL,
                      MCP4728_GAIN_2X);
   for (j = 0; j < numReadings; j++) {
    SensorValue[j] = analogRead(SensorPin); //read the value of the pressure sensor from PIN A2
    
    delay(10);                               //delay for reading stability
  }

  // we now have 64 readings, so we average them
  result = 0;
  for (j = 0; j < numReadings; j++) {
    result = result + SensorValue[j];
  }
  average = result / numReadings;               
  return average;                          // our calibration value 
}


void setup(void) {
  pinMode(errorLed, OUTPUT);        
  pinMode(connectionLed, OUTPUT); 
  Serial.begin(9600);                   // initiliaze serial communication
  mcp.begin();                          // initiliaze the ADC
  if (!mcp.begin()) {
    digitalWrite(errorLed, HIGH);
  }
  calibration_pressure = calibration(); // get the calibration value
  mcp.setChannelValue(MCP4728_CHANNEL_A, 0, MCP4728_VREF_INTERNAL,
                      MCP4728_GAIN_2X);

}



void loop() {
    // check serial 
  if ( Serial.available()){
    // cast the string read in an integer 
    digitalWrite(connectionLed, HIGH);   //
    read_input_pressure = Serial.parseInt(); 
  }
  if (read_input_pressure >= 0 && read_input_pressure <= 1000) {
          pressure_read = map(analogRead(SensorPin), calibration_pressure, 1023, 0, 1010); //convert readings to mbar. TODO. 
          set_pressure_value_mapped = map(read_input_pressure, 0, 1000, 784, 3995);
          mcp.setChannelValue(MCP4728_CHANNEL_A, set_pressure_value_mapped, MCP4728_VREF_INTERNAL,
                      MCP4728_GAIN_2X);
      Serial.println(pressure_read);
      digitalWrite(errorLed, LOW);
      digitalWrite(connectionLed, LOW);
  }
      else {
  Serial.println("Set Pressure Value is outside range. Please give a value between 0 and 1000 [mbar]");
  digitalWrite(errorLed, HIGH);
  }
delay(100);
}  




 
