//
//  LQSensor.hpp
//  LINQ_mbed
//
//  Created by Iwadate Ryosuke on 2017/03/15.
//  Copyright © 2017年 jagaNikuman. All rights reserved.
//

#ifndef LQSensor_hpp
#define LQSensor_hpp

#include <cstdint>

#include "mbed.h"
#include "VL6180x.h"
#include "TPA81.h"
#include "SRF05.h"
#include "PCA9547.h"
#include "Servo.h"
#include "Ping.h"


class LQSensor {
private:
	mbed::Serial rs = mbed::Serial(PA_9, PA_10);
	Ping *usonic = nullptr;
	PCA9547 *mux = nullptr;
	TPA81 *temperature1 = nullptr;
	TPA81 *temperature2 = nullptr;
	VL6180x *dist1 = nullptr;
	VL6180x *dist2 = nullptr;
	VL6180x *dist3 = nullptr;
	VL6180x *dist4 = nullptr;
	
	
	
public:
	LQSensor(Ping *_usonic, PCA9547 *_mux, TPA81 *_temperature1, TPA81 *_temperature2, VL6180x *_dist1, VL6180x *_dist2, VL6180x *_dist3, VL6180x *_dist4);
	void CRCallback();
	int8_t getDistValue(int);
	int8_t getTempValue(int);
	int8_t getUSValue();
};
#endif /* LQSensor_hpp */
