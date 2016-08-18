#include "mbed.h"
#include "TPA81.h"



TPA81::TPA81(PinName mysda, PinName myscl): _TPA(mysda,myscl) {
    _delay = 51;
    _addr = 0xD2;
}

void TPA81::setAddress(char inAddr) {

}

int TPA81::getTempAt() {
    _cmd[0] = 1;
    _cmd[1] = 1;

    _TPA.write(_addr, _cmd, 2);
    _TPA.read(_addr, _cmd, 1);

    return _cmd[0];
}

int TPA81::getTemp(short i) {
    _cmd[0] = i;
    _cmd[1] = i;

    _TPA.write(_addr, _cmd, 2);
    _TPA.read(_addr, _cmd, 1);

    return _cmd[0];
}