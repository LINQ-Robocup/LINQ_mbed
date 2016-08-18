#ifndef MY_TPA_H
#define MY_TPA_H

class TPA81{
public:
    TPA81(PinName, PinName);
    void setAddress(char);
    int getTempAt();
    int getTemp(short);
protected:
    int _aTemp;
    int _temp[8];
    I2C _TPA;
    char _addr;
    char _cmd[2];
    float _delay;
};

#endif