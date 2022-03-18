# tkDate

Time library for arduino

## Installation

Put `tkDate` folder in `Documents/Arduino/libraries/`

## Example

```cpp
#include "tkDate.h"

// Year, Month (1 - 12), Day, Hours, Minutes, Seconds
tkDate date1(2020, 12, 31, 23, 59, 59);

Serial.println(date1.toISOString());
// 2020-12-01T23:59:59Z

// Epoch time (in seconds)
Serial.println(date1.getTime());
// 1606867199

// Offset time by -7 hours
date1.setTime(date1.getTime() - (7 * 60 * 60));
Serial.println(date1.toISOString());
// 2020-12-01T16:59:59Z
```

## Document

```cpp
// Definition
tkDate(int YYYY, int MM, int DD, int hh, int mm, int ss);

// Methods
int getTime(); // Epoch time (in seconds)
void setTime(unsigned long s);

int getHours();
int getMinutes();
int getSeconds();

int getDate(); // Day of the month (1 - 31)
int getDay(); // Day of the week (0 - 6), where 0 represents Sunday
int getMonth(); // Month (0 - 11)
int getFullYear();

String toISOString(); // YYYY-MM-DDTHH:mm:ssZ
```

## Contributing

Feel free to fix my error.

## Authors

* **Athicha Leksansern** - *Initial work* - [Tonkaew](https://github.com/tonkaew131/)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details