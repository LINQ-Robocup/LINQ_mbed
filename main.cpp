#include "mbed.h"
#include <VL6180x.h>
#include <TPA81.h>



int main() {
    Timer timer;
    TPA81 temp(D4, D5);
    Serial pc(USBTX, USBRX);
    pc.baud(9600);
    wait_ms(500);
    
    int val;
    int val2;
    timer.reset();
    timer.start();
    
    for(int i = 0; i < 10000; i++){
        val = temp.getTemp(4);
        val2 = temp.getTemp(5);    
    }
    int time = timer.read_ms();
     
    while(1){
        printf("%d \n", time);
    }
}
