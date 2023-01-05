int followTrack(){
  // line tracer action
  // 0 : center
  // 1 : right
  // 2 : left
  // 3 : right most
  // 4 : left most
}

void forward(int ostep) {
  int s = 4;
  for(int i = 0; i < ostep; i=i+s){
    ledcWrite(fr1, MHIGH); ledcWrite(fr2, MLOW);
    ledcWrite(fl1, MHIGH); ledcWrite(fl2, MLOW);
    ledcWrite(br1, MHIGH); ledcWrite(br2, MLOW);
    ledcWrite(bl1, MHIGH); ledcWrite(bl2, MLOW);
    delay(s*20);
    stopM();
    delay(s*20);
  }
}

void backward(int ostep){
  int s = 4;
  for(int i = 0; i < ostep; i=i+s){
    ledcWrite(fr1, MLOW);  ledcWrite(fr2, MHIGH);
    ledcWrite(fl1, MLOW);  ledcWrite(fl2, MHIGH);
    ledcWrite(br1, MLOW);  ledcWrite(br2, MHIGH);
    ledcWrite(bl1, MLOW);  ledcWrite(bl2, MHIGH);
    delay(s*20);
    stopM();
    delay(s*20);
  }
}

void rightSlide(int ostep){
  int s = 4;
  for(int i = 0; i < ostep; i=i+s){
    ledcWrite(fr1, MLOW);  ledcWrite(fr2, MHIGH);
    ledcWrite(fl1, MHIGH); ledcWrite(fl2, MLOW);
    ledcWrite(br1, MHIGH); ledcWrite(br2, MLOW);
    ledcWrite(bl1, MLOW);  ledcWrite(bl2, MHIGH);
    delay(s*20);
    stopM();
    delay(s*20);
  }
}

void leftSlide(int ostep){
  int s = 4;
  for(int i = 0; i < ostep; i=i+s){
    ledcWrite(fr1, MHIGH); ledcWrite(fr2, MLOW);
    ledcWrite(fl1, MLOW);  ledcWrite(fl2, MHIGH);
    ledcWrite(br1, MLOW);  ledcWrite(br2, MHIGH);
    ledcWrite(bl1, MHIGH); ledcWrite(bl2, MLOW);
    delay(s*20);
    stopM();
    delay(s*20);
  }
}

void uTurn(){
  ledcWrite(fr1, MLOW);  ledcWrite(fr2, MHIGH);
  ledcWrite(fl1, MHIGH); ledcWrite(fl2, MLOW);
  ledcWrite(br1, MLOW);  ledcWrite(br2, MHIGH);
  ledcWrite(bl1, MHIGH); ledcWrite(bl2, MLOW);
  delay(5000);
}

//void left(){
//  ledcWrite(fr1, MHIGH); ledcWrite(fr2, MLOW);
//  ledcWrite(fl1, MLOW);  ledcWrite(fl2, MHIGH);
//  ledcWrite(br1, MHIGH); ledcWrite(br2, MLOW);
//  ledcWrite(bl1, MLOW);  ledcWrite(bl2, MHIGH);
//  delay(600);
//}
//
//void right(){
//  ledcWrite(fr1, MLOW);  ledcWrite(fr2, MHIGH);
//  ledcWrite(fl1, MHIGH); ledcWrite(fl2, MLOW);
//  ledcWrite(br1, MLOW);  ledcWrite(br2, MHIGH);
//  ledcWrite(bl1, MHIGH); ledcWrite(bl2, MLOW);
//  delay(600);
//}

void stopM(){
  ledcWrite(fr1, MLOW); ledcWrite(fr2, MLOW);
  ledcWrite(fl1, MLOW); ledcWrite(fl2, MLOW);
  ledcWrite(br1, MLOW); ledcWrite(br2, MLOW);
  ledcWrite(bl1, MLOW); ledcWrite(bl2, MLOW);
}

void test() {
  forward(onestep);
  stopM();
  delay(1000);
  //leftSlide(onestep);
  
  servoMove();
  
  left();
  stopM();
  delay(1000);
  forward(onestep);
  stopM();
  delay(1000);
  
  servoMove();
  
//    rightSlide(onestep);
  right();
  stopM();
  delay(1000);
  forward(onestep);
  stopM();
  delay(1000);
  
  servoMove();
  
  right();
  stopM();
  delay(1000);
  forward(onestep);
  stopM();
  delay(2000);
//    uTurn();
//  backward(onestep);
//  stopM();
//  delay(1000);
}
