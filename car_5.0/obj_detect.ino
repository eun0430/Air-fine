//void SR04() {
//  // Clears the trigPin
//  digitalWrite(trigPin, LOW);
//  delayMicroseconds(2);
//  // Sets the trigPin on HIGH state for 10 micro seconds
//  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPin, LOW);
//  
//  // 음파 이동 시간을 계산해 저장 
//  duration = pulseIn(echoPin, HIGH);
//  distanceCm = duration * SOUND_SPEED/2;   // 물체와의 거리를 cm으로 계산 
//
//  // 출력
//  Serial.print("Distance (cm): ");
//  Serial.println(distanceCm);
//}
//
void servoMove() { // 객체 인식했을 때, 서보 각도 조절하는 함수

  servo.write(Rangle);
  delay(1000);
  servo.write(Langle);
  delay(1000);
}

//  if (distanceCm <= 15.00) {
//    servo.write(Rangle);
//    delay(1000);
//    
//    servo.write(Langle);
//    delay(1000);
//    
//    servo.write(angle);
//    delay(1000);

//void servo_SR04() {
//  // 회전
//  servo.write(angle);
//  delay(50); // 0.5초 간격으로 서보모터 angle로 회전      
//
//  // Clears the trigPin
//  digitalWrite(trigPin, LOW);
//  delayMicroseconds(2);
//  // Sets the trigPin on HIGH state for 10 micro seconds
//  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPin, LOW);
//  
//  // 음파 이동 시간을 계산해 저장 
//  duration = pulseIn(echoPin, HIGH);
//  distanceCm = duration * SOUND_SPEED/2;   // 물체와의 거리를 cm으로 계산 
//
//  // 출력
//  Serial.print("Distance (cm): ");
//  Serial.println(distanceCm);
//  
//  
//  //회전 각도
//  servo.write(angle);
//  
//  if(distanceCm <= 15.00) {
//    servo.write(Rangle);
//    delay(1000);
//    servo.write(Langle);
//    delay(1000);  // 서보모터가 이동하는 시간 줘야 함
//  }
//}
