#include "mbed.h"
#include <VL6180x.h>
#include <TPA81.h>
#include <SRF05.h>
#include <PCA9547.h>

int main() {
    Timer timer;
    TPA81 temp(D4, D5);
    VL6180x sonar(D4, D5, 0x29 << 1);
    SRF05 usonic(D11, D12);
    PCA9547 mux(D4, D5, 0xE0);

    Serial pc(USBTX, USBRX);
    Serial rs(PA_9, PA_10);
    pc.baud(9600);
    mux.select(0);
    
    sonar.VL6180xInit();
    sonar.VL6180xDefautSettings();
    
    uint8_t ir;
    float usonicval;
    int temp1;
    int temp2;
    int temp3;
    int temp4;
    
    DigitalOut rs485SW(D5);
    rs485SW = 1;
    while(1) {
        rs.putc(3);
//        printf("%d \n", rs.getc());
    }
        
    while(1) {
        ir = sonar.getDistance();
        usonicval = usonic.read();
        mux.select(0);
        temp1 = temp.getTemp(4);
        temp2 = temp.getTemp(5);
        mux.select(4);
        temp3 = temp.getTemp(4);
        temp4 = temp.getTemp(5);
        
        printf("IR: %4d, USonic: %3.2f, Temp1_1: %4d, Temp1_2: %4d, Temp1_Avg: %4d, Temp2_1: %4d, Temp2_2: %4d, Temp2_Avg: %4d\n", ir, usonicval, temp1, temp2, (temp1+temp2)/2, temp3, temp4, (temp3+temp4)/2);
        
    }
    
    /* measure TPA81 read speed(about 1ms/read)
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
    */
}
