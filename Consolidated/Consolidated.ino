#include <DallasTemperature.h> //For Liquid Temperature Sensor

#include <OneWire.h> // For Liquid Temperature Sensor

#include <dht.h> // For DHT11 Temperature Sensor 

#define LIQUIDTEMP_ONE_WIRE_BUS 2 // Digital Pin 2 for Liquid Temperature Sensor 

#define DHT11Temp_PIN 7 // Digital Pin 7 for DHT11 Temperature Sensor

#define pHSensor_Pin A2 //pH meter Analog output to Arduino Analog Input Pin 2 for pH Sensor

#define pHSensor_Offset 0.00 //Deviation compensate for pH Sensor

#define pHSensor_LED 13 // For pH sensor 

#define pHSensor_samplingInterval 20 // For pH Sensor

#define pHSensor_printInterval 800 //For pH Sensor

#define pHSensor_ArrayLenth  40 //Times of collection for pH Sensor

OneWire LiquidTemp_oneWire(LIQUIDTEMP_ONE_WIRE_BUS); //For Liquid Temperature Sensor

DallasTemperature LiquidTemp_sensors(&LiquidTemp_oneWire); //For Liquid Temperature Sensor

dht DHT11Temp_DHT; //For DHT11 Temperature Sensor

int soil_moisture_sensor_pin = A0; // Analog Pin 0 for Soil Moisture Sensor

int ThermistorTemp_ThermistorPin = A1; //Thermistor Temperature Analog Pin 1

int pHSensor_pHArray[pHSensor_ArrayLenth]; //Store the average value of the sensor feedback for pH Sensor

int pHSensor_pHArrayIndex=0; // For pH Sensor 

const int BackupWatering_MOISTURE_LEVEL = 250; // The Value After The LED Goes On for Backup Watering System


void setup() {

  Serial.begin(9600); 
  LiquidTemp_Setup(); //For Liquid Temperature Sensor
  SoilMoistureSetup(); // For Soil Moisture Sensor
  ThermistorTemp_Setup(); // For Thermistor Temperature Sensor
  DHT11Temp_Setup(); // For DHT11 Temperature Sensor
  phSensor_Setup(); // For pH Sensor  
  BackupWatering_Setup(); // For BAckup Watering System

   }

void LedState(int state)
{
  digitalWrite(13,state);  // Function for Backup Watering System 
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
   
  float pHSensor_Output = pHSensor_Loop();
  
  Serial.print("pH value: ");
  
  Serial.print(pHSensor_Output);

  BackupWatering_Loop();

  
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

void phSensor_Setup()
{
  pinMode(pHSensor_LED,OUTPUT);  
  Serial.println("pH meter experiment!");    //Test the serial monitor
}

float pHSensor_Loop()
{
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float pHValue,voltage;
  if(millis()-samplingTime > pHSensor_samplingInterval)
  {
      pHSensor_pHArray[pHSensor_pHArrayIndex++]=analogRead(pHSensor_Pin);
      if(pHSensor_pHArrayIndex==pHSensor_ArrayLenth)pHSensor_pHArrayIndex=0;
      voltage = avergearray(pHSensor_pHArray, pHSensor_ArrayLenth)*5.0/1024;
      pHValue = 3.5*voltage+pHSensor_Offset;
      samplingTime=millis();
  }
  if(millis() - printTime > pHSensor_printInterval)   //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
  {
        digitalWrite(pHSensor_LED,digitalRead(pHSensor_LED)^1);
        printTime=millis();
        return pHValue;
  }   
}  

double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i];
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;
}

void BackupWatering_Setup()
{
  pinMode(13, OUTPUT);
  pinMode(4, OUTPUT);
  
}

void BackupWatering_Loop()
{
  int moisture = analogRead(soil_moisture_sensor_pin);  
  if(moisture > BackupWatering_MOISTURE_LEVEL)
  {
    LedState(HIGH);
    digitalWrite(4,HIGH);
  }
  else 
  {
    LedState(LOW);
    digitalWrite(4,LOW);
  }
  
  delay(500);
}


