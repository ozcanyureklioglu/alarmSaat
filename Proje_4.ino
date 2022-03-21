#include <virtuabotixRTC.h>
#include <Time.h>
#include <LiquidCrystal.h>


/*##################################MUSİC###############################################*/

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST 0


int tempo=144; 


int buzzer = 2;

int melody[] = {

  //Based on the arrangement at https://www.flutetunes.com/tunes.php?id=192
  
  NOTE_E5, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_C5,8,  NOTE_B4,8,
  NOTE_A4, 4,  NOTE_A4,8,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
  NOTE_B4, -4,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
  NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,8,  NOTE_A4,4,  NOTE_B4,8,  NOTE_C5,8,

  NOTE_D5, -4,  NOTE_F5,8,  NOTE_A5,4,  NOTE_G5,8,  NOTE_F5,8,
  NOTE_E5, -4,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
  NOTE_B4, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
  NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,4, REST, 4,

  NOTE_E5, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_C5,8,  NOTE_B4,8,
  NOTE_A4, 4,  NOTE_A4,8,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
  NOTE_B4, -4,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
  NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,8,  NOTE_A4,4,  NOTE_B4,8,  NOTE_C5,8,

  NOTE_D5, -4,  NOTE_F5,8,  NOTE_A5,4,  NOTE_G5,8,  NOTE_F5,8,
  NOTE_E5, -4,  NOTE_C5,8,  NOTE_E5,4,  NOTE_D5,8,  NOTE_C5,8,
  NOTE_B4, 4,  NOTE_B4,8,  NOTE_C5,8,  NOTE_D5,4,  NOTE_E5,4,
  NOTE_C5, 4,  NOTE_A4,4,  NOTE_A4,4, REST, 4,
  

 

};


int notes=sizeof(melody)/sizeof(melody[0])/2; 

int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;

/*##################################MUSİC###############################################*/

virtuabotixRTC RTC_DS1302(12, 11, 13);
LiquidCrystal lcd(8,9,4,5,6,7);

byte Bell[8] = {
  B00000,
  B00100,
  B01110,
  B01110,
  B01110,
  B11111,
  B00000,
  B00100
};

int sensorValue = 0;
int sensorPin = A0; 

int h=0;  
int m=0;
int Sh=0;
int Sm=0;
int x;
int y=0;
int gun;
int ay;
int yil;
int tarihAyarSayaci=0;
bool set=false;
bool isaret=true;
bool alarm=false;
bool saat=true;
bool dakika=false;
bool saatAyarlandi=false;
bool tarihAyarlandi=false;
unsigned long previousMillis = 0;
const long interval = 1000;
void setup() {
  
  lcd.begin (16,2);
  lcd.setCursor(0,0);
  Serial.begin(9600);
  lcd.createChar(0,Bell);


  
}

void loop() {
  RTC_DS1302.updateTime();
  x = analogRead (0);
  //Serial.println(x);
  if(x>1000 && y==0){// Herhangi bir tuşa basılmaz ise Tarih ve saati göster
    
    lcd.setCursor(0,0);
    lcd.print(RTC_DS1302.dayofmonth);
    lcd.print("/");
    lcd.print(RTC_DS1302.month);
    lcd.print("/");
    lcd.print(RTC_DS1302.year);
    lcd.setCursor(0,11);
    lcd.setCursor(11,0);
    if (RTC_DS1302.hours < 10)
    {
      lcd.print("0");
      lcd.print(RTC_DS1302.hours);
    }
    else
    {
      lcd.print(RTC_DS1302.hours);
    }

    
    unsigned long currentMillis = millis();
    lcd.setCursor(13,0);
    if (currentMillis - previousMillis >= interval) {//ANA EKRANDA SANİYE GÖSTERİCİ YANIP SÖNME
      
      previousMillis = currentMillis;
  
      if(isaret){
        lcd.print(":");
        
        
        isaret=false;
      }else{
        
        lcd.print(" ");
        
        isaret=true;
      }
    }
    lcd.setCursor(14,0);
    if (RTC_DS1302.minutes < 10)
    {
      lcd.print("0");
      lcd.print(RTC_DS1302.minutes);
    }
    else
    {
      lcd.print(RTC_DS1302.minutes);
    }


    if(alarm){
      lcd.setCursor(0,1);
      
      lcd.print("ALARM ON");
      lcd.print(" ");
      
    }else{
      lcd.setCursor(0,1);
      
      lcd.print("ALARM OFF");
      
    }
    
    if(alarm){//Alarm kuruluysa LCD de göster
      lcd.setCursor(11,1);
      
      if (h < 10){
        lcd.print("0");
        lcd.print(h);
      }
      else
      {
        lcd.print(h);
      }
      
      lcd.write(byte(0));
      
      if (m < 10){
        lcd.print("0");
        lcd.print(m);
      }
      else
      {
        lcd.print(m);
      }
      
      
    }else{//Alarm gösterge sonu
    lcd.setCursor(11,1);
    lcd.print("     ");
    
    }

    if(RTC_DS1302.hours==h && m==RTC_DS1302.minutes && alarm){// Alarm aktif ise ses çal
      ses(); 
    }
    
    
    
  }// Her hangi bir tuş basılı değil ise sonu
  else if(x>600 && x<1000){ //SELECT TUŞU
    set=true;
    saat=true;
    dakika=false;
    y++;
    lcd.clear();
    if(y==1){
      lcd.print("ALARM KUR");
      
      h=RTC_DS1302.hours;
      m=RTC_DS1302.minutes;
      m--;
    }else if(y==2){
      lcd.print("SAAT AYARI");
      saatAyarlandi=false;
      
      Sh=RTC_DS1302.hours;
      Sm=RTC_DS1302.minutes;
    }else if(y==3){
      lcd.print("TARIH AYARI");
      tarihAyarlandi=false;
      gun=RTC_DS1302.dayofmonth;
      ay=RTC_DS1302.month;
      yil=RTC_DS1302.year;
      
    }else{
      
      y=0;
      set=false;
    }
    
    delay(200);
  }else if(x>98 && x<250 && set){ //UP TUSU

      if(y==1){// EĞER UP TUŞU TIKLANDIĞINDA ALARM AYAR MODUNDAYSA
        if(saat){
        
        h++;
        if(h>24){h=0;}
        
        }else{
          
          m++;
          if(m>60){m=0;}
        }
      }else if(y==2){// EĞER UP TUŞU TIKLANDIĞINDA SAAT AYAR MODUNDAYSA
        saatAyarlandi=true;
        
        if(saat){
        
        Sh++;
        if(Sh>24){Sh=0;}
        
        }else{
          
          Sm++;
          if(Sm>60){Sm=0;}
        }
      }else if(y==3){ // EĞER UP TUŞU TIKLANDIĞINDA TARIH AYAR MODUNDAYSA
        tarihAyarlandi=true;
        if(tarihAyarSayaci==0){
          
          if(gun<31){
            gun++;
          }else{gun=1;}
        }else if(tarihAyarSayaci==1){
          if(ay<12){
            ay++;
          }else{ay=1;}
          
        }else if(tarihAyarSayaci==2){
          yil++;
        }
      }
      
      

      
      delay(200);
      
    }else if(x>250 && x<400 && set){ // DOWN TUSU
    
      if(y==1){// EĞER DOWN TUŞU TIKLANDIĞINDA ALARM AYAR MODUNDAYSA
        if(saat){
          h--;
          if(h<0){
            h=24;}
        }
        else{
        
          m--;
          if(m<0){m=60;}
        
        }
      }else if(y==2){// EĞER DOWN TUŞU TIKLANDIĞINDA SAAT AYAR MODUNDAYSA
        saatAyarlandi=true;
        
        if(saat){
          Sh--;
          if(Sh<0){
            Sh=24;}
        }
        else{
        
          Sm--;
          if(Sm<0){Sm=60;}
        
        }
      }else if(y==3){ // EĞER DOWN TUŞU TIKLANDIĞINDA TARIH AYAR MODUNDAYSA
        tarihAyarlandi=true;
        if(tarihAyarSayaci==0){
          if(gun>1){
            gun--;
          }else{gun=31;}
        }else if(tarihAyarSayaci==1){
          if(ay>1){
            ay--;
          }else{ay=12;}
          
        }else if(tarihAyarSayaci==2){
          yil--;
        }
      }
      
      
      
      
      delay(200);
    }else if(x>420 && x<600 && set){ // LEFT TUSU
      saat=true;
      dakika=false;

      if(y==3 && tarihAyarSayaci!=0){
        tarihAyarSayaci--;
      }
      
      delay(200);
    }else if(x>0 && x<250 && set){// RIGHT TUSU
      saat=false;
      dakika=true;
      if(y==3 && tarihAyarSayaci!=2){
        tarihAyarSayaci++;
      }
      delay(200);
    }else if(x>420 && x<600 && !set){ // ANA EKRAN ALARM KAPAT
      alarm=false;
      delay(200);
    }else if(x>0 && x<250 && !set){// ANA EKRAN ALARM AÇ
      alarm=true;
      delay(200);
    }

    

    if((y==1) && saat){//ALARM AYARLAMA MODUNDA SAAT AYARINA GEÇİŞ YAPILIRSA
      
      lcd.setCursor(3,1);
      if (m < 10){
        lcd.print("0");
        lcd.print(m);
      }
      else
      {
        lcd.print(m);
      }
      
      unsigned long currentMillis = millis();
      lcd.setCursor(0,1);
      if (currentMillis - previousMillis >= 300) {// SAAT KISMI AYARLAMA SÜRESİNCE YANIP SÖNME
        
        previousMillis = currentMillis;
    
        if(isaret){
          if (h < 10){
              lcd.print("0");
              lcd.print(h);
            }
            else
            {
              lcd.print(h);
            }
          isaret=false;
        }else{
          lcd.print("  ");
          isaret=true;
        }
      }
      lcd.setCursor(2,1);
      lcd.print(":");
      
    }else if((y==1) && dakika){//ALARM AYARLAMA MODUNDA DAKİKA AYARINA GEÇİŞ YAPILIRSA
      lcd.setCursor(0,1);
      if (h < 10){
        lcd.print("0");
        lcd.print(h);
      }
      else
      {
        lcd.print(h);
      }
      
      unsigned long currentMillis = millis();
      lcd.setCursor(3,1);
      if (currentMillis - previousMillis >= 300) {// DAKİKA KISMI AYARLAMA SÜRESİNCE YANIP SÖNME
        
        previousMillis = currentMillis;
    
        if(isaret){
          if (m < 10){
              lcd.print("0");
              lcd.print(m);
            }
            else
            {
              lcd.print(m);
            }
          isaret=false;
        }else{
          lcd.print("  ");
          isaret=true;
        }
      }
    } // ALARM AYARLAMA MODU SONU

    /*SAAT AYARLAMA KISMI BAŞLANGICI*/

    if((y==2) && saat){//SAAT AYARLAMA MODUNDA SAAT AYARINA GEÇİŞ YAPILIRSA
      
      lcd.setCursor(3,1);
      if (Sm < 10){
        lcd.print("0");
        lcd.print(Sm);
      }
      else
      {
        lcd.print(Sm);
      }
      
      unsigned long currentMillis = millis();
      lcd.setCursor(0,1);
      if (currentMillis - previousMillis >= 300) {// SAAT KISMI AYARLAMA SÜRESİNCE YANIP SÖNME
        
        previousMillis = currentMillis;
    
        if(isaret){
          if (h < 10){
              lcd.print("0");
              lcd.print(Sh);
            }
            else
            {
              lcd.print(Sh);
            }
          isaret=false;
        }else{
          lcd.print("  ");
          isaret=true;
        }
      }
      lcd.setCursor(2,1);
      lcd.print(":");
      
    }else if((y==2) && dakika){//SAAT AYARLAMA MODUNDA DAKİKA AYARINA GEÇİŞ YAPILIRSA
      lcd.setCursor(0,1);
      if (Sh < 10){
        lcd.print("0");
        lcd.print(Sh);
      }
      else
      {
        lcd.print(Sh);
      }
      
      unsigned long currentMillis = millis();
      lcd.setCursor(3,1);
      if (currentMillis - previousMillis >= 300) {// DAKİKA KISMI AYARLAMA SÜRESİNCE YANIP SÖNME
        
        previousMillis = currentMillis;
    
        if(isaret){
          if (Sm < 10){
              lcd.print("0");
              lcd.print(Sm);
            }
            else
            {
              lcd.print(Sm);
            }
          isaret=false;
        }else{
          lcd.print("  ");
          isaret=true;
        }
      }
    }//SAAT AYARLAMA SONU 


    /***********TARİH AYAR BOLUMU BASLANGIC**************/

    if(y==3 && tarihAyarSayaci==0){//TARİH AYAR MODUNDA GUN AYARINA GEÇİŞ YAPILIRSA
      
      lcd.setCursor(2,1);
      lcd.print("/");
      if(ay<10){
        lcd.print("0");
        lcd.print(ay);
      }else{
        lcd.print(ay);
      }
      lcd.print("/");
      lcd.print(yil);
      
      unsigned long currentMillis = millis();
      lcd.setCursor(0,1);
      if (currentMillis - previousMillis >= 300) {// GUN KISMI AYARLAMA SÜRESİNCE YANIP SÖNME
        
        previousMillis = currentMillis;
    
        if(isaret){
          if (gun < 10){
              lcd.print("0");
              lcd.print(gun);
            }
            else
            {
              lcd.print(gun);
            }
          isaret=false;
        }else{
          lcd.print("  ");
          isaret=true;
        }
      }
      
      
    }else if(y==3 && tarihAyarSayaci==1){//TARIH AYARLAMA MODUNDA AY AYARINA GEÇİŞ YAPILIRSA
      lcd.setCursor(0,1);
      if(gun<10){
        lcd.print("0");
        lcd.print(gun);
      }else{
        lcd.print(gun);
      }
      lcd.print("/");
      
      
      unsigned long currentMillis = millis();
      lcd.setCursor(3,1);
      if (currentMillis - previousMillis >= 300) {// AY KISMI AYARLAMA SÜRESİNCE YANIP SÖNME
        
        previousMillis = currentMillis;
    
        if(isaret){
          if (ay < 10){
              lcd.print("0");
              lcd.print(ay);
            }
            else
            {
              lcd.print(ay);
            }
          isaret=false;
        }else{
          lcd.print("  ");
          isaret=true;
        }
      }
      lcd.setCursor(5,1);
      lcd.print("/");
      lcd.print(yil);
      
    }else if((y==3) && tarihAyarSayaci==2){//TARIH AYARLAMA MODUNDA YIL AYARINA GEÇİŞ YAPILIRSA
       
      unsigned long currentMillis = millis();
      lcd.setCursor(6,1);
      if (currentMillis - previousMillis >= 300) {// YIL KISMI AYARLAMA SÜRESİNCE YANIP SÖNME
        
        previousMillis = currentMillis;
    
        if(isaret){
          lcd.print(yil);
          isaret=false;
        }else{
          lcd.print("    ");
          isaret=true;
        }
      }

      lcd.setCursor(0,1);
      if(gun<10){
        lcd.print("0");
        lcd.print(gun);
      }else{
        lcd.print(gun);
      }
      lcd.print("/");
      if(ay<10){
        lcd.print("0");
        lcd.print(ay);
      }else{
        lcd.print(ay);
      }
      lcd.print("/");
      
    }
    

    if(saatAyarlandi){// SAAT AYARI YAPILDISYA

      Serial.print("Saat ayari yapildi");
      RTC_DS1302.setDS1302Time(00, Sm, Sh, 6, RTC_DS1302.dayofmonth, RTC_DS1302.month, RTC_DS1302.year);
      saatAyarlandi=false;
      
    }
    if(tarihAyarlandi){// TARIH AYARI YAPILDIYSA
      Serial.print("Tarih ayari yapildi");
      RTC_DS1302.setDS1302Time(00, RTC_DS1302.minutes, RTC_DS1302.hours, 6, gun, ay, yil);
      tarihAyarlandi=false;
    }

    
    
  }//LOOP FONKSİYONU SONU
  
  




void ses(){// ALARM SES TONU OYNATMA
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    
    
    
    divider = melody[thisNote + 1];
    if (divider > 0) {
      
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; 
    }

    
    tone(buzzer, melody[thisNote], noteDuration*0.9);

    
    delay(noteDuration);
    
    
    noTone(buzzer);
  }
}
