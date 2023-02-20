                                                                                                                  
volatile long ch[8];
int lastch[8];
unsigned long currenttime, lasttime[8];


void setup() {

  Serial.begin(9600);

  PCICR |= (1 << PCIE2);                 //enable pin change interrupts for portD(Digital 0-7) inside pin.change.interuupt control register                                                 
  PCMSK2 |= (1 << PCINT16);
  //PCMSK2 |= (1 << PCINT17);
  PCMSK2 |= (1 << PCINT18);
  //PCMSK2 |= (1 << PCINT19);
  PCMSK2 |= (1 << PCINT20);             // enable pin change interrupt for pin D2->D7
  PCMSK2 |= (1 << PCINT21);
  PCMSK2 |= (1 << PCINT22);
  PCMSK2 |= (1 << PCINT23);
  
}


void loop() {

  Serial.println("ch1: " + String(ch[0]) + "    " + "ch2: " + String(ch[1]) + "    " + "ch3: " + String(ch[2]) + "    " + "ch4: " + String(ch[3]) + "    " + "ch5: " + String(ch[4]) + "    " + "ch6: " + String(ch[5])+ "    " + "ch7: " + String(ch[6])+ "    " + "ch8: " + String(ch[7]) );

}

//RC Receiver capture input routine ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ISR(PCINT2_vect) {
  currenttime=micros();                                   //same principple as the ultrasonic sensor in obstacle avoidance
//CH1  ///////////////////////////////////////////
  if(PIND & B00000001){
    if(lastch[0] == 0){
      lastch[0]=1;
      lasttime[0]=currenttime;
    }
  }
  else if(lastch[0] == 1){
    lastch[0]=0;
    ch[0]=currenttime-lasttime[0];
  }
//CH2  ///////////////////////////////////////////
  /*if(PIND & B00000010){
    if(lastch[1] == 0){
      lastch[1]=1;
      lasttime[1]=currenttime;
    }
  }
  else if(lastch[1] == 1){
    lastch[1]=0;
    ch[1]=currenttime-lasttime[1];
  }*/
//CH3  ///////////////////////////////////////////
  if(PIND & B00000100){
    if(lastch[2] == 0){
      lastch[2]=1;
      lasttime[2]=currenttime;
    }
  }
  else if(lastch[2] == 1){
    lastch[2]=0;
    ch[2]=currenttime-lasttime[2];
  }
//CH4  ////////////////////////////////////////////
 /* if(PIND & B00001000){
    if(lastch[3] == 0){
      lastch[3]=1;
      lasttime[3]=currenttime;
    }
  }
  else if(lastch[1] == 1){
    lastch[3]=0;
    ch[3]=currenttime-lasttime[3];
  }*/
//CH5  /////////////////////////////////////////////
  if(PIND & B00010000){
    if(lastch[4] == 0){
      lastch[4]=1;
      lasttime[4]=currenttime;
    }
  }
  else if(lastch[4] == 1){
    lastch[4]=0;
    ch[4]=currenttime-lasttime[4];
  }
//CH6  /////////////////////////////////////////////
  if(PIND & B00100000){
    if(lastch[5] == 0){
      lastch[5]=1;
      lasttime[5]=currenttime;
    }
  }
  else if(lastch[5] == 1){
    lastch[5]=0;
    ch[5]=currenttime-lasttime[5];
  }
//CH7  //////////////////////////////////////////////
  if(PIND & B01000000){
    if(lastch[6] == 0){
      lastch[6]=1;
      lasttime[6]=currenttime;
    }
  }
  else if(lastch[6] == 1){
    lastch[6]=0;
    ch[6]=currenttime-lasttime[6];
  }
//CH8  //////////////////////////////////////////////
  if(PIND & B10000000){
    if(lastch[7] == 0){
      lastch[7]=1;
      lasttime[7]=currenttime;
    }
  }
  else if(lastch[7] == 1){
    lastch[7]=0;
    ch[7]=currenttime-lasttime[7];
  }
  
}
