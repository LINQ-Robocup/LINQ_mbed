//
//  LQSensor.cpp
//  LINQ_mbed
//
//  Created by Iwadate Ryosuke on 2017/03/15.
//  Copyright © 2017年 jagaNikuman. All rights reserved.
//

#include "LQSensor.hpp"
#include <cstdio>

LQSensor::LQSensor(Ping *_usonic, PCA9547 *_mux,
				   TPA81 *_temperature1, TPA81 *_temperature2,
				   VL6180x *_dist1, VL6180x *_dist2,
				   VL6180x *_dist3, VL6180x *_dist4) : usonic(_usonic), mux(_mux),
temperature1(_temperature1), temperature2(_temperature2),
dist1(_dist1), dist2(_dist2), dist3(_dist3), dist4(_dist4) {
	
}


int8_t LQSensor::getDistValue(int l) {
	
}


void LQSensor::CRCallback() {
	int getData = rs.getc();
	printf("%d\n", getData);
	int count = 0;
	switch (getData) {
		case 0:
			count = 7;
			sendData[0] = 10;
			sendData[1] = 20;
			sendData[2] = 30;
			sendData[3] = 50;
			sendData[4] = 50;
			sendData[5] = 60;
			sendData[6] = 80;
			break;
			
		case 1:
			count = 1;
			
			break;
			
		case 2:
			sendData[0] = 2;
			break;
			
		case 3:
			sendData[0] = 3;
			break;
			
		case 4:
			sendData[0] = 4;
			break;
			
		case 5:
			sendData[0] = 5;
			break;
			
		case 6:
			sendData[0] = 6;
			break;
			
		case 7:
			sendData[0] = 7;
			break;
		case 20:
			
			
		default:
			break;
	}
	
	//send Data
	rsSW = 1;
	
	for(int i = 0; i < count; i++) {
		rs.putc(sendData[i]);
		wait_ms(1);
	}
	wait_ms(1);
	
	rsSW = 0;
}
