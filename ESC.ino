#define M0 PB0
#define M1 PB1
#define M2 PB2
#define M3 PB3

int ESC1, ESC2, ESC3, ESC4, output1=1000, output2=1000, output3=1000, output4=1000;
long MIN_Timer1 = 16384, MIN_Timer2 = 64, MAX_Timer1 = 32768, MAX_Timer2 = 128 ;

void setup() {
  DDRB |= ( ( 1<<M0 ) | ( 1<<M1 ) | ( 1<<M2 ) | ( 1<<M3 ) );
  
  Serial.begin(9600);
 sei();                                           // set global interrupt enable 
  
  TCCR1A = 0;                                                                       
  TCCR1B = 0;                                                                       
  TCCR1B &= ~(1<<CS12);                                                              
  TCCR1B &= ~(1<<CS11);                                                             
  TCCR1B |= (1<<CS10);                                                            
  TIMSK1 |= (1<<OCIE1A);                                                    
  TIMSK1 |= (1<<OCIE1B);                                                                              
  TIMSK1 |= (1<<TOIE1);                                             
 

  TCCR2A = 0;                                               
  TCCR2B = 0;                                                             
  TCCR2B |= (1<<CS22);                                                      
  TCCR2B |= (1<<CS21);                                                   
  TCCR2B &= ~(1<<CS20);                                                                    
  TIMSK2 |= (1<<OCIE2A);                                                                  
  TIMSK2 |= (1<<OCIE2B);                                                                
  TIMSK2 |= (1<<TOIE2);                                                                     
  
  OCR2A = MAX_Timer2;                                                         
  OCR2B = MAX_Timer2;                                                           
  OCR1A = MAX_Timer1;                                                               
  OCR1B = MAX_Timer1;                                                           
  
  TCNT2 = 0;                                                                              
  TCNT1 = 0;                    
  
}

void loop() {
if(Serial.available()>0){
 output1 = Serial.parseInt();
 output2 = output1;
 output3 = output1;
 output4 = output1; 
 }

 ESC1 = mapp(output1,1000,2000,MIN_Timer1,MAX_Timer1); 
 ESC2 = mapp(output2,1000,2000,MIN_Timer1,MAX_Timer1);  
 ESC3 = mapp(output3,1000,2000,MIN_Timer2,MAX_Timer2); 
 ESC4 = mapp(output4,1000,2000,MIN_Timer2,MAX_Timer2);  


Serial.println(String(ESC1) + "   " + String(output1));
    
  
}




ISR(TIMER1_COMPA_vect){
  PORTB &= ~(1<<M0);
}


ISR(TIMER1_COMPB_vect){
  PORTB &= ~(1<<M1);
}


ISR(TIMER2_COMPA_vect){
  PORTB &= ~(1<<M2);
}

ISR(TIMER2_COMPB_vect){
  PORTB &= ~(1<<M3);
}


ISR(TIMER2_OVF_vect){
  PORTB |= (1<<M2);
  PORTB |= (1<<M3);

      
  OCR2A = ESC3;     
  OCR2B = ESC4;  

}

ISR(TIMER1_OVF_vect){
  PORTB |= (1<<M0);
  PORTB |= (1<<M1);

  OCR1A = ESC1;       
  OCR1B = ESC2;
}

float mapp(float var, float min1, float max1, float min2, float max2){
  return min2 + (var-min1)*(max2-min2)/(max1-min1);
}




