#include "mbed.h"
#include <VL6180x.h>
#include <TPA81.h>
#include <SRF05.h>
#include <PCA9547.h>
#include <Servo.h>
#include <Ping.h>

//RS485インスタンス(複数の関数から使うためグローバル)
mbed::Serial rs(PA_9, PA_10);
mbed::DigitalOut rsSW(D3);

float sendData[] = {1, 2, 3, 4, 5, 6, 7};

//==============================================================
void SerialAvailavle()
{
	int getData = rs.getc();
	//		printf("%d\n", getData);
	wait_ms(1);
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
	
	const int IRDIST1	= 4;
	const int IRDIST2	= 5;
	const int IRDIST3	= 0;
	const int IRDIST4	= 1;
	const int TEMP1		= 3;
	const int TEMP2		= 2;
	const int SR		= NULL;

	mbed::Serial pc(USBTX, USBRX);
	pc.baud(9600);
	
	//超音波距離センサ
//	SRF05 usonic(D11, D12);
	Ping usonic(D12);
	
//	PwmOut pwm(PB_0);
	PCA9547 mux(D4, D5, 0xE0);
	mux.select(0);
	
	//温度センサのインスタンス作成
	mux.select(TEMP1);
	TPA81 temp2(D4, D5, 0xD2);
	mux.select(TEMP2);
	TPA81 temp(D4, D5, 0xD0);
	
	//IR距離センサのインスタンス作成
	mux.select(IRDIST1);
	VL6180x irDist(D4, D5, 0x29 << 1);
	irDist.VL6180xInit();
	irDist.VL6180xDefautSettings();
	
	mux.select(IRDIST2);
	irDist.VL6180xInit();
	irDist.VL6180xDefautSettings();
	
	mux.select(IRDIST3);
	irDist.VL6180xInit();
	irDist.VL6180xDefautSettings();
	
	mux.select(IRDIST4);
	irDist.VL6180xInit();
	irDist.VL6180xDefautSettings();
	
	
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

//		ping.Send();
//		wait_us(2500);
//		printf("usonic=%4d\t", ping.Read_cm());
		mux.select(IRDIST1);
		sendData[0] = irDist.getDistance()/2;
		mux.select(IRDIST2);
		sendData[1] = irDist.getDistance()/2;
		mux.select(IRDIST3);
		sendData[2] = irDist.getDistance()/2;
		mux.select(IRDIST4);
		sendData[3] = irDist.getDistance()/2;
		mux.select(TEMP1);
		sendData[4] = temp.getTemp(4);
		mux.select(TEMP2);
		sendData[5] = temp2.getTemp(4);
		for(int i = 0; i < 7; i++){
			printf("%4d\t", (int)sendData[i]);
		}puts("");
	}
}


