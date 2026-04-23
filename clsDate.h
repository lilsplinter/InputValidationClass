#pragma once
#include<iostream>
#include<string>
#include <ctime>
#include <iomanip>
#include <limits>

using namespace std;

class clsDate
{

private:

short _Day;
short _Month;
short _Year;
void SetDate() {
    tm timeInfo;
    time_t now = time(0);
    localtime_s(&timeInfo, &now);
    _Day = timeInfo.tm_mday;
    _Month = timeInfo.tm_mon +1;
    _Year = timeInfo.tm_year + 1900;
}
void SetDate(string sDate , string delimter = "/")
{
    int DateParts[3] = {0,0,0};
	size_t pos = 0;
    if (sDate.empty()) {
        SetDate();
        return;
	}
    short index = 0;
    while (!sDate.empty() && pos != string::npos) {
        if (index > 2) {
            break;
        }
        pos = sDate.find(delimter);
        if (pos != string::npos) {
            DateParts[index] = stoi(sDate.substr(0, pos));
            sDate.erase(0, pos + 1);
			index++;
        }
        else {
            DateParts[index] = stoi(sDate);
            index++;
		}
    }
	clsDate date = ValidateDate(clsDate(DateParts[0], DateParts[1], DateParts[2]));
	_Day = date.Day;
	_Month = date.Month;
	_Year = date.Year;
}
void SetDate(short Day, short Month, short Year)
{
    clsDate date = ValidateDate(clsDate(Day, Month, Year));
    _Day = date.Day;
    _Month = date.Month;
    _Year = date.Year;
}
void SetDate(short days, short Year)
{
	clsDate date = GetDateFromDayOrderInYear(days, Year);
    _Day = date.Day;
    _Month = date.Month;
	_Year = date.Year;
}
public:
        
clsDate()
{
    SetDate();
}
clsDate(string sDate)
{
	SetDate(sDate);
}
clsDate(short Day, short Month, short Year)
{
	SetDate(Day, Month, Year);
}
clsDate(short days, short Year)
{
	SetDate(days, Year);
}
static clsDate ValidateDate(clsDate date) {
	short extraDays = 0;
	short extraMonths = 0;
    if (date.Year < 1) {
        date.Year = 1;
    }
    if (date.Month < 1) {
        date.Month = 1;
	}
    if (date.Day < 1) {
        date.Day = 1;
    }
    if (date.Month > 12) {
		extraMonths = date.Month - 12;
		date.Month = 12;
		date = date.IncreaseDateByXMonths(extraMonths);
    } 
    if (date.Day > NumberOfDaysInAMonth(date.Month, date.Year)) {
		extraDays = date.Day - NumberOfDaysInAMonth(date.Month, date.Year);
		date.Day = NumberOfDaysInAMonth(date.Month, date.Year);
		date = date.AddDays(extraDays);
    }
    return date;
}
clsDate ValidateDate() {
    return ValidateDate(*this);
}
void SetDay(short Day) {
    *this = ValidateDate(clsDate(Day, _Month, _Year));
} short GetDay() const { 
    return _Day; 
}
void SetMonth(short Month) {
    *this = ValidateDate(clsDate(_Day, Month, _Year));
}
short GetMonth() const { 
    return _Month; 
}
void SetYear(short Year) {
    *this = ValidateDate(clsDate(_Day, _Month, Year));
}
short GetYear() const { 
    return _Year; 
}
void Print() {
    cout << DateToString();
}
__declspec(property(get = GetDay, put = SetDay)) short Day;
__declspec(property(get = GetMonth, put = SetMonth)) short Month;
__declspec(property(get = GetYear, put = SetYear)) short Year;
static clsDate GetSystemDate() {
    clsDate date;
    tm timeInfo;
    time_t now = time(0);
    localtime_s(&timeInfo, &now);
    date.Day = timeInfo.tm_mday;
    date.Month = timeInfo.tm_mon + 1;
    date.Year = timeInfo.tm_year + 1900;
    return date;
}
static bool IsValidDate(clsDate Date) {
    if (Date.Day > NumberOfDaysInAMonth(Date.Month, Date.Year) || Date.Month > 12 || Date.Year < 1) {
        return false;
    }
    return true;
}
bool IsValid() {
	return IsValidDate(*this);
}
static string DateToString(clsDate Date) {
    return to_string(Date._Day) + "/" +
        to_string(Date._Month) + "/" +
        to_string(Date._Year);
}
string DateToString() {
    return DateToString(*this);
}
static bool IsLeapYear(short Year) {
    return Year % 4 == 0 && Year % 100 != 0 ||  Year % 400 == 0;
}
bool IsLeapYear() {
    return IsLeapYear(_Year);
}
static short NumberOfDaysInAYear(short Year) {
    if (IsLeapYear(Year)) {
        return 366;
    }
    else {
        return 365;
    }
}
short NumberOfDaysInAYear() {
    return NumberOfDaysInAYear(_Year);
}
static short NumberOfHoursInAYear(short Year) { 
    return NumberOfDaysInAYear(Year) * 24;
}
short NumberOfHoursInAYear() {
    return NumberOfHoursInAYear(_Year);
}
static int NumberOfMinutesInAYear(short Year) {
    return NumberOfHoursInAYear(Year) * 60;
}
int NumberOfMinutesInAYear() {
    return NumberOfMinutesInAYear(_Year);
}
static int NumberOfSecondsInAYear(short Year) {
    return NumberOfMinutesInAYear(Year) * 60;
}
int NumberOfSecondsInAYear() {
    return NumberOfSecondsInAYear(_Year);
}
static short NumberOfDaysInAMonth(short Month, short Year) {
    short MonthsDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (Month == 2) {
        if (IsLeapYear(Year)) {
            return 29;
        }
        else {
            return 28;
        }
    }
    else {
        return MonthsDays[Month - 1];
    }
}
short NumberOfDaysInAMonth() {
    return NumberOfDaysInAMonth(_Month, _Year);
}
static short NumberOfHoursInAMonth(short Month, short Year) {
    return NumberOfDaysInAMonth(Month, Year) * 24;
}
short NumberOfHoursInAMonth() {
    return NumberOfHoursInAMonth(_Month, _Year);
}
static int NumberOfMinutesInAMonth(short Month, short Year) {
    return NumberOfHoursInAMonth(Month, Year) * 60;
}
int NumberOfMinutesInAMonth() {
    return NumberOfMinutesInAMonth(_Month, _Year);
}
static int NumberOfSecondsInAMonth(short Month, short Year) {
    return NumberOfMinutesInAMonth(Month, Year) * 60;
}
int NumberOfSecondsInAMonth() {
    return NumberOfSecondsInAMonth(_Month, _Year);
}
static short DayOfWeekOrder(short Day, short Month, short Year) {
    return (Day + (13 * (Month + 1) / 5) + Year % 100 + (Year % 100) / 4 + Year / 100 + 5 * (Year / 100)) % 7;
}
short DayOfWeekOrder() {
    return DayOfWeekOrder(_Day,_Month,_Year);
}
static string DayShortName(short DayOfWeekOrder) {
	string ShortName[7] = { "Sat", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri" };
	return ShortName[DayOfWeekOrder];
}
static string DayShortName(short Day, short Month, short Year) {
	return DayShortName(DayOfWeekOrder(Day, Month, Year));
}
string DayShortName() {
    return DayShortName(_Day, _Month, _Year);
}
static string MonthShortName(short MonthNumber) {
    string ShortName[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Sep", "Dec" };
    return ShortName[MonthNumber - 1];
}
static void PrintMonthCalendar(short Month, short Year) {
    cout << "______________" << MonthShortName(Month) << "________________" << endl << endl;
    cout << "Sun  Mon  Tue  Wed  Thu  Fri  Sat" << endl;
    int Day = 1;
    short firstDayIndex = DayOfWeekOrder(1, Month, Year);
    short totaldays = NumberOfDaysInAMonth(Month, Year);
    for (int i = 0; i < 42; i++) {
        if (i >= firstDayIndex && Day <= totaldays) {
            cout << setw(3) << Day << "  ";
            Day++;
        }
        else {
            cout << setw(3) << "   ";
        }
        if (i % 7 == 6) {
            cout << endl;
        }
    }
    cout << "_________________________________" << endl << endl;
}
void PrintMonthCalendar() {
	PrintMonthCalendar(_Month, _Year);
}
static void PrintYearCalendar(int Year) {
    for (int i = 1; i <= 12; i++) {
        PrintMonthCalendar(i, Year);
	}
}
void PrintYearCalendar() {
	PrintYearCalendar(_Year);
}
static short DaysFromTheBeginningOfTheYear(short Day, short Month, short Year) {
    short totaldays = 0;
    if (Month < 1 || Month > 12) {
            return totaldays;
	}
    for (int i = 1; i < Month; i++) {
        totaldays += NumberOfDaysInAMonth(i, Year);
	}
	return totaldays + Day;
}
short DaysFromTheBeginningOfTheYear() {
	return DaysFromTheBeginningOfTheYear(_Day, _Month, _Year);
}
static clsDate GetDateFromDayOrderInYear(short DateOrderInYear, short Year) {
    short maxDays = IsLeapYear(Year) ? 366 : 365;
    if (DateOrderInYear < 1 || DateOrderInYear > maxDays) {
        return clsDate();
	}
    short Month = 1;
    while (true) {
        short daysInMonth = NumberOfDaysInAMonth(Month, Year);
        if (DateOrderInYear <= daysInMonth) {
            return clsDate(DateOrderInYear, Month, Year);
        }
        DateOrderInYear -= daysInMonth;
        Month++;
    }
}
static bool IsDate1BeforeDate2(const clsDate& Date1,const clsDate& Date2) {
    if (Date1.GetYear() < Date2.GetYear()) return true;
    if (Date1.GetYear() > Date2.GetYear()) return false;
    if (Date1.GetMonth() < Date2.GetMonth()) return true;
    if (Date1.GetMonth() > Date2.GetMonth()) return false;
    return Date1.GetDay() < Date2.GetDay();
}
bool IsDate1BeforeDate2(const clsDate& Date2) {
    return IsDate1BeforeDate2(*this, Date2);
}
static bool IsDate1EqualDate2(const clsDate& Date1, const clsDate& Date2) {
    return Date1.GetYear() == Date2.GetYear() &&
            Date1.GetMonth() == Date2.GetMonth() &&
            Date1.GetDay() == Date2.GetDay();
}
bool IsDate1EqualDate2(const clsDate& Date2) {
    return IsDate1EqualDate2(*this, Date2);
}
static bool IsDate1AfterDate2(const clsDate& Date1, const clsDate& Date2) {
    return !IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2);
}
bool IsDate1AfterDate2(const clsDate& Date2) {
    return IsDate1AfterDate2(*this, Date2);
}
static bool IsLastDayInMonth(const clsDate& Date) {
	return NumberOfDaysInAMonth(Date.GetMonth(), Date.GetYear()) == Date.GetDay();
}
bool IsLastDayInMonth() {
	return IsLastDayInMonth(*this);
}
static bool IsLastMonthInYear(short Month) {
	return Month == 12;
}
static clsDate AddOneDay(clsDate Date) {
    if (Date.Day == NumberOfDaysInAMonth(Date.Month, Date.Year)) {
        if (Date.Month == 12) {
            Date.Year++;
            Date.Month = 1;
            Date.Day = 1;
        }
        else {
            Date.Day = 1;
            Date.Month++;
        }
    }
    else {
		Date.Day++;
    }
	return Date;
}
clsDate AddOneDay() {
	return AddOneDay(*this);
}
static clsDate AddDays(int days,clsDate Date) {
    for (int i = 1; i <= days; i++) {
        Date = AddOneDay(Date);
    }
	return Date;
}
clsDate AddDays(int days) {
	return AddDays(days, *this);
}
static void SwapDates(clsDate& Date1, clsDate& Date2) {
	clsDate temp = Date2;
	Date2 = Date1;
	Date1 = temp;
}
static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false) {
    if (IsDate1AfterDate2(Date1, Date2)) {
        SwapDates(Date1, Date2);
	}
	int difference = 0;
    while (!IsDate1EqualDate2(Date1, Date2)) {
        Date1 = AddOneDay(Date1);
        difference++;
    }
    if (IncludeEndDay) {
        difference++;
    }
	return difference;
}
int GetDifferenceInDays(clsDate Date2, bool IncludeEndDay = false) {
	return GetDifferenceInDays(*this, Date2, IncludeEndDay);
}
static int CalculateMyAgeInDays(clsDate DateOfBirth) {
	clsDate today = GetSystemDate();
	return GetDifferenceInDays(DateOfBirth, today);
}
static clsDate IncreaseDateByOneWeek(clsDate Date) {
	return AddDays(7, Date);
}
clsDate IncreaseDateByOneWeek() {
	return IncreaseDateByOneWeek(*this);
}
static clsDate IncreaseDateByXWeeks(short Weeks, clsDate Date) {
    for (short i = 1; i <= Weeks; i++) {
        Date = IncreaseDateByOneWeek(Date);
	}
	return Date;
}
clsDate IncreaseDateByXWeeks(short Weeks) {
	return IncreaseDateByXWeeks(Weeks, *this);
}
static clsDate IncreaseDateByOneMonth(clsDate Date) {
        if (Date.Month == 12) {
            Date.Year++;
            Date.Month = 1;
        }   
        if (Date.Day > NumberOfDaysInAMonth(Date.Month, Date.Year)) {
            Date.Day = NumberOfDaysInAMonth(Date.Month, Date.Year);
            Date.Month++;
		}
        else {
            Date.Month++;
		}
		return Date;
}
clsDate IncreaseDateByOneMonth() {
	return IncreaseDateByOneMonth(*this);
}
static clsDate IncreaseDateByXMonths(short Months, clsDate& Date) {
    for (short i = 1; i <= Months; i++) {
        Date = IncreaseDateByOneMonth(Date);
    }
	return Date;
}
clsDate IncreaseDateByXMonths(short Months) {
	return IncreaseDateByXMonths(Months, *this);
}
static clsDate IncreaseDateByOneYear(clsDate& Date) {
    if (Date.Month == 2 && Date.Day == 29 && !IsLeapYear(Date.Year + 1)) {
        Date.Day = 28;
	}
	Date.Year++;
	return Date;
}
clsDate IncreaseDateByOneYear() {
	return IncreaseDateByOneYear(*this);
}
static clsDate IncreaseDateByXYears(short Years, clsDate& Date) {
    for (short i = 1; i <= Years; i++) {
        Date = IncreaseDateByOneYear(Date);
	}
	return Date;
}
clsDate IncreaseDateByXYears(short Years) {
	return IncreaseDateByXYears(Years, *this);
}
static clsDate IncreaseDateByOneDecade(clsDate& Date) {
	return IncreaseDateByXYears(10, Date);
}
clsDate IncreaseDateByOneDecade() {
	return IncreaseDateByOneDecade(*this);
}
static clsDate IncreaseDateByXDecades(short Decade, clsDate& Date) {
    for (short i = 1; i <= Decade; i++) {
        Date = IncreaseDateByOneDecade(Date);
    }
	return Date;
}
clsDate IncreaseDateByXDecades(short Decade) {
	return IncreaseDateByXDecades(Decade, *this);
}
static clsDate IncreaseDateByOneCentury(clsDate& Date) {
	return IncreaseDateByXDecades(10, Date);
}
clsDate IncreaseDateByOneCentury() {
	return IncreaseDateByOneCentury(*this);
}
static clsDate IncreaseDateByOneMillennium(clsDate& Date) {
	return IncreaseDateByXDecades(100, Date);
}
clsDate IncreaseDateByOneMillennium() {
	return IncreaseDateByOneMillennium(*this);
}
static clsDate DecreaseDateByOneDay(clsDate Date) {
    if (Date.Day == 1) {
        if (Date.Month == 1) {
            Date.Year--;
            Date.Month = 12;
            Date.Day = 31;
        }
        else {
            Date.Month--;
            Date.Day = NumberOfDaysInAMonth(Date.Month,Date.Year);
        }
    }
    else {
        Date.Day--;
    }
    return Date;
}
clsDate DecreaseDateByOneDay() {
	return DecreaseDateByOneDay(*this);
}
static clsDate DecreaseDateByXDays(short Days, clsDate& Date) {
    for (short i = 1; i <= Days; i++) {
        Date = DecreaseDateByOneDay(Date);
	}
	return Date;
}
clsDate DecreaseDateByXDays(short Days) {
	return DecreaseDateByXDays(Days, *this);
}
static clsDate DecreaseDateByOneWeek(clsDate Date) {
    return DecreaseDateByXDays(7, Date);
}
clsDate DecreaseDateByOneWeek() {
    return DecreaseDateByOneWeek(*this);
}
static clsDate DecreaseDateByXWeeks(short Weeks, clsDate Date) {
    return DecreaseDateByXDays(Weeks * 7, Date);
}
clsDate DecreaseDateByXWeeks(short Weeks) {
    return DecreaseDateByXWeeks(Weeks, *this);
}
static clsDate DecreaseDateByOneMonth(clsDate Date) {
    if (Date.Month == 1) {
        Date.Year--;
        Date.Month = 12;
    }
    else if (Date.Day > NumberOfDaysInAMonth(Date.Month - 1, Date.Year)) {
        Date.Day = NumberOfDaysInAMonth(Date.Month - 1, Date.Year);
        Date.Month--;
    }
    else {
        Date.Month--;
    }
    return Date;
}
clsDate DecreaseDateByOneMonth() {
    return DecreaseDateByOneMonth(*this);
}
static clsDate DecreaseDateByXMonths(short Months, clsDate Date) {
    for (short i = 1; i <= Months; i++) {
        Date = DecreaseDateByOneMonth(Date);
    }
    return Date;
}
clsDate DecreaseDateByXMonths(short Months) {
    return DecreaseDateByXMonths(Months, *this);
}
static clsDate DecreaseDateByOneYear(clsDate Date) {
    if (Date.Month == 2 && Date.Day == 29 && !IsLeapYear(Date.Year - 1)) {
        Date.Day = 28;
    }
    Date.Year--;
    return Date;
}
clsDate DecreaseDateByOneYear() {
    return DecreaseDateByOneYear(*this);
}
static clsDate DecreaseDateByXYears(short Years, clsDate Date) {
    for (short i = 1; i <= Years; i++) {
        Date = DecreaseDateByOneYear(Date);
    }
    return Date;
}
clsDate DecreaseDateByXYears(short Years) {
    return DecreaseDateByXYears(Years, *this);
}
static clsDate DecreaseDateByOneDecade(clsDate Date) {
    return DecreaseDateByXYears(10, Date);
}
clsDate DecreaseDateByOneDecade() {
    return DecreaseDateByOneDecade(*this);
}
static clsDate DecreaseDateByXDecades(short Decades, clsDate Date) {
    for (short i = 1; i <= Decades; i++) {
        Date = DecreaseDateByOneDecade(Date);
    }
    return Date;
}
clsDate DecreaseDateByXDecades(short Decades) {
    return DecreaseDateByXDecades(Decades, *this);
}
static clsDate DecreaseDateByOneCentury(clsDate Date) {
    return DecreaseDateByXDecades(10, Date);
}
clsDate DecreaseDateByOneCentury() {
    return DecreaseDateByOneCentury(*this);
}
static clsDate DecreaseDateByOneMillennium(clsDate Date) {
    return DecreaseDateByXDecades(100, Date);
}
clsDate DecreaseDateByOneMillennium() {
    return DecreaseDateByOneMillennium(*this);
}
static bool IsEndOfWeek(clsDate Date) {
    return DayOfWeekOrder(Date.Day, Date.Month, Date.Year) == 0;
}
bool IsEndOfWeek() {
	return IsEndOfWeek(*this);
}
static bool IsWeekend(clsDate Date) {
    return IsEndOfWeek(Date) || DayOfWeekOrder(Date.Day, Date.Month, Date.Year) == 1;
}
bool IsWeekend() {
	return IsWeekend(*this);
}
static bool IsBusinessDay(clsDate Date) {
	return !IsWeekend(Date);
}
bool IsBusinessDay() {
	return IsBusinessDay(*this);
}
static short DaysUntilTheEndOfWeek(clsDate Date) {
	return (7 - DayOfWeekOrder(Date.Day, Date.Month, Date.Year)) % 7;
}
short DaysUntilTheEndOfWeek() {
	return DaysUntilTheEndOfWeek(*this);
}
static short DaysUntilTheEndOfMonth(clsDate Date1) {
	return NumberOfDaysInAMonth(Date1.Month, Date1.Year) - Date1.Day;
}
short DaysUntilTheEndOfMonth() {
	return DaysUntilTheEndOfMonth(*this);
}
static short DaysUntilTheEndOfYear(clsDate Date1) {
	return NumberOfDaysInAYear(Date1.Year) - DaysFromTheBeginningOfTheYear(Date1.Day, Date1.Month, Date1.Year);
}
short DaysUntilTheEndOfYear() {
	return DaysUntilTheEndOfYear(*this);
}
static short CalculateBusinessDays(clsDate DateFrom, clsDate DateTo) {
    short days = 0;
    while (!IsDate1EqualDate2(DateFrom, DateTo)) {
        if (IsBusinessDay(DateFrom)) {
            days++;
        }
        DateFrom = AddOneDay(DateFrom);
	}
	return days;
}
static short CalculateVacationDays(clsDate DateFrom, clsDate DateTo) {
    short days = 0;
    while (!IsDate1EqualDate2(DateFrom, DateTo)) {
        if (!IsBusinessDay(DateFrom)) {
            days++;
        }
        DateFrom = AddOneDay(DateFrom);
	}
	return days;
}
static clsDate CalculateVacationReturnDate(clsDate DateFrom, short VacationDays) {
    while (VacationDays > 0) {
        DateFrom = AddOneDay(DateFrom);
        if (IsBusinessDay(DateFrom)) {
            VacationDays--;
        }
	}
	return DateFrom;
}
enum enDateCompare { Before = -1, Equal = 0, After = 1 };
static enDateCompare CompareDates(clsDate Date1, clsDate Date2) {
    if (IsDate1BeforeDate2(Date1, Date2)) {
        return Before;
    }
    else if (IsDate1EqualDate2(Date1, Date2)) {
        return Equal;
    }
    else {
        return After;
	}
}
enDateCompare CompareDates(clsDate Date2) {
	return CompareDates(*this, Date2);
}

};