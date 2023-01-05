void setup_wifi(){
  delay(10);                      // start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to "); Serial.println(ssid);

  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
//    wait_count++;
//    if(wait_count > RECONNECT_COUNT) break;
    Serial.print(".");
  }

  Serial.println("");
  //Serial.println("WiFi connected");
  Serial.print("IP address: "); Serial.println(WiFi.localIP());
}



void Make_json(){
  time_t rawtime;
  time(&rawtime);
}
