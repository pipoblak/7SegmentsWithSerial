 #include "SevSeg.h"
 SevSeg sevseg; //Instantiate a seven segment object

void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200);
   Serial.println("Serial ON");
   byte numDigits = 4;   
   // d1,d2,d3,d4
   byte digitPins[] = {11, 10, 9, 6};
   //a b c d e f g h
   byte segmentPins[] = {A1, 3, 4, 5, A0, 7, 8, 0};
   bool resistorsOnSegments = false; 
   byte hardwareConfig = COMMON_ANODE; // See README.md of SevSeg.h for options
   sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(Serial.available()>0){
     String recivedDataStr = "";
    char recivedChar;
    
    while (Serial.available() > 0) {
      recivedChar = Serial.read();
      if(recivedChar != '\n'){
         recivedDataStr.concat(recivedChar);
         delay(10);
      }
    }
    if(recivedDataStr.indexOf("$")>=0){
      Serial.println("COUNTER DEVICE");
    }
    if(recivedDataStr.indexOf("#")>=0){
      String strNumber= recivedDataStr.substring(recivedDataStr.indexOf("#")+1);
      Serial.println(strNumber);
      sevseg.setNumber( strNumber.toInt());
    }
    
  }
  
  sevseg.refreshDisplay(); // Must run repeatedly
}
