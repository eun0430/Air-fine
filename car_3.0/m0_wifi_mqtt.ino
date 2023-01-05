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
    Serial.print("connected with ID : "); Serial.println(myID);
    // Subscribe
    client.subscribe(control);
    client.subscribe(route);
  } else {
    Serial.print("FAIL: rc="); Serial.print(client.state()); Serial.println(" try again in 5 seconds");
  }
}

void callback(char* topic, byte* payload, unsigned int length){
  String payloadTemp;
  
  /*for (int i = 0; i < length; i++){
    payloadTemp += (char)payload[i];
  }
  Serial.print("Message arrived on topic: "); Serial.print(topic); Serial.print(". Payload: ");
  Serial.println(payloadTemp);*/

  if(strcmp(topic,route)== 0){
    test();
  }

  if(strcmp(topic, control) == 0){
    char key = (char)payload[0];
    switch(key){
      case 'f': Serial.println("forward");forward(onestep); break;
      case 'L': Serial.println("LS");leftSlide(onestep);    break;
      case 'l': Serial.println("left");left();              break;
      case 'R': Serial.println("RS");rightSlide(onestep);   break;
      case 'r': Serial.println("right");right();            break;
      case 'b': Serial.println("back");backward(onestep);   break;
      case 'U': Serial.println("U-turn");uTurn();           break;
      case 's': Serial.println("stop");stopM();             break;
      case 'A': Serial.println("Sensor_A");test();          break;
      defalut: Serial.println("unknown"); break;
    }
  }
  

}


void Make_json(){
  //Serial.println(&timeinfo, "timeinfo %A, %B %d %Y %H:%M:%S");
  //strftime(strftime_buf, 20,"%X %x", &timeinfo);
  time_t rawtime;
  time(&rawtime);
  //sprintf(pubMsg, "\{\"%s\"\:%d, \"%s\"\:%s, \"%s\"\:%s\}", "t", rawtime, "C", currPosition, "P", prevPosition);
  Serial.println(pubMsg);
}
