byte led_alpha[26];

void show_words(unsigned long now) {  
  static bool after_letter = false;
  
  if (now > animation_timer) {
    if(letter_index == 0) {
      Serial.println("Show word");
      Serial.println(letters);
      Serial.println(strlen(letters));
      FastLED.clear();
      // if letters is not set, select a random string from our list
      if(strlen(letters) == 0 || letters[0] == 0) {
        get_words();
      }
    }
    // if we have completed all the letters, turn off and reset
    if(letter_index >= strlen(letters) || letters[letter_index] == 0) {
      FastLED.show();
      state_complete = true;
      letter_index = 0;
      after_letter = false;
      strcpy(letters, "");
      wait_timer = now + random(5000, 10000);
    } else {
      if(after_letter) {
        FastLED.show();
        animation_timer = now + random(50, 200);
        after_letter = false;
      } else {
        // set the current letter
        char current_letter = letters[letter_index];
        // convert from ascii to 0-26
        byte idx = current_letter >= 97 ? current_letter-97 : current_letter-65;

        byte character_position = led_alpha[idx];
        leds[character_position] = get_color_by_index(character_position);
        letter_index++;
        
        animation_timer = now + random(1000, 2000);
        FastLED.show();

        leds[character_position] = CRGB::Black; // clear for the next time
        after_letter = true;
      }
    }
  }
}

#define SET_LETTERS(X) strcpy(letters, X);
void get_words() {
  // randomly select words from a predefined list
  byte index = random(0, 8);
  switch(index) {
    case 0:
      SET_LETTERS("IMHERE");
      break;
    case 1:
      SET_LETTERS("RUN");
      break;
    case 2:
      SET_LETTERS("HELP");
      break;
    case 3:
      SET_LETTERS("TRUNKORTREAT");
      break;
    case 4:
      SET_LETTERS("THEUPSIDEDOWN");
      break;
    case 5:
      SET_LETTERS("WILLBYERS");
      break;
    case 6:
      SET_LETTERS("ELEVEN");
      break;
    case 7:
      SET_LETTERS("MIRKWOOD");
      break;
  }
  Serial.println(letters);
}

void setup_led_letters() {
//  // set each letter to the index on the strand that lines up with it
  led_alpha[0] = 43;    // A
  led_alpha[1] = 42;    // B
  led_alpha[2] = 40;    // C
  led_alpha[3] = 38;    // D
  led_alpha[4] = 37;    // E
  led_alpha[5] = 36;    // F
  led_alpha[6] = 34;    // G
  led_alpha[7] = 33;    // H
  led_alpha[8] = 16;    // I
  led_alpha[9] = 18;    // J
  led_alpha[10] = 20;   // K
  led_alpha[11] = 21;   // L
  led_alpha[12] = 23;   // M
  led_alpha[13] = 24;   // N
  led_alpha[14] = 25;   // O
  led_alpha[15] = 27;   // P
  led_alpha[16] = 29;   // Q
  led_alpha[17] = 12;   // R
  led_alpha[18] = 10;   // S
  led_alpha[19] = 9;    // T
  led_alpha[20] = 7;    // U
  led_alpha[21] = 6;    // V
  led_alpha[22] = 5;    // W
  led_alpha[23] = 4;    // X
  led_alpha[24] = 3;    // Y
  led_alpha[25] = 1;    // Z
}
