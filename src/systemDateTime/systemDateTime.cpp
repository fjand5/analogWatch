#include "systemDateTime.h"

DaysStruct cvtSun2Lunar(uint8_t dd, uint8_t mm, uint8_t yy)
{
    SunYear curYear;
    memcpy_P(&curYear, &sunYear[yy], sizeof(SunYear));
    SunMonth curMonth = curYear.sunMonth[mm - 1];
    uint8_t lunarDay = curMonth.lunarDay;     // Ngày âm ứng với ngày 1
    uint8_t lunarMonth = curMonth.lunarMonth; // Tháng âm ứng với ngày 1
    int8_t lunarYear = yy;
    if (mm > curYear.sunMonthOfTet)
    {
        lunarYear = yy;
    }
    else if (mm == curYear.sunMonthOfTet)
    {
        if (dd >= curYear.sunDayOfTet)
            lunarYear = yy;
        else
            lunarYear = yy - 1;
    }
    else
    {
        lunarYear = yy - 1;
    }
    uint8_t endDay = curMonth.isLeap[0] ? 30 : 29;
    uint8_t nextLunarMonth;
    if (mm < 12)
        nextLunarMonth = curYear.sunMonth[mm].lunarMonth;
    else if (mm == 12)
    {
        SunYear nextYear;
        memcpy_P(&nextYear, &sunYear[yy + 1], sizeof(SunYear));
        nextLunarMonth = nextYear.sunMonth[0].lunarMonth;
    }
    else
        nextLunarMonth = 13;
    for (uint8_t i = 1; i < dd; i++)
    {
        lunarDay++;
        if (lunarDay > endDay)
        {
            endDay = curMonth.isLeap[1] ? 30 : 29;
            if (lunarMonth != nextLunarMonth)
            {
                lunarMonth++;
            }
            if (lunarMonth > 12)
                lunarMonth = 1;
            lunarDay = 1;
        }
    }
    DaysStruct ret = {
        lunarDay,
        lunarMonth,
        lunarYear};
    return ret;
}