
/*
  copyright ? ESONHUGH 2018-05-28 15:49:21
                     YYYY-MM-DD HH:MM:SS

                by esonhugh

  未完成编译和实现
  实现情况为

  ardunio mega开发板

  接口如下
  左侧前轮 1号
  右侧前轮 2号
  左侧后轮 7号
  右侧后轮 8号

  带球轮胎 左侧3号
  带球轮胎 右侧4号

  如下非注释部分为具体代码
*/

#include "MATRIX.h"

int left1 = 1;
int right1 = 2;
int left2 = 7;
int right2 = 8;

int speed1 = 50;

unsigned char
    MX_safety; //创建变量，用于安全防范。当没有检测到手柄则变量累加，检测到手柄则变量清零。当变量累加到20则说明连续20次没有检测到手柄，则停止所有电机。

void setup() {
  MX_Init(); //系统初始化程序，编程必写
  MX_teamFlag(); //用于选择，并显示队伍颜色、队员号码，参赛必备
}

void loop() {
  MX_screenBatteryV(); //刷新时间及电量显示
  MX_runUSB();         //运行USB设备
  if (MX_gamepadConnected()) {
    MX_safety = 0; //如果检测到了手柄，则变量清零。
    //手柄右摇杆控制驱动轮前后左右，其中Y轴控制前后，X轴控制左右
    // MX_motorControl
    // 为电机控制函数，第一个参数为端口号；第二个参数为电机功能；第三个参数为电机转速；第四个参数为角度或时间

    if (MX_gamepadPress(B)) {
      MX_motorControl(
          left1, 10, MX_gamepadLeftY * -1 + MX_gamepadLeftX * -0.3,
          0); //左驱动轮，恒速模式：手柄Y轴反相+手柄X轴反相，手柄X轴乘0.3减弱效果
      MX_motorControl(
          left2, 10, MX_gamepadLeftY * -1 + MX_gamepadLeftX * -0.3,
          0); //左驱动轮，恒速模式：手柄Y轴反相+手柄X轴反相，手柄X轴乘0.3减弱效果
      MX_motorControl(
          right1, 10, MX_gamepadLeftY * 1 + MX_gamepadLeftX * -0.3,
          0); //右驱动轮，恒速模式：手柄Y轴+手柄X轴反相，手柄X轴乘0.3减弱效果
      MX_motorControl(
          right2, 10, MX_gamepadLeftY * 1 + MX_gamepadLeftX * -0.3,
          0); //右驱动轮，恒速模式：手柄Y轴+手柄X轴反相，手柄X轴乘0.3减弱效果
    } else {
      int code;
      code = judge();
      process(code);
    }

    /*
        MX_motorControl(left1, 10, MX_gamepadRightY * -1 + MX_gamepadRightX *
       -0.3, 0);
       //左驱动轮，恒速模式：手柄Y轴反相+手柄X轴反相，手柄X轴乘0.3减弱效果
        MX_motorControl(left2, 10, MX_gamepadRightY * -1 + MX_gamepadRightX *
       -0.3, 0);
       //左驱动轮，恒速模式：手柄Y轴反相+手柄X轴反相，手柄X轴乘0.3减弱效果
        MX_motorControl(right1, 10, MX_gamepadRightY * 1 + MX_gamepadRightX *
       -0.3, 0); //右驱动轮，恒速模式：手柄Y轴+手柄X轴反相，手柄X轴乘0.3减弱效果
        MX_motorControl(right2, 10, MX_gamepadRightY * 1 + MX_gamepadRightX *
       -0.3, 0); //右驱动轮，恒速模式：手柄Y轴+手柄X轴反相，手柄X轴乘0.3减弱效果

        //如果右侧全向轮胎无法使用 左侧全向可以进行代替控制





        //带球部分
        if (MX_gamepadClick(L1)) //如果按下手柄L1键
        {
          MX_motorControl(3, 0, -100, 0);
       //左带球轮，功率百分比模式：100%功率反向转动 MX_motorControl(4, 0, 10,
       0); //右带球轮，功率百分比模式：10%功率正向转动
        }
        if (MX_gamepadClick(R1)) //如果按下手柄R1键
        {
          MX_motorControl(3, 0, -10, 0);
       //左带球轮，功率百分比模式：10%功率反向转动 MX_motorControl(4, 0, 100,
       0); //右带球轮，功率百分比模式：100%功率正向转动
        }
        if (MX_gamepadClick(A)) //如果按下手柄A键
        {
          MX_relayControl(6); //令6号端口的弹射器动作
          MX_motorControl(3, 22, 0, 0); //左带球轮无阻力停止
          MX_motorControl(4, 22, 0, 0); //右带球轮无阻力停止
        }


                   if(MX_gamepadClick(Y))//如果按下手柄Y键
                  {
                    MX_motorControl(3,22,0,0);   //左带球轮无阻力停止
                    MX_motorControl(4,22,0,0);   //右带球轮无阻力停止
                  }



        //带球模式结束

    */

  } else //如果没检测到手柄
  {
    MX_safety++; //变量累加
  }
  if (MX_safety == 20) {
    MX_screenBatteryV(); //刷新时间及电量显示
    MX_runUSB();         //运行USB设备
    MX_safety = 0;
  }
}

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
