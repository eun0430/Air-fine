/*********
  
*********/
#include <WiFi.h>
#include "time.h"
#include <PubSubClient.h>
#include <Arduino_JSON.h>
#include "Arduino.h"
#include "ESP32Servo.h"

const char* ssid = "admin";
const char* password = "01082842186";
const char* mqtt_server = "broker.hivemq.com";      // mqtt server addr
long int wait_time;
int wait_count;

/* for ntp */
struct tm   timeinfo;
char        strftime_buf[64];
const char* ntpServer = "pool.ntp.org";       // ntp server
const int   timezone = 9;                     // seoul
const int   tz_offset_sec = 3600;             // for seoul offset is 3600 * 9
const int   daylightOffset_sec = 0;
long  int   currtime;

/* for mqtt */
#define RECONNECT_COUNT   5                   // count for mqtt reconnect
int reconnect_count = 0;                      // mqtt reconnect 횟수
long int connect_time;                        // mqtt waiting time
#define pubPeriod     60*1000                 // publishing period 1 min
long int pubTime = 0;                         // publishing tie
long int subTime = 0; 
char myID[20] = "hywu-c0";                    // mqtt id
char tmp_buf[20];

WiFiClient espClient;                         //espCilent 라이브러리 사용
PubSubClient client(espClient);
char pubMsg[40];                              // publish msg buffer
//수신된 버퍼의 크기를 확인하는 명령어 > rxbuf
byte *rxBuf;                                  // callback msg buffer -- use at float2byte
boolean startCarrier = false;                 // callback msg arrived

/* for car */
int onestep = 100;                // 한번 forward 거리 

// setting PWM properties
// PWM Channel
const int freq = 5000;
const int fl1 = 1;          // PWM channel
const int fl2 = 2;
const int fr1 = 3;
const int fr2 = 4;
const int br1 = 5;
const int br2 = 6;
const int bl1 = 7;
const int bl2 = 8;

const int resolution = 8;

/* for moter */
#define FR1     4          // Front Right motor 1 (모터에 달린 빨간선/하얀선 2개여서 각각 2개 지정)
#define FR2     0          // Front Right motor 2
#define FL1     26         // Front Left motor 1
#define FL2     25         // Front Left motor 2
#define BR1     2          // Back Right motor 1
#define BR2     15         // Back Right motor 2
#define BL1     14         // Back Left motor 1
#define BL2     27         // Back Left motor 2

#define MHIGH       150     // analogwrite duty 0~255    바꿀 수 있는 값
#define MLOW        0       // analogwrite duty 0% //pwm 속도 지정

// obstacle detector
#define OD0 36
#define OD1 39

/* for servo */
Servo servo;                // 서브 모터 객체 변수
#define servoPin    5       // 서브모터 시작하는데 사용되는 핀
//#define State       1       // 처음 시작 각도 
#define angle       68      // 정각
#define Rangle      10      // 오른쪽 앵글 각도
#define Langle      130     // 왼쪽 앵글 각도

/* for SR04 */
#define trigPin     13      // trig 핀 설정
#define echoPin     12      // echo 핀 설정
#define SOUND_SPEED 0.034   //음속 cm 단위로 설정

long duration;
float distanceCm;
float distanceInch;


/* for multi-processing */
TaskHandle_t Task1;
TaskHandle_t Task2;

//Task1code: read sensors and write to display, play melody
void Task1code( void * pvParameters ){

    Serial.print(1);
//  while(1){
//    forward(onestep);
//    stopM();
//    delay(1000);
////    left();
////    stopM();
////    delay(1000);
////    forward(onestep);
////    stopM();
////    delay(1000);
////    right();
////    stopM();
////    delay(1000);
////    forward(onestep);
////    stopM();
////    delay(1000);
//  }
}

//Task2code: send sensors data to network or serial
void Task2code( void * pvParameters ){
  // try connect mqtt broker 'reconnect_count' times
  if (!client.connected()){
    if(reconnect_count <= RECONNECT_COUNT){
      if((millis() - connect_time) > 5000){
        reconnect();
        reconnect_count++;
        connect_time = millis();
      }
    }
  }
  client.loop();

  
  while(1){
    // 시간 유지
    if((millis() - currtime) > (1000 * 3600)){    // update exact time every 1 hour
      configTime((long)timezone*tz_offset_sec, daylightOffset_sec, ntpServer);
      currtime = millis();
    }
    //

    // mqtt publish
    if((millis() - pubTime) > pubPeriod){         // publish period --  pubPeriod
      if (client.connected()){
        Make_json();
        client.publish(myID, pubMsg);
      }
      pubTime = millis();
    }

    //mqtt subscribe
    if((millis() - subTime) > pubPeriod){  // publish period --  pubPeriod
      Serial.print(2);
      if (client.connected()){
        client.subscribe("key");
        client.setCallback(callback);
        Serial.print(2);
      }
      subTime = millis();
    }
    
  } // end while
}


void setup(){

 //
  Serial.begin(115200);
  
  // wifi
  setup_wifi();
  client.setServer(mqtt_server, 1883);
//  client.setCallback(callback);

  // servo
  servo.attach(servoPin);
  servo.write(angle);
  delay(1000);

  // 초음파 설정
  pinMode(trigPin, OUTPUT); // trig 핀이 초음파를 방출
  pinMode(echoPin, INPUT); // echo 핀이 반사파 수신

  // Init and get the time
  configTime((long)timezone*tz_offset_sec, daylightOffset_sec, ntpServer);
  delay(1000);
  getLocalTime(&timeinfo);
  Serial.println(&timeinfo, "timeinfo %A, %B %d %Y %H:%M:%S");
  
  
  // configure LED PWM functionalitites
  // ledcSetup(PWM채널, 주파수, 분해능) resolution = 8
  ledcSetup(fl1, freq, resolution); ledcSetup(fl2, freq, resolution);
  ledcSetup(fr1, freq, resolution); ledcSetup(fr2, freq, resolution);
  ledcSetup(bl1, freq, resolution); ledcSetup(bl2, freq, resolution);
  ledcSetup(br1, freq, resolution); ledcSetup(br2, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  // ledcAttachPin(포트번호, PWM 채널) co
  ledcAttachPin(FR1, fr1); ledcAttachPin(FR2, fr2);
  ledcAttachPin(FL1, fl1); ledcAttachPin(FL2, fl2);
  ledcAttachPin(BR1, br1); ledcAttachPin(BR2, br2);
  ledcAttachPin(BL1, bl1); ledcAttachPin(BL2, bl2);
  
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
