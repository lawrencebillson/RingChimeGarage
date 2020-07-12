/* 
Hack a Ring Chime to operate a garage door

Lawrence Billson, 2020

Inside the Ring Chime (old) - Arduino Nano

DC     -> Nano 5v
Gnd    -> Ground
TP15   -> Nano D2 - This contains serial audio data when the chime is triggered

To control a door - connect

Nano D3 to the garage door via an opto-isolator. 

*/


// Define pins

#define TP15 2
#define OPTO 3
#define INDICATOR LED_BUILTIN


// Global pulse count variable  
long int pulsecount = 0;


// AVR Timer CTC Interrupts Calculator
// v. 8
// http://www.arduinoslovakia.eu/application/timer-calculator
// Microcontroller: ATmega328P
// Created: 2020-07-07T07:52:23.506Z


void setupTimer1() {
  noInterrupts();
  // Clear registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  // 1 Hz (16000000/((15624+1)*1024))
  OCR1A = 15624;
  // CTC
  TCCR1B |= (1 << WGM12);
  // Prescaler 1024
  TCCR1B |= (1 << CS12) | (1 << CS10);
  // Output Compare Match A Interrupt Enable
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
}

void setup() {
  pinMode(TP15, INPUT);
  pinMode(OPTO, OUTPUT);
  pinMode(INDICATOR, OUTPUT);
  digitalWrite(OPTO,LOW);
  
  Serial.begin(115200);

  // Setup our interrupts
  setupTimer1();
  attachInterrupt(digitalPinToInterrupt(TP15), countp, RISING);

  // Print some debugging info
  Serial.println("Ring Chime - Garage Door hack - startng up");
}

void loop() {
 // Detect a 'chime' event - threshold is 5000 pulses in the one second
 if (pulsecount >> 5000) {   
   Serial.println("Detected Chime - sending an open pulse");
   digitalWrite(OPTO,HIGH);
   digitalWrite(INDICATOR,HIGH);
   delay(250);
   digitalWrite(OPTO,LOW);
   digitalWrite(INDICATOR,LOW);
   delay(15000); // fifteen second lockout
   Serial.println("Waiting for chime events");
  }
  

  
}

ISR(TIMER1_COMPA_vect) {
  Serial.print("Pulse count: ");
  Serial.println(pulsecount);
  pulsecount = 0;
}

void countp() {
  pulsecount++;
}
