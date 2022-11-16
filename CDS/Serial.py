import serial
from serial.tools import list_ports

def main():
    ports=list_ports.comports()
    device=[info for info in ports if "Arduino" in info.description]

    if len(device) == 0:
        return 0

    print("COM Port : ",device[0].device)

    with serial.Serial(device[0].device, 9600) as ser:
        while True:
            val_arduino = ser.readline()
            val_decoded = ( float(repr(val_arduino.decode())[1:-5]) - 4 ) * 10
            print("     Retuen", end=' > ')
            print( int(val_decoded) )
        
        ser.close()

    return p

if __name__ == "__main__":
    main()
"""
- [(python⇔Arduino)シリアル通信で数値をやりとり](https://haizairenmei.com/2019/11/13/pyserial-arduino/)
- [[Python]ArduinoのCOMポートが変わってもコードを編集せずにポートを開く方法](https://qiita.com/ronpte1/items/cc16fa70e078f8146a8c)
- [Python→Arduino　受信した値をリアルタイムでシリアルモニターで見たいです](https://teratail.com/questions/259259)
"""