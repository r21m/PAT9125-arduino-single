//
#ifndef PAT9125_H
#define PAT9125_H
//

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

// PAT9125 Registers
#define PAT9125_PID1            0x00
#define PAT9125_PID2            0x01
#define PAT9125_MOTION          0x02
#define PAT9125_DELTA_XL        0x03//
#define PAT9125_DELTA_YL        0x04//
#define PAT9125_MODE            0x05
#define PAT9125_CONFIG          0x06
#define PAT9125_WP              0x09
#define PAT9125_SLEEP1          0x0a
#define PAT9125_SLEEP2          0x0b
#define PAT9125_RES_X           0x0d
#define PAT9125_RES_Y           0x0e
#define PAT9125_DELTA_XYH       0x12
#define PAT9125_SHUTTER         0x14
#define PAT9125_FRAME           0x17
#define PAT9125_ORIENTATION     0x19
#define PAT9125_BANK_SELECTION  0x7f
//
class PAT9125
{
  public:
    explicit PAT9125(uint8_t addr);

    void pat9125_init();
    void pat9125_reset();

    long pat9125_x = 0;
    long pat9125_y = 0;
    long pat9125_x2 = 0;
    long pat9125_y2 = 0;
    int8_t pat9125_b = 0;//Brightness
    int8_t pat9125_s = 0;//Shutter
     
    void pat9125_set_res(uint8_t xres, uint8_t yres,bool bitres12 = false);
    void pat9125_set_res_x(uint8_t xres);
    void pat9125_set_res_y(uint8_t yres);
    bool pat9125_read_pid();
    void pat9125_update();
    void pat9125_update_x2();
    void pat9125_update_x();
    void pat9125_update_y2();
    void pat9125_update_y();
    void pat9125_serial_echo();
    
    bool pat9125_read_test();

    uint8_t pat9125_PID1; //product ident
    uint8_t pat9125_PID2; //product ident
    
    private:
    
    uint8_t _addr;
    uint8_t _xres;
    uint8_t _yres;
    //internal
    uint8_t ucMotion;
    uint8_t ucXL;
    uint8_t ucYL;
    uint8_t ucXYH;
    int8_t dy;
    int8_t dx; 
    int16_t iDX;
    int16_t iDY;
    
    //bool _inverse = false;
    bool _bitres12 = false;
    //
    uint16_t read_reg(uint8_t reg);
    void write_reg(uint8_t reg, uint8_t _data);
    uint16_t pat9125_wr_reg_verify(uint8_t reg, uint16_t _data);
};

#endif
//
// END OF FILE
//
