/*********
  
*********/
#include <WiFi.h>
#include "time.h"
#include "AsyncUDP.h"                         // UDP
#include <Arduino_JSON.h>
#include <Arduino.h>

const char* ssid = "HL0C";
const char* password = "22042206";
//const char* ssid = "ecover-2.4";
//const char* password = "easy@1234";

long int wait_time;

// for ntp
struct tm   timeinfo;
char        strftime_buf[64];
const char* ntpServer = "pool.ntp.org";       // ntp server
const int   timezone = 9;                     // seoul
const int   tz_offset_sec = 3600;             // for seoul offset is 3600 * 9
const int   daylightOffset_sec = 0;
long  int   currtime;

// for UDP
AsyncUDP udp;

// for wifi and mqtt
#define COM_PIN 23                             // LED

// for interrupt
#define interIn  5
#define interOut  19

/*
 for car
 */
int onestep = 5000;                           // 한번 forward 거리

// setting PWM properties
const int freq = 1000;
const int fl1 = 0;          // PWM channel
const int fl2 = 1;
const int fr1 = 2;
const int fr2 = 3;
const int br1 = 4;
const int br2 = 5;
const int bl1 = 6;
const int bl2 = 7;

const int resolution = 8;

// for motor esp pin
#define FR1     26          // Front Right motor 1
#define FR2     25          // Front Right motor 2
#define FL1     32          // Front Left motor 1
#define FL2     33          // Front Left motor 2
#define BR1     13
#define BR2     12
#define BL1     27
#define BL2     4

#define MHIGH       200     // analogwrite duty 0~255    바꿀 수 있는 값
#define MLOW        0       // analogwrite duty 0%

// servo
const int servo = 15;       // servo PWM channel
#define servoPin   18       // servo output Pin

// obstacle detector
#define OD0 36
#define OD1 39

// for multi-processing
TaskHandle_t Task1;
TaskHandle_t Task2;

//Task1code: read sensors and write to display, play melody
void Task1code( void * pvParameters ){
  while(1){
   //delay(1000);
   runServo();

    /*forward(onestep);
    stopM();
    delay(1000);
    leftSlide(onestep);
    stopM();
    delay(1000);
    rightSlide(onestep);
    stopM();
    delay(1000);
    uTurn(onestep);
    stopM();
    delay(10000);*/
  }
}

//Task2code: send sensors data to network or serial
void Task2code( void * pvParameters ){
  while(1){
    delay(1000);
    // 시간 유지
    if((millis() - currtime) > (1000 * 3600)){    // update exact time every 1 hour
      configTime((long)timezone*tz_offset_sec, daylightOffset_sec, ntpServer);
      currtime = millis();
    }
    //
  } // end while
}

void setup(){

 //
  Serial.begin(115200);
  pinMode(COM_PIN, OUTPUT);
  setup_wifi();

  // interrupt
  pinMode(interIn, INPUT_PULLDOWN);
  pinMode(interOut, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(interIn), stopS, HIGH);
  
  // Init and get the time
  configTime((long)timezone*tz_offset_sec, daylightOffset_sec, ntpServer);
  delay(1000);
  getLocalTime(&timeinfo);
  Serial.println(&timeinfo, "timeinfo %A, %B %d %Y %H:%M:%S");

  // servo
  ledcSetup(servo, freq, resolution);     // configure Servo PWM fn
  ledcAttachPin(servoPin, servo);          // attach pin to channel

  // configure LED PWM functionalitites
  ledcSetup(fl1, freq, resolution); ledcSetup(fl2, freq, resolution);
  ledcSetup(fr1, freq, resolution); ledcSetup(fr2, freq, resolution);
  ledcSetup(bl1, freq, resolution); ledcSetup(bl2, freq, resolution);
  ledcSetup(br1, freq, resolution); ledcSetup(br2, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(FR1, fr1); ledcAttachPin(FR2, fr2);
  ledcAttachPin(FL1, fl1); ledcAttachPin(FL2, fl2);
  ledcAttachPin(BR1, br1); ledcAttachPin(BR2, br2);
  ledcAttachPin(BL1, bl1); ledcAttachPin(BL2, bl2);

  // UDP
  if(udp.listen(1234)){
    Serial.print("UDP Listening on IP: ");  Serial.println(WiFi.localIP());
    digitalWrite(COM_PIN, HIGH);
    udp.onPacket([](AsyncUDPPacket packet){
      uint8_t *key;
      Serial.print("UDP Packet Type: ");
      Serial.print(packet.isBroadcast() ? "Broadcast" : packet.isMulticast() ? "Multicast" : "Unicast");
      Serial.print(", From: ");
      Serial.print(packet.remoteIP());
      Serial.print(":");
      Serial.print(packet.remotePort());
      Serial.print(", To: ");
      Serial.print(packet.localIP());
      Serial.print(":");
      Serial.print(packet.localPort());
      Serial.print(", Length: ");
      Serial.print(packet.length()); //
      Serial.print(", Data: ");
      key = packet.data();
      Serial.write(packet.data(), packet.length());
      
      Serial.println();
      moveCar(key[0]);
      packet.printf("Got %u bytes of data", packet.length());
    });
  }
  
  //create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(
                    Task1code,   /* Task function. */
                    "Task1",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task1,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */                  
  delay(500); 

  //create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
  xTaskCreatePinnedToCore(
                    Task2code,   /* Task function. */
                    "Task2",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task2,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 1 */
    delay(500); 
}

void loop(){
}
