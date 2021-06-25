// Guit Arnet
// @RoniBandini
// June 2021
// Buenos Aires, Argentina

// Conexiones 
// Pot A2, A3 3v, GND
// Distance sensor D8, D9, VCC, GND
// Joystick A0, A1, VCC, GND
// LED D11 y D12

// Penta blues scale E: E G A A# B D E - 5tas B D E F F# A B
// Penta blues scale A: A C D D# E G A - 5tas E G A A# B D E

#define echoPin 8
#define trigPin 9
#define joyX A0
#define joyY A1
#define potPin A2
#define potPinEffect A3
#define ledGreen 12
#define ledYellow 11

int large=15;

// Midi notes
int myScaleE[] = {40, 43, 45, 46, 47, 50, 52};
int myScaleE5[] = {47, 50 , 52, 53, 54, 57, 59};

int myScaleA[] = {45, 48, 50, 51, 52, 55, 57};
int myScaleA5[] = {52, 55, 57, 58, 59, 62, 64};

void SendMidiToSerial (unsigned char word0, unsigned char word1, unsigned char word2) {
  Serial.write(word0);
  Serial.write(word1);
  Serial.write(word2);
}

void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}

void setup () {

  // distance sensor
  pinMode(trigPin, OUTPUT);    
  pinMode(echoPin, INPUT);

  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  
  Serial.begin(57600);

  // test Leds
  digitalWrite(ledGreen, HIGH);
  delay(1000);
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledYellow, HIGH);
  delay(1000);
  digitalWrite(ledYellow, LOW);
  
}


void loop () {   
   
 int xValue = analogRead(joyX);
 int yValue = analogRead(joyY);  

 int potValue = analogRead(potPin); 
 int effectValue = analogRead(potPinEffect);  

 int myScale=map(potValue,0,800,1,3); 
 int myEffect=map(effectValue,0,800,1,3); 

  /*
  Serial.println("X:");
  Serial.println(xValue);
  Serial.println("Y:");
  Serial.println(yValue);
  Serial.println("Pot:");
  Serial.println(potValue);
  Serial.println("Scale:");
  Serial.println(myScale);

  Serial.println("Effect:");
  Serial.println(effectValue);
  */
    

   // calculate distance
  digitalWrite(trigPin,LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);  
  float tiempo=pulseIn(echoPin, HIGH);
  float distancia= int(0.017*tiempo);
  
  // map distance to index
  int noteIndex=map(distancia,0,large,5,0);   
  
  if (myScale==1 and (yValue<50 or yValue>950)){

        digitalWrite(ledGreen, HIGH);
        
        int myNote=myScaleE[noteIndex];
    
        if (myNote>myScaleE[6]) myNote=myScaleE[6];
        if (myNote<myScaleE[0]) myNote=myScaleE[0];
    
        if (distancia>large) myNote=myScaleE[0];
    
        noteOn(0x90, myNote , 0x40);

        if (myEffect==2){
         // turn off note
         delay(15);
         noteOn(0x90, myNote, 0x00);
        }

   
    }   


    if (myScale==1 and (xValue<50 or xValue>950)){   

        digitalWrite(ledYellow, HIGH);
    
        int myNote=myScaleE[noteIndex];
        int myNote2=myScaleE5[noteIndex];
    
        if (myNote>myScaleE[6]) myNote=myScaleE[6];
        if (myNote<myScaleE[0]) myNote=myScaleE[0];

        if (myNote2>myScaleE5[6]) myNote2=myScaleE5[6];
        if (myNote2<myScaleE5[0]) myNote2=myScaleE5[0];
    
        if (distancia>large) myNote=myScaleE[0];
        if (distancia>large) myNote2=myScaleE5[0];
    
        noteOn(0x90, myNote , 0x40);
        noteOn(0x90, myNote2 , 0x40);

         if (myEffect==2){
         // turn off note
         delay(15);
         noteOn(0x90, myNote, 0x00);
         noteOn(0x90, myNote2 , 0x00);
        }        
   
    } 

     if (myScale==2 and (yValue<50 or yValue>950)){       

        digitalWrite(ledGreen, HIGH);
               
        int myNote=myScaleA[noteIndex];
    
        if (myNote>myScaleA[6]) myNote=myScaleA[6];
        if (myNote<myScaleA[0]) myNote=myScaleA[0];
    
        if (distancia>large) myNote=myScaleA[0];
    
        noteOn(0x90, myNote , 0x40);
        
       if (myEffect==2){
         // turn off note
         delay(15);
         noteOn(0x90, myNote, 0x00);
        }

   
    }   


    if (myScale==2 and (xValue<50 or xValue>950)){     

        digitalWrite(ledYellow, HIGH);
        
        int myNote=myScaleA[noteIndex];
        int myNote2=myScaleA5[noteIndex];
    
        if (myNote>myScaleA[6]) myNote=myScaleA[6];
        if (myNote<myScaleA[0]) myNote=myScaleA[0];

        if (myNote2>myScaleA5[6]) myNote2=myScaleA5[6];
        if (myNote2<myScaleA5[0]) myNote2=myScaleA5[0];
    
        if (distancia>large) myNote=myScaleA[0];
        if (distancia>large) myNote2=myScaleA5[0];
    
        noteOn(0x90, myNote , 0x40);
        noteOn(0x90, myNote2 , 0x40);
        
        if (myEffect==2){
         // turn off note
         delay(15);
         noteOn(0x90, myNote, 0x00);
         noteOn(0x90, myNote2 , 0x00);
        }

   
    }   

  delay(15);
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledYellow, LOW);
  
}
