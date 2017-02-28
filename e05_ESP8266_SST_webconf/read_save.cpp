#include <Arduino.h>
#include "constants.h"
#include "read_save.h"
#include "FS.h"
#include <ArduinoJson.h>

//Constructor
ReadSave::ReadSave(){
};

void ReadSave::setDisplayBright(int displayBright) {
  json_iDisplayBright = displayBright;
}

void ReadSave::setClock(int clock) {
  json_bClock = clock;
}

void ReadSave::setTimeZone(int timeZone) {
  json_timeZone = timeZone;
}

void ReadSave::setDayLightSavingTime(int dayLightSavingTime) {
  json_DayLightSavingTime = dayLightSavingTime;
}

void ReadSave::setChrono(int crono) {
  json_bCrono = crono;
}

void ReadSave::setCronoLearn(int cronoLearn) {
  json_bCronoLearn = cronoLearn;
}

void ReadSave::setSystem(int system) {
  json_bSystem = system;
}

void ReadSave::setLayout1(int layout1) {
  json_bLayout1 = layout1;
}

void ReadSave::setLayout2(int layout2) {
  json_bLayout2 = layout2;
}

void ReadSave::setOffsetDHT(float offsetDHT) {
  json_fOffsetDHT = offsetDHT;
}

void ReadSave::save_spiffs_prefs(int iDisplayBright, int bClock, int timeZone, int DayLightSavingTime, int bCrono, int bCronoLearn, int bSystem, int bLayout1, int bLayout2, float fOffsetDHT) {
  json_fOffsetDHT = iDisplayBright;
  json_bClock = bClock;
  json_timeZone = timeZone;
  json_DayLightSavingTime = DayLightSavingTime;
  json_bCrono = bCrono;
  json_bCronoLearn = bCronoLearn;
  json_bSystem = bSystem;
  json_bLayout1 = bLayout1;
  json_bLayout2 = bLayout1;
  save_spiffs_prefs();
}

void ReadSave::save_spiffs_prefs() {
  SPIFFS.begin();
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["Luminosita"] = json_iDisplayBright;
  root["Orologio"] = json_bClock;
  root["Tzone"] = json_timeZone;
  root["DayLightSavingTime"] = json_DayLightSavingTime;
  root["Crono"] = json_bCrono;
  root["CronoLearn"] = json_bCronoLearn;
  root["Dispositivo"] = json_bSystem;
  root["Layout1"] = json_bLayout1;
  root["Layout2"] = json_bLayout2;
  root["OffsetDHT"] = json_fOffsetDHT;
  //Serial.print("Ecco i dati in json: ");
  //root.printTo(Serial);
  char buffer[256];
  root.printTo(buffer, sizeof(buffer));
  //Serial.println();

  // open file for writing
  File sst_spiffs = SPIFFS.open("/sst_settings.json", "w");
  if (!sst_spiffs) {
    Serial.println("sst_settings.json open failed");
  }
  //qui salvo il buffer su file
  sst_spiffs.println(buffer);
  Serial.print("Salvo in SPIFFS il buffer con i settings :"); Serial.println(buffer);
  delay(1);
  //chiudo il file
  sst_spiffs.close();
}

int ReadSave::read_spiffs_prefs(const char*  valuedaleggere) {
  File  sst_spiffs_inlettura = SPIFFS.open("/sst_settings.json", "r");
  if (!sst_spiffs_inlettura) {
    Serial.println("sst_settings.json open failed");
    return 0;
  }
  String risultato = sst_spiffs_inlettura.readStringUntil('\n');
  //Serial.print("Ho letto dal file : ");Serial.println(risultato);
  char json[200];
  risultato.toCharArray(json, 200);
  //Serial.print("Ecco l'array json convertito: ");Serial.println(json);
  StaticJsonBuffer<200> jsonBuffer_inlettura;
  JsonObject& root_inlettura = jsonBuffer_inlettura.parseObject(json);
  if (!root_inlettura.success()) {
    Serial.println("parseObject() failed");
    return 0;
  }
  //leggo il valore e lo parso:
  int risultatoparsed = root_inlettura[valuedaleggere];
  Serial.print("Spiffs Json parsed value of "); Serial.print(valuedaleggere); Serial.print(" :");
  Serial.println(risultatoparsed);
  sst_spiffs_inlettura.close();
  return risultatoparsed;
}

void ReadSave::spiffs_Reset() {
  Serial.println("Reset SST");
  Serial.print("SPIFFS Formatting... ");
  if (SPIFFS.format()) {
    Serial.println("OK");
  } else {
    Serial.println("Fail");
  }

}
