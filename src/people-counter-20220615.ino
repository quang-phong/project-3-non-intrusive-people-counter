#define BLYNK_TEMPLATE_ID "TMPLHIFj60vI"
#define BLYNK_DEVICE_NAME "People Counter"
#define BLYNK_AUTH_TOKEN "QuMhaEo1YdzifyjJReOhpjx2Nk5JRdRi"

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "TP-Link_0D10"; //Aubeldomein12C, TP-Link_B002, TP-Link_E381; TP-Link_0D10
char pass[] = "38838599"; //GHMaastricht2015, 38874354, 39101245; 38838599


#include <RunningMedian.h>
//#include <WiFi.h>
//#include <WiFiClient.h>
//
//#include <Blynk.h>
#include <BlynkSimpleEsp32.h>


RunningMedian samples1 = RunningMedian(50);
RunningMedian samples2 = RunningMedian(50);


// changeable parameters
int reset = 0; // reset or not
int manualCount = 0; // handtyped people number (based on observation)
int allowedTime = 300; // the transition will be 0 again after this amount of milliseconds
int threshold = 70; // "unusual" gap between 2 sensors, which may indicate somebody is passing them
int position = 0; // position = 0 when the sensor is mounted on the right of the hallway when you enter the room

// most important output
int people = 0; // number of people

// constant parameters
int count = 0; // for getting median values
int sensorPin1 = 34;
int sensorPin2 = 35;
long sensorValue1;  // variable to store the value coming from the sensor
long sensorValue2; // variable to store the value coming from the sensor
long differential; // differential between 2 sensors at a time t
unsigned long start; // get the beginning time of the transition
int directionn; // to know the direction of the movement (entrance or exit)
int transition = 0; // to denote transition (yes or no)
int lastPeople = 0; // number of people last time uploaded to Blynk
int x;
int y;


BLYNK_WRITE(V1) {
  reset = param.asInt();
}
BLYNK_WRITE(V2) {
  manualCount = param.asInt();
}
BLYNK_WRITE(V3) {
  allowedTime = param.asInt();
}
BLYNK_WRITE(V4) {
  threshold = param.asInt();
}
BLYNK_WRITE(V5) {
  position = param.asInt();
}

void read2Analog() {
  x = analogRead(sensorPin1);
  samples1.add(x);
  y = analogRead(sensorPin2);
  samples2.add(y);
  count++;
  if (count = 50)
  {
    sensorValue1 = samples1.getMedian();
    sensorValue2 = samples2.getMedian();
    differential = sensorValue1 - sensorValue2;
    // Serial.print(m);
    // Serial.print(",");
    // Serial.print(n);
    // Serial.print(",");
    //Serial.println(differential);
    count = 0;
  }
  else {
  }
}

void detectOccupancy() {
  if (reset == 1) {
    if (position == 0) {
      people = manualCount;
    }
    else {
      people = (-1) * manualCount;
    }
  }


  if ((transition == 0) && (abs(differential) >= threshold)) {
    start = millis();
    directionn = differential / abs(differential);
    transition = 1;
  }
  if ((transition == 1) && (differential * directionn <= ((-1)*threshold))) {
    transition = 0;
    people += directionn;
    //delay(allowedTime/2);
  }
  if ((millis() - start) >= allowedTime) {
    transition = 0;
  }

}

void updatePeople() {
  // Upload to Blynk only when there is a change
  if (people != lastPeople) {
    if (position == 0) {
      //Serial.println(people);
      Blynk.virtualWrite(V0, people);
      lastPeople = people;
    }
    else {
      //Serial.println((-1)*people);
      Blynk.virtualWrite(V0, (-1)*people);
      lastPeople = people;
    }
  }
}

// Define NTP Client to get time
// WiFiUDP ntpUDP;
// NTPClient timeClient(ntpUDP);

//String formattedDate;
//String dayStamp;
//String timeStamp;
//
//// https://espitek.com/arduino/lay-thoi-gian-tu-internet-voi-esp32-ntp-client/
//void resetByTime() {
//
//  while (!timeClient.update()) {
//    timeClient.forceUpdate();
//  }
//
//  formattedDate = timeClient.getFormattedDate(); // 2018-04-30T16:00:13Z
//
//  int splitT = formattedDate.indexOf("T");
//  dayStamp = formattedDate.substring(0, splitT); //DATE: 2018-06-20
//  timeStamp = formattedDate.substring(splitT + 1, formattedDate.length() - 1); //HOUR: 14:37:40
//
//  if (timeStamp == "HOUR: 22:00:00") {
//    people = 0;
//  }
//}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //WiFi.begin(ssid, pass);
  Blynk.begin(auth, ssid, pass, "fra1.blynk.cloud", 8080);

  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Initialize a NTPClient to get time
//  timeClient.begin();
//  timeClient.setTimeOffset(+1 * 60 * 60); // 1 because Netherlands UTC +1
}


void loop() {
  // put your main code here, to run repeatedly:
  //digitalWrite(energypin, HIGH);
  Blynk.run();
  read2Analog();
  detectOccupancy();
  updatePeople();
//  resetByTime();
}
