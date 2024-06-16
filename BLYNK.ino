//Include the library files

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <OneWire.h>
#include <DallasTemperature.h>  
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   
#define BLYNK_TEMPLATE_ID "TMPL3j7QKmnoN"
#define BLYNK_TEMPLATE_NAME "INDUCTION 23"
#define BLYNK_AUTH_TOKEN "OhAsKM4vjrgdBJab0YWf8_11_TInPQlZ"

char ssid[] = "The Robotics Club";//Enter your WIFI name
char pass[] = "trcsnist@2022";//Enter your WIFI password

BlynkTimer timer;

// Define component pins
const int oneWireBus = 4;     
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);
const int PulseWire = 16;       
int Threshold = 550;           
                               
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"

void setup() {
  Blynk.begin( BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  Serial.begin(115200);
//Call the functions
  timer.setInterval(100L, tempsensor);
  timer.setInterval(100L, pulsesensor);
}

//Get the Temparature sensor values
void tempsensor() {
sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
  float temperatureF = sensors.getTempFByIndex(0);
  Blynk.virtualWrite(V0,temperatureC);
}


void pulsesensor() {
   if (pulseSensor.sawStartOfBeat()) {          
int myBPM = pulseSensor.getBeatsPerMinute();  
 Serial.println(myBPM);   
 Blynk.virtualWrite(V1, myBPM);                     
 }
}

// //Get the PIR sensor values
// void pirsensor() {
//   bool value = digitalRead(PIR);
//   if (pirbutton == 1) {
//     if (value == 0) {
//       digitalWrite(Buzzer, LOW);
//     } else if (value == 1) {
//       Blynk.notify("Warning! Please check your security system");
//       digitalWrite(Buzzer, HIGH);
//     }
//   }
// }

// //Get the ultrasonic sensor values
// void ultrasonic() {
//   digitalWrite(trig, LOW);
//   delayMicroseconds(4);
//   digitalWrite(trig, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(trig, LOW);
//   long t = pulseIn(echo, HIGH);
//   long cm = t / 29 / 2;
//   Blynk.virtualWrite(V4, cm);


// }

// // //Get buttons values
// // BLYNK_WRITE(V5) {
// //  bool RelayOne = param.asInt();
// //   if (RelayOne == 1) {
// //     digitalWrite(relay1, LOW);
// //   } else {
// //     digitalWrite(relay1, HIGH);
// //   }
// // }

// // //Get buttons values
// // BLYNK_WRITE(V6) {
// //  bool RelayTwo = param.asInt();
// //   if (RelayTwo == 1) {
// //     digitalWrite(relay2, LOW);
// //   } else {
// //     digitalWrite(relay2, HIGH);
// //   }
// // }

void loop() {
  Blynk.run();//Run the Blynk library
  timer.run();//Run the Blynk timer
}
