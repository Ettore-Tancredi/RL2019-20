#ifndef CONSTANTS_H
#define CONSTANTS_H

struct speed_range
{
	double v_min;
	double v_max;
};

extern const speed_range table[2][2];

extern const int IMU_ADDRESS;
extern const int TOF_ADDRESS;
extern const int STD_SPEED;
extern const double INTERRUPT_JUMP;
extern const double MAX_OBSTACLE_DIM;
extern const int MIN_OBSTACLE_DIST;

enum LINE_TYPE{					//da confrontare con i valori scritti a seriale dall'UDOO
	INTERRUPT = 0,
	STD_LINE = 1,
	INTERSECTION = 2,
	UNKNOWN = 3
};

#endif