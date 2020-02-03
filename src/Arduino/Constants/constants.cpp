#include "constants.h"


/***********************************************/
//Fix this values
/***********************************************/
const int IMU_ADDRESS = 1; 
const int TOF_ADDRESS = 1;
const int STD_SPEED = 1;
const double INTERRUPT_JUMP = 1;   //expressed in cm
const double MAX_OBSTACLE_DIM = 15;   //expressed in cm
const int MIN_OBSTACLE_DIST = 30;  //expressed in mm

const speed_range table[0][0].v_min = -1;   //determinare sperimentalmente
const speed_range table[0][0].v_max = -1;   //determinare sperimentalmente

const speed_range table[1][0].v_min = 125;   //   [rpm]
const speed_range table[1][0].v_max = 1250;   //   [rpm]

const speed_range table[0][1].v_min = 125;   //   [rpm]
const speed_range table[0][1].v_max = 5000;   //   [rpm]

const speed_range table[1][1].v_min = 125;   //   [rpm]
const speed_range table[1][1].v_max = 20000;   //   [rpm]

/**********************************************/