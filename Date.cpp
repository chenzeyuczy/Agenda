// Copyright [2013] chenzy
#include "Date.h"

Date::Date():year_(1000), month_(1), day_(1), hour_(0), minute_(0) {}
Date::Date(int y, int m, int d, int h, int min): year_(y),
    month_(m), day_(d), hour_(h), minute_(min) {}
int Date::getYear() const {return year_;}
void Date::setYear(int year) {year_ = year;}
int Date::getMonth() const {return month_;}
void Date::setMonth(int month) {month_ = month;}
int Date::getDay() const {return day_;}
void Date::setDay(int day) {day_ = day;}
int Date::getHour() const {return hour_;}
void Date::setHour(int hour) {hour_ = hour;}
int Date::getMinute() const {return minute_;}
void Date::setMinute(int minute) {minute_ = minute;}
bool Date::isValid(Date date) {
  if (date.year_ < 1000 || date.year_ > 9999) return false;
  if (date.month_ < 1 || date.month_ > 12) return false;
  if (date.day_ < 1 || date.day_ > 31) return false;
  if (date.hour_ < 0 || date.hour_ > 23) return false;
  if (date.minute_ < 0 || date.minute_ > 59) return false;
  if (date.day_ == 31) {
    switch (date.month_) {
    case 4: case 6: case 9: case 11:
      return false;
    }
  }
  if (date.month_ == 2) {
    if ((date.year_ % 4 == 0 && date.year_ % 100 != 0) ||
    date.year_ % 400 == 0) {
      if (date.day_ >29) return false;
    } else {
      if (date.day_ > 28) return false;
    }
  }
  return true;
}
Date Date::stringToDate(std::string dateString) {
  int y, m, d, h, min, i;
  y = m = d = h = min = 0;
  for (i = 0; i < 4; i++) {
    y *= 10;
    y += dateString[i] - '0';
  }
  for (i = 5; i < 7; i++) {
    m *= 10;
    m += dateString[i] - '0';
  }
  for (i =8; i < 10; i++) {
    d *= 10;
    d += dateString[i] - '0';
  }
  for (i = 11; i < 13; i++) {
    h *= 10;
    h += dateString[i] - '0';
  }
  for (i = 14; i < 16; i++) {
    min *= 10;
    min += dateString[i] - '0';
  }
  Date temp(y, m, d, h, min);
  return temp;
}
std::string Date::dateToString(Date date) {
  std::string s;
  s += date.year_ / 1000 + '0';
  s += date.year_ % 1000 / 100 + '0';
  s += date.year_ % 100 / 10 + '0';
  s += date.year_ % 10 + '0';
  s += '-';
  s += date.month_ < 10 ? '0' : '1';
  s += date.month_ % 10 + '0';
  s += '-';
  s += date.day_ / 10 + '0';
  s += date.day_ % 10 + '0';
  s += '/';
  s += date.hour_ / 10 + '0';
  s += date.hour_ % 10 + '0';
  s += ':';
  s += date.minute_ / 10 + '0';
  s += date.minute_ % 10 + '0';
  return s;
}

Date &Date::operator=(const Date& date) {
  year_ = date.year_;
  month_ = date.month_;
  day_ = date.day_;
  hour_ = date.hour_;
  minute_ = date.minute_;
  return *this;
}
bool Date::operator==(const Date& date) const {
  if (year_ != date.year_) return false;
  if (month_ != date.month_) return false;
  if (day_ != date.day_) return false;
  if (hour_ != date.hour_) return false;
  if (minute_ != date.minute_) return false;
  return true;
}
bool Date::operator>(const Date& date) const {
  if (year_ > date.year_) return true;
  if (year_ < date.year_) return false;
  if (month_ > date.month_) return true;
  if (month_ < date.month_) return false;
  if (day_ > date.day_) return true;
  if (day_ < date.day_) return false;
  if (hour_ > date.hour_) return true;
  if (hour_ < date.hour_) return false;
  if (minute_ > date.minute_) return true;
  if (minute_ < date.minute_) return false;
  return false;
}
bool Date::operator<(const Date& date) const {
  if (year_ < date.year_) return true;
  if (year_ > date.year_) return false;
  if (month_ < date.month_) return true;
  if (month_ > date.month_) return false;
  if (day_ < date.day_) return true;
  if (day_ > date.day_) return false;
  if (hour_ < date.hour_) return true;
  if (hour_ > date.hour_) return false;
  if (minute_ < date.minute_) return true;
  if (minute_ > date.minute_) return false;
  return false;
}
bool Date::operator>=(const Date& date) const {
  if (year_ > date.year_) return true;
  if (year_ < date.year_) return false;
  if (month_ > date.month_) return true;
  if (month_ < date.month_) return false;
  if (day_ > date.day_) return true;
  if (day_ < date.day_) return false;
  if (hour_ > date.hour_) return true;
  if (hour_ < date.hour_) return false;
  if (minute_ > date.minute_) return true;
  if (minute_ < date.minute_) return false;
  return true;
}
bool Date::operator<=(const Date& date) const {
  if (year_ < date.year_) return true;
  if (year_ > date.year_) return false;
  if (month_ < date.month_) return true;
  if (month_ > date.month_) return false;
  if (day_ < date.day_) return true;
  if (day_ > date.day_) return false;
  if (hour_ < date.hour_) return true;
  if (hour_ > date.hour_) return false;
  if (minute_ < date.minute_) return true;
  if (minute_ > date.minute_) return false;
  return true;
}
