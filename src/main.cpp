#include <Arduino.h>
#include <BleKeyboard.h>
#include "M5StickCPlus2.h"

BleKeyboard bleKeyboard("M5 remote media", "clement van peuter", 100);

void handleClick(float x, float y)
{
  if (abs(x) < 0.70 && abs(y) < 0.70)
  {
    bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
  }
  else if (x < -0.70 && abs(y) < 0.70)
  {
    bleKeyboard.write(KEY_MEDIA_NEXT_TRACK);
  }
  else if (x > 0.70 && abs(y) < 0.70)
  {
    bleKeyboard.write(KEY_MEDIA_PREVIOUS_TRACK);
  }
}

void handleHold(float x, float y)
{
  if (abs(x) < 0.70)
  {
    if (y > 0.70)
    {
      bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
    }
    else if (y < -0.70)
    {
      bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);
    }
  }
}

void setup()
{
  M5.begin();
  bleKeyboard.begin();
  M5.Lcd.sleep();
}

void loop()
{
  static float x;
  static float y;

  M5.update();
  if (StickCP2.Imu.update())
  {
    auto data = StickCP2.Imu.getImuData();
    x = data.accel.x;
    y = data.accel.y;
  }

  if (M5.BtnA.wasClicked())
  {
    handleClick(x, y);
  }

  if (M5.BtnA.isHolding())
  {
    handleHold(x, y);
  }

  delay(100);
}
