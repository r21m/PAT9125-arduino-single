
#include "pat9125.h"

PAT9125 PAT(0x75);
//
void setup() {
  Serial.begin(115200);
  PAT.pat9125_init();
  PAT.pat9125_set_res(240,240);
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
  PAT.pat9125_update_y();
  delay(1);
  
  serial_echo();
  delay(1000);
}
