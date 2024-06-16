// code for PET'S HEALTH MONITORING SYSTEM

// Declarations 
#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <OneWire.h>
#include <DallasTemperature.h>
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   

// GPIO where the DS18B20 is connected to
const int oneWireBus = 4;     
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);
// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

int ECG_pin=A0;     //Data wire is connected to analog pin 0 on the NodeMCU
const int PulseWire = 16;       // PulseSensor PURPLE WIRE connected to digital PIN 1
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.
                              //  Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                              //  Otherwise leave the default "550" value. 
                               
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"

// const int xpin = 5; //Data wire is connected to digital pin 2 on the NodeMCU

// const int ypin = 0;
// const int zpin = 1;
// float threshold = 6;
// float xval[100] = {0};
// float yval[100] = {0};
// float zval[100] = {0};
// float xavg, yavg, zavg;
// int steps, flag = 0;

void setup()
{
  // Pin declerations
  // pinMode(3, INPUT); //ECG Setup for leads off detection LO +
  // pinMode(2, INPUT); //ECG Setup for leads off detection LO -
  // calibrate();

  pulseSensor.analogInput(PulseWire);   
  pulseSensor.setThreshold(Threshold);   

  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
   if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  }
  Serial.begin(115200);
  sensors.begin();	// Start up the library

pinMode(14, INPUT); // Setup for leads off detection LO +
pinMode(12, INPUT); // Setup for leads off detection LO -

}

void loop()
{

// temparature sensor
  sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
  float temperatureF = sensors.getTempFByIndex(0);
  Serial.print("Dog temperature in Celsius is:");
  Serial.print(temperatureC);
  Serial.println("ºC");
  Serial.print("Dog temperature in Fahrenheit is:");
  Serial.print(temperatureF);
  Serial.println("ºF");
  delay(1000);

// Pulse sensor
if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened".
int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
                                               // "myBPM" hold this BPM value now. 
 Serial.println("♥  A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
 Serial.print("BPM: ");                        // Print phrase "BPM: " 
 Serial.println(myBPM);                        // Print the value inside of myBPM. 
}

  delay(200);  
   
// // ADXL 355
//   int acc = 0;
//   float totvect[100] = {0};
//   float totave[100] = {0};
//   float xaccl[100] = {0};
//   float yaccl[100] = {0};
//   float zaccl[100] = {0};

//   for (int a = 0; a < 100; a++)
//   {
//     xaccl[a] = float(analogRead(xpin) - 345);
//     delay(1);
//     yaccl[a] = float(analogRead(ypin) - 346);
//     delay(1);
//     zaccl[a] = float(analogRead(zpin) - 416);
//     delay(1);

//     totvect[a] = sqrt(((xaccl[a] - xavg) * (xaccl[a] - xavg)) + ((yaccl[a] - yavg) * (yaccl[a] - yavg)) + ((zval[a] - zavg) * (zval[a] - zavg)));
//     totave[a] = (totvect[a] + totvect[a - 1]) / 2 ;

//     Serial.println("totave[a]");
//     Serial.println(totave[a]);

//     delay(100);

//     if (totave[a] > threshold && flag == 0)
//     {
//       steps = steps + 1;
//       flag = 1;
//     }
//     else if (totave[a] > threshold && flag == 1)
//     {
//       // Don't Count
//     }
//     if (totave[a] < threshold   && flag == 1)
//    {
//       flag = 0;
//     }
//     if (steps < 0) {
//       steps = 0;
//     }

//     Serial.println('\n');
//     Serial.print("steps: ");
//     Serial.println(steps);
//     delay(1000);
//   }
//   delay(1000);
// }

// void calibrate()
// {

//   float sum = 0;
//   float sum1 = 0;
//   float sum2 = 0;
//   for (int i = 0; i < 100; i++) {
//     xval[i] = float(analogRead(xpin) - 345);
//     sum = xval[i] + sum;
//   }

//   delay(100);

//   xavg = sum / 100.0;
//   Serial.println(xavg);
//   for (int j = 0; j < 100; j++)
//   {
//     yval[j] = float(analogRead(ypin) - 346);
//     sum1 = yval[j] + sum1;
//   }

//   yavg = sum1 / 100.0;
//   Serial.println(yavg);
//   delay(100);
//   for (int q = 0; q < 100; q++)
//   {
//     zval[q] = float(analogRead(zpin) - 416);
//     sum2 = zval[q] + sum2;

//   }

//   zavg = sum2 / 100.0;
//   delay(100);
//   Serial.println(zavg);

// ECG sensor

  if((digitalRead(10) == 1)||(digitalRead(11) == 1)){
    Serial.println('!');
  }
  else{
    // send the value of analog input 0:
    Serial.print("ECG Reading:");
      Serial.println(analogRead(ECG_pin));
  }
  //Wait for a bit to keep serial data from saturating
  delay(1);
}

