//シリアル通信(PC⇔Arduino)
char data;
const int LED_PIN = 13;

void setup() {
 Serial.begin(9600);
 pinMode(LED_PIN, OUTPUT);
}

void loop(){
  int analog_data;
  float voltage;

 if (Serial.available() > 0) {
   data = Serial.read();
   if(data == '1'){
     //実行したい内容
     digitalWrite(LED_PIN, HIGH);
   }
   else{
     //違う時
     digitalWrite(LED_PIN, LOW);
   }

  delay(100);
  analog_data = analogRead(0);
  voltage = float(analog_data) * (5.0/1023.0);
  Serial.println(voltage);
 }
}