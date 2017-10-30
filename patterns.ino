void show_christmas_lights(unsigned long now) {
  // christmas lights
  for(byte i=0; i<NUM_LEDS;i++) {
    leds[i] = get_color_by_index(i);
  }
  FastLED.show();
  state_complete = true;
  int wait_seconds = random(20, 30);
  wait_timer = now + (wait_seconds*1000);
  Serial.print("Waiting ");
  Serial.print(wait_seconds);
  Serial.println(" seconds...");
}

void show_halloween_lights(unsigned long now) {
  // halloween lights
  for(byte i=0; i<NUM_LEDS;i++) {
    //leds[i] = CRGB::Orange;
    leds[i] = CRGB(255, 25, 0);
  }
  FastLED.show();
  state_complete = true;
  int wait_seconds = random(20, 30);
  wait_timer = now + (wait_seconds*1000);
  Serial.print("Waiting ");
  Serial.print(wait_seconds);
  Serial.println(" seconds...");
}

void show_red_lights(unsigned long now) {
  // red lights
  static byte red = 0;
  static bool dir_up = true;
  static byte counter = 0;
  
  if(now >= animation_timer) {
    animation_timer = now + 50;
    for(byte i=0; i<NUM_LEDS;i++) {
      leds[i] = CRGB(red, 0, 0);
    }
    red = red + (dir_up ? 1 : -1);
    FastLED.show();
  }

  if(dir_up && red >= 255) {
    dir_up = false;
  } else if(!dir_up && red <= 20) {
    counter++;
    dir_up = true;

    if(counter >= 5) {
      red = 0;
      counter = 0;
      state_complete = true;
    }
  }
}

void show_flash(unsigned long now) {
  // flash
  static byte counter = 0;
  
  if(now >= animation_timer) {
    for(byte i=0; i<NUM_LEDS;i++) {
      bool flash_on = random(2) > .5;
      leds[i] = flash_on ? get_color_by_index(i) : CRGB::Black;
      animation_timer = now + random(50,100);
    }
//    flash_off = !flash_off;
    FastLED.show();

    if(++counter > 100) {
      FastLED.clear();
      counter = 0;
      state_complete = true;
    }
  }
}

void show_chase(unsigned long now) {
  static byte index = 0xFF;
  if(index == 0xFF) {
    FastLED.clear();
    index = NUM_LEDS-1;
    Serial.println(index);
  }
  
  if(now >= animation_timer) {
    leds[index] = get_color_by_index(index);
    animation_timer = now + random(100, 500);
    FastLED.show();

    if(index == 0) {
      state_complete = true;
      index = 0xFF;
    } else
      index--;
  }
}

CRGB get_color_by_index(byte index) {
  switch(index%10) {
    case 0:
      return CRGB(0,255,255);     // aqua
    case 1:
      return CRGB(153, 50, 204);  // dark orchid
    case 2:
      return CRGB(255, 255, 0);   // yellow
    case 3:
      return CRGB(0, 255, 127);   // spring green
    case 4:
      return CRGB(255, 165, 0);   // orange
    case 5:
      return CRGB(65, 105, 255);  // royal blue
    case 6:
      return CRGB(76, 0, 153);    // dark purple
    case 7:
      return CRGB(255, 105, 180); // hot pink
    case 8:
      return CRGB(0, 128, 0);     // dark green
    case 9:
      return CRGB(255, 0, 0);     // red
  }
  return CRGB::Black;
}
