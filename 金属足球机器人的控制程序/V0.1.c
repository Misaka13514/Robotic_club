/*足球机器人示例程序*/
/*
左驱动轮：Port 1
右驱动轮：Port 2


左带球轮：Port 3
右带球轮：Port 4

麦克纳姆轮后轮 port 7 8
  弹射器：Port 6
*/
#include <MATRIX.h>

int L1 = 1;
int R1 = 2;
int L2 = 7;
int R2 = 8;

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

    MX_motorControl(
        L1, 10, MX_gamepadRightY * -1 + MX_gamepadRightX * -0.3,
        0); //左驱动轮，恒速模式：手柄Y轴反相+手柄X轴反相，手柄X轴乘0.3减弱效果
    MX_motorControl(
        L2, 10, MX_gamepadRightY * -1 + MX_gamepadRightX * -0.3,
        0); //左驱动轮，恒速模式：手柄Y轴反相+手柄X轴反相，手柄X轴乘0.3减弱效果
    MX_motorControl(
        R1, 10, MX_gamepadRightY * 1 + MX_gamepadRightX * -0.3,
        0); //右驱动轮，恒速模式：手柄Y轴+手柄X轴反相，手柄X轴乘0.3减弱效果
    MX_motorControl(
        R2, 10, MX_gamepadRightY * 1 + MX_gamepadRightX * -0.3,
        0); //右驱动轮，恒速模式：手柄Y轴+手柄X轴反相，手柄X轴乘0.3减弱效果

    if (MX_gamepadPress(LEFT)) {
      turn - left();
    }
    if (MX_gamepadPress(RIGHT)) {
      turn - right();
    }
    if (MX_gamepadPress(up)) {
      MX(L1, 100, true);
      MX(R1, 100, true);
      MX(L2, 100, true);
      MX(R2, 100, true);
    }
    if (MX_gamepadPress(down)) {
      MX(L1, 100, false);
      MX(R1, 100, false);
      MX(L2, 100, false);
      MX(R2, 100, false);
    }

    //带球部分
    if (MX_gamepadClick(L1)) //如果按下手柄L1键
    {
      MX_motorControl(3, 0, -100,
                      0); //左带球轮，功率百分比模式：100%功率反向转动
      MX_motorControl(4, 0, 10, 0); //右带球轮，功率百分比模式：10%功率正向转动
    }
    if (MX_gamepadClick(R1)) //如果按下手柄R1键
    {
      MX_motorControl(3, 0, -10, 0); //左带球轮，功率百分比模式：10%功率反向转动
      MX_motorControl(4, 0, 100,
                      0); //右带球轮，功率百分比模式：100%功率正向转动
    }
    if (MX_gamepadClick(A)) //如果按下手柄A键
    {
      MX_relayControl(6);           //令6号端口的弹射器动作
      MX_motorControl(3, 22, 0, 0); //左带球轮无阻力停止
      MX_motorControl(4, 22, 0, 0); //右带球轮无阻力停止
    }
    if (MX_gamepadClick(Y)) //如果按下手柄Y键
    {
      MX_motorControl(3, 22, 0, 0); //左带球轮无阻力停止
      MX_motorControl(4, 22, 0, 0); //右带球轮无阻力停止
    }

    //带球模式结束
  } else //如果没检测到手柄
  {
    MX_safety++; //变量累加
  }
  if (MX_safety == 20) {
    MX(L1, 0, true);
    MX(R1, 0, true);
    MX(L2, 0, true);
    MX(R2, 0, true);
    MX_screenBatteryV(); //刷新时间及电量显示
    MX_runUSB();         //运行USB设备
    MX_safety = 0;
  }
}

//默认恒速模式 强行把左右轮胎速度设为正值
void MX(int port, int MX_V, bool MX_D) {

  if (MX_V < 0 or MX_V > 100) { //安全检查部分
    MX_V = 0;
  }

  if (port = R1 or port = R2) { //如果是右边轮子的话 那么则强行改为反向
    if (MX_D == true) {
      NX_D = false;
    } else if (MX_D == false) {
      MX_D = true;
    } else {
      MV_V = 0;
    }
  }

  if (MX_D == false) { //如果方向是反的话 ，那么强行设为正 然后速度反速
    MX_V = -MX_V;
  }
  MX_motorControl(port, 10, MX_V, 00);
}

int usualspeed = 50;
//转向模式
void turn - right() {
  MX(L1, usualspeed, false);
  MX(L2, usualspeed, false);
  MX(R1, usualspeed, true);
  MX(R2, usualspeed, true);
}
void turn - left() {
  MX(L1, usualspeed, true);
  MX(L2, usualspeed, true);
  MX(R1, usualspeed, false);
  MX(R2, usualspeed, false);
}
