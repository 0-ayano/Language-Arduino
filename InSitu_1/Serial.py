import serial
from serial.tools import list_ports

def main():
    ports=list_ports.comports()
    device=[info for info in ports if "Arduino" in info.description]

    if len(device) == 0:
        return 0

    print("COM Port : ",device[0].device)

    with serial.Serial(device[0].device) as ser:
        while True:
            print("Input Char (q:quit)", end=' > ')
            p = input()

            if p == 'q':
                break

            flag = bytes(p, 'utf-8')
            ser.write(flag)   # 入力した文字を送信

            val_arduino = ser.readline()
            val_decoded = ( float(repr(val_arduino.decode())[1:-5]) - 4 ) * 10
            print("     Retuen", end=' > ')
            print( int(val_decoded) )
        ser.close()

if __name__ == "__main__":
    main()

"""
- [Pythonでarduinoを動かしてみる](https://fabeee.co.jp/column/employee-blog/mura_02/)
- [[Python]ArduinoのCOMポートが変わってもコードを編集せずにポートを開く方法](https://qiita.com/ronpte1/items/cc16fa70e078f8146a8c)
"""