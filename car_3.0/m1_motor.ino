/*
 * 
 */

//void forward(int ostep) {
//  int s = 4;
//  for(int i = 0; i < ostep; i=i+s){
//    ledcWrite(fr1, MHIGH); ledcWrite(fr2, MLOW);
//    ledcWrite(fl1, MHIGH); ledcWrite(fl2, MLOW);
//    ledcWrite(br1, MHIGH); ledcWrite(br2, MLOW);
//    ledcWrite(bl1, MHIGH); ledcWrite(bl2, MLOW);
//    delay(s*20);
//    stopM();
//    delay(s*20)z;
//  }
//  delay(ostep);
//}

void forward(int ostep) {
    ledcWrite(fr1, MHIGH); ledcWrite(fr2, MLOW);
    ledcWrite(fl1, MHIGH); ledcWrite(fl2, MLOW);
    ledcWrite(br1, MHIGH); ledcWrite(br2, MLOW);
    ledcWrite(bl1, MHIGH); ledcWrite(bl2, MLOW);
    delay(ostep);
    stopM();
    //delay(5000);
    Smotor();
}

//void backward(int ostep){
//  int s = 4;
//  for(int i = 0; i < ostep; i=i+s){
//    ledcWrite(fr1, MLOW);  ledcWrite(fr2, MHIGH);
//    ledcWrite(fl1, MLOW);  ledcWrite(fl2, MHIGH);
//    ledcWrite(br1, MLOW);  ledcWrite(br2, MHIGH);
//    ledcWrite(bl1, MLOW);  ledcWrite(bl2, MHIGH);
//    delay(s*20);
//    stopM();
//    delay(s*20);
//  }
//  delay(ostep);
//}

void backward(int ostep) {
    ledcWrite(fr1, MLOW);  ledcWrite(fr2, MHIGH);
    ledcWrite(fl1, MLOW);  ledcWrite(fl2, MHIGH);
    ledcWrite(br1, MLOW);  ledcWrite(br2, MHIGH);
    ledcWrite(bl1, MLOW);  ledcWrite(bl2, MHIGH);
}

//void rightSlide(int ostep){
//  int s = 4;
//  for(int i = 0; i < ostep; i=i+s){
//    ledcWrite(fr1, MLOW);  ledcWrite(fr2, MHIGH);
//    ledcWrite(fl1, MHIGH); ledcWrite(fl2, MLOW);
//    ledcWrite(br1, MHIGH); ledcWrite(br2, MLOW);
//    ledcWrite(bl1, MLOW);  ledcWrite(bl2, MHIGH);
//    delay(s*20);
//    stopM();
//    delay(s*20);
//  }
//}

void rightSlide(int ostep){
    ledcWrite(fr1, MLOW);  ledcWrite(fr2, MHIGH);
    ledcWrite(fl1, MHIGH); ledcWrite(fl2, MLOW);
    ledcWrite(br1, MHIGH); ledcWrite(br2, MLOW);
    ledcWrite(bl1, MLOW);  ledcWrite(bl2, MHIGH);
}

//void leftSlide(int ostep){
//  int s = 4;
//  for(int i = 0; i < ostep; i=i+s){
//    ledcWrite(fr1, MHIGH); ledcWrite(fr2, MLOW);
//    ledcWrite(fl1, MLOW);  ledcWrite(fl2, MHIGH);
//    ledcWrite(br1, MLOW);  ledcWrite(br2, MHIGH);
//    ledcWrite(bl1, MHIGH); ledcWrite(bl2, MLOW);
//    delay(s*20);
//    stopM();
//    delay(s*20);
//  }
//}


void leftSlide(int ostep){
    ledcWrite(fr1, MHIGH); ledcWrite(fr2, MLOW);
    ledcWrite(fl1, MLOW);  ledcWrite(fl2, MHIGH);
    ledcWrite(br1, MLOW);  ledcWrite(br2, MHIGH);
    ledcWrite(bl1, MHIGH); ledcWrite(bl2, MLOW);
}

void uTurn(){
  ledcWrite(fr1, MLOW);  ledcWrite(fr2, MHIGH);
  ledcWrite(fl1, MHIGH); ledcWrite(fl2, MLOW);
  ledcWrite(br1, MLOW);  ledcWrite(br2, MHIGH);
  ledcWrite(bl1, MHIGH); ledcWrite(bl2, MLOW);
}

void left(){
  ledcWrite(fr1, MHIGH); ledcWrite(fr2, MLOW);
  ledcWrite(fl1, MLOW);  ledcWrite(fl2, MHIGH);
  ledcWrite(br1, MHIGH); ledcWrite(br2, MLOW);
  ledcWrite(bl1, MLOW);  ledcWrite(bl2, MHIGH);
  delay(600);
  stopM();
}

void right(){
  ledcWrite(fr1, MLOW);  ledcWrite(fr2, MHIGH);
  ledcWrite(fl1, MHIGH); ledcWrite(fl2, MLOW);
  ledcWrite(br1, MLOW);  ledcWrite(br2, MHIGH);
  ledcWrite(bl1, MHIGH); ledcWrite(bl2, MLOW);
  delay(650);
  stopM();
}

void stopM(){
  ledcWrite(fr1, MLOW); ledcWrite(fr2, MLOW);
  ledcWrite(fl1, MLOW); ledcWrite(fl2, MLOW);
  ledcWrite(br1, MLOW); ledcWrite(br2, MLOW);
  ledcWrite(bl1, MLOW); ledcWrite(bl2, MLOW);
  delay(500);
}
