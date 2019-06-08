
#include "pat9125.h"

PAT9125 PAT(0x75);
//

int to_reset = 0;

void setup() {
  Serial.begin(115200);
  PAT.pat9125_init();
  PAT.pat9125_set_res(240,240,true);
}

void serial_echo(){
    Serial.print(PAT.pat9125_x);
    Serial.print("\t");
    Serial.print(PAT.pat9125_y);
    Serial.print("\t");
    Serial.print(PAT.pat9125_b);
    Serial.print("\t");
    Serial.print(PAT.pat9125_s);
    Serial.print("\t");
    Serial.print(PAT.pat9125_x2);
    Serial.print("\t");
    Serial.println(PAT.pat9125_y2);
}

void loop() { 
  PAT.pat9125_update();
  PAT.pat9125_update_y2();
  PAT.pat9125_update_x2();

  delay(1);
  
  serial_echo();
  delay(500);
  if(to_reset > 20){
    Serial.println("reset!");
    PAT.pat9125_reset();
    to_reset = 0;
  }
  
  to_reset++;
}
