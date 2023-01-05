/*
 * 
 */

int followTrack(){
  // line tracer action
  // 0 : center
  // 1 : right
  // 2 : left
  // 3 : right most
  // 4 : left most
}

void forward(int ostep) { // car 코드에서 ostep = 1000으로 지정
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
  delay(ostep/2);
}

void leftSlide(int ostep){
  ledcWrite(fr1, MHIGH); ledcWrite(fr2, MLOW);
  ledcWrite(fl1, MLOW);  ledcWrite(fl2, MHIGH);
  ledcWrite(br1, MLOW);  ledcWrite(br2, MHIGH);
  ledcWrite(bl1, MHIGH); ledcWrite(bl2, MLOW);
  delay(ostep/2);
}

void uTurn(){
  ledcWrite(fr1, MLOW);  ledcWrite(fr2, MHIGH);
  ledcWrite(fl1, MHIGH); ledcWrite(fl2, MLOW);
  ledcWrite(br1, MLOW);  ledcWrite(br2, MHIGH);
  ledcWrite(bl1, MHIGH); ledcWrite(bl2, MLOW);
  delay(5000);
}

void left(){
  ledcWrite(fr1, MHIGH); ledcWrite(fr2, MLOW);
  ledcWrite(fl1, MLOW);  ledcWrite(fl2, MHIGH);
  ledcWrite(br1, MHIGH); ledcWrite(br2, MLOW);
  ledcWrite(bl1, MLOW);  ledcWrite(bl2, MHIGH);
  delay(5000);
  stopM();
}

void right(){
  ledcWrite(fr1, MLOW);  ledcWrite(fr2, MHIGH);
  ledcWrite(fl1, MHIGH); ledcWrite(fl2, MLOW);
  ledcWrite(br1, MLOW);  ledcWrite(br2, MHIGH);
  ledcWrite(bl1, MHIGH); ledcWrite(bl2, MLOW);
  delay(5000);
  stopM();
}

void stopM(){
  ledcWrite(fr1, MLOW); ledcWrite(fr2, MLOW);
  ledcWrite(fl1, MLOW); ledcWrite(fl2, MLOW);
  ledcWrite(br1, MLOW); ledcWrite(br2, MLOW);
  ledcWrite(bl1, MLOW); ledcWrite(bl2, MLOW);
}
