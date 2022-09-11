// midi codes for message type
int NOTE_ON = 9;
int NOTE_OFF = 8;
int CC_VOLUME = 11;
// CC is the output Midi channel ? 
int CC = 1;
int CC2 = 0;

void setup() {
  // LED pins
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  
  // init serial port with midi baud rate
  Serial.begin(31250);

  sendMidi2 (NOTE_ON, 0, 40, 40);
  delay(300);
  sendMidi2 (NOTE_OFF, 0, 40, 40);
  sendMidi (NOTE_ON, 1, 40, 40);
  delay(300);
  sendMidi (NOTE_OFF, 1, 40, 40);
  

  Serial.print("hello world");
}



void sendMidi (int type, int ch, int v0, int v1) {
  // build midi header from type and channel
  Serial.write ((type<<4)+0);
  // Pitch (NOTE_ON) oder controler channel (CC)
  Serial.write (40);
  // Velocity (NOTE_ON) oder  Wert (CC)
  Serial.write (40);
  Serial.flush(); 
}


void sendMidi2 (int type, int ch, int v0, int v1) {
  // build midi header from type and channel
  Serial.write ((type<<4)+1);
  //Serial.print("sendMidi2",ch)
  // Pitch (NOTE_ON) oder controler channel (CC)
  Serial.write (40);
  // Velocity (NOTE_ON) oder  Wert (CC)
  Serial.write (40);
  Serial.flush(); 
}

int s = 0;
int values[8] = {50, 62, 50, 63, 50, 62, 53, 65};

int noteOn = 0;
int tmp = 0;
int cnt = 0;
int thresh = 0;
int lastValue = 0;
int currentNote = 0;

int noteOn2 = 0;
int tmp2 = 0; 
int cnt2 = 0;
int thresh2 = 0; 
int lastValue2 = 0; 
int currentNote2 = 0;



void loop() {

 
  int value = analogRead(A4);
  int velocity = value;
  int value2 = analogRead(A2);
  int velocity2 = value2;
 
  if (lastValue != value)
    digitalWrite (7, HIGH);
  else 
    digitalWrite (7, LOW);
  lastValue = value;
      
  if (value > thresh)
    digitalWrite (6, HIGH);
  else 
    digitalWrite (6, LOW);


  if (value>thresh && noteOn==0){
    
    currentNote = values[cnt]-20;
    sendMidi (NOTE_ON, 1, currentNote, velocity);
    tmp = value+5;
    noteOn=1;
    digitalWrite (7, HIGH);
    cnt = (cnt+1)%8;
  }
  
  if (tmp<=0 && noteOn==1) {
    delay(0.5);
    sendMidi (NOTE_OFF, 1, currentNote, 40);
    sendMidi (CC, 1, CC_VOLUME, velocity);
    tmp=0; 
    noteOn = 0;
    digitalWrite (7, LOW);}

    delay(0.3);

// now comes the same for input Channel 2 to MidiChannel 2
// question is about the digital outputs ... needed for what?


 if (lastValue2 != value2)
      digitalWrite (7, HIGH);
    else 
    digitalWrite (7, LOW);
    lastValue2 = value2;
      
  if (value2 > thresh2)
    digitalWrite (6, HIGH);
  else 
    digitalWrite (6, LOW);

 delay(0.2);
  
  if (value2>thresh2 && noteOn2==0){
    
    currentNote2 = values[cnt2]-20;
    sendMidi2 (NOTE_ON, 0, currentNote2, velocity2);
    tmp2 = value2+5;
    noteOn2=1;
    digitalWrite (7, HIGH);
    cnt2 = (cnt2+1)%8;
    
  }
  
  if (tmp2<=0 && noteOn2==1) {
    delay(0.4);
    sendMidi2 (NOTE_OFF, 0, currentNote2, 40);
    sendMidi2 (CC2, 0, CC_VOLUME, velocity2);

    tmp2=0; 
    noteOn2 = 0;
    digitalWrite (7, LOW);
  }

  delay(0.3);
  tmp -= 1; 
  tmp2 -=1; 
  Serial.flush(); 
}
