//Super Simple LED Light Bar with only odd I/O pins!

void setup() { 
  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT); 
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT); 
  pinMode(8, OUTPUT);
  pinMode(10, OUTPUT); 
  pinMode(12, OUTPUT);
}
void loop() { 
  originalLightBar();
}

void originalLightBar(){
  digitalWrite(12, LOW);
  digitalWrite(0, HIGH); 
  delay(100);
  digitalWrite(2, HIGH);
  digitalWrite(0, LOW);
  delay(100);
  digitalWrite(4, HIGH);
  digitalWrite(2, LOW);
  delay(100);
  digitalWrite(6, HIGH);
  digitalWrite(4, LOW);
  delay(100);
  digitalWrite(8, HIGH);
  digitalWrite(6, LOW);
  delay(100);
  digitalWrite(10, HIGH);
  digitalWrite(8, LOW);
  delay(100);
  digitalWrite(12, HIGH);
  digitalWrite(10, LOW);
  delay(100);
  digitalWrite(10, HIGH);
  digitalWrite(12, LOW);
  delay(100);
  digitalWrite(8, HIGH);
  digitalWrite(10, LOW);
  delay(100);
  digitalWrite(6, HIGH);
  digitalWrite(8, LOW);
  delay(100);
  digitalWrite(4, HIGH);
  digitalWrite(6, LOW);
  delay(100);
  digitalWrite(2, HIGH);
  digitalWrite(4, LOW);
  delay(100);
  digitalWrite(2, LOW);
}

