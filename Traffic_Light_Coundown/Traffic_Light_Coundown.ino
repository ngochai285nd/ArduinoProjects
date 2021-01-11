/*Clock Bắc Nam*/
int BNlatchPin = 10;//Chân ST_CP của 74HC595
int BNclockPin = 12;//Chân SH_CP của 74HC595
int BNdataPin = 11;//Chân DS của 74HC595

/*Clock Đông Tây*/
int DTlatchPin = 5;//Chân ST_CP của 74HC595
int DTclockPin = 6;//Chân SH_CP của 74HC595
int DTdataPin = 7;//Chân DS của 74HC595

/*Đèn Đông Tây*/
int ledRedDT = A0;
int ledYellowDT = A1;
int ledGreenDT = A2;

/*Đèn Bắc Nam*/
int ledRedBN = A3;
int ledYellowBN = A4;
int ledGreenBN = A5;

// Ta sẽ xây dựng mảng hằng số với các giá trị cho trước
// Các bit được đánh số thứ tự (0-7) từ phải qua trái (tương ứng với A-F,DP)
// Vì ta dùng LED 7 đoạn chung cực dương nên với các bit 0
// thì các đoạn của LED 7 đoạn sẽ sáng
// với các bit 1 thì đoạn ấy sẽ tắt

/*Tạo mảng có 10 số (từ 0-9)*/
const byte Seg[10] = {
  //0b1[dp][f][e][d][c][b][a]
  0b11000000,//0
  0b11111001,//1
  0b10100100,//2
  0b10110000,//3
  0b10011001,//4
  0b10010010,//5
  0b10000010,//6
  0b11111000,//7
  0b10000000,//8
  0b10010000,//9
};

void setup() {
  pinMode(BNlatchPin, OUTPUT);
  pinMode(BNclockPin, OUTPUT);
  pinMode(BNdataPin, OUTPUT);
  pinMode(DTlatchPin, OUTPUT);
  pinMode(DTclockPin, OUTPUT);
  pinMode(DTdataPin, OUTPUT);
  pinMode(ledRedDT, OUTPUT);
  pinMode(ledRedBN, OUTPUT);
  pinMode(ledYellowDT, OUTPUT);
  pinMode(ledYellowBN, OUTPUT);
  pinMode(ledGreenDT, OUTPUT);
  pinMode(ledGreenBN, OUTPUT);

  digitalWrite(ledRedDT, LOW);
  digitalWrite(ledRedBN, LOW);
  digitalWrite(ledYellowDT, LOW);
  digitalWrite(ledYellowBN, LOW);
  digitalWrite(ledGreenDT, LOW);
  digitalWrite(ledGreenBN, LOW);
}

void HienThiClockBN(unsigned long Giatri, byte SoLed) {
  byte *array = new byte[SoLed];
  for (byte i = 0; i < SoLed; i++) {
    //Lấy các chữ số từ phải qua trái
    array[i] = (byte)(Giatri % 10UL);
    Giatri = (unsigned long)(Giatri / 10UL);
  }
  digitalWrite(BNlatchPin, LOW);
  for (int i = SoLed - 1; i >= 0; i--) {
    shiftOut(BNdataPin, BNclockPin, MSBFIRST, Seg[array[i]]);
  }
  digitalWrite(BNlatchPin, HIGH);
  free(array);
}

void HienThiClockDT(unsigned long Giatri, byte SoLed) {
  byte *array = new byte[SoLed];
  for (byte i = 0; i < SoLed; i++) {
    //Lấy các chữ số từ phải qua trái
    array[i] = (byte)(Giatri % 10UL);
    Giatri = (unsigned long)(Giatri / 10UL);
  }
  digitalWrite(DTlatchPin, LOW);
  for (int i = SoLed - 1; i >= 0; i--) {
    shiftOut(DTdataPin, DTclockPin, MSBFIRST, Seg[array[i]]);
  }
  digitalWrite(DTlatchPin, HIGH);
  free(array);
}

void loop() {
  unsigned long point = 18;
  for (int i = point; i >= 0; i--) {
    digitalWrite(ledRedBN, HIGH);
    HienThiClockBN(i, 2);
    if (i > 3) {
      digitalWrite(ledGreenDT, HIGH);
      HienThiClockDT(i - 3, 2);
    }
    else {
      HienThiClockDT(0, 2);
      digitalWrite(ledGreenDT, LOW);
      digitalWrite(ledYellowDT, HIGH);
    }
    delay(1000);
  }
  digitalWrite(ledRedBN, LOW);
  digitalWrite(ledYellowDT, LOW);

  for (int i = point; i >= 0; i--) {
    digitalWrite(ledRedDT, HIGH);
    HienThiClockDT(i, 2);
    if (i > 15) {
      digitalWrite(ledYellowBN, HIGH);
      HienThiClockBN(i - 15, 2);
    }
    else {
      HienThiClockBN(i, 2);
      digitalWrite(ledYellowBN, LOW);
      digitalWrite(ledGreenBN, HIGH);
    }
    delay(1000);
  }
  digitalWrite(ledRedDT, LOW);
  digitalWrite(ledGreenBN, LOW);

  for (int i = 3; i > 0; i--) {
    HienThiClockBN(i, 2);
    HienThiClockDT(i, 2);
    digitalWrite(ledYellowBN, HIGH);
    digitalWrite(ledYellowDT, HIGH);
    delay(1000);
  }
  digitalWrite(ledYellowDT, LOW);
  digitalWrite(ledYellowBN, LOW);
}
