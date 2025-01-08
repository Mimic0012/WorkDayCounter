# WorkDayCounter

This repository contains a C program designed to check for valid dates, determine if a given date is a workday, and count the total and workdays between two dates. It includes functionality to account for leap years and national holidays, making it a comprehensive tool for date-related computations.

## Features
- **Leap Year Check:** Determines if a given year is a leap year.
- **Days in Month:** Retrieves the number of days in a specified month, considering leap years.
- **Valid Date Check:** Ensures a given date is valid.
- **National Holidays Check:** Identifies if a given date is a national holiday.
- **Workday Check:** Determines if a given date is a workday (Monday to Friday, excluding holidays).
- **Count Days:** Calculates the total and workdays between two specified dates.

## Functions
- `bool leapyear(int y)`: Checks if the given year is a leap year.
- `int days_in_month(int m, int y)`: Returns the number of days in the specified month and year.
- `bool is_valid_date(int y, int m, int d)`: Validates the given date.
- `bool national_holiday(int m, int d)`: Checks if the specified date is a national holiday.
- `bool isWorkDay(int y, int m, int d)`: Determines if the given date is a workday.
- `TResult countDays(int y1, int m1, int d1, int y2, int m2, int d2)`: Counts the total and workdays between two dates.

## Usage
Compile the program using a C compiler:
```sh
gcc -o workdaycounter workdaycounter.c
