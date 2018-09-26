#include "Date.h"
#include "stdlib.h"
#include <sstream>
using std::string;
Date::Date() {}
Date::Date(int y, int m, int d, int h, int mi) {
  year_ = y;
  month_ = m;
  day_ = d;
  hour_ = h;
  minute_ = mi;
}
int Date::getYear(void) const {
  return year_;
}
void Date::setYear(int y) {
  year_ = y;
}
int Date::getMonth(void) const {
  return month_;
}
void Date::setMonth(int m) {
  month_ = m;
}
int Date::getDay(void) const {
  return day_;
}
void Date::setDay(int d) {
  day_ = d;
}
int Date::getHour(void) const {
  return hour_;
}
void Date::setHour(int h) {
  hour_ = h;
}
int Date::getMinute(void) const {
  return minute_;
}
void Date::setMinute(int m) {
  minute_ = m;
}
bool Date::isValid(Date d) {
  if (d.year_ < 1000 || d.year_ > 9999)
    return false;
  if (d.month_ < 1 || d.month_ > 12)
    return false;
  if (d.day_ < 1 || d.day_ > 31)
    return false;
  if ((d.month_ == 4 || d.month_ == 6 || d.month_ == 9
       || d.month_ == 11) && d.day_ > 30)
    return false;
  if (d.month_ == 2 && d.day_ > 29)
    return false;
  if ((d.year_%4 != 0 || (d.year_%100 == 0 && d.year_%400 != 0))
      && d.month_ == 2 && d.day_ > 28)
    return false;
  if (d.hour_ < 0 || d.hour_ > 23)
    return false;
  if (d.minute_ < 0 || d.minute_ > 59)
    return false;
  return true;
}
Date Date::stringToDate(std::string s) {
  Date d;
  int tmp, i;
  tmp = 0;
  for (i = 0; i < 4; i++)
    tmp = tmp*10+s[i]-'0';
  d.setYear(tmp);
  tmp = 0;
  for (i = 5; i < 7; i++)
    tmp = tmp*10+s[i]-'0';
  d.setMonth(tmp);
  tmp = 0;
  for (i = 8; i < 10; i++)
    tmp = tmp*10+s[i]-'0';
  d.setDay(tmp);
  tmp = 0;
  for (i = 11; i < 13; i++)
    tmp = tmp*10+s[i]-'0';
  d.setHour(tmp);
  tmp = 0;
  for (i = 14; i < 16; i++)
    tmp = tmp*10+s[i]-'0';
  d.setMinute(tmp);
  return d;
}
std::string Date::dateToString(Date d) {
  if (!isValid(d))
    return "Invalid";
  string s;
  std::stringstream ss;
  ss << d.getYear() << '-';
  if (d.getMonth() < 10)
      ss << '0';
  ss << d.getMonth() << '-';
    if (d.getDay() < 10)
      ss << '0';
  ss << d.getDay() << '/';
  if (d.getHour() < 10)
      ss << '0';
  ss << d.getHour() << ':';
  if (d.getMinute() < 10)
      ss << '0';
  ss << d.getMinute();
  ss >> s;
  return s;
}
Date& Date::operator=(const Date& d) {
  year_ = d.year_;
  month_ = d.month_;
  day_ = d.day_;
  hour_ = d.hour_;
  minute_ = d.minute_;
  return *this;
}
bool Date::operator==(const Date& d) const {
  return year_ == d.year_ && month_ == d.month_ &&
    day_ == d.day_ && hour_ == d.hour_ && minute_ == d.minute_;
}
bool Date::operator>(const Date& d) const {
  if (year_ > d.year_) {
    return true;
  } else if (year_ < d.year_) {
    return false;
  } else {
    if (month_ > d.month_) {
      return true;
    } else if (month_ < d.month_) {
      return false;
    } else {
      if (day_ > d.day_) {
          return true;
      } else if (day_ < d.day_) {
          return false;
      } else {
          if (hour_ > d.hour_) {
              return true;
          } else if (hour_ < d.hour_) {
              return false;
          } else {
              if (minute_ > d.minute_) {
                  return true;
              } else {
                  return false;
              }
          }
      }
    }
  }
}
bool Date::operator<(const Date& d) const {
  return !(*this > d) && !(*this == d);
}
bool Date::operator>=(const Date& d) const {
  return (*this > d) || (*this == d);
}
bool Date::operator<=(const Date& d) const {
  return (*this < d) || (*this == d);
}
