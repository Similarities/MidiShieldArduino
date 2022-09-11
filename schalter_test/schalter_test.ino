// midi codes for message type
int NOTE_ON = 9;
int NOTE_OFF = 8;
int CC_VOLUME = 11;
int CC = 11;

void setup() {
  
  // LED pins
  pinMode (6, OUTPUT);
  pinMode (7, OUTPUT);
  pinMode (A0, INPUT_PULLUP);
  
  // init serial port with midi baud rate
  //Serial.begin(31250);
  Serial.begin(57600);
}

void sendMidi (int type, int ch, int v0, int v1) {
  // build midi header from type and channel
  Serial.write ((type<<4)+ch);
  // Pitch (NOTE_ON) oder controler channel (CC)
  Serial.write (v0);
  // Velocity (NOTE_ON) oder  Wert (CC)
  Serial.write (v1);
}

uint8_t cnt[4] = {0,0,0,0};
uint8_t max = 4;

void button(uint8_t id) {
  cnt[id] = (cnt[id]+1)%max;
  
  if (cnt[0]==0) {
    digitalWrite(6,1);
    digitalWrite(7,0);
    Serial.write("0");
  }
  
  else if (cnt[0]==1) {
    digitalWrite(6,0);
    digitalWrite(7,1);
    Serial.write("1");
  }
  
  else if (cnt[0]==2) {
    digitalWrite(6,1);
    digitalWrite(7,0);
    Serial.write("2");
  }
  
  else if (cnt[0]==3) {
    digitalWrite(6,0);
    digitalWrite(7,1);
    Serial.write("3");
  }
  
}

int last[4] = {1,1,1,1};

void loop() {

  for (int i=0; i<4; i++) {
    int current = digitalRead(A0+i);

    if (current==0 && last[i]==1)
      button(i);
    last[i] = current;
  }

  delay(10);
}
