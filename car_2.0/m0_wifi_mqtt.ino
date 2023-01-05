/*
 * 
 */
/*
 * float2byte
 * given float value, change to byte array
 * ee is start point of byte array
 * in this program ee is start of numeric
 */
template <typename T> unsigned int float2byte(int ee, const T& value){
    const byte* p = (const byte*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
        rxBuf[ee++] = *p++;
    return i;
}
template <typename T> unsigned int byte2float(int ee, T& value){
    byte* p = (byte*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
        *p++ = rxBuf[ee++];
    return i;
}

void setup_wifi(){
  delay(10);                      // start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to "); Serial.println(ssid);

  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    wait_count++;
    if(wait_count > RECONNECT_COUNT) break;
    Serial.print(".");
  }

  Serial.println("");
  //Serial.println("WiFi connected");
  Serial.print("IP address: "); Serial.println(WiFi.localIP());
}

void reconnect(){
  // Loop until we're reconnected
  Serial.print("Attempting MQTT connection...");
  
  // Attempt to connect
  if (client.connect(myID)) {
    Serial.println("connected with ID : "); Serial.println(myID);
    // Subscribe
    client.subscribe("esp32/output");
  } else {
    Serial.print("FAIL: rc="); Serial.print(client.state()); Serial.println(" try again in 5 seconds");
  }
}

void callback(char* topic, byte* message, unsigned int length){
 /* Serial.print("Message arrived on topic: "); Serial.print(topic); Serial.print(". Message: ");
  rxBuf = message;
  String messageTemp;
  
  for (int i = 0; i < length; i++){
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.print(F("callback message = ")); Serial.println(messageTemp);

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off". 
  // Changes the output state according to the message

  // message format =  "CR0 = 10" or "CR0 = H"
  int key;
  byte2float(6, key);
  switch(key){
    case 1  : pathPtr = path1; break;
    case 2  : pathPtr = path2; break;
    case 3  : pathPtr = path3; break;
    case 4  : pathPtr = path4; break;
    case 5  : pathPtr = path5; break;
    case 6  : pathPtr = path6; break;
    
    case 19 : pathPtr = path1b; break;
    case 29 : pathPtr = path2b; break;
    case 39 : pathPtr = path3b; break;
    case 49 : pathPtr = path4b; break;
    case 59 : pathPtr = path5b; break;
    case 69 : pathPtr = path6b; break;
    default : Serial.println(F("ERROR0, unknown path!!"));break;
  }
   Serial.println("selected path = "); Serial.print(key);

   startCarrier = true;             // callback msg arrived, start carrier
   
  /* if (String(topic) == "esp32/output") {
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("on");
      digitalWrite(ledPin, HIGH);
    }
    else if(messageTemp == "off"){
      Serial.println("off");
      digitalWrite(ledPin, LOW);
    }
  } */
}


void Make_json(){
  //Serial.println(&timeinfo, "timeinfo %A, %B %d %Y %H:%M:%S");
  //strftime(strftime_buf, 20,"%X %x", &timeinfo);
  time_t rawtime;
  time(&rawtime);
  //sprintf(pubMsg, "\{\"%s\"\:%d, \"%s\"\:%s, \"%s\"\:%s\}", "t", rawtime, "C", currPosition, "P", prevPosition);
  Serial.println(pubMsg);
}
