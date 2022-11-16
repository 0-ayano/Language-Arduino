void setup() {
  Serial.begin(9600);//シリアル通信を9600bpsで初期化
}

void loop() {
  int analog_data;
  float voltage;

  analog_data = analogRead(0);//アナログ0番ピンの入力状態をanalog_dataに代入

  voltage = float(analog_data) * (5.0/1023.0);//A/D値から電圧値を算出
  Serial.println(voltage);//「voltage」を送信
  delay(100);//1000msec待機(1秒待機)
}