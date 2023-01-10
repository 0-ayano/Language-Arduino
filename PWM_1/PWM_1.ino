/*
  Arduinoの処理を状態遷移を用いてコーディングした試作
  利点：処理の様子を確認しやすい、処理を追加しやすい
  欠点：処理が冗長
  注意：処理の粒度、割り込み処理を利用する際に状態の矛盾や上書きに注意が必要

  グローバル変数「state」
  0: 電源オフの処理
  10: 待機（ラズパイの指示待ち）
    ラズパイから制御信号（文字列または数値を送信）
    ・「20;」: 次状態→20（処理後の次状態→10）
    ・「21;」: 次状態→21（処理後の次状態→10）
    ・「30;」: 次状態→30（処理後の次状態→10）
    ・「31;」: 次状態→31（処理後の次状態→10）
    ・「40;」： 次状態→40（処理後の次状態→10）
    ・「41;」： 次状態→41（処理後の次状態→10）
    ・「50;」： 次状態→50（処理後の次状態→10）
    ・「0;」 ： 次状態→0 （処理後の次状態は？）
    ・入力なし/「10;」：次状態→10（処理後の次状態→10）

  20: LED0をON
      ・次状態→10
  21: LED0をOFF
      ・次状態→10
  30: LED1をON
      ・次状態→10
  31: LED1をOFF
      ・次状態→10
  40: LED2をON
      ・次状態→10
  41: LED2をOFF
      ・次状態→10
  50: CdSの値を読みラズパイへ送信
      ・次状態→10
*/

//各種ポートの設定
const int led0 = 9;
const int led1 = 10;
const int led2 = 11;
const int analogInPin = A0;

//int a;
int sensorValue = 0;
int outputValue = 0;

static int status;            // 次の状態を保存

void Status0( void );         // 電源オフ
void Status10( void );        // 待機
void Status20( void );        // LED0点灯
void Status21( void );        // LED0消灯
void Status30( void );        // LED1点灯
void Status31( void );        // LED1消灯
void Status40( void );        // LED1点灯
void Status41( void );        // LED2消灯
void Status50( void );        // CdSの値を送信

void setup() {
  // 初期設定（ボーレートなど）
  Serial.begin(9600);
  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  digitalWrite(led0, LOW);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  status = 10;        // 初期状態は「待機」
}

void loop() {

  while (1)
  {
    // ラズパイから制御信号を受け取る
    // 受け取らないときは空ループ（「status=10」で待機状態）
    while ( Serial.available() ) {
      // 「;」を終端文字とする（「;」を受け取るまで通信）
      String str = Serial.readStringUntil(';');
      // 文字列を整数値へ変換
      status = str.toInt();

      switch ( status ) // 状態遷移を管理
      {
        case 10:  Status10(); break;
        case 20:  Status20(); break;
        case 21:  Status21(); break;
        case 30:  Status30(); break;
        case 31:  Status31(); break;
        case 40:  Status40(); break;
        case 41:  Status41(); break;
        case 50:  Status50(); break;
        case 0:   Status0();  break;
        default:  Status10(); break;
      }
    }
  }
}

void Status0( void )
{
  // 電源OFFの処理
  // 次状態をどうするか？
  return;
}

void Status10( void )
{
  // 待機（不要と思われる関数だが、動作確認用に残す）
  status = 10;
  return;
}

void Status20( void )
{
  // LED0を点灯
  digitalWrite(led0, HIGH);
  status = 10;
  return;
}

void Status21( void )
{
  // LED0を消灯
  digitalWrite(led0, LOW);
  status = 10;
  return;
}

void Status30( void )
{
  // LED1を点灯
  digitalWrite(led1, HIGH);
  status = 10;
  return;
}

void Status31( void )
{
  // LED1を消灯
  digitalWrite(led1, LOW);
  status = 10;
  return;
}

void Status40( void )
{
  // LED2を点灯
  digitalWrite(led2, HIGH);
  status = 10;
  return;
}

void Status41( void )
{
  // LED2を消灯
  digitalWrite(led2, LOW);
  status = 10;
  return;
}

void Status50( void )
{
  // CdSの値を読み込み、ラズパイへ送信
  sensorValue = analogRead(analogInPin);
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  Serial.println( String(outputValue) );
  status = 10;
  return;
}
