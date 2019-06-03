/*
 * اجرای آردواینو و ماژول ساعت DS3231 و شیلد 16x2 LCD display
 * نحوه اتصال به Arduino UNO:                                
 * مازول ساعت DS3231                                      
 * پایه GND به GND                                      
 * پایه VCC به VCC                                      
 * پایه SDA به A4                                       
 * پایه SCL به A5                                       
 * شیلد 16x2 LCD display                                  
 * پایه LCD_RS به پین 8                                 
 * پایه LCD_ENA به پین 9                                 
 * پایه LCD_D4 به پین 4                                 
 * پایه LCD_D5 به پین 5                                 
 * پایه LCD_D6 به پین 6                                 
 * پایه LCD_D7 به پین 7                                 
 */

#include <LiquidCrystal.h>

#include <Wire.h>
#include <DS3231.h>

//تعریف ساعت
DS3231 clock;
RTCDateTime now;

// تعریف تعداد کارکتر ها و سطر های نمایشگر
const uint8_t LCD_ROWS = 2;
const uint8_t LCD_COLS = 16;

// تعریف ثابت های نمایشگر
const uint8_t LCD_RS = 8;
const uint8_t LCD_ENA = 9;
const uint8_t LCD_D4 = 4;
const uint8_t LCD_D5 = LCD_D4+1;
const uint8_t LCD_D6 = LCD_D4+2;
const uint8_t LCD_D7 = LCD_D4+3;

LiquidCrystal lcd(LCD_RS, LCD_ENA, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void setup() {  
  // شروع ترمینال سریال
  Serial.begin(9600);

  // شروع ماژول ساعت
  Serial.println("-=( WEBILI.IR)=-");
  Serial.println("Shorooe saat...");
  clock.begin();

  // ذخیره ساعت با توجه به زمان و تاریخ کامپیوتر
  clock.setDateTime(__DATE__, __TIME__);

  //شروع شیلد نمایشگر
  Serial.println("Shorooe Namayeshgar...");
  lcd.begin(16, 2);
  // نمایش یک پیام در نمایشگر
  lcd.print("SALAM, Donya!");
  lcd.setCursor(0,1);
  lcd.print("-=( WEBILI.IR)=-");

  // 3 ثانیه نمایش پیام
  delay(3000);
}

void loop() {
  //پاک نمودن صفحه نمایش
  lcd.clear();
  
  //دریافت زمان از ماژول ساعت
  now = clock.getDateTime();

  //نمایش اطلاعات زمان در ترمینال

  Serial.print("Date and Time: ");
  Serial.print(now.year);   Serial.print("-");
  Serial.print(now.month);  Serial.print("-");
  Serial.print(now.day);    Serial.print(" ");
  Serial.print(now.hour);   Serial.print(":");
  Serial.print(now.minute); Serial.print(":");
  Serial.print(now.second); Serial.println("");

  //اجرای تابع تاریخ جهت نمایش در نمایشگر
  showDate();
  
  //اجرای تابع زمان جهت نمایش در نمایشگر
  showTime();

  // 1 ثانیه تاخیر در حلقه
  delay(1000);
}

//تعریف تابع نمایش تاریخ
 void showDate()
 {
  //مشخص نمودن نقطه شروع در نمایشگر
  lcd.setCursor(0,0);

  //نمایش سال
  lcd.print(now.year);
  lcd.print('/');

  //نمایش ماه
  lcd.print(now.month);
  lcd.print('/');

  //نمایش روز
  lcd.print(now.day);
 }

//تعریف تابع نمایش زمان
 void showTime()
 {
  //مشخص نمودن نقطه شروع در نمایشگر
  lcd.setCursor(0,1);
  
  //نمایش ساعت
  lcd.print(now.hour);
  lcd.print(':');
  
  //نمایش دقیقه
  lcd.print(now.minute);
  lcd.print(':');

  //نمایش ثانیه
  lcd.print(now.second);
 } 
