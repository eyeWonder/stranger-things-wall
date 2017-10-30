void check_bluetooth_le() {
  // Tell the nRF8001 to do whatever it should be working on.
  ble_serial.pollACI();

  // Ask what is our current status
  aci_evt_opcode_t status = ble_serial.getState();
  // If the status changed....
  if (status != ble_last_status) {
    // print it out!
    if (status == ACI_EVT_DEVICE_STARTED) {
        Serial.println(F("* Advertising started"));
    }
    if (status == ACI_EVT_CONNECTED) {
        Serial.println(F("* Connected!"));
    }
    if (status == ACI_EVT_DISCONNECTED) {
        Serial.println(F("* Disconnected or advertising timed out"));
    }
    // OK set the last status change to this one
    ble_last_status = status;
  }

  if (status == ACI_EVT_CONNECTED) {
    // Lets see if there's any data for us!
    if (ble_serial.available()) {
      Serial.print("* "); Serial.print(ble_serial.available()); Serial.println(F(" bytes available from ble_serial"));

      // OK while we still have something to read, get a character and print it out
      byte idx = 0;
      strcpy(letters, "");
      while (ble_serial.available()) {
        char c = ble_serial.read();
        if(is_char(c)) {
          Serial.print(c);
          letters[idx] = c;
        }
        idx++;
      }
      letters[idx] = 0;
      run_command();
    }
  }
}

bool is_char(char c) {
  if(c < 65)
    return false;
  else if(c > 122)
    return false;
  else if(c > 90 && c < 97)
    return false;
  else
    return true;
}


void check_serial() {
  if(Serial.available() > 0) {
    byte idx = 0;
    strcpy(letters, "");
    while (Serial.available()) {
      char c = Serial.read();
      if(is_char(c)) {
        Serial.print(c);
        letters[idx] = c;
      }
      idx++;
      delay(10);
    }
    letters[idx] = 0;
    run_command();
  }
}

void run_command() {
    state = State_Words;
    state_complete = false;
    Serial.println();

    Serial.print("letters length: ");
    Serial.println(strlen(letters));
    if(strlen(letters) == 1) {
      Serial.println(letters[0]);
      switch(letters[0]) {
        case 'c':
          state = State_Christmas;
          break;
        case 'h':
          state = State_Halloween;
          break;
        case 'r':
          state = State_Red;
          break;
        case 'f':
          state = State_Flash;
          break;
        case 's':
          state = State_Chase;
          break;
        case 'w':
          state = State_Words;
          letter_index = 0;
          strcpy(letters, "");
          break;
        case 'z':
          state = State_NotSet;
          break;
      }
      if(state != State_Words)
        strcpy(letters, "");
    }
}

