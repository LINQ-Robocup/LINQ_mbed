#include "mbed.h"
#include <VL6180x.h>
#include <TPA81.h>
#include <SRF05.h>
#include <PCA9547.h>
#include <Servo.h>

PCA9547 mux(D4, D5, 0xE0);

int main() {
    
//    Timer timer;
//    TPA81 temp(D4, D5);
//    VL6180x sonar(D4, D5, 0x29 << 1);
//    SRF05 usonic(D11, D12);
//    PCA9547 mux(D4, D5, 0xE0);
//    Servo servo(PB_0);
//    PwmOut pwm(PB_0);

    Serial pc(USBTX, USBRX);
    Serial rs(PA_9, PA_10);
    pc.baud(9600);
    
    //温度センサのインスタンス作成
    mux.select(0);
    TPA81       temp2(D4, D5, 0xD2);
    mux.select(1);
    TPA81       temp(D4, D5, 0xD0);
    
    //IR距離センサのインスタンス作成
    mux.select(2);
    VL6180x     irDist(D4, D5, 0x29 << 1);
    irDist.VL6180xInit();
    irDist.VL6180xDefautSettings();
    
    mux.select(3);
    irDist.VL6180xInit();
    irDist.VL6180xDefautSettings();
    
    mux.select(4);
    irDist.VL6180xInit();
    irDist.VL6180xDefautSettings();  
    
    mux.select(5);
    irDist.VL6180xInit();
    irDist.VL6180xDefautSettings();  

    while(1) {
//        mux.select(0);
//        pc.printf("ir1=%d  %t", irDist.getDistance());
//        wait_ms(10);
//        mux.select(1);
//        pc.printf("ir2=%d  %t", irDist2.getDistance());
        mux.select(0);
        pc.printf("temp=%d  %t", temp2.getTemp(4));
        mux.select(1);
        pc.printf("temp2=%d  %t", temp.getTemp(4));
        mux.select(2);
        pc.printf("irDist=%d  %t", irDist.getDistance());
        mux.select(3);
        pc.printf("irDist2=%d  %t", irDist.getDistance());
        mux.select(4);
        pc.printf("irDist3=%d  %t", irDist.getDistance());
        mux.select(5);
        pc.printf("irDist4=%d  %t", irDist.getDistance());
        pc.printf("\n");
    }
//    for(int i = 0; i < 4; i++) {
//        mux.select(i);
//        wait_ms(10);
//        irDist.VL6180xInit();
//        irDist.VL6180xDefautSettings();
//    }
        
//    while(1) {
//        for(int i = 0; i < 4; i++) {
//            mux.select(i);
//            wait_ms(10);
//            pc.printf("ir%d=%d     %t", i, irDist.getDistance());
//        }
//        pc.printf("\n");
//    }

//    while(1) {
//        ir = sonar.getDistance();
//        usonicval = usonic.read();
//        mux.select(0);
//        temp1 = temp.getTemp(4);
//        temp2 = temp.getTemp(5);
//        mux.select(4);
//        temp3 = temp.getTemp(4);
//        temp4 = temp.getTemp(5);
//
//        printf("IR: %4d, USonic: %3.2f, Temp1_1: %4d, Temp1_2: %4d, Temp1_Avg: %4d, Temp2_1: %4d, Temp2_2: %4d, Temp2_Avg: %4d\n", ir, usonicval, temp1, temp2, (temp1+temp2)/2, temp3, temp4, (temp3+temp4)/2);
//
//    }
}

//    rs.baud(115200);
//    DigitalOut rs485SW(D5);
//    rs485SW = 1;
//    int8_t rstemp =-5;
//    char send = (char)rstemp;

