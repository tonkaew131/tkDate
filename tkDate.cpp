#include "tkDate.h"

#include "Arduino.h"

const int dayInMonths[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const int sPerDay = 86400;
const int sPerHour = 3600;
const int sPerMinute = 60;

tkDate::tkDate(int YYYY, int MM, int DD, int hh, int mm, int ss) {
    if (YYYY < 1970) YYYY = 1970;
    _YYYY = YYYY;

    if (MM > 11) MM = 11;
    if (MM < 0) MM = 0;
    _MM = MM - 1;

    _DD = DD;

    _hh = hh;
    _mm = mm;
    _ss = ss;
}

int isLeapYear(int YYYY) {
    if (YYYY % 4 == 0) {
        if (YYYY % 100 == 0) {
            if (YYYY % 400 == 0) return true;
            return false;
        }
        return true;
    }
    return false;
}

void tkDate::setTime(unsigned long s) {
    // days in every 10 years since 1970
    unsigned int dayEveryTenYear[] = {
        0, 3652, 7305, 10957, 14610, 18262, 21915, 25567,
        29220, 32872, 36525, 40177, 43830, 47482, 51134, 54786,
        58439, 62091, 65744, 69396, 73049, 76701, 80354, 84006,
        87658, 91310, 94963, 98615, 102268, 105920, 109573, 113225,
        116878, 120530, 124182, 127834, 131487, 135139, 138792, 142444,
        146097, 149749, 153402, 157054, 160707, 164359, 168012, 171664,
        175317, 178969, 182622, 186274, 189927, 193579, 197231, 200883,
        204536, 208188, 211841, 215493, 219146, 222798, 226451, 230103,
        233755, 237407, 241060, 244712, 248365, 252017, 255670, 259322,
        262975, 266627, 270279, 273931, 277584, 281236, 284889, 288541,
        292194, 295846, 299499, 303151, 306804, 310456, 314109, 317761,
        321414, 325066, 328719, 332371, 336024, 339676, 343328, 346980,
        350633, 354285, 357938, 361590};

    int tenYear = 0;
    int day = s / sPerDay;
    for (int i = 1; i < (sizeof(dayEveryTenYear) - sizeof(dayEveryTenYear[0])) - 1; i++) {
        if (dayEveryTenYear[i + 1] > day) {
            tenYear = i;
            break;
        }
    }
    if (day < dayEveryTenYear[1]) tenYear = 0;
    s -= dayEveryTenYear[tenYear] * sPerDay;

    int currYear = (tenYear * 10) + 1970;
    int dayFromYear;
    while (true) {
        dayFromYear = 365;
        if (isLeapYear(currYear)) dayFromYear += 1;

        // Less than a Year
        if (s < (dayFromYear * sPerDay))
            break;

        s -= dayFromYear * sPerDay;
        currYear += 1;
    }
    _YYYY = currYear;

    int currMonth = 0;
    int dayFromMonth;
    for (int m = 0; m < 12; m++) {
        dayFromMonth = dayInMonths[m];
        if (m == 1 && isLeapYear(_YYYY)) dayFromMonth += 1;

        // Less than a Month
        if (s < (dayFromMonth * sPerDay)) {
            currMonth = m;
            break;
        }

        s -= dayFromMonth * sPerDay;
    }
    _MM = currMonth;

    int currDay = (s - (s % sPerDay)) / sPerDay;
    s -= currDay * sPerDay;
    currDay += 1;
    _DD = currDay;

    int currHour = (s - (s % sPerHour)) / sPerHour;
    s -= currHour * sPerHour;
    _hh = currHour;

    int currMinute = (s - (s % sPerMinute)) / sPerMinute;
    s -= currMinute * sPerMinute;
    _mm = currMinute;

    _ss = s;
}

int tkDate::getTime() {
    unsigned long s = 0UL;

    int dayFromYear = (_YYYY - 1970) * 365;
    dayFromYear += floor((_YYYY - 1969) / 4);
    dayFromYear -= floor((_YYYY - 1901) / 100);
    dayFromYear += floor((_YYYY - 1601) / 400);
    s += sPerDay * dayFromYear;

    int dayFromMonth = 0;
    for (int m = 0; m < _MM; m++) {
        dayFromMonth += dayInMonths[m];
        if (m == 1 && isLeapYear(_YYYY)) dayFromMonth += 1;
    }
    s += sPerDay * dayFromMonth;

    s += sPerDay * (_DD - 1);
    s += sPerHour * _hh;
    s += sPerMinute * _mm;
    s += _ss;
    return s;
}

int tkDate::getHours() {
    return _hh;
}

int tkDate::getMinutes() {
    return _mm;
}

int tkDate::getSeconds() {
    return _ss;
}

int tkDate::getDate() {
    // Day of the month
    return _DD;
}

int tkDate::getDay() {
    // Sunday - Saturday : 0 - 6
    int day = floor(getTime() / sPerDay);
    return (day + 4) % 7;
}

int tkDate::getMonth() {
    // 0 - 11
    return _MM;
}

int tkDate::getFullYear() {
    return _YYYY;
}

String leadingZero(int num, int digit) {
    String str = String(num);
    for (int i = 0; i < digit; i++) str = String("0") + str;

    return str.substring(str.length() - digit, str.length());
}

String tkDate::toISOString() {
    String date = leadingZero(_YYYY, 4) + String("-");
    date += leadingZero(_MM + 1, 2) + String("-");
    date += leadingZero(_DD, 2) + String("T");

    date += leadingZero(_hh, 2) + String(":");
    date += leadingZero(_mm, 2) + String(":");
    date += leadingZero(_ss, 2) + String("Z");
    return date;
}