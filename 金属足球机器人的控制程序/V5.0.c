#include <MATRIX.h>
int left1 = 1;
int right1 = 2;
int left2 = 7;
int right2 = 8;

int speed1 = 50;

int speed2 = 75;
unsigned char
    MX_safety; //创建变量，用于安全防范。当没有检测到手柄则变量累加，检测到手柄则变量清零。当变量累加到20则说明连续20次没有检测到手柄，则停止所有电机。

void setup() {
  MX_Init(); //系统初始化程序，编程必写
  MX_teamFlag(); //用于选择，并显示队伍颜色、队员号码，参赛必备
}

void loop() {
  MX_screenBatteryV();       //刷新时间及电量显示
  MX_runUSB();               //运行USB设备
  if (MX_gamepadConnected()) //检测如果连接了USB手柄
  {
    MX_safety = 0; //如果检测到了手柄，则变量清零。
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
      new_process();
    }
  } else //如果没检测到手柄
  {
    MX_safety++; //变量累加
  }
  if (MX_safety == 20) //如果变量等于20，说明连续20次没有检测到手柄
  {
    MX_motorControl(1, 22, 0, 0);
    MX_motorControl(2, 22, 0, 0);
    MX_motorControl(8, 22, 0, 0);
    MX_motorControl(7, 22, 0, 0); //停止所有电机
    MX_safety = 0;
  }
}
//函数板块 MX_motor 第一个是端口号 第二个是速度大小
void MX_motor(int port, int MX_V) {
  if (port == right1 or port == right2) {
    MX_V = -MX_V;
    //将右侧轮胎速度变为负值
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
  MX_motor(left1, -speed1);
  MX_motor(left2, speed1);
  MX_motor(right1, speed1);
  MX_motor(right2, -speed1);
}
void slideright() {
  MX_motor(left1, speed1);
  MX_motor(left2, -speed1);
  MX_motor(right1, -speed1);
  MX_motor(right2, speed1);
}
//前后移动模块
void ahead() {
  MX_motor(left1, speed2);
  MX_motor(left2, speed2);
  MX_motor(right1, speed2);
  MX_motor(right2, speed2);
}
void back() {
  MX_motor(left1, -speed2);
  MX_motor(left2, -speed2);
  MX_motor(right1, -speed2);
  MX_motor(right2, -speed2);
}
void new_process() {
  int code1 = 0;
  int code = 0;
  int against = 0;
  if (MX_gamepadPress(LEFT)) {
    code = 1;
    against = 2;
  }
  if (MX_gamepadPress(RIGHT)) {
    code = 2;
  }
  if (MX_gamepadPress(UP)) {
    code = 3;
    against = 4;
  }
  if (MX_gamepadPress(DOWN)) {
    code = 4;
  }
  if (MX_gamepadPress(X)) {
    code = 5;
    against = 6;
  }
  if (MX_gamepadPress(Y)) {
    code = 6;
  }
  code1 = code;
  //传递参数指令
  if (code == against) {
    code1 = 0;
  }
  switch (code1) {
  case 0:
    MX_motor(1, 0);
    MX_motor(2, 0);
    MX_motor(7, 0);
    MX_motor(8, 0);
    MX_motorControl(1, 22, 0, 0);
    MX_motorControl(2, 22, 0, 0);
    MX_motorControl(7, 22, 0, 0);
    MX_motorControl(8, 22, 0, 0);
    break;

  case 1:
    turnleft();
    break;

  case 2:
    turnright();
    break;

  case 3:
    ahead();
    break;

  case 4:
    back();
    break;

  case 5:
    slideleft();
    break;

  case 6:
    slideright();
    break;

  default:
    MX_motor(1, 0);
    MX_motor(2, 0);
    MX_motor(7, 0);
    MX_motor(8, 0);
    MX_motorControl(1, 22, 0, 0);
    MX_motorControl(2, 22, 0, 0);
    MX_motorControl(7, 22, 0, 0);
    MX_motorControl(8, 22, 0, 0);
    break;
  }
}