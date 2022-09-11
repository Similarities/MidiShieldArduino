int NOTE_ON = 9;
int NOTE_OFF = 8;
int CC = 11;

void setup() {
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  Serial.begin(31250);

  sendMidi (NOTE_ON, 11, 40, 40);
  delay(300);
  sendMidi (NOTE_OFF, 11, 40, 40);
}



void sendMidi (int type, int ch, int v0, int v1) {
  Serial.write ((type<<4)+ch);
  Serial.write (v0);
  Serial.write (v1);
}

int noteOn = 0;
int s = 0;
int values[8] = {50, 62, 50, 63, 50, 62, 53, 65};
int tmp = 0;
int cnt = 0;
int thresh = 20;
int lastVal2 = 0;
int currentNote = 0;
void loop() {

 
  int value = analogRead(A1);
  int val2 = analogRead(A5)/5;
 
  if (lastVal2 != val2)
    digitalWrite (7, HIGH);
  else 
    digitalWrite (7, LOW);
  lastVal2 = val2;
      
  if (value > thresh)
    digitalWrite (6, HIGH);
  else 
    digitalWrite (6, LOW);

  delay(1);
  if (value>thresh && noteOn==0){
    
    currentNote = values[cnt]-20;
    sendMidi (NOTE_ON, 11, currentNote, 10);
    tmp = val2+5;
    noteOn=1;
    digitalWrite (7, HIGH);
    cnt = (cnt+1)%8;
  }
  
  if (tmp<=0 && noteOn==1) {
    sendMidi (NOTE_OFF, 11, currentNote, 40);
    tmp=0;
    noteOn = 0;
    digitalWrite (7, LOW);
  }
  tmp -= 1; 
}
