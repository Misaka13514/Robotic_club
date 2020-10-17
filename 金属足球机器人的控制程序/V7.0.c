#include <header.h>

unsigned char
    MX_safety; //创建变量，用于安全防范。当没有检测到手柄则变量累加，检测到手柄则变量清零。当变量累加到20则说明连续20次没有检测到手柄，则停止电机。

void setup() {
  MX_Init();
  MX_teamFlag();
}

void loop() {
  MX_screenBatteryV();
  MX_runUSB();
  if (MX_gamepadConnected()) {
    MX_safety = 0;
    if (MX_gamepadPress(B)) {
      MX_motorControl(left1, 10,
                      MX_gamepadLeftY * -0.5 + MX_gamepadLeftX * -0.3 * 0.5, 0);
      MX_motorControl(left2, 10,
                      MX_gamepadLeftY * -0.5 + MX_gamepadLeftX * -0.3 * 0.5, 0);
      MX_motorControl(right1, 10,
                      MX_gamepadLeftY * 0.5 + MX_gamepadLeftX * -0.3 * 0.5, 0);
      MX_motorControl(right2, 10,
                      MX_gamepadLeftY * 0.5 + MX_gamepadLeftX * -0.3 * 0.5, 0);
    } else {
      process();
    }
  } else {
    MX_safety++;
  }
  if (MX_safety == 20) {
    MX_motorControl(1, 22, 0, 0);
    MX_motorControl(2, 22, 0, 0);
    MX_motorControl(8, 22, 0, 0);
    MX_motorControl(7, 22, 0, 0);
    MX_safety = 0;
  }
  if (MX_gamepadClick(A)) {
    processWithCode(0);
  }
}