void moveCar(char key){
  Serial.print("key : ");Serial.println(key);
  switch(key){
    case 'f': Serial.println("forward");     forward(onestep);    break;
    case 'L': Serial.println("leftSlide");   leftSlide(onestep);  break;
    case 'l': Serial.println("left");        left();              break;
    case 'R': Serial.println("rightSlide");  rightSlide(onestep); break;
    case 'r': Serial.println("right");       right();             break;                                         break;
    case 'b': Serial.println("back");        backward(onestep);   break;
    case 'U': Serial.println("uTurn");       uTurn();             break;
    case 's': Serial.println("stop");        stopM();             break;
    default: Serial.println("key : unknown"); break;
  }
}

void forward(int ostep) {
    ledcWrite(fr1, MHIGH); ledcWrite(fr2, MLOW);
    ledcWrite(fl1, MHIGH); ledcWrite(fl2, MLOW);
    ledcWrite(br1, MHIGH); ledcWrite(br2, MLOW);
    ledcWrite(bl1, MHIGH); ledcWrite(bl2, MLOW);
    delay(onestep);
}

void backward(int ostep) {
    ledcWrite(fr1, MLOW);  ledcWrite(fr2, MHIGH);
    ledcWrite(fl1, MLOW);  ledcWrite(fl2, MHIGH);
    ledcWrite(br1, MLOW);  ledcWrite(br2, MHIGH);
    ledcWrite(bl1, MLOW);  ledcWrite(bl2, MHIGH);
    delay(ostep);
}

void rightSlide(int ostep){
    ledcWrite(fr1, MLOW);  ledcWrite(fr2, MHIGH);
    ledcWrite(fl1, MHIGH); ledcWrite(fl2, MLOW);
    ledcWrite(br1, MHIGH); ledcWrite(br2, MLOW);
    ledcWrite(bl1, MLOW);  ledcWrite(bl2, MHIGH);
    delay(ostep);
}

void leftSlide(int ostep){
    ledcWrite(fr1, MHIGH); ledcWrite(fr2, MLOW);
    ledcWrite(fl1, MLOW);  ledcWrite(fl2, MHIGH);
    ledcWrite(br1, MLOW);  ledcWrite(br2, MHIGH);
    ledcWrite(bl1, MHIGH); ledcWrite(bl2, MLOW);
    delay(ostep);
}

void uTurn(){
  ledcWrite(fr1, MLOW);  ledcWrite(fr2, MHIGH);
  ledcWrite(fl1, MHIGH); ledcWrite(fl2, MLOW);
  ledcWrite(br1, MLOW);  ledcWrite(br2, MHIGH);
  ledcWrite(bl1, MHIGH); ledcWrite(bl2, MLOW);
  delay(810);
  stopM();
}

void left(){
  ledcWrite(fr1, MHIGH); ledcWrite(fr2, MLOW);
  ledcWrite(fl1, MLOW);  ledcWrite(fl2, MHIGH);
  ledcWrite(br1, MHIGH); ledcWrite(br2, MLOW);
  ledcWrite(bl1, MLOW);  ledcWrite(bl2, MHIGH);
  delay(400);
  stopM();

}

void right(){
  ledcWrite(fr1, MLOW);  ledcWrite(fr2, MHIGH);
  ledcWrite(fl1, MHIGH); ledcWrite(fl2, MLOW);
  ledcWrite(br1, MLOW);  ledcWrite(br2, MHIGH);
  ledcWrite(bl1, MHIGH); ledcWrite(bl2, MLOW);
  delay(420); // mhigh 130, delay 550 직각
  stopM();
}

void stopM(){
  ledcWrite(fr1, MLOW); ledcWrite(fr2, MLOW);
  ledcWrite(fl1, MLOW); ledcWrite(fl2, MLOW);
  ledcWrite(br1, MLOW); ledcWrite(br2, MLOW);
  ledcWrite(bl1, MLOW); ledcWrite(bl2, MLOW);
  delay(800);

}
 
