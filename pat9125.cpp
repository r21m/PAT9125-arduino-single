#include "pat9125.h"
#include <Wire.h>

PAT9125::PAT9125(uint8_t addr) {
  _addr = addr;
  //_xres = xres;
  //_yres = yres;
}

void PAT9125::pat9125_init() {
  Wire.begin();
  write_reg(PAT9125_CONFIG, 0x97); // reset 
}

bool PAT9125::pat9125_read_pid(){
  pat9125_PID1 = read_reg(PAT9125_PID1);//0x31 = 49dec
  pat9125_PID2 = read_reg(PAT9125_PID2);//0x91 = 145dex
  if ((pat9125_PID1 == 0x31) && (pat9125_PID2 == 0x91)) return true;
  else return false; 
}

void PAT9125::pat9125_set_res(uint8_t xres, uint8_t yres) {
  //write_reg(PAT9125_ORIENTATION, 0x04);//12bit resolution
  write_reg(PAT9125_RES_X, xres);
  write_reg(PAT9125_RES_Y, yres);
}

bool PAT9125::pat9125_read_test(){
  
  pat9125_b = read_reg(PAT9125_FRAME);
  pat9125_s = read_reg(PAT9125_SHUTTER);
  
  if ((pat9125_s == -1) or (pat9125_b == -1))
  return true;
  
}


void PAT9125::pat9125_update() {
  ucMotion = read_reg(PAT9125_MOTION);
  pat9125_b = read_reg(PAT9125_FRAME);
  pat9125_s = read_reg(PAT9125_SHUTTER);
  if (ucMotion & 0x80)
  {
    ucXL = read_reg(PAT9125_DELTA_XL);
    ucYL = read_reg(PAT9125_DELTA_YL);
    ucXYH = read_reg(PAT9125_DELTA_XYH);

    //pat9125_x2 += ucXL;
    //pat9125_y2 -= ucYL;
    
    iDX = ucXL | ((ucXYH << 4) & 0xf00);
    //if(iDX & 0x800)    iDX |= 0xfffff000;//16bit resolution
    iDY = ucYL | ((ucXYH << 8) & 0xf00);
    //if(iDY & 0x800)    iDY |= 0xfffff000;//16bit resolution
    
    
    if (iDX & 0x800) iDX -= 4096;
    if (iDY & 0x800) iDY -= 4096;

    pat9125_x += iDX;
    pat9125_y -= iDY;    
  }
}

void PAT9125::pat9125_update_y() {
  ucMotion = read_reg(PAT9125_MOTION);
  if (ucMotion & 0x80)
  {
    ucYL = read_reg(PAT9125_DELTA_YL);
    ucXYH = read_reg(PAT9125_DELTA_XYH);
    iDY = ucYL | ((ucXYH << 8) & 0xf00);
    if (iDY & 0x800) iDY -= 4096;
    pat9125_y -= iDY;
  }
}

void PAT9125::pat9125_update_y2()
{
  ucMotion = read_reg(PAT9125_MOTION);
  if (ucMotion & 0x80) {
    dy = read_reg(PAT9125_DELTA_YL);
    pat9125_y2 -= dy;
  }
}

void PAT9125::pat9125_update_x() {
  ucMotion = read_reg(PAT9125_MOTION);
  if (ucMotion & 0x80)
  {
    ucXL = read_reg(PAT9125_DELTA_XL);
    ucXYH = read_reg(PAT9125_DELTA_XYH);
    iDX = ucXL | ((ucXYH << 4) & 0xf00);
    if (iDX & 0x800) iDX -= 4096;
    pat9125_x += iDX;
  }
}

void PAT9125::pat9125_update_x2()
{
  ucMotion = read_reg(PAT9125_MOTION);
  if (ucMotion & 0x80) {
    dx = read_reg(PAT9125_DELTA_XL);
    pat9125_x2 += dx;
  }
}

//----PRIVATE----
void PAT9125::write_reg(uint8_t reg, uint16_t _data) {
  uint8_t _reg = reg;
  //Wire.begin();
  Wire.beginTransmission(_addr);
  Wire.write(_reg);
  Wire.write(_data);
  Wire.endTransmission();
  delay(1);
}

uint16_t PAT9125::read_reg(uint8_t reg) {
  uint8_t _reg = reg;
  Wire.beginTransmission(_addr);
  Wire.write(_reg);
  Wire.endTransmission();
  Wire.requestFrom(_addr, 4);
  uint8_t c = Wire.read();
  Wire.endTransmission();
  delay(1);
  return c;
}
