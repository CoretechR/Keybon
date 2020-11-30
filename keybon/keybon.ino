#include <USBComposite.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Button.h> // https://github.com/JChristensen/Button
#include "bmp.h"

USBHID HID;
HIDKeyboard Keyboard(HID);
HIDConsumer Consumer(HID);
USBCompositeSerial CompositeSerial;


#define PRODUCT_ID 0x29

#define SW01 PA3
#define SW02 PB0
#define SW03 PB12
#define SW04 PA15
#define SW05 PB11
#define SW06 PA9
#define SW07 PA14
#define SW08 PB10
#define SW09 PA8

#define OLED_MOSI  PA7
#define OLED_CLK   PA5
#define OLED_DC    PA2
#define OLED_CS01    PB5
#define OLED_CS02    PA4
#define OLED_CS03    PB13
#define OLED_CS04    PB4
#define OLED_CS05    PA6
#define OLED_CS06    PB14
#define OLED_CS07    PB3
#define OLED_CS08    PB1
#define OLED_CS09    PB15
#define OLED_RESET PA1

Adafruit_SSD1306 OLED01(128, 48, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS01);
Adafruit_SSD1306 OLED02(128, 48, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS02);
Adafruit_SSD1306 OLED03(128, 48, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS03);
Adafruit_SSD1306 OLED04(128, 48, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS04);
Adafruit_SSD1306 OLED05(128, 48, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS05);
Adafruit_SSD1306 OLED06(128, 48, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS06);
Adafruit_SSD1306 OLED07(128, 48, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS07);
Adafruit_SSD1306 OLED08(128, 48, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS08);
Adafruit_SSD1306 OLED09(128, 48, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS09);

Button button01(SW01, true, true, 5); //pin, pullup, invert, debounce
Button button02(SW02, true, true, 5); //pin, pullup, invert, debounce
Button button03(SW03, true, true, 5); //pin, pullup, invert, debounce
Button button04(SW04, true, true, 5); //pin, pullup, invert, debounce
Button button05(SW05, true, true, 5); //pin, pullup, invert, debounce
Button button06(SW06, true, true, 5); //pin, pullup, invert, debounce
Button button07(SW07, true, true, 5); //pin, pullup, invert, debounce
Button button08(SW08, true, true, 5); //pin, pullup, invert, debounce
Button button09(SW09, true, true, 5); //pin, pullup, invert, debounce

unsigned int cursor = 0;

boolean defaultLayoutActive = true;


void setup() {
  pinMode(SW01, INPUT_PULLUP);
  pinMode(SW02, INPUT_PULLUP);
  pinMode(SW03, INPUT_PULLUP);
  pinMode(SW04, INPUT_PULLUP);
  pinMode(SW05, INPUT_PULLUP);
  pinMode(SW06, INPUT_PULLUP);
  pinMode(SW07, INPUT_PULLUP);
  pinMode(SW08, INPUT_PULLUP);
  pinMode(SW09, INPUT_PULLUP);
  
  USBComposite.setProductId(PRODUCT_ID);
  HID.registerComponent();
  CompositeSerial.registerComponent();
  USBComposite.begin();

  OLED01.begin(SSD1306_SWITCHCAPVCC, 0, true, true); // OLEDs share same reset line, o
  OLED01.setRotation(0);
  OLED02.begin(SSD1306_SWITCHCAPVCC, 0, false, true);
  OLED02.setRotation(0);
  OLED03.begin(SSD1306_SWITCHCAPVCC, 0, false, true);
  OLED03.setRotation(0);
  OLED04.begin(SSD1306_SWITCHCAPVCC, 0, false, true);
  OLED04.setRotation(0);
  OLED05.begin(SSD1306_SWITCHCAPVCC, 0, false, true);
  OLED05.setRotation(0);
  OLED06.begin(SSD1306_SWITCHCAPVCC, 0, false, true);
  OLED06.setRotation(0);
  OLED07.begin(SSD1306_SWITCHCAPVCC, 0, false, true);
  OLED07.setRotation(0);
  OLED08.begin(SSD1306_SWITCHCAPVCC, 0, false, true);
  OLED08.setRotation(0);
  OLED09.begin(SSD1306_SWITCHCAPVCC, 0, false, true);
  OLED09.setRotation(0);

  displayContrast(LOW);
  
  OLED01.clearDisplay();   // clears the screen and buffer
  OLED02.clearDisplay();
  OLED03.clearDisplay();
  OLED04.clearDisplay();
  OLED05.clearDisplay();
  OLED06.clearDisplay();
  OLED07.clearDisplay();
  OLED08.clearDisplay();
  OLED09.clearDisplay();
  
  //delay(500);
  CompositeSerial.setTimeout(200);

  OLED01.drawBitmap(32, 0, bmp_mute, 64, 48, WHITE);
  OLED02.drawBitmap(32, 0, bmp_volume_down, 64, 48, WHITE);
  OLED03.drawBitmap(32, 0, bmp_volume_up, 64, 48, WHITE);
  OLED04.drawBitmap(32, 0, bmp_backward, 64, 48, WHITE);
  OLED05.drawBitmap(32, 0, bmp_play, 64, 48, WHITE);
  OLED06.drawBitmap(32, 0, bmp_forward, 64, 48, WHITE);
  OLED07.drawBitmap(32, 0, bmp_explorer, 64, 48, WHITE);
  OLED08.drawBitmap(32, 0, bmp_snapshot, 64, 48, WHITE);
  OLED09.drawBitmap(32, 0, bmp_calc, 64, 48, WHITE);
}

void loop() {

  if(button01.wasPressed() or button01.pressedFor(300)){
    if(defaultLayoutActive){
      Consumer.press(HIDConsumer::MUTE);
      Consumer.release();
    }
    else CompositeSerial.print("1");
  }
  if(button02.wasPressed() or button02.pressedFor(300)){
    if(defaultLayoutActive){
      Consumer.press(HIDConsumer::VOLUME_DOWN);
      Consumer.release();
    }
    else CompositeSerial.print("2");
  }
  if(button03.wasPressed() or button03.pressedFor(300)){
    if(defaultLayoutActive){
      Consumer.press(HIDConsumer::VOLUME_UP);
      Consumer.release();
    }
    else CompositeSerial.print("3");
  }
  if(button04.wasPressed() or button04.pressedFor(300)){
    if(defaultLayoutActive){
      Consumer.press(182);
      Consumer.release();
    }
    else CompositeSerial.print("4");
  }
  if(button05.wasPressed() or button05.pressedFor(300)){
    if(defaultLayoutActive){
      Consumer.press(HIDConsumer::PLAY_OR_PAUSE);
      Consumer.release();
    }
    else CompositeSerial.print("5");
  }
  if(button06.wasPressed() or button06.pressedFor(300)){
    if(defaultLayoutActive){
      Consumer.press(181);
      Consumer.release();
    }
    else CompositeSerial.print("6");
  }
  if(button07.wasPressed() or button07.pressedFor(300)){
    if(defaultLayoutActive){
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press('e');
      Keyboard.release('e');
      Keyboard.release(KEY_LEFT_GUI);
    }
    else CompositeSerial.print("7");
  }
  if(button08.wasPressed() or button08.pressedFor(300)){
    if(defaultLayoutActive){
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press('s');
      Keyboard.release('s');
      Keyboard.release(KEY_LEFT_SHIFT);
      Keyboard.release(KEY_LEFT_GUI);
    }
    else CompositeSerial.print("8");
  }
  if(button09.wasPressed() or button09.pressedFor(300)){
    if(defaultLayoutActive){
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press('r');
      Keyboard.release('r');
      Keyboard.release(KEY_LEFT_GUI);
      Keyboard.print("calc");
      Keyboard.press('\n');
      Keyboard.release('\n');
    }
    else CompositeSerial.print("9");
  }

  
  while (CompositeSerial.available() > 0){
    byte command = CompositeSerial.read();
    if(command >= '0' && command <= '8'){
      defaultLayoutActive = false;
      CompositeSerial.readBytes(bmp_swap,384);
      if(command == '0'){
        OLED01.clearDisplay();
        OLED01.drawBitmap(32, 0, bmp_swap, 64, 48, WHITE);
      }
      if(command == '1'){
        OLED02.clearDisplay();
        OLED02.drawBitmap(32, 0, bmp_swap, 64, 48, WHITE);
      }
      if(command == '2'){
        OLED03.clearDisplay();
        OLED03.drawBitmap(32, 0, bmp_swap, 64, 48, WHITE);
      }
      if(command == '3'){
        OLED04.clearDisplay();
        OLED04.drawBitmap(32, 0, bmp_swap, 64, 48, WHITE);
      }
      if(command == '4'){
        OLED05.clearDisplay();
        OLED05.drawBitmap(32, 0, bmp_swap, 64, 48, WHITE);
      }
      if(command == '5'){
        OLED06.clearDisplay();
        OLED06.drawBitmap(32, 0, bmp_swap, 64, 48, WHITE);
      }
      if(command == '6'){
        OLED07.clearDisplay();
        OLED07.drawBitmap(32, 0, bmp_swap, 64, 48, WHITE);
      }
      if(command == '7'){
        OLED08.clearDisplay();
        OLED08.drawBitmap(32, 0, bmp_swap, 64, 48, WHITE);
      }
      if(command == '8'){
        OLED09.clearDisplay();
        OLED09.drawBitmap(32, 0, bmp_swap, 64, 48, WHITE);
      }
    }
    else if(command == 'D'){ //fallback to internal Layout
      defaultLayoutActive = true;
      OLED01.clearDisplay();   // clears the screen and buffer
      OLED02.clearDisplay();
      OLED03.clearDisplay();
      OLED04.clearDisplay();
      OLED05.clearDisplay();
      OLED06.clearDisplay();
      OLED07.clearDisplay();
      OLED08.clearDisplay();
      OLED09.clearDisplay();
      OLED01.drawBitmap(32, 0, bmp_mute, 64, 48, WHITE);
      OLED02.drawBitmap(32, 0, bmp_volume_down, 64, 48, WHITE);
      OLED03.drawBitmap(32, 0, bmp_volume_up, 64, 48, WHITE);
      OLED04.drawBitmap(32, 0, bmp_backward, 64, 48, WHITE);
      OLED05.drawBitmap(32, 0, bmp_play, 64, 48, WHITE);
      OLED06.drawBitmap(32, 0, bmp_forward, 64, 48, WHITE);
      OLED07.drawBitmap(32, 0, bmp_explorer, 64, 48, WHITE);
      OLED08.drawBitmap(32, 0, bmp_snapshot, 64, 48, WHITE);
      OLED09.drawBitmap(32, 0, bmp_calc, 64, 48, WHITE);
    }
    else if(command == 'A'){ //Answer to call
      CompositeSerial.print("a");
    }
    else if(command == 'B'){ //high brightness
      displayContrast(HIGH);
    }
    else if(command == 'b'){ //low brightness
      displayContrast(LOW);
    }
  }
  
  //OLED09.setCursor(32, 10);
  //OLED09.setTextColor(WHITE);
  //OLED09.setTextSize(1);
  //OLED09.print(cursor);

  OLED01.display();
  OLED02.display();
  OLED03.display();
  OLED04.display();
  OLED05.display();
  OLED06.display();
  OLED07.display();
  OLED08.display();
  OLED09.display();

  button01.read();
  button02.read();
  button03.read();
  button04.read();
  button05.read();
  button06.read();
  button07.read();
  button08.read();
  button09.read();

}

void displayContrast(boolean contrast){
  byte contrastSetting = 0x35;
  if(contrast == HIGH) contrastSetting = 0x7F;
  
  OLED01.ssd1306_command(SSD1306_SETCONTRAST);
  OLED01.ssd1306_command(contrastSetting);
  OLED02.ssd1306_command(SSD1306_SETCONTRAST);
  OLED02.ssd1306_command(contrastSetting);
  OLED03.ssd1306_command(SSD1306_SETCONTRAST);
  OLED03.ssd1306_command(contrastSetting);
  OLED04.ssd1306_command(SSD1306_SETCONTRAST);
  OLED04.ssd1306_command(contrastSetting);
  OLED05.ssd1306_command(SSD1306_SETCONTRAST);
  OLED05.ssd1306_command(contrastSetting);
  OLED06.ssd1306_command(SSD1306_SETCONTRAST);
  OLED06.ssd1306_command(contrastSetting);
  OLED07.ssd1306_command(SSD1306_SETCONTRAST);
  OLED07.ssd1306_command(contrastSetting);
  OLED08.ssd1306_command(SSD1306_SETCONTRAST);
  OLED08.ssd1306_command(contrastSetting);
  OLED09.ssd1306_command(SSD1306_SETCONTRAST);
  OLED09.ssd1306_command(contrastSetting);
}
