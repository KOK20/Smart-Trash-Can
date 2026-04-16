#ifndef __VISION_H__
#define __VISION_H__
#include "sys.h"
//视觉坐标极限范围
#define Vision_X_MAX 10000.0f
#define Vision_Y_MAX 0000.0f
//垃圾桶坐标极限范围
#define Can_X_MAX  24.0f
#define Can_Y_MAX 26.0f
//齿轮半径
#define Radius 2.3f
//圆周率
#define PI 3.1415926535f

#define X 0
#define Y 1

typedef enum{
	Hazardous_Waste=1,
	Kitchen_Waste,
	Other_Waste,
	Recyclable_Waste
	
	
}Type_Gar;
typedef enum
{
	
	d
}s;

typedef enum{
	ZERO,
	NINETY
}Angle;
typedef struct
{
	Type_Gar garType;//垃圾类型
	int x;//视觉传过来的x坐标
	int y;//视觉传过来的y坐标
	Angle agl;//垃圾两种角度
	
	int destination[2];//终点
	int diff_val[2];//与终点坐标差值
}Garbage;

extern Garbage garbage;
void Vision_Data_Solve(uint8_t dt[]);
void Data_Init(Garbage *init);
#endif
