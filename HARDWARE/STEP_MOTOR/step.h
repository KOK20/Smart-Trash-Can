#ifndef __STEP_H__
#define __STEP_H__

#include "vision.h"

#define CW 1
#define CCW 0

void GoToX(Garbage *xx);
void GoToY(Garbage *yy);

void Axis_Calc(Garbage *axis);
void GO_ZERO(Garbage *pos);
void DIR_Change(int axis,char dir);
void DIR_Init(void);
void DIR(void);
void X_GO_Dis(Garbage *pos);
void Y_GO_Dis(Garbage *pos);
void angle_1(double ag);
void angle_2(double ag);
#endif
