#include <Adafruit_CircuitPlayground.h>
#include <Dictionary.h>

struct Note {
  int pin1;
  int pin2;
  double freq1;
  double freq2;
  int color1[3];
  int color2[3];
  int neoPixIdx1;
  int neoPixIdx2; 
  int capPin1;
  int capPin2;
};

struct Note note1 = {0, 2, 523., 587., {255, 152, 1}, {185, 187, 0},1,3,0,0};
struct Note note2 = {2, 3, 659., 698.5, {115, 221, 0},  {45, 255, 0},3,4,0,0};
struct Note note3 = {3, 10, 784., 880., {30, 255, 85}, {1, 255, 255},4,5,0,0};
struct Note note4 = {10, 9, 988.,1046.5, {14, 255, 255}, {28, 135, 255},5,6,0,0};
struct Note note5 = {9, 6, 1175., 1318.5,{43, 0, 255}, {184, 0, 221},6,8,0,0};
struct Note note6 = {6, 6, 1397., 1397., {113, 0, 107}, {113, 0, 107},8,8,0,0};
//struct Note note6 = {6, 12, 1046.5,1109., { 255, 152, 1}, {185, 187, 6}};
//struct Note note7 = {12, 12, 1175., 1244.5, {115, 221, 0}, {45, 255, 7}};
//struct Note note8 = {8, 9, 1318.5, 1397.,{30, 255, 85}, {1, 255, 255}};
//struct Note note9 = {9, 9, 1480., 1480., {14, 255, 255}, {14, 255, 255}};
Note tabNotes[] = {note1, note2, note3, note4, note5, note6};

#define CAP_THRESHOLD   20
#define DEBOUNCE        250
const int speaker = 5; 
long timeInMilliseconds = 2000;

boolean capButton(uint8_t pad) {
  if (CircuitPlayground.readCap(pad) > CAP_THRESHOLD) {
    //Serial.println(CircuitPlayground.readCap(pad));
    return true;  
  } else {
    return false;
  }
}

void setup() {
  CircuitPlayground.begin();
  pinMode(speaker, OUTPUT);
}

void loop() {
  for(int i =0; i<6; i++)
  {
    while( capButton(tabNotes[i].pin1)==1 )
    {
      while( capButton(tabNotes[i].pin2)==1 and capButton(tabNotes[i].pin1)==1)
      {
        //CircuitPlayground.setPixelColor(tabNotes[i].neoPixIdx2, tabNotes[i].color2);
        makeTone(speaker,tabNotes[i].freq2,timeInMilliseconds);
        //Serial.println(CircuitPlayground.readCap(tabNotes[i].pin1));
        //Serial.println("cap button pin 1:");
        //Serial.println(capButton(tabNotes[i].pin1));
        //Serial.print(tabNotes[i].pin1);
        //Serial.print(" ");
        //Serial.println(tabNotes[i].pin2);
        //Serial.println(CircuitPlayground.readCap(tabNotes[i].pin1));
        //Serial.println();
        //break;
      }
      while( capButton(tabNotes[i].pin2)==0 and capButton(tabNotes[i].pin1)==1)
      {
        //CircuitPlayground.setPixelColor(tabNotes[i].neoPixIdx1, tabNotes[i].color1);
        makeTone(speaker,tabNotes[i].freq1,timeInMilliseconds);
        //Serial.println(tabNotes[i].pin1);
        //Serial.println("cap button pin 1:");
        
        //Serial.println(capButton(tabNotes[i].pin1));
        //Serial.println(CircuitPlayground.readCap(tabNotes[i].pin1));
        //Serial.println();
        //Serial.println("cap button pin 2:");
        //Serial.println(capButton(tabNotes[i].pin2));
        //break;
      }
    }
    
  }
  
  CircuitPlayground.clearPixels();
  //Serial.println("delay");
  delay(60);
}

void makeTone (unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds) {
  int x;   
  long delayAmount = (long)(1000000/frequencyInHertz);
  long loopTime = (long)((timeInMilliseconds*100)/(delayAmount));
  for (x=0; x<loopTime; x++) {        // the wave will be symetrical (same time high & low)
     digitalWrite(speakerPin,HIGH);   // Set the pin high
     delayMicroseconds(delayAmount);  // and make the tall part of the wave
     digitalWrite(speakerPin,LOW);    // switch the pin back to low
     delayMicroseconds(delayAmount);  // and make the bottom part of the wave
  }  
}
