# Stranger Things Wall
Stranger Things light wall that runs on Arduino.

### Inspiration
The show obvisouly. Also [this instructable](http://www.instructables.com/id/Arduino-Based-Stranger-Things-Lights/) but as the author admits he is not a programmer and his code shows it. I used his ideas for hardware but I wrote my own software and I think it's cleaner and definitely easier to adjust to your own build.

"Don't keep this curiousity door locked."

### Hardware
- Arduino UNO
- WS2811 Individually Addressable RGB LED Strand 5V
 I bought [this one](https://www.amazon.com/gp/product/B01AG923GI) for $16 but any WS2811 5V strand should work.
- Optional: nRF8001


### Setup
The LED strand is mounted on a posterboard with letters A-Z painted on it. Connect one end of the LED strand to the Arduino. Power to 5V, Ground to GND, and Signal to PIN 6 or whatever pin you want to use. Some people recommend a separate power source for the LEDs but I wanted mine to be portable and think it's bright enough running from the Arduino power.

The led to letter mapping is set in the `setup_led_letters()` function. Set the value to the index (zero-based) of the LED for each letter.
````
led_alpha[0] = 43;    // A is the 44th led in the strand
led_alpha[1] = 42;    // B is the 43rd led in the strand
led_alpha[2] = 40;    // C is the 41st led in the strand
````

Flash the program to your Arduino and the lights should start. It's setup to randomly cycle through a bunch of different patterns including Christmas Lights, Halloween Lights, crazy flashing, and of course spelling out words. I power mine with a USB power bank to keep it portable.


### Bluetooth Low-Energy Setup
I added an nRF8001 bluetooth le module to allow the wall to be controlled from my phone. If wired in like in the code the module will start advertising with the name STRANGE when it powers up. If you connect with a Bluetooth LE Serial app you should be able to send ascii characters that will then be displayed in sequence.