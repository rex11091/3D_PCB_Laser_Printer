#ifndef _MOTORCONTROLLER_H
#define _MOTORCONTROLLER_H



typedef struct LineInfo LineInfo;
struct LineInfo {
  int dx;
  int dy;
  int dz;
  int X;
  int Y;
  int Z;
  int d;
  double m;
  int StartCoord[3];
  int EndCoord[3];
  int stepX;
  int stepY;
  int stepZ;
  int change; // variable to determine the changes of end point and final point
};
void setupMovement(int start[],int end[],LineInfo *LineInfo);
void MotorToNextStep(LineInfo *lineinfo);
void DrawLine(LineInfo *lineinfo);
#endif // _MOTORCONTROLLER_H
