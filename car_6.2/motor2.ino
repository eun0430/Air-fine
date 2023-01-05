//void forward(int ostep) {
//  int s = 4;
//  for(int i = 0; i < ostep; i=i+s){
//    ledcWrite(fr1, MHIGH); ledcWrite(fr2, MLOW);
//    ledcWrite(fl1, MHIGH); ledcWrite(fl2, MLOW);
//    ledcWrite(br1, MHIGH); ledcWrite(br2, MLOW);
//    ledcWrite(bl1, MHIGH); ledcWrite(bl2, MLOW);
//    delay(s*20);
//    stopM();
//    delay(s);
//  }
//  delay(ostep);
//  
//}
//
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
