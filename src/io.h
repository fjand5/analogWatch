
#include "store.h"
#include "timer.h"
#include "ultis.h"
#define RL1 D0
#define RL2 D1
#define RL3 D2
#define RL4 D3

#define ON false
#define OFF true
void setupIO(){
  pinMode(RL1, OUTPUT);
  pinMode(RL2, OUTPUT);
  pinMode(RL3, OUTPUT);
  pinMode(RL4, OUTPUT);
  digitalWrite(RL1, OFF);
  digitalWrite(RL2, OFF);
  digitalWrite(RL3, OFF);
  digitalWrite(RL4, OFF);
  setOnStoreChange([](String id, String val, bool isChange){
      if(id == "device1")
        digitalWrite(RL1, val == "true" ? ON: OFF);
      else if(id == "device2")
        digitalWrite(RL2, val == "true" ? ON: OFF);
      else if(id == "device3")
        digitalWrite(RL3, val == "true" ? ON: OFF);
      else if(id == "device4")
        digitalWrite(RL4, val == "true" ? ON: OFF);
  });
  setOnMinute([](int h, int m){

    //Serial.println(String("time: ") + h + " : " + m);
    String sod1 = getValue("schedule-on-device1");
    if( checkKey("schedule-on-device1")
    && splitString(sod1, ":", 0).toInt() == h 
    && splitString(sod1, ":", 1).toInt() == m 
    ){
        digitalWrite(RL1, ON);
        //Serial.println("digitalWrite(RL1, ON);");
    }

    String sod2 = getValue("schedule-on-device2");
    if( checkKey("schedule-on-device2")
    && splitString(sod2, ":", 0).toInt() == h 
    && splitString(sod2, ":", 1).toInt() == m 
    ){
        digitalWrite(RL2, ON);
        //Serial.println("digitalWrite(RL2, ON);");
    }

    String sod3 = getValue("schedule-on-device3");
    if( checkKey("schedule-on-device3")
    && splitString(sod3, ":", 0).toInt() == h 
    && splitString(sod3, ":", 1).toInt() == m 
    ){
        digitalWrite(RL3, ON);
        //Serial.println("digitalWrite(RL3, ON);");
    }

    String sod4 = getValue("schedule-on-device4");
    if( checkKey("schedule-on-device4")
    && splitString(sod4, ":", 0).toInt() == h 
    && splitString(sod4, ":", 1).toInt() == m 
    ){
        digitalWrite(RL4, ON);
        //Serial.println("digitalWrite(RL4, ON);");
    }

    String soffd1 = getValue("schedule-off-device1");
    if( checkKey("schedule-off-device1")
    && splitString(soffd1, ":", 0).toInt() == h 
    && splitString(soffd1, ":", 1).toInt() == m 
    ){
        digitalWrite(RL1, OFF);
        //Serial.println("digitalWrite(RL1, OFF);");
    }

    String soffd2 = getValue("schedule-off-device2");
    if( checkKey("schedule-off-device2")
    && splitString(soffd2, ":", 0).toInt() == h 
    && splitString(soffd2, ":", 1).toInt() == m 
    ){
        digitalWrite(RL2, OFF);
        //Serial.println("digitalWrite(RL2, OFF);");
    }

    String soffd3 = getValue("schedule-off-device3");
    if( checkKey("schedule-off-device3")
    && splitString(soffd3, ":", 0).toInt() == h 
    && splitString(soffd3, ":", 1).toInt() == m 
    ){
        digitalWrite(RL3, OFF);
        //Serial.println("digitalWrite(RL3, OFF);");
    }

    String soffd4 = getValue("schedule-off-device4");
    if( checkKey("schedule-off-device4")
    && splitString(soffd4, ":", 0).toInt() == h 
    && splitString(soffd4, ":", 1).toInt() == m 
    ){
        digitalWrite(RL4, OFF);
        //Serial.println("digitalWrite(RL4, OFF);");
    }
  });

}

void loopIO() {
}