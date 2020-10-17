#include <header.h>
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
      process();
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