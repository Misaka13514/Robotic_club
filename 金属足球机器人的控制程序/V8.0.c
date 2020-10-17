#include <header V4.0.h>
unsigned char MX_safety;
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
      robort_action();
    } else {
      all_directions();
    }
  } else {
    MX_safety++;
  }

  if (MX_safety == 20) {
    stopmotor();
    MX_safety = 0;
  }
  if (MX_gamepadClick(A)) {
    process(0);
  }
}