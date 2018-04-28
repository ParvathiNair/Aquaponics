#include <DallasTemperature.h> //For Liquid Temperature Sensor
#include <OneWire.h> //For Liquid Temperature Sensor
#define LIQUIDTEMP_ONE_WIRE_BUS 2 // Digital Pin 2 
OneWire LiquidTemp_oneWire(LIQUIDTEMP_ONE_WIRE_BUS); //For Liquid Temperature Sensor
DallasTemperature LiquidTemp_sensors(&LiquidTemp_oneWire); //For Liquid Temperature Sensor
int soil_moisture_sensor_pin = A0; // For Soil Moisture Sensor

void setup() {

  LiquidTemp_Setup(); //For Liquid Temperature Sensor
  SoilMoistureSetup(); // For Soil Moisture Sensor


   }

void loop() {

  int Liquid_Temp = LiquidTemp_Loop(); //For Liquid Temperature Sensor

  Serial.print("Temperature is: "); //For Liquid Temperature Sensor
                                
  Serial.print(Liquid_Temp); //For Liquid Temperature Sensor

  int Soil_Moisture = SoilMoistureLoop();

   Serial.print("Moisture : "); // For Soil Moisture Sensor

   Serial.print(Soil_Moisture); // For Soil Moisture Sensor

   Serial.println("%"); // For Soil Moisture Sensor
   

delay(1000);
   
   }


void LiquidTemp_Setup() // Liquid Temperature Setup

{
  // start serial port 
 
 Serial.begin(9600); 
 
 Serial.println("Dallas Temperature IC Control Library Demo"); 
 
 // Start up the library 
 
 LiquidTemp_sensors.begin();        
  
}

int LiquidTemp_Loop() //Liquid Temperature Loop
{
  int Temp_Output;

 Serial.print(" Requesting temperatures..."); 
 
 LiquidTemp_sensors.requestTemperatures(); // Send the command to get temperature readings 

 Temp_Output = LiquidTemp_sensors.getTempCByIndex(0);

 return Temp_Output;

}



void SoilMoistureSetup() // Soil Moisture Setup
{

 Serial.begin(9600);

   Serial.println("Reading From the Sensor ...");

   delay(2000);

}


int SoilMoistureLoop() //Soil Moisture Loop
{
  int output_value ;

   output_value= analogRead(soil_moisture_sensor_pin);

   output_value = map(output_value,550,0,0,100);
   
   return output_value;
}

