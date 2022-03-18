#ifndef tkdate_h
#define tkdate_h

#include "Arduino.h"

class tkDate {
   public:
    tkDate(int YYYY, int MM, int DD, int hh, int mm, int ss);

    int getTime();
    void setTime(unsigned long s);

    int getHours();
    int getMinutes();
    int getSeconds();

    int getDate();
    int getDay();
    int getMonth();
    int getFullYear();

    String toISOString();

   private:
    int _YYYY;
    int _MM;
    int _DD;
    int _hh;
    int _mm;
    int _ss;
};

#endif