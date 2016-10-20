#include "mbed.h"
#include <VL6180x.h>
#include <TPA81.h>
#include <SRF05.h>
#include <PCA9547.h>
#include <Servo.h>

//RS485インスタンス(複数の関数から使うためグローバル)
mbed::Serial rs(PA_9, PA_10);
mbed::DigitalOut rsSW(D3);

float sendData[] = {11, 22, 33, 44, 55, 66, 77};

//==============================================================
void SerialAvailavle()
{
	int getData = rs.getc();
	//	printf("%d\n", getData);
	//	wait_ms(1);
	rsSW = 1;
	if(getData < 7 && getData >= 0){
		for (int i = 0; i < 7; i++) {
			rs.putc(sendData[getData+i]);
			wait_ms(1);
		}
	}
	wait_ms(1);
	rsSW = 0;
}
//==============================================================
int main(int MBED_UNUSED argc, const char MBED_UNUSED * argv[])
{
	mbed::Serial pc(USBTX, USBRX);
	pc.baud(9600);
	
	//各種インスタンス
	//  SRF05 usonic(D11, D12);
	//  PwmOut pw    m(PB_0);
//	PCA9547 mux(D4, D5, 0xE0);
	
	//温度センサのインスタンス作成
//	mux.select(0);
//	TPA81       temp2(D4, D5, 0xD0);
//	mux.select(1);
//	TPA81   temp(D4, D5, 0xD2);
	
	
	//IR距離センサのインスタンス作成
//	VL6180x irDist(D4, D5, 0x29 << 1);
//	irDist.VL6180xInit();
//	irDist.VL6180xDefautSettings();
//	for(int i = 2; i < 6; i++) {
//		mux.select(i);
//		irDist.VL6180xInit();
//		irDist.VL6180xDefautSettings();
//	}
	
	//RS485初期設定
	rs.baud(9600);
	rs.attach(SerialAvailavle);
	/* rsSW 0=受信, 1=送信 */
	rsSW = 0;
	
	//LEDs
	mbed::DigitalOut ledDebug1(D7);
	mbed::DigitalOut ledDebug2(D8);
	mbed::DigitalOut ledDebug3(D11);
	mbed::DigitalOut ledDebug4(D12);
	
	while(1) {
		//疑似センサ
		sendData[0] += 0.01;
		sendData[1] += 0.02;
		sendData[2] += 0.03;
		sendData[3] += 0.04;
		sendData[4] += 0.05;
		sendData[5] += 0.06;
		sendData[6] += 0.07;
		for(int i = 0; i < 7; i++){
			printf("%4d\t", (int)sendData[i]);
		}puts("");
	}
}