#ifndef READ_SAVE_H
#define READ_SAVE_H

#include <Arduino.h>

class ReadSave {
private:
    int json_iDisplayBright;
    int json_bClock;
    int json_timeZone;
    int json_DayLightSavingTime;
    int json_bCrono;
    int json_bCronoLearn;
    int json_bSystem;
    int json_bLayout1;
    int json_bLayout2;
    float json_fOffsetDHT;

    public:
      ReadSave();
      void setDisplayBright(int displayBright);
      void setClock(int clock);
      void setTimeZone(int timeZone);
      void setDayLightSavingTime(int dayLightSavingTime);
      void setChrono(int crono);
      void setCronoLearn(int cronoLearn);
      void setSystem(int system);
      void setLayout1(int layout1);
      void setLayout2(int layout2);
      void setOffsetDHT(float offsetDHT);

      int read_spiffs_prefs(const char*);
      void save_spiffs_prefs(int iDisplayBright, int bClock, int timeZone, int DayLightSavingTime, int bCrono, int bCronoLearn, int bSystem, int bLayout1, int bLayout2, float fOffsetDHT);
      void save_spiffs_prefs();
      void spiffs_Reset();
};

#endif
