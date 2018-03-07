#include <SPI.h>
#include <RFID.h>

#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN,RST_PIN);


int power = 7;
int led = 8; 
int serNum[5];
int currentByte;

enum State {WAIT,READY,WRITE,END,ERR};

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    SPI.begin();
    rfid.init();
}

State stepForward(State currentState) {
  switch(currentState) {
    case WAIT:
      return rfid.isCard() ? READY : WAIT;
    case READY:
      if(!rfid.readCardSerial())
        return ERR;
      //Serial.print("R");
      currentByte = 0;
      return WRITE;
    case WRITE:
      if(currentByte >= 5)
        return END;
      //if(Serial.read() == -1)
        //return WRITE;
      Serial.print(rfid.serNum[currentByte++]);
      return WRITE;
    case END:
      //if(Serial.read() == -1)
      //return END;
      //Serial.print("E");
      delay(2000);
      return WAIT;
    case ERR:
      //TODO: Send an error code
      return WAIT;
    default:
      return ERR;  
  }  
}

void loop() {
  // put your main code here, to run repeatedly:
  static State currentState = WAIT;
  currentState = stepForward(currentState);
  /*if(rfid.isCard()){
    if(rfid.readCardSerial()){
      Serial.print("RED");
      while(Serial.read() == -1);
      Serial.print(rfid.serNum[0]);
      while(Serial.read() == -1);
      Serial.print(rfid.serNum[1]);
      while(Serial.read() == -1);
      Serial.print(rfid.serNum[2]);
      while(Serial.read() == -1);
      Serial.print(rfid.serNum[3]);
      while(Serial.read() == -1);
      Serial.print(rfid.serNum[4]);
      while(Serial.read() == -1);
      Serial.print("END");  
    }
    rfid.halt();*/
  //}
}
