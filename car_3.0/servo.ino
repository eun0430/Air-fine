void Smotor(){
  servo.write(Rangle);
  delay(800);
  servo.write(Langle);
  delay(800);
  servo.write(angle);
  delay(300);
}
