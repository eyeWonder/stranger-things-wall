/* 
 Stranger Things Lights
 
 Created Oct 17, 2017
 by Teddy Bort
 */
 
#include <FastLED.h>
#include <Adafruit_BLE_UART.h>
#include <SPI.h>

// hardware defines
#define NUM_LEDS 50
#define PIN_LED_DATA 6
#define PIN_BLE_REQ 10
#define PIN_BLE_RDY 2     // This should be an interrupt pin, on Uno thats #2 or #3
#define PIN_BLE_RST 9
// Connect CLK/MISO/MOSI to hardware SPI
// e.g. On UNO & compatible: CLK = 13, MISO = 12, MOSI = 11

// application defines


CRGB leds[NUM_LEDS];
Adafruit_BLE_UART ble_serial = Adafruit_BLE_UART(PIN_BLE_REQ, PIN_BLE_RDY, PIN_BLE_RST);
aci_evt_opcode_t ble_last_status = ACI_EVT_DISCONNECTED;

enum States {
  State_NotSet,
  State_Christmas,
  State_Halloween,
  State_Red,
  State_Flash,
  State_Chase,
  State_Words,
};
States state = State_NotSet;
//States state = State_Chase;
bool state_complete = false;
unsigned long wait_timer = 0;
unsigned long animation_timer = 0;

char letters[50];
byte letter_index = 0;

const char compile_date[] = __DATE__ " " __TIME__;

void setup() {
  // seed random numbers to make more random
  randomSeed(analogRead(0));
  
  // setup leds
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  FastLED.addLeds<WS2811, PIN_LED_DATA, RGB>(leds, NUM_LEDS);
  setup_led_letters();  // defines which leds map to with letters
  
  // setup bluetooth
  ble_serial.setDeviceName("Strange"); /* 7 characters max! */
  ble_serial.begin();

  // setup serial and output app info
  Serial.begin(9600);
  while(!Serial); // Leonardo/Micro should wait for serial init
  Serial.println(F("Stranger Things Lights..."));
  Serial.println(compile_date);
  Serial.println();

  FastLED.clear();
}

void loop() {
  check_bluetooth_le();
  check_serial();

  unsigned long now = millis();

  if(!state_complete && state != State_NotSet) {
    switch(state) {
      case State_Red:
        show_red_lights(now);
        break;
      case State_Flash:
        show_flash(now);
        break;
      case State_Chase:
        show_chase(now);
        break;
      case State_Words:
        show_words(now);
        break;
      case State_Halloween:
        show_halloween_lights(now);
        break;
      case State_Christmas:
      default:
        show_christmas_lights(now);
        break;
    }
  } else {
    // if state is complete, see if it has requested a wait period otherwise transition to next state
    if(wait_timer > 0) {
      if(now > wait_timer) {
        wait_timer = 0;
      }
    } else {
      state_complete = false;
      state = random(State_Christmas, (State_Words+1));
//      state = State_Halloween;
      Serial.print("State: ");
      Serial.println(get_state_name());
    }
  }
}

char* get_state_name() {
  switch(state) {
    case State_Red:
      return "Red lights";
    case State_Flash:
      return "Flashing lights";
    case State_Chase:
      return "Chase lights";
    case State_Words:
      return "Words";
    case State_Halloween:
      return "Halloween lights";
    case State_Christmas:
      return "Christmas lights";
    default:
      return "Unknown";
  }
}

