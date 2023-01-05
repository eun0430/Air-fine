/*
 * 
 */
void moveCar(char key){
  Serial.print("key : ");Serial.println(key);
  if(key == 's'){
    digitalWrite(interOut, HIGH);
  }
  switch(key){
    case 'f': forward(onestep);    break;
    case 'L': leftSlide(onestep);  break;
    case 'l': left(onestep/2);     break;
    case 'R': rightSlide(onestep); break;
    case 'r': ;right(onestep/2);   break;
    case 'b': backward(onestep);   break;
    case 'U': uTurn(onestep);      break;
    case 's':  break;
    defalut: Serial.println("key : unknown"); break;
  }
}

void runServo(){
  Serial.println("Servo run....");
  for(int pos = 0; pos <= 180; pos += 1){
    ledcWrite(servo, pos);
    delay(40);
  }
  for(int pos = 180; pos >= 0; pos -= 1){
    ledcWrite(servo, pos);
    delay(40);
  }
}

void forward(int ostep) {
  int s = 4;
  for(int i = 0; i < ostep; i=i+s){
    ledcWrite(fr1, MHIGH); ledcWrite(fr2, MLOW);
    ledcWrite(fl1, MHIGH); ledcWrite(fl2, MLOW);
    ledcWrite(br1, MHIGH); ledcWrite(br2, MLOW);
    ledcWrite(bl1, MHIGH); ledcWrite(bl2, MLOW);
    delay(s);
    stopM();
    delay(s);
  }
}

void backward(int ostep){
  int s = 4;
  for(int i = 0; i < ostep; i=i+s){
    ledcWrite(fr1, MLOW);  ledcWrite(fr2, MHIGH);
    ledcWrite(fl1, MLOW);  ledcWrite(fl2, MHIGH);
    ledcWrite(br1, MLOW);  ledcWrite(br2, MHIGH);
    ledcWrite(bl1, MLOW);  ledcWrite(bl2, MHIGH);
    delay(s);
    stopM();
    delay(s);
  }
}

void rightSlide(int ostep){
  int s = 4;
  for(int i = 0; i < ostep; i=i+s){
    ledcWrite(fr1, MLOW);  ledcWrite(fr2, MHIGH);
    ledcWrite(fl1, MHIGH); ledcWrite(fl2, MLOW);
    ledcWrite(br1, MHIGH); ledcWrite(br2, MLOW);
    ledcWrite(bl1, MLOW);  ledcWrite(bl2, MHIGH);
    delay(s);
    stopM();
    delay(s);
  }
}

void leftSlide(int ostep){
  int s = 4;
  for(int i = 0; i < ostep; i=i+s){
    ledcWrite(fr1, MHIGH); ledcWrite(fr2, MLOW);
    ledcWrite(fl1, MLOW);  ledcWrite(fl2, MHIGH);
    ledcWrite(br1, MLOW);  ledcWrite(br2, MHIGH);
    ledcWrite(bl1, MHIGH); ledcWrite(bl2, MLOW);
    delay(s);
    stopM();
    delay(s);
  }
}

void uTurn(int ostep){
  int s = 4;
  for(int i = 0; i < ostep; i=i+s){
    ledcWrite(fr1, MLOW);  ledcWrite(fr2, MHIGH);
    ledcWrite(fl1, MHIGH); ledcWrite(fl2, MLOW);
    ledcWrite(br1, MLOW);  ledcWrite(br2, MHIGH);
    ledcWrite(bl1, MHIGH); ledcWrite(bl2, MLOW);
    delay(s);
    stopM();
    delay(s);
  }
}

void left(int ostep){
  int s = 4;
  for(int i = 0; i < ostep; i=i+s){
    ledcWrite(fr1, MHIGH); ledcWrite(fr2, MLOW);
    ledcWrite(fl1, MLOW);  ledcWrite(fl2, MHIGH);
    ledcWrite(br1, MHIGH); ledcWrite(br2, MLOW);
    ledcWrite(bl1, MLOW);  ledcWrite(bl2, MHIGH);
    delay(s);
    stopM();
    delay(s);
  }
}

void right(int ostep){
  int s = 4;
  for(int i = 0; i < ostep; i=i+s){
    ledcWrite(fr1, MLOW);  ledcWrite(fr2, MHIGH);
    ledcWrite(fl1, MHIGH); ledcWrite(fl2, MLOW);
    ledcWrite(br1, MLOW);  ledcWrite(br2, MHIGH);
    ledcWrite(bl1, MHIGH); ledcWrite(bl2, MLOW);
    delay(s);
    stopM();
    delay(s);
  }
}


void stopS(){
  digitalWrite(interOut, LOW);
  Serial.println("interrupt occured...STOP!!..");
  ledcWrite(fr1, MLOW); ledcWrite(fr2, MLOW);
  ledcWrite(fl1, MLOW); ledcWrite(fl2, MLOW);
  ledcWrite(br1, MLOW); ledcWrite(br2, MLOW);
  ledcWrite(bl1, MLOW); ledcWrite(bl2, MLOW);
}

void stopM(){
  ledcWrite(fr1, MLOW); ledcWrite(fr2, MLOW);
  ledcWrite(fl1, MLOW); ledcWrite(fl2, MLOW);
  ledcWrite(br1, MLOW); ledcWrite(br2, MLOW);
  ledcWrite(bl1, MLOW); ledcWrite(bl2, MLOW);
}
