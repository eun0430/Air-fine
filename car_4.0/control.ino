void controlK (){
  Serial.println("Interrupt 접속");
    switch(key){
      case 'f': Serial.println("forward");    forward(onestep);     break;
      case 'L': Serial.println("LS");         leftSlide(onestep);   break;
      case 'l': Serial.println("left");       left();               break;
      case 'R': Serial.println("RS");         rightSlide(onestep);  break;
      case 'r': Serial.println("right");      right();              break;
      case 'b': Serial.println("back");       backward(onestep);    break;
      case 'U': Serial.println("U-turn");     uTurn();              break;
      case 's': Serial.println("stop");       stopM();              break;
      case 'A': Serial.println("Sensor_A");   test();               break;
      defalut: Serial.println("unknown");                           break;
    }
    digitalWrite(interruptOutPin, LOW);
  }
