#include "mbed.h"
#include "VL6180x.h"
#include "TPA81.h"
#include "SRF05.h"
#include "PCA9547.h"
#include "Servo.h"
#include "Ping.h"

#define DEBUG
//Prototype
void rotateServo(int);
void SerialAvailavle();


float data[] = {1, 2, 3, 4, 5, 6, 7, 8};
float sendData[] = {1, 2, 3, 4, 5, 6, 7, 8};


const int DIST_R	= 0;
const int DIST_L	= 1;
const int DIST_FR	= 2;
const int DIST_FL	= 3;
const int TEMP_R	= 4;
const int TEMP_L	= 5;
const int SR		= 6;

bool led1Flag = false;
bool led2Flag = false;
bool led3Flag = false;

bool sonicFlag = false;

//==============================================================

mbed::Serial pc(USBTX, USBRX);
mbed::Serial rs(PA_9, PA_10);
mbed::DigitalOut rsSW(D3);
Ping usonic(D6);
DigitalInOut pingPin(D6);
Timer t;
PwmOut servo(D9);

//LEDs
mbed::DigitalOut led1(D10);
mbed::DigitalOut led2(D11);
mbed::DigitalOut led3(D12);

//==============================================================

const int angleOffset = 2000/180;
void rotateServo(int angle) {
	servo.pulsewidth_us(500 + angleOffset * angle);
}

//==============================================================

const int READ_ALL = 1;
const int ENABLE_SONIC = 2;
const int DISABLE_SONIC = 3;

const int LED_BLUE_ON = 20;
const int LED_BLUE_OFF = 21;
const int LED_GREEN_ON = 22;
const int LED_GREEN_OFF = 23;
const int LED_YELLOW_ON = 24;
const int LED_YELLOW_OFF = 25;



//==============================================================

int readSonic() {
	pingPin.output();
	pingPin = 0;
	wait_us(5);
	pingPin = 1;
	wait_us(5);
	pingPin = 0;
	pingPin.input();
	
	while (! pingPin);
	t.reset();
	while (pingPin);
	int duration =  t.read_us()/2;
	return duration*34/1000;
}


//==============================================================
void SerialAvailavle(){
	
	bool writeFlag = false;
	
	int getData = rs.getc();
//#ifdef DEBUG
//	printf("%d\n",getData);
//#endif
	
	int count = 0;
	switch (getData) {
		case READ_ALL:
			writeFlag = true;
			count = 8;
			sendData[0] = (data[DIST_FL] < 127 && data[DIST_FL] > 0) ? data[DIST_FL] : 127;
			sendData[1] = (data[DIST_FR] < 127 && data[DIST_FR] > 0) ? data[DIST_FR] : 127;
			sendData[2] = (data[DIST_L]  < 127 && data[DIST_L]  > 0) ? data[DIST_L] : 127;
			sendData[3] = (data[DIST_R]  < 127 && data[DIST_R]  > 0) ? data[DIST_R] : 127;
			sendData[4] = data[TEMP_L];
			sendData[5] = data[TEMP_R];
			sendData[6] = (data[SR] < 127 && data[SR] > 0) ? data[SR] : 127;;
			sendData[7] = 111;
			sonicFlag = false;
			break;
		
		case ENABLE_SONIC:
			sonicFlag = true;
			break;

		case 20:
			led1Flag = true;
			break;
		case 21:
			led1Flag = false;
			break;
		
		case 22:
			led2Flag = true;
			break;
		case 23:
			led2Flag = false;
			break;
		
		case 24:
			led3Flag = true;
			break;
		case 25:
			led3Flag = false;
			break;
		case 30:
			rotateServo(100);
			wait_ms(250);
			rotateServo(60);
			wait_ms(500);
			rotateServo(88);
			wait_ms(500);
			rotateServo(70);
			wait_ms(500);
			rotateServo(110);
			wait_ms(500);
			rotateServo(100);
			//total 2000ms
			break;
		default:
			break;
		case 31:
			//debug led on
			led1=1;
			//send message to raspi
			pc.printf("hello");
			//receive message from raspi & set send data
			sendData[0] = pc.getc();
			
			writeFlag = true;
			count = 1;
			
			//debug led off
			led1=0;
			break;
	}
	
	if(writeFlag == true) {
		rsSW = 1;
		wait_ms(1);
		for(int i = 0; i < count; i++) {
			rs.putc(sendData[i]);
			wait_ms(1);
		}
		wait_ms(1);
		rsSW = 0;
	}
}

//==============================================================


int main(int MBED_UNUSED argc, const char MBED_UNUSED * argv[]) {
	
	//mux channel
	const int M_DIST1	= 3;
	const int M_DIST2	= 2;
	const int M_DIST3	= 4;
	const int M_DIST4	= 5;
	const int M_TEMP1	= 1;
	const int M_TEMP2	= 0;
	
	const int wallDistanceOffset = 60;

	pc.baud(9600);
	
	servo.period_ms(20);
	
	//超音波距離センサ
//	Ping usonic(D6);
	
	PCA9547 mux(D4, D5, 0xE0);
	mux.select(0);
	
	//温度センサのインスタンス作成
	mux.select(M_TEMP1);
	TPA81 temp1(D4, D5, 0xD0);
	mux.select(M_TEMP2);
	TPA81 temp2(D4, D5, 0xD2);
	
	//IR距離センサのインスタンス作成
	mux.select(M_DIST1);
	VL6180x dist(D4, D5, 0x29 << 1);
	dist.VL6180xInit();
	dist.VL6180xDefautSettings();
	
	mux.select(M_DIST2);
	dist.VL6180xInit();
	dist.VL6180xDefautSettings();
	
	mux.select(M_DIST3);
	dist.VL6180xInit();
	dist.VL6180xDefautSettings();
	
	mux.select(M_DIST4);
	dist.VL6180xInit();
	dist.VL6180xDefautSettings();
	
	//RS485初期設定
	rs.baud(9600);
	rs.attach(SerialAvailavle);
	/* rsSW 0=受信, 1=送信 */
	rsSW = 0;
	t.start();
	
	/* testArea */
	
	/* end */
	while(1) {
		mux.select(M_DIST1);
		data[DIST_FR] = dist.getDistance()/2;
		
		mux.select(M_DIST2);
		data[DIST_R] = dist.getDistance()/2;
		
		mux.select(M_DIST3);
		data[DIST_L] = dist.getDistance()/2;
		
		mux.select(M_DIST4);
		data[DIST_FL] = dist.getDistance()/2;
		
		if(data[DIST_R] < wallDistanceOffset) {
			mux.select(M_TEMP1);
			data[TEMP_R] = temp1.getTemp(4);
		}else{
			data[TEMP_R] = 10;
		}
		if(data[DIST_L] < wallDistanceOffset) {
			mux.select(M_TEMP2);
			data[TEMP_L] = temp2.getTemp(4);
		}else{
			data[TEMP_L] = 10;
		}
		
		if(sonicFlag) {
			data[SR] = readSonic();
			if(data[SR] > 127) {
				data[SR] = 127;
			}
		}
		
		if(led1Flag == true) {
			led1 = 1;
		}else{
			led1 = 0;
		}
		
		if(led2Flag == true) {
			led2 = 1;
		}else{
			led2 = 0;
		}
		
		if(led3Flag == true) {
			led3 = 1;
		}else{
			led3 = 0;
		}
		
//		for(int i = 0; i < 7; i++){
//			printf("%4d\t", (int)data[i]);
//		}puts("");
	}
}

