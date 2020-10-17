#include "MATRIX.h"

int left1 = 1;
int right1 = 2;
int left2 = 7;
int right2 = 8;

int speed1 = 50;

int judge() {
  int code = 0;
  if (MX_gamepadPress(LEFT)) {
    code = 1;
  }
  if (MX_gamepadPress(RIGHT)) {
    code = 2;
  }
  if (MX_gamepadPress(UP)) {
    code = 3;
  }
  if (MX_gamepadPress(DOWN)) {
    code = 4;
  }
  if (MX_gamepadPress(X)) {
    code = 5;
  }
  if (MX_gamepadPress(Y)) {
    code = 6;
  }
  return (code);
}

void process(int code1) {
  if (code1 == 0) {
    MX_motor(1, 0);
    MX_motor(2, 0);
    MX_motor(7, 0);
    MX_motor(8, 0);
  }
  if (code1 == 1) {
    turnleft();
  }
  if (code1 == 2) {
    turnright();
  }
  if (code1 == 3) {
    ahead();
  }
  if (code1 == 4) {
    back();
  }
  if (code1 == 5) {
    slideleft();
  }
  if (code1 == 6) {
    slideright();
  }
}

//全程序最主要的函数板块 MX_motor 第一个是端口号 第二个是速度大小
void MX_motor(int port, int MX_V) {
  ;
  if (port == right1 or right2) {
    MX_V = -MX_V; //将右侧轮胎速度变为负值
  }
  MX_motorControl(port, 10, MX_V, 0);
}

//转向模块
void turnright() {
  MX_motor(left1, speed1);
  MX_motor(left2, speed1);
  MX_motor(right1, -speed1);
  MX_motor(right2, -speed1);
}

void turnleft() {
  MX_motor(left1, -speed1);
  MX_motor(left2, -speed1);
  MX_motor(right1, speed1);
  MX_motor(right2, speed1);
}

//平移模块
void slideleft() {
  MX_motor(left1, speed1);
  MX_motor(left2, -speed1);
  MX_motor(right1, speed1);
  MX_motor(right2, -speed1);
}

void slideright() {
  MX_motor(left1, -speed1);
  MX_motor(left2, speed1);
  MX_motor(right1, -speed1);
  MX_motor(right2, speed1);
}

//前后移动模块
void ahead() {
  MX_motor(left1, speed1);
  MX_motor(left2, speed1);
  MX_motor(right1, speed1);
  MX_motor(right2, speed1);
}

void back() {
  MX_motor(left1, -speed1);
  MX_motor(left2, -speed1);
  MX_motor(right1, -speed1);
  MX_motor(right2, -speed1);
}
