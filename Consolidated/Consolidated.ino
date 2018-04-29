#include <DallasTemperature.h> //For Liquid Temperature Sensor
#include <OneWire.h> // For Liquid Temperature Sensor
#include <dht.h> // For DHT11 Temperature Sensor 
#define LIQUIDTEMP_ONE_WIRE_BUS 2 // Digital Pin 2 for Liquid Temperature Sensor 
#define DHT11Temp_PIN 7 // Digital Pin 7 for DHT11 Temperature Sensor
OneWire LiquidTemp_oneWire(LIQUIDTEMP_ONE_WIRE_BUS); //For Liquid Temperature Sensor
DallasTemperature LiquidTemp_sensors(&LiquidTemp_oneWire); //For Liquid Temperature Sensor
dht DHT11Temp_DHT; //For DHT11 Temperature Sensor
int soil_moisture_sensor_pin = A0; // For Soil Moisture Sensor
int ThermistorTemp_ThermistorPin = A1; //Thermistor Temperature Analog Pin


void setup() {

  Serial.begin(9600); 
  LiquidTemp_Setup(); //For Liquid Temperature Sensor
  SoilMoistureSetup(); // For Soil Moisture Sensor
  ThermistorTemp_Setup(); // For Thermistor Temperature Sensor
  DHT11Temp_Setup(); // For DHT11 Temperature Sensor

   }

void loop() {

  int Liquid_Temp = LiquidTemp_Loop(); //For Liquid Temperature Sensor

  Serial.print("Temperature is: "); //For Liquid Temperature Sensor
                                
  Serial.print(Liquid_Temp); //For Liquid Temperature Sensor

  int Soil_Moisture = SoilMoistureLoop(); // For Soil Moisture Sensor

  Serial.print("Moisture : "); // For Soil Moisture Sensor

  Serial.print(Soil_Moisture); // For Soil Moisture Sensor

  Serial.println("%"); // For Soil Moisture Sensor

  int Temperature_Thermistor_Output = ThermistorTemp_Loop(); // For Thermistor Temperature Sensor
  
  Serial.print("Temperature in Celcius: "); // For Thermistor Temperature Sensor
  
  Serial.print(Temperature_Thermistor_Output); // For Thermistor Temperature Sensor
  
  Serial.println(" C"); // For Thermistor Temperature Sensor

  int DHT11_Output = DHT11Temp_Loop(); // For DHT11 Temperature Sensor
  
  Serial.print("Temperature = "); // For DHT11 Temperature Sensor
  
  Serial.println(DHT11_Output); // For DHT11 Temperature Sensor 
   
  delay(1000);
   
   }


void LiquidTemp_Setup() // Liquid Temperature Setup

{
  // start serial port 
 
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

   Serial.println("Reading From the Sensor ...");

}


int SoilMoistureLoop() //Soil Moisture Loop
{
  int output_value ;

   output_value= analogRead(soil_moisture_sensor_pin);

   output_value = map(output_value,550,0,0,100);
   
   return output_value;
}

void ThermistorTemp_Setup()
{

}

int ThermistorTemp_Loop()
{
  int ThermistorTemp_Vo;
  
  float ThermistorTemp_R1 = 10000;
  
  float ThermistorTemp_logR2, ThermistorTemp_R2, ThermistorTemp_T, ThermistorTemp_Tc;
  
  float ThermistorTemp_c1 = 1.009249522e-03, ThermistorTemp_c2 = 2.378405444e-04, ThermistorTemp_c3 = 2.019202697e-07;

  ThermistorTemp_Vo = analogRead(ThermistorTemp_ThermistorPin);
  
  ThermistorTemp_R2 = ThermistorTemp_R1 * (1023.0 / (float)ThermistorTemp_Vo - 1.0);
  
  ThermistorTemp_logR2 = log(ThermistorTemp_R2);
  
  ThermistorTemp_T = (1.0 / (ThermistorTemp_c1 + ThermistorTemp_c2*ThermistorTemp_logR2 + ThermistorTemp_c3*ThermistorTemp_logR2*ThermistorTemp_logR2*ThermistorTemp_logR2));
  
  ThermistorTemp_Tc = ThermistorTemp_T - 273.15;
  
  return ThermistorTemp_Tc;
  
}

void DHT11Temp_Setup()
{
  
}

int DHT11Temp_Loop()
{
  
  int chk = DHT11Temp_DHT.read11(DHT11Temp_PIN);
  int DHT11Temp_Output = DHT11Temp_DHT.temperature;
  return DHT11Temp_Output;
}

