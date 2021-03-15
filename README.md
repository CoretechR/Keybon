# Keybon - Adaptive Macro Keyboard

Keybon is a macro keyboard with configurable layouts and functions. Integrated into each of its nine tactile buttons is a 0.66” OLED screen. Depending on which app is active on the connected computer, Keybon switches to the suitable key layout thanks to its companion software.

![](keybon%20animated.gif)

![](Explosion%20Animation.gif)

# Instructions

1.  Download the USB bootloader: https://github.com/rogerclarkmelbourne/STM32duino-bootloader

    Connect a USB-to-Serial adapter to the TX/RX pins of your board. Close the BOOT0 jumper before applying power.
    
    Flash the USB bootloader to the STM32 via the STM32 flasher:  https://www.st.com/en/development-tools/flasher-stm32.html
2.  Install the required Arduino libraries listed in the keybon.ino file

    Important: Adafruit_GFX_Library version 1.7.5 must be installed (dependencies for newer versions are incompatible with the STM32)
    
    Add these lines to the Adafruit_SSD1306 (in Arduino/libraries/...)
    ![](https://user-images.githubusercontent.com/13223470/107243109-f9623400-6a2c-11eb-850f-8f4064462722.png)
    ```C++
    else if ((WIDTH == 128) && (HEIGHT == 48)) {
    comPins = 0x12;
	  contrast = (vccstate == SSD1306_EXTERNALVCC) ? 0x9F : 0xCF;
    }
    ```
3.  Install STM32 support for the Arduino IDE: https://github.com/rogerclarkmelbourne/Arduino_STM32

    Install the corresponding drivers: https://github.com/rogerclarkmelbourne/Arduino_STM32/tree/master/drivers
4.  Compile and upload the Arduino sketch:

    ![](https://user-images.githubusercontent.com/13223470/107160061-3b8b6700-6994-11eb-9f17-666364d7964a.png)
