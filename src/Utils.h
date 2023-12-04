#pragma once

#include <iostream>
using std::ostream;

class Date {

private:
	unsigned short int _day_of_month;
	unsigned short int _month;
	unsigned short int _year;
	unsigned short int _minutes;
	unsigned short int _hours;
	unsigned short int _seconds;
	void normalizeDate();
public:
	Date(std::string& date);
	Date(unsigned short int d,
		 unsigned short int m,
		 unsigned short int y,
		 unsigned short int min = 0,
		 unsigned short int h = 0,
		 unsigned short int s = 0) :
			_day_of_month(d), _month(m), _year(y), _minutes(min), _hours(h), _seconds(s)
	{
		normalizeDate();
	}
	inline unsigned short int day() const { return _day_of_month; }
	inline unsigned short int month() const { return _month; }
	inline unsigned short int year() const { return _year; }
	inline unsigned short int minutes() const { return _minutes; }
	inline unsigned short int hours() const { return _hours; }
	inline unsigned short int seconds() const { return _seconds; }
};

class Interval {
public:
	enum Type {DAYS, WEEKS, MONTHS};
private:
	unsigned int _number;
	Type _time;
public:
	Interval(std::string interval);
	Interval(unsigned int number, Type time) : _number(number), _time(time) {};
	~Interval() {};
	inline unsigned int number() const { return _number; }
	inline const Type& type() const { return _time; }
};

ostream& operator<<(ostream& os, const Date&);
ostream& operator<<(ostream& os, const Interval&);

Date& operator+(const Date&, const Interval&);
