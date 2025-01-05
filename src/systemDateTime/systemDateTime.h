#pragma once
#define DS1307_SDA 33
#define DS1307_CLK 32
#include <Arduino.h>
#include "RTClib.h"

#include <functional>

#include <WiFiUdp.h>

#include <NTPClient.h>
#include "webserver/webserver.h"
#include "wifi/wifi.h"
#define PREF_SYSTEM_DATE_TIME_NAME "__SysDateTime"

typedef std::function<void(DateTime now)> TimerEvent;
struct DaysStruct
{
    uint8_t day;
    uint8_t month;
    int8_t year;
};
struct SunMonth
{
    // Tháng âm tương ứng có nhuận hay không (trường hợp tháng dương chứa 2 tháng âm).
    bool isLeap[2];
    // Ngày 1 tháng dương ứng với ngày mấy tháng, tháng mấy âm
    uint8_t lunarDay;
    uint8_t lunarMonth;
};
struct SunYear
{
    // Ngày Tết là ngày nào, tháng nào.
    uint8_t sunDayOfTet;
    uint8_t sunMonthOfTet;
    SunMonth sunMonth[12];
};
const SunYear sunYear[100] PROGMEM = {
    5, 2, {{{true, false}, 25, 11}, {{false, false}, 26, 12}, {{true, false}, 26, 1}, {{true, false}, 27, 2}, {{false, false}, 27, 3}, {{false, false}, 29, 4}, {{true, false}, 30, 5}, {{false, false}, 2, 7}, {{true, false}, 4, 8}, {{false, false}, 4, 9}, {{true, false}, 6, 10}, {{true, false}, 6, 11}}, 24, 1, {{{false, false}, 7, 12}, {{true, false}, 9, 1}, {{true, false}, 7, 2}, {{false, false}, 8, 3}, {{true, false}, 9, 4}, {{false, false}, 10, 4}, {{true, false}, 11, 5}, {{false, false}, 12, 6}, {{false, false}, 14, 7}, {{true, false}, 15, 8}, {{false, false}, 16, 9}, {{true, false}, 17, 10}}, 12, 2, {{{false, false}, 18, 11}, {{true, false}, 20, 12}, {{true, false}, 18, 1}, {{true, false}, 19, 2}, {{false, false}, 19, 3}, {{true, false}, 21, 4}, {{false, false}, 21, 5}, {{true, false}, 23, 6}, {{false, false}, 24, 7}, {{false, false}, 25, 8}, {{true, false}, 27, 9}, {{false, false}, 27, 10}}, 1, 2, {{{true, false}, 29, 11}, {{false, false}, 1, 1}, {{true, false}, 29, 1}, {{true, false}, 30, 2}, {{true, false}, 1, 4}, {{true, false}, 2, 5}, {{false, false}, 2, 6}, {{true, false}, 4, 7}, {{false, false}, 5, 8}, {{false, false}, 6, 9}, {{true, false}, 8, 10}, {{false, false}, 8, 11}}, 22, 1, {{{true, false}, 10, 12}, {{false, false}, 11, 1}, {{true, false}, 11, 2}, {{false, false}, 12, 2}, {{true, false}, 13, 3}, {{true, false}, 14, 4}, {{false, false}, 14, 5}, {{true, false}, 16, 6}, {{false, false}, 17, 7}, {{true, false}, 18, 8}, {{false, false}, 19, 9}, {{true, false}, 20, 10}}, 9, 2, {{{false, false}, 21, 11}, {{true, false}, 23, 12}, {{false, false}, 21, 1}, {{true, false}, 23, 2}, {{false, false}, 23, 3}, {{true, false}, 25, 4}, {{false, false}, 25, 5}, {{true, false}, 27, 6}, {{true, false}, 28, 7}, {{false, false}, 28, 8}, {{true, false}, 30, 9}, {{true, false}, 1, 11}}, 29, 1, {{{false, false}, 2, 12}, {{true, false}, 4, 1}, {{false, false}, 2, 2}, {{true, false}, 4, 3}, {{false, false}, 4, 4}, {{false, false}, 6, 5}, {{true, false}, 7, 6}, {{true, false}, 8, 7}, {{false, false}, 9, 7}, {{true, false}, 10, 8}, {{true, false}, 11, 9}, {{false, false}, 11, 10}}, 17, 2, {{{true, false}, 13, 11}, {{false, false}, 14, 12}, {{true, false}, 13, 1}, {{false, false}, 14, 2}, {{true, false}, 15, 3}, {{false, false}, 16, 4}, {{false, false}, 17, 5}, {{true, false}, 19, 6}, {{false, false}, 20, 7}, {{true, false}, 21, 8}, {{true, false}, 22, 9}, {{true, false}, 22, 10}}, 7, 2, {{{false, false}, 23, 11}, {{true, false}, 25, 12}, {{true, false}, 24, 1}, {{false, false}, 25, 2}, {{false, false}, 26, 3}, {{true, false}, 28, 4}, {{false, false}, 28, 5}, {{true, false}, 1, 7}, {{false, false}, 2, 8}, {{true, false}, 3, 9}, {{false, false}, 4, 10}, {{true, false}, 5, 11}}, 26, 1, {{{true, false}, 6, 12}, {{true, false}, 7, 1}, {{false, false}, 5, 2}, {{true, false}, 7, 3}, {{false, false}, 7, 4}, {{true, false}, 9, 5}, {{false, false}, 9, 5}, {{false, false}, 11, 6}, {{true, false}, 13, 7}, {{false, false}, 13, 8}, {{true, false}, 15, 9}, {{false, false}, 15, 10}}, 14, 2, {{{true, false}, 17, 11}, {{true, false}, 18, 12}, {{true, false}, 16, 1}, {{false, false}, 17, 2}, {{true, false}, 18, 3}, {{false, false}, 19, 4}, {{true, false}, 20, 5}, {{false, false}, 21, 6}, {{false, false}, 23, 7}, {{true, false}, 24, 8}, {{false, false}, 25, 9}, {{true, false}, 26, 10}}, 3, 2, {{{false, false}, 27, 11}, {{true, false}, 29, 12}, {{true, false}, 27, 1}, {{false, false}, 28, 2}, {{true, false}, 29, 3}, {{true, false}, 30, 4}, {{true, false}, 1, 6}, {{false, false}, 2, 7}, {{false, false}, 4, 8}, {{true, false}, 5, 9}, {{false, false}, 6, 10}, {{true, false}, 7, 11}}, 23, 1, {{{false, false}, 8, 12}, {{true, false}, 10, 1}, {{false, false}, 9, 2}, {{true, false}, 11, 3}, {{true, false}, 11, 4}, {{false, false}, 12, 4}, {{true, false}, 13, 5}, {{false, false}, 14, 6}, {{true, false}, 16, 7}, {{false, false}, 16, 8}, {{true, false}, 18, 9}, {{false, false}, 18, 10}}, 10, 2, {{{true, false}, 20, 11}, {{false, false}, 21, 12}, {{true, false}, 20, 1}, {{false, false}, 21, 2}, {{true, false}, 22, 3}, {{false, false}, 23, 4}, {{true, false}, 24, 5}, {{true, false}, 25, 6}, {{false, false}, 26, 7}, {{true, false}, 27, 8}, {{false, false}, 28, 9}, {{true, false}, 29, 10}}, 31, 1, {{{true, false}, 1, 12}, {{false, false}, 2, 1}, {{true, false}, 1, 2}, {{false, false}, 2, 3}, {{true, false}, 3, 4}, {{false, false}, 4, 5}, {{true, false}, 5, 6}, {{false, false}, 6, 7}, {{true, false}, 8, 8}, {{true, false}, 8, 9}, {{false, false}, 9, 9}, {{true, false}, 10, 10}}, 19, 2, {{{false, false}, 11, 11}, {{true, false}, 13, 12}, {{false, false}, 11, 1}, {{true, false}, 13, 2}, {{false, false}, 13, 3}, {{false, false}, 15, 4}, {{true, false}, 16, 5}, {{false, false}, 17, 6}, {{true, false}, 19, 7}, {{true, false}, 19, 8}, {{true, false}, 20, 9}, {{false, false}, 20, 10}}, 8, 2, {{{true, false}, 22, 11}, {{false, false}, 23, 12}, {{true, false}, 23, 1}, {{false, false}, 24, 2}, {{true, false}, 25, 3}, {{false, false}, 26, 4}, {{false, false}, 27, 5}, {{true, false}, 29, 6}, {{true, false}, 1, 8}, {{true, false}, 1, 9}, {{false, false}, 2, 10}, {{true, false}, 3, 11}}, 28, 1, {{{true, false}, 4, 12}, {{false, false}, 5, 1}, {{true, false}, 4, 2}, {{false, false}, 5, 3}, {{true, false}, 6, 4}, {{false, false}, 7, 5}, {{false, false}, 8, 6}, {{true, false}, 10, 6}, {{false, false}, 11, 7}, {{true, false}, 12, 8}, {{false, false}, 13, 9}, {{true, false}, 14, 10}}, 16, 2, {{{true, false}, 15, 11}, {{true, false}, 16, 12}, {{false, false}, 14, 1}, {{true, false}, 16, 2}, {{false, false}, 16, 3}, {{true, false}, 18, 4}, {{false, false}, 18, 5}, {{false, false}, 20, 6}, {{true, false}, 22, 7}, {{false, false}, 22, 8}, {{false, false}, 24, 9}, {{true, false}, 25, 10}}, 5, 2, {{{true, false}, 26, 11}, {{true, false}, 27, 12}, {{false, false}, 25, 1}, {{true, false}, 27, 2}, {{true, false}, 27, 3}, {{false, false}, 28, 4}, {{true, false}, 29, 5}, {{false, false}, 1, 7}, {{true, false}, 3, 8}, {{false, false}, 3, 9}, {{false, false}, 5, 10}, {{true, false}, 6, 11}}, 25, 1, {{{true, false}, 7, 12}, {{false, false}, 8, 1}, {{true, false}, 8, 2}, {{true, false}, 9, 3}, {{true, false}, 9, 4}, {{false, false}, 10, 4}, {{true, false}, 11, 5}, {{false, false}, 12, 6}, {{false, false}, 14, 7}, {{true, false}, 15, 8}, {{false, false}, 16, 9}, {{false, false}, 17, 10}}, 12, 2, {{{true, false}, 19, 11}, {{true, false}, 20, 12}, {{false, false}, 18, 1}, {{true, false}, 20, 2}, {{true, false}, 20, 3}, {{false, false}, 21, 4}, {{true, false}, 22, 5}, {{false, false}, 23, 6}, {{true, false}, 25, 7}, {{false, false}, 25, 8}, {{true, false}, 27, 9}, {{false, false}, 27, 10}}, 1, 2, {{{true, false}, 29, 11}, {{false, false}, 1, 1}, {{true, false}, 29, 1}, {{true, false}, 1, 3}, {{false, false}, 1, 4}, {{true, false}, 3, 5}, {{true, false}, 3, 6}, {{false, false}, 4, 7}, {{true, false}, 6, 8}, {{false, false}, 6, 9}, {{true, false}, 8, 10}, {{false, false}, 8, 11}}, 22, 1, {{{true, false}, 10, 12}, {{false, false}, 11, 1}, {{true, false}, 10, 2}, {{false, false}, 11, 2}, {{false, false}, 12, 3}, {{true, false}, 14, 4}, {{true, false}, 14, 5}, {{false, false}, 15, 6}, {{true, false}, 17, 7}, {{true, false}, 17, 8}, {{false, false}, 18, 9}, {{true, false}, 19, 10}}, 10, 2, {{{false, false}, 20, 11}, {{true, false}, 22, 12}, {{false, false}, 21, 1}, {{true, false}, 23, 2}, {{false, false}, 23, 3}, {{false, false}, 25, 4}, {{true, false}, 26, 5}, {{false, false}, 27, 6}, {{true, false}, 29, 7}, {{true, false}, 29, 8}, {{true, false}, 1, 10}, {{true, false}, 1, 11}}, // Năm 24
    29,
    1,
    {{{false, false}, 2, 12}, {{true, false}, 4, 1}, {{false, false}, 2, 2}, {{true, false}, 4, 3}, {{false, false}, 4, 4}, {{false, false}, 6, 5}, {{true, false}, 7, 6}, {{false, false}, 8, 6}, {{true, false}, 10, 7}, {{false, false}, 10, 8}, {{true, false}, 12, 9}, {{true, false}, 12, 10}},
    17,
    2,
    {{{true, false}, 13, 11}, {{false, false}, 14, 12}, {{true, false}, 13, 1}, {{false, false}, 14, 2}, {{true, false}, 15, 3}, {{false, false}, 16, 4}, {{false, false}, 17, 5}, {{true, false}, 19, 6}, {{false, false}, 20, 7}, {{false, false}, 21, 8}, {{true, false}, 23, 9}, {{true, false}, 23, 10}},
    6,
    2,
    {{{true, false}, 24, 11}, {{false, false}, 25, 12}, {{true, false}, 24, 1}, {{true, false}, 25, 2}, {{false, false}, 25, 3}, {{true, false}, 27, 4}, {{false, false}, 27, 5}, {{false, true}, 29, 6}, {{false, false}, 1, 8}, {{false, false}, 2, 9}, {{true, false}, 4, 10}, {{true, false}, 4, 11}}, // Năm 27
    26,
    1,
    {{{false, false}, 5, 12}, {{true, false}, 7, 1}, {{true, false}, 6, 2}, {{true, false}, 7, 3}, {{false, false}, 7, 4}, {{true, false}, 9, 5}, {{false, false}, 9, 5}, {{false, false}, 11, 6}, {{true, false}, 13, 7}, {{false, false}, 13, 8}, {{false, false}, 15, 9}, {{true, false}, 16, 10}},
    13,
    2,
    {{{true, false}, 17, 11}, {{false, false}, 18, 12}, {{true, false}, 17, 1}, {{true, false}, 18, 2}, {{false, false}, 18, 3}, {{true, false}, 20, 4}, {{false, false}, 20, 5}, {{true, false}, 22, 6}, {{false, false}, 23, 7}, {{true, false}, 24, 8}, {{false, false}, 25, 9}, {{false, false}, 26, 10}},
    2,
    2,
    {{{true, false}, 28, 11}, {{false, false}, 29, 12}, {{true, false}, 28, 1}, {{true, false}, 29, 2}, {{false, true}, 29, 3}, {{true, true}, 1, 5}, {{false, false}, 1, 6}, {{true, false}, 3, 7}, {{false, false}, 4, 8}, {{true, false}, 5, 9}, {{false, false}, 6, 10}, {{true, false}, 7, 11}}, // Năm 30
    23,
    1,
    {{{false, false}, 8, 12}, {{false, false}, 10, 1}, {{true, false}, 9, 2}, {{false, false}, 10, 3}, {{true, false}, 11, 3}, {{true, false}, 12, 4}, {{false, false}, 12, 5}, {{true, false}, 14, 6}, {{true, false}, 15, 7}, {{false, false}, 15, 8}, {{true, false}, 17, 9}, {{false, false}, 17, 10}},
    11,
    2,
    {{{true, false}, 19, 11}, {{false, false}, 20, 12}, {{false, false}, 20, 1}, {{true, false}, 22, 2}, {{false, false}, 22, 3}, {{true, false}, 24, 4}, {{false, false}, 24, 5}, {{true, false}, 26, 6}, {{true, false}, 27, 7}, {{false, false}, 27, 8}, {{true, false}, 29, 9}, {{true, false}, 29, 10}},
    31,
    1,
    {{{true, false}, 1, 12}, {{false, false}, 2, 1}, {{true, false}, 1, 2}, {{false, false}, 2, 3}, {{false, false}, 3, 4}, {{true, false}, 5, 5}, {{false, false}, 5, 6}, {{true, false}, 7, 7}, {{false, false}, 8, 8}, {{true, false}, 9, 9}, {{true, false}, 10, 10}, {{true, false}, 10, 11}}, // Năm 33
    19,
    2,
    {{{false, false}, 11, 11}, {{true, false}, 13, 12}, {{false, false}, 11, 1}, {{true, false}, 13, 2}, {{false, false}, 13, 3}, {{false, false}, 15, 4}, {{true, false}, 16, 5}, {{false, false}, 17, 6}, {{false, false}, 19, 7}, {{true, false}, 20, 8}, {{true, false}, 21, 9}, {{true, false}, 21, 10}},
    8,
    2,
    {{{false, false}, 22, 11}, {{true, false}, 24, 12}, {{true, false}, 22, 1}, {{false, false}, 23, 2}, {{true, false}, 24, 3}, {{false, false}, 25, 4}, {{false, false}, 26, 5}, {{true, false}, 28, 6}, {{false, false}, 29, 7}, {{true, false}, 1, 9}, {{true, false}, 2, 10}, {{false, false}, 2, 11}},
    28,
    1,
    {{{true, false}, 4, 12}, {{true, false}, 5, 1}, {{true, false}, 4, 2}, {{false, false}, 5, 3}, {{true, false}, 6, 4}, {{false, false}, 7, 5}, {{false, false}, 8, 6}, {{true, false}, 10, 6}, {{false, false}, 11, 7}, {{false, false}, 12, 8}, {{true, false}, 14, 9}, {{false, false}, 14, 10}},
    15,
    2,
    {{{true, false}, 16, 11}, {{true, false}, 17, 12}, {{true, false}, 15, 1}, {{false, false}, 16, 2}, {{true, false}, 17, 3}, {{true, false}, 18, 4}, {{false, false}, 18, 5}, {{false, false}, 20, 6}, {{true, false}, 22, 7}, {{false, false}, 22, 8}, {{false, false}, 24, 9}, {{true, false}, 25, 10}},
    4,
    2,
    {{{false, false}, 26, 11}, {{true, false}, 28, 12}, {{true, false}, 26, 1}, {{false, false}, 27, 2}, {{true, false}, 28, 3}, {{true, false}, 29, 4}, {{false, true}, 29, 5}, {{false, false}, 1, 7}, {{true, false}, 3, 8}, {{false, false}, 3, 9}, {{false, false}, 5, 10}, {{true, false}, 6, 11}}, // Năm 38
    24,
    1,
    {{{false, false}, 7, 12}, {{true, false}, 9, 1}, {{true, false}, 7, 2}, {{false, false}, 8, 3}, {{true, false}, 9, 4}, {{true, false}, 10, 5}, {{false, false}, 10, 5}, {{true, false}, 12, 6}, {{false, false}, 13, 7}, {{true, false}, 14, 8}, {{false, false}, 15, 9}, {{false, false}, 16, 10}},
    12,
    2,
    {{{true, false}, 18, 11}, {{false, false}, 19, 12}, {{true, false}, 19, 1}, {{false, false}, 20, 2}, {{true, false}, 21, 3}, {{true, false}, 22, 4}, {{false, false}, 22, 5}, {{true, false}, 24, 6}, {{false, false}, 25, 7}, {{true, false}, 26, 8}, {{true, false}, 27, 9}, {{false, false}, 27, 10}},
    1,
    2,
    {{{true, false}, 29, 11}, {{false, false}, 1, 1}, {{false, true}, 29, 1}, {{false, false}, 1, 3}, {{true, false}, 2, 4}, {{false, false}, 3, 5}, {{true, false}, 4, 6}, {{false, false}, 5, 7}, {{true, false}, 7, 8}, {{true, false}, 7, 9}, {{true, false}, 8, 10}, {{false, false}, 8, 11}}, // Năm 41
    22,
    1,
    {{{true, false}, 10, 12}, {{false, false}, 11, 1}, {{true, false}, 10, 2}, {{false, false}, 11, 2}, {{false, false}, 12, 3}, {{true, false}, 14, 4}, {{false, false}, 14, 5}, {{true, false}, 16, 6}, {{false, false}, 17, 7}, {{true, false}, 18, 8}, {{true, false}, 19, 9}, {{false, false}, 19, 10}},
    10,
    2,
    {{{true, false}, 21, 11}, {{true, false}, 22, 12}, {{false, false}, 20, 1}, {{true, false}, 22, 2}, {{false, false}, 22, 3}, {{false, false}, 24, 4}, {{true, false}, 25, 5}, {{false, false}, 26, 6}, {{false, false}, 28, 7}, {{true, false}, 29, 8}, {{true, false}, 30, 9}, {{true, false}, 1, 11}},
    30,
    1,
    {{{true, false}, 2, 12}, {{true, false}, 3, 1}, {{false, false}, 2, 2}, {{true, false}, 4, 3}, {{false, false}, 4, 4}, {{false, false}, 6, 5}, {{true, false}, 7, 6}, {{false, false}, 8, 7}, {{false, false}, 10, 7}, {{true, false}, 11, 8}, {{false, false}, 12, 9}, {{true, false}, 13, 10}},
    17,
    2,
    {{{true, false}, 14, 11}, {{true, false}, 15, 12}, {{true, false}, 13, 1}, {{false, false}, 14, 2}, {{true, false}, 15, 3}, {{false, false}, 16, 4}, {{false, false}, 17, 5}, {{true, false}, 19, 6}, {{false, false}, 20, 7}, {{false, false}, 21, 8}, {{true, false}, 23, 9}, {{false, false}, 23, 10}},
    6,
    2,
    {{{true, false}, 25, 11}, {{true, false}, 26, 12}, {{true, false}, 24, 1}, {{false, false}, 25, 2}, {{true, false}, 26, 3}, {{false, false}, 27, 4}, {{true, false}, 28, 5}, {{false, true}, 29, 6}, {{false, false}, 1, 8}, {{false, false}, 2, 9}, {{true, false}, 4, 10}, {{false, false}, 4, 11}}, // Năm 46
    26,
    1,
    {{{true, false}, 6, 12}, {{true, false}, 7, 1}, {{false, false}, 5, 2}, {{true, false}, 7, 3}, {{true, false}, 7, 4}, {{false, false}, 8, 5}, {{true, false}, 9, 5}, {{false, false}, 10, 6}, {{true, false}, 12, 7}, {{false, false}, 12, 8}, {{false, false}, 14, 9}, {{true, false}, 15, 10}},
    14,
    2,
    {{{false, false}, 16, 11}, {{true, false}, 18, 12}, {{false, false}, 17, 1}, {{true, false}, 19, 2}, {{true, false}, 19, 3}, {{false, false}, 20, 4}, {{true, false}, 21, 5}, {{true, false}, 22, 6}, {{false, false}, 23, 7}, {{true, false}, 24, 8}, {{false, false}, 25, 9}, {{false, false}, 26, 10}},
    2,
    2,
    {{{true, false}, 28, 11}, {{false, false}, 29, 12}, {{true, false}, 28, 1}, {{false, false}, 29, 2}, {{true, false}, 30, 3}, {{true, false}, 2, 5}, {{true, false}, 2, 6}, {{false, false}, 3, 7}, {{true, false}, 5, 8}, {{false, false}, 5, 9}, {{true, false}, 7, 10}, {{true, false}, 7, 11}},
    23,
    1,
    {{{false, false}, 8, 12}, {{false, false}, 10, 1}, {{true, false}, 9, 2}, {{false, false}, 10, 3}, {{true, false}, 11, 3}, {{false, false}, 12, 4}, {{true, false}, 13, 5}, {{false, false}, 14, 6}, {{true, false}, 16, 7}, {{true, false}, 16, 8}, {{false, false}, 17, 9}, {{true, false}, 18, 10}},
    11,
    2,
    {{{true, false}, 19, 11}, {{false, false}, 20, 12}, {{false, false}, 19, 1}, {{true, false}, 21, 2}, {{false, false}, 21, 3}, {{true, false}, 23, 4}, {{false, false}, 23, 5}, {{false, false}, 25, 6}, {{true, false}, 27, 7}, {{true, false}, 27, 8}, {{false, false}, 28, 9}, {{true, false}, 29, 10}}, // Năm 51
    1,
    2,
    {{{true, true}, 30, 11}, {{false, false}, 1, 1}, {{true, false}, 1, 2}, {{false, false}, 2, 3}, {{false, false}, 3, 4}, {{true, false}, 5, 5}, {{false, false}, 5, 6}, {{false, false}, 7, 7}, {{true, false}, 9, 8}, {{false, false}, 9, 8}, {{true, false}, 11, 9}, {{true, false}, 11, 10}}, // Năm 52
    18,
    2,
    {{{true, false}, 12, 11}, {{false, false}, 13, 12}, {{true, false}, 12, 1}, {{true, false}, 13, 2}, {{false, false}, 13, 3}, {{false, false}, 15, 4}, {{true, false}, 16, 5}, {{false, false}, 17, 6}, {{false, false}, 19, 7}, {{true, false}, 20, 8}, {{false, false}, 21, 9}, {{true, false}, 22, 10}},
    8,
    2,
    {{{true, false}, 23, 11}, {{true, false}, 24, 12}, {{false, false}, 22, 1}, {{true, false}, 24, 2}, {{false, false}, 24, 3}, {{true, false}, 26, 4}, {{false, false}, 26, 5}, {{true, false}, 28, 6}, {{false, false}, 29, 7}, {{true, false}, 1, 9}, {{false, false}, 2, 10}, {{true, false}, 3, 11}},
    28,
    1,
    {{{true, false}, 4, 12}, {{false, false}, 5, 1}, {{true, false}, 4, 2}, {{true, false}, 5, 3}, {{false, false}, 5, 4}, {{true, false}, 7, 5}, {{false, false}, 7, 6}, {{true, false}, 9, 6}, {{false, false}, 10, 7}, {{false, false}, 11, 8}, {{true, false}, 13, 9}, {{false, false}, 13, 10}},
    15,
    2,
    {{{true, false}, 15, 11}, {{false, false}, 16, 12}, {{true, false}, 16, 1}, {{true, false}, 17, 2}, {{false, false}, 17, 3}, {{true, false}, 19, 4}, {{true, false}, 19, 5}, {{false, false}, 20, 6}, {{true, false}, 22, 7}, {{false, false}, 22, 8}, {{false, false}, 24, 9}, {{true, false}, 25, 10}},
    4,
    2,
    {{{false, false}, 26, 11}, {{true, false}, 28, 12}, {{false, false}, 26, 1}, {{true, false}, 28, 2}, {{false, false}, 28, 3}, {{true, false}, 30, 4}, {{true, false}, 30, 5}, {{true, false}, 2, 7}, {{false, false}, 3, 8}, {{true, false}, 4, 9}, {{false, false}, 5, 10}, {{true, false}, 6, 11}},
    24,
    1,
    {{{false, false}, 7, 12}, {{true, false}, 9, 1}, {{false, false}, 7, 2}, {{true, false}, 9, 3}, {{false, false}, 9, 4}, {{true, false}, 11, 4}, {{false, false}, 11, 5}, {{true, false}, 13, 6}, {{true, false}, 14, 7}, {{false, false}, 14, 8}, {{true, false}, 16, 9}, {{false, false}, 16, 10}},
    12,
    2,
    {{{true, false}, 18, 11}, {{false, false}, 19, 12}, {{true, false}, 18, 1}, {{false, false}, 19, 2}, {{true, false}, 20, 3}, {{false, false}, 21, 4}, {{true, false}, 22, 5}, {{false, false}, 23, 6}, {{true, false}, 25, 7}, {{false, false}, 25, 8}, {{true, false}, 27, 9}, {{true, false}, 27, 10}},
    2,
    2,
    {{{false, false}, 28, 11}, {{true, false}, 30, 12}, {{false, true}, 29, 1}, {{false, false}, 1, 3}, {{true, false}, 2, 4}, {{false, false}, 3, 5}, {{false, false}, 4, 6}, {{true, false}, 6, 7}, {{false, false}, 7, 8}, {{true, false}, 8, 9}, {{true, false}, 9, 10}, {{true, false}, 9, 11}}, // Năm 60
    21,
    1,
    {{{false, false}, 10, 12}, {{true, false}, 12, 1}, {{true, false}, 10, 2}, {{false, false}, 11, 3}, {{false, false}, 12, 3}, {{true, false}, 14, 4}, {{false, false}, 14, 5}, {{false, false}, 16, 6}, {{true, false}, 18, 7}, {{false, false}, 18, 8}, {{true, false}, 20, 9}, {{true, false}, 20, 10}},
    9,
    2,
    {{{true, false}, 21, 11}, {{false, false}, 22, 12}, {{true, false}, 21, 1}, {{true, false}, 22, 2}, {{false, false}, 22, 3}, {{false, false}, 24, 4}, {{true, false}, 25, 5}, {{false, false}, 26, 6}, {{false, false}, 28, 7}, {{true, false}, 29, 8}, {{true, true}, 1, 10}, {{false, false}, 1, 11}}, // Năm 62
    29,
    1,
    {{{true, false}, 3, 12}, {{true, false}, 4, 1}, {{true, false}, 2, 2}, {{false, false}, 3, 3}, {{true, false}, 4, 4}, {{false, false}, 5, 5}, {{true, false}, 6, 6}, {{false, false}, 7, 7}, {{false, false}, 9, 7}, {{true, false}, 10, 8}, {{false, false}, 11, 9}, {{true, false}, 12, 10}},
    17,
    2,
    {{{false, false}, 13, 11}, {{true, false}, 15, 12}, {{true, false}, 14, 1}, {{true, false}, 15, 2}, {{false, false}, 15, 3}, {{true, false}, 17, 4}, {{false, false}, 17, 5}, {{true, false}, 19, 6}, {{false, false}, 20, 7}, {{false, false}, 21, 8}, {{true, false}, 23, 9}, {{false, false}, 23, 10}},
    5,
    2,
    {{{true, false}, 25, 11}, {{false, false}, 26, 12}, {{true, false}, 25, 1}, {{true, false}, 26, 2}, {{false, false}, 26, 3}, {{true, false}, 28, 4}, {{true, false}, 28, 5}, {{false, false}, 29, 6}, {{true, false}, 2, 8}, {{false, false}, 2, 9}, {{true, false}, 4, 10}, {{false, false}, 4, 11}},
    26,
    1,
    {{{true, false}, 6, 12}, {{false, false}, 7, 1}, {{true, false}, 6, 2}, {{false, false}, 7, 3}, {{true, false}, 8, 4}, {{true, false}, 9, 5}, {{false, false}, 9, 5}, {{true, false}, 11, 6}, {{false, false}, 12, 7}, {{true, false}, 13, 8}, {{false, false}, 14, 9}, {{true, false}, 15, 10}},
    14,
    2,
    {{{false, false}, 16, 11}, {{true, false}, 18, 12}, {{false, false}, 16, 1}, {{true, false}, 18, 2}, {{false, false}, 18, 3}, {{true, false}, 20, 4}, {{false, false}, 20, 5}, {{true, false}, 22, 6}, {{true, false}, 23, 7}, {{false, false}, 23, 8}, {{true, false}, 25, 9}, {{false, false}, 25, 10}},
    3,
    2,
    {{{true, false}, 27, 11}, {{false, false}, 28, 12}, {{true, false}, 28, 1}, {{false, false}, 29, 2}, {{true, false}, 30, 3}, {{false, false}, 2, 5}, {{true, false}, 3, 6}, {{true, false}, 4, 7}, {{false, false}, 5, 8}, {{true, false}, 6, 9}, {{true, false}, 7, 10}, {{false, false}, 7, 11}},
    23,
    1,
    {{{true, false}, 9, 12}, {{false, false}, 10, 1}, {{true, false}, 9, 2}, {{false, false}, 10, 3}, {{true, false}, 11, 4}, {{false, false}, 12, 4}, {{false, false}, 13, 5}, {{true, false}, 15, 6}, {{false, false}, 16, 7}, {{true, false}, 17, 8}, {{true, false}, 18, 9}, {{true, false}, 18, 10}},
    11,
    2,
    {{{false, false}, 19, 11}, {{true, false}, 21, 12}, {{false, false}, 19, 1}, {{true, false}, 21, 2}, {{false, false}, 21, 3}, {{true, false}, 23, 4}, {{false, false}, 23, 5}, {{false, false}, 25, 6}, {{true, false}, 27, 7}, {{false, false}, 27, 8}, {{true, false}, 29, 9}, {{false, true}, 29, 10}}, // Năm 70
    31,
    1,
    {{{true, false}, 1, 12}, {{false, false}, 2, 1}, {{true, false}, 30, 1}, {{true, false}, 2, 3}, {{false, false}, 2, 4}, {{true, false}, 4, 5}, {{false, false}, 4, 6}, {{false, false}, 6, 7}, {{true, false}, 8, 8}, {{false, false}, 8, 8}, {{true, false}, 10, 9}, {{false, false}, 10, 10}},
    19,
    2,
    {{{true, false}, 12, 11}, {{true, false}, 13, 12}, {{true, false}, 12, 1}, {{false, false}, 13, 2}, {{true, false}, 14, 3}, {{false, false}, 15, 4}, {{true, false}, 16, 5}, {{false, false}, 17, 6}, {{false, false}, 19, 7}, {{true, false}, 20, 8}, {{false, false}, 21, 9}, {{false, false}, 22, 10}},
    7,
    2,
    {{{true, false}, 24, 11}, {{true, false}, 25, 12}, {{true, false}, 23, 1}, {{false, false}, 24, 2}, {{true, false}, 25, 3}, {{true, false}, 26, 4}, {{false, false}, 26, 5}, {{true, false}, 28, 6}, {{false, false}, 29, 7}, {{true, false}, 1, 9}, {{false, false}, 2, 10}, {{false, false}, 3, 11}},
    27,
    1,
    {{{true, false}, 5, 12}, {{true, false}, 6, 1}, {{false, false}, 4, 2}, {{true, false}, 6, 3}, {{true, false}, 6, 4}, {{false, false}, 7, 5}, {{true, false}, 8, 6}, {{false, false}, 9, 6}, {{true, false}, 11, 7}, {{false, false}, 11, 8}, {{true, false}, 13, 9}, {{false, false}, 13, 10}},
    15,
    2,
    {{{true, false}, 15, 11}, {{false, false}, 16, 12}, {{true, false}, 15, 1}, {{false, false}, 16, 2}, {{true, false}, 17, 3}, {{false, false}, 18, 4}, {{true, false}, 19, 5}, {{true, false}, 20, 6}, {{false, false}, 21, 7}, {{true, false}, 22, 8}, {{false, false}, 23, 9}, {{true, false}, 24, 10}},
    5,
    2,
    {{{false, false}, 25, 11}, {{true, false}, 27, 12}, {{false, false}, 26, 1}, {{true, false}, 28, 2}, {{false, false}, 28, 3}, {{true, false}, 30, 4}, {{true, false}, 1, 6}, {{false, false}, 2, 7}, {{true, false}, 4, 8}, {{true, false}, 4, 9}, {{false, false}, 5, 10}, {{true, false}, 6, 11}},
    24,
    1,
    {{{false, false}, 7, 12}, {{true, false}, 9, 1}, {{false, false}, 7, 2}, {{true, false}, 9, 3}, {{false, false}, 9, 4}, {{false, false}, 11, 4}, {{true, false}, 12, 5}, {{false, false}, 13, 6}, {{true, false}, 15, 7}, {{true, false}, 15, 8}, {{false, false}, 16, 9}, {{true, false}, 17, 10}},
    12,
    2,
    {{{true, false}, 18, 11}, {{false, false}, 19, 12}, {{true, false}, 18, 1}, {{false, false}, 19, 2}, {{true, false}, 20, 3}, {{false, false}, 21, 4}, {{false, false}, 22, 5}, {{true, false}, 24, 6}, {{false, false}, 25, 7}, {{true, false}, 26, 8}, {{false, false}, 27, 9}, {{true, false}, 28, 10}}, // Năm 78
    2,
    2,
    {{{true, false}, 29, 11}, {{true, false}, 30, 12}, {{false, false}, 28, 1}, {{true, false}, 30, 2}, {{true, false}, 1, 4}, {{false, false}, 2, 5}, {{false, false}, 3, 6}, {{true, false}, 5, 7}, {{false, false}, 6, 8}, {{true, false}, 7, 9}, {{false, false}, 8, 10}, {{true, false}, 9, 11}},
    22,
    1,
    {{{true, false}, 10, 12}, {{true, false}, 11, 1}, {{false, false}, 10, 2}, {{true, false}, 12, 3}, {{false, false}, 12, 3}, {{true, false}, 14, 4}, {{false, false}, 14, 5}, {{false, false}, 16, 6}, {{false, false}, 18, 7}, {{true, false}, 19, 8}, {{false, false}, 20, 9}, {{true, false}, 21, 10}},
    9,
    2,
    {{{true, false}, 22, 11}, {{true, false}, 23, 12}, {{false, false}, 21, 1}, {{true, false}, 23, 2}, {{true, false}, 23, 3}, {{false, false}, 24, 4}, {{true, false}, 25, 5}, {{false, false}, 26, 6}, {{false, false}, 28, 7}, {{true, false}, 29, 8}, {{false, false}, 1, 10}, {{true, false}, 2, 11}},
    29,
    1,
    {{{true, false}, 3, 12}, {{false, false}, 4, 1}, {{true, false}, 3, 2}, {{true, false}, 4, 3}, {{false, false}, 4, 4}, {{true, false}, 6, 5}, {{false, false}, 6, 6}, {{true, false}, 8, 7}, {{false, false}, 9, 7}, {{true, false}, 10, 8}, {{false, false}, 11, 9}, {{false, false}, 12, 10}},
    17,
    2,
    {{{true, false}, 14, 11}, {{true, false}, 15, 12}, {{false, false}, 13, 1}, {{true, false}, 15, 2}, {{true, false}, 15, 3}, {{false, false}, 16, 4}, {{true, false}, 17, 5}, {{false, false}, 18, 6}, {{true, false}, 20, 7}, {{false, false}, 20, 8}, {{true, false}, 22, 9}, {{false, false}, 22, 10}},
    6,
    2,
    {{{true, false}, 24, 11}, {{false, false}, 25, 12}, {{true, false}, 25, 1}, {{false, false}, 26, 2}, {{true, false}, 27, 3}, {{false, false}, 28, 4}, {{true, false}, 29, 5}, {{true, false}, 30, 6}, {{true, false}, 2, 8}, {{false, false}, 2, 9}, {{true, false}, 4, 10}, {{false, false}, 4, 11}},
    26,
    1,
    {{{true, false}, 6, 12}, {{false, false}, 7, 1}, {{false, false}, 6, 2}, {{true, false}, 8, 3}, {{false, false}, 8, 4}, {{true, false}, 10, 5}, {{true, false}, 10, 5}, {{false, false}, 11, 6}, {{true, false}, 13, 7}, {{false, false}, 13, 8}, {{true, false}, 15, 9}, {{true, false}, 15, 10}},
    14,
    2,
    {{{false, false}, 16, 11}, {{true, false}, 18, 12}, {{false, false}, 16, 1}, {{false, false}, 18, 2}, {{true, false}, 19, 3}, {{false, false}, 20, 4}, {{true, false}, 21, 5}, {{false, false}, 22, 6}, {{true, false}, 24, 7}, {{true, false}, 24, 8}, {{false, false}, 25, 9}, {{true, false}, 26, 10}},
    3,
    2,
    {{{true, false}, 27, 11}, {{false, false}, 28, 12}, {{true, false}, 27, 1}, {{false, false}, 28, 2}, {{true, false}, 29, 3}, {{false, false}, 1, 5}, {{true, false}, 2, 6}, {{false, false}, 3, 7}, {{true, false}, 5, 8}, {{false, false}, 5, 9}, {{true, false}, 7, 10}, {{true, false}, 7, 11}},
    24,
    1,
    {{{true, false}, 8, 12}, {{false, false}, 9, 1}, {{true, false}, 9, 2}, {{false, false}, 10, 3}, {{true, false}, 11, 4}, {{false, false}, 12, 4}, {{false, false}, 13, 5}, {{false, false}, 15, 6}, {{true, false}, 17, 7}, {{false, false}, 17, 8}, {{true, false}, 19, 9}, {{true, false}, 19, 10}},
    10,
    2,
    {{{true, false}, 20, 11}, {{false, false}, 21, 12}, {{true, false}, 20, 1}, {{true, false}, 21, 2}, {{false, false}, 21, 3}, {{true, false}, 23, 4}, {{false, false}, 23, 5}, {{false, false}, 25, 6}, {{false, false}, 27, 7}, {{true, false}, 28, 8}, {{false, false}, 29, 9}, {{true, true}, 30, 10}}, // Năm 89
    30,
    1,
    {{{false, false}, 1, 12}, {{true, false}, 3, 1}, {{true, false}, 1, 2}, {{true, false}, 2, 3}, {{false, false}, 2, 4}, {{true, false}, 4, 5}, {{false, false}, 4, 6}, {{false, false}, 6, 7}, {{true, false}, 8, 8}, {{false, false}, 8, 8}, {{false, false}, 10, 9}, {{true, false}, 11, 10}},
    18,
    2,
    {{{false, false}, 12, 11}, {{true, false}, 14, 12}, {{true, false}, 12, 1}, {{true, false}, 13, 2}, {{false, false}, 13, 3}, {{true, false}, 15, 4}, {{false, false}, 15, 5}, {{true, false}, 17, 6}, {{false, false}, 18, 7}, {{true, false}, 19, 8}, {{false, false}, 20, 9}, {{false, false}, 21, 10}},
    7,
    2,
    {{{true, false}, 23, 11}, {{false, false}, 24, 12}, {{true, false}, 24, 1}, {{true, false}, 25, 2}, {{false, false}, 25, 3}, {{true, false}, 27, 4}, {{true, false}, 27, 5}, {{false, false}, 28, 6}, {{true, false}, 30, 7}, {{true, false}, 1, 9}, {{false, false}, 2, 10}, {{false, false}, 3, 11}},
    27,
    1,
    {{{true, false}, 5, 12}, {{false, false}, 6, 1}, {{true, false}, 5, 2}, {{false, false}, 6, 3}, {{true, false}, 7, 4}, {{true, false}, 8, 5}, {{false, false}, 8, 6}, {{true, false}, 10, 6}, {{true, false}, 11, 7}, {{false, false}, 11, 8}, {{true, false}, 13, 9}, {{false, false}, 13, 10}},
    15,
    2,
    {{{true, false}, 15, 11}, {{false, false}, 16, 12}, {{false, false}, 15, 1}, {{true, false}, 17, 2}, {{false, false}, 17, 3}, {{true, false}, 19, 4}, {{false, false}, 19, 5}, {{true, false}, 21, 6}, {{true, false}, 22, 7}, {{false, false}, 22, 8}, {{true, false}, 24, 9}, {{true, false}, 24, 10}},
    5,
    2,
    {{{false, false}, 25, 11}, {{true, false}, 27, 12}, {{false, false}, 25, 1}, {{false, false}, 27, 2}, {{true, false}, 28, 3}, {{false, false}, 29, 4}, {{true, false}, 30, 5}, {{true, false}, 2, 7}, {{false, false}, 3, 8}, {{true, false}, 4, 9}, {{true, false}, 5, 10}, {{true, false}, 5, 11}},
    25,
    1,
    {{{false, false}, 6, 12}, {{true, false}, 8, 1}, {{false, false}, 7, 2}, {{true, false}, 9, 3}, {{false, false}, 9, 4}, {{false, false}, 11, 4}, {{true, false}, 12, 5}, {{false, false}, 13, 6}, {{false, false}, 15, 7}, {{true, false}, 16, 8}, {{true, false}, 17, 9}, {{true, false}, 17, 10}},
    12,
    2,
    {{{false, false}, 18, 11}, {{true, false}, 20, 12}, {{true, false}, 18, 1}, {{false, false}, 19, 2}, {{true, false}, 20, 3}, {{false, false}, 21, 4}, {{false, false}, 22, 5}, {{false, false}, 24, 6}, {{true, false}, 26, 7}, {{false, false}, 26, 8}, {{true, false}, 28, 9}, {{true, false}, 28, 10}},
    1,
    2,
    {{{false, true}, 29, 11}, {{false, false}, 1, 1}, {{true, false}, 29, 1}, {{true, false}, 30, 2}, {{true, false}, 1, 4}, {{false, false}, 2, 5}, {{false, false}, 3, 6}, {{false, false}, 5, 7}, {{true, false}, 7, 8}, {{false, false}, 7, 9}, {{true, false}, 9, 10}, {{false, false}, 9, 11}}, // Năm 98
    21,
    1,
    {{{true, false}, 11, 12}, {{true, false}, 12, 1}, {{true, false}, 10, 2}, {{false, false}, 11, 2}, {{true, false}, 12, 3}, {{false, false}, 13, 4}, {{true, false}, 14, 5}, {{false, false}, 15, 6}, {{false, false}, 17, 7}, {{true, false}, 18, 8}, {{false, false}, 19, 9}, {{true, false}, 20, 10}}};

DaysStruct cvtSun2Lunar(uint8_t dd, uint8_t mm, uint8_t yy = 00);
