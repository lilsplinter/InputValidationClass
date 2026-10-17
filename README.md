# Input Validation Class (C++)

*Deutsch: C++-Klasse `clsInputValidate` zum Einlesen und Prüfen von Benutzereingaben in der Konsole (ganze Zahlen, Dezimalzahlen, Zahlenbereiche, Datum).*

A small reusable C++ class that reads input from the console and checks it before the program uses it. Wrong input (letters, `12abc`, numbers out of range, impossible dates) is rejected and the user is asked again, so the program does not crash or work with bad data.

## Features

| Function | What it does |
|---|---|
| `ReadIntNumber(message)` | Reads a whole line and accepts only a valid integer |
| `ReadIntNumberBetween(message, from, to)` | Same, but the number must be inside the range |
| `ReadDblNumber(message)` | Reads a decimal number (`nan` and `inf` are rejected) |
| `ReadDblNumberBetween(message, from, to)` | Same, but the number must be inside the range |
| `IsNumberBetween(number, from, to)` | Range check for any number type (template) |
| `IsDateBetween(date, from, to)` | Checks if a date is inside a date range |
| `IsValidDate(day, month, year)` | Checks if the numbers form a real date (`31/4/2025` is invalid) |

## Files

- `clsInputValidate.h`: the input validation class
- `clsDate.h`: date class used for the date checks
- `InputValidate.cpp`: example program that uses the class

## How to run

1. Open `InputValidate.sln` in Visual Studio (Windows).
2. Press **F5**.

`clsDate.h` uses `__declspec(property)` and `localtime_s`, which are Visual Studio (MSVC) features, so it does not compile with GCC.

## Example

```cpp
#include <iostream>
#include "clsInputValidate.h"
using namespace std;

int main()
{
    int Age = clsInputValidate::ReadIntNumberBetween("Enter your age (18-65): ", 18, 65);
    cout << "Age accepted: " << Age << endl;

    cout << clsInputValidate::IsValidDate(31, 4, 2025) << endl; // 0 (April has 30 days)
}
```

Input / output:

```
Enter your age (18-65): abc
Invalid number, please try again.
Enter your age (18-65): 70
The number must be between 18 and 65.
Enter your age (18-65): 30
Age accepted: 30
```

## Why it matters

Checking input before using it prevents crashes and wrong data. It is a basic habit in backend and security work.

## What I learned

- Reading a whole line with `getline` and checking it, instead of `cin >> number`, which leaves characters in the input
- Writing a reusable class with static functions and a template
- Why a date class that corrects wrong values by itself cannot be used to validate input

## Possible improvements

- Add string checks (empty input, maximum length, allowed characters)
- Add email and password rules
- Make `clsDate` work with GCC and Clang
- Add unit tests
