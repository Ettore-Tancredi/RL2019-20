#ifndef CONSTANTS_H
#define CONSTANTS_H

extern const int IMU_ADDRESS;
extern const int TOF_ADDRESS;
extern const int STD_SPEED;
extern const double INTERRUPT_DELAY;
extern const double OBSTACLE_DELAY;
extern const int MIN_OBSTACLE_DIST;

enum LINE_TYPE{					//da confrontare con i valori scritti a seriale dall'UDOO
	INTERRUPT = 0,
	STD_LINE,
	T_INTERSECTION,
	C_INTERSECTION,
	UNKNOWN
};

#endif