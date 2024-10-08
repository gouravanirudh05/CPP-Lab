#include <iostream>
#include <ctime>
#include <string>
#include <vector>
using namespace std;
int getdetails(vector<string> &a);
int year_days(int year, int month, int day);
bool isLeapYear(int year);
int Month_days(int year, int month);
int isValidAddress(string address, vector<string> &, bool flag = true);
void handle_error()
{
	cout << -1 << endl
		 << "Error" << endl;
}

class Time
{
	private:
	int hour, minute;
	public:
	Time(int hour, int minute)
	{
		this->hour = hour;
		this->minute = minute;
	}
	Time()
	{
		this->hour = 0;
		this->minute = 0;
	}
	~Time() {}
	int getHour() 
	{ 
		return this->hour; 
	}
	int getMinute()
	{
		return this->minute;
	}
	void setHour(int hour)
	{
		if (hour >= 0 && hour < 24)
            this->hour = hour;
	}
	void setMinute(int minute)
	{
		if (minute >= 0 && minute < 60)
            this->minute = minute;
	}
	bool operator>=(Time &secondobj)
	{
		bool ans = (this->hour > secondobj.hour || (this->hour == secondobj.hour && this->minute >= secondobj.minute));
		return ans;
	}
	bool operator>(Time &secondobj)
	{

		bool ans = (this->hour > secondobj.hour || this->minute > secondobj.minute);
		return ans;
	}
	bool operator==(Time &secondobj)
	{

		bool ans = (this->hour == secondobj.hour && this->minute == secondobj.minute);
		return ans;
	}
	int operator-(const Time &secondobj)const 
	{
		int ans = (((this->hour - secondobj.hour) * 60) + this->minute - secondobj.minute);
		return ans;
	}
	friend ostream &operator<<(ostream &os, const Time &time)
	{
		if (time.hour < 10)
			os << '0';
		os << time.hour << ':';
		if (time.minute < 10)
			os << '0';
		os << time.minute;

		return os;
	}
};

class Date
{
	private:
	int year, month, day;
	public:
	Date(int year, int month, int day)
	{
		this->day = day;
		this->month = month;
		this->year = year;
	}
	Date()
	{
		this->day = 0;
		this->month = 0;
		this->year = 0;
	}
	~Date() {}
	int getDay()
	{
		return this->day;
	}
	int getMonth()
	{
        return this->month;
    }
	int getYear()
	{
		return this->year;
	}
	void setDay(int day)
	{
		if (day >= 1 && day <= Month_days(this->year, this->month))
            this->day = day;
	}
	void setMonth(int month)
	{
		if (month >= 1 && month <= 12)
            this->month = month;
	}
	void setYear(int year)
	{
		this->year = year;
	}
	bool operator>=(const Date &secondobj)
	{
		if (this->year != secondobj.year)
			return this->year > secondobj.year;

		if (this->month != secondobj.month)
			return this->month > secondobj.month;

		return this->day >= secondobj.day;
	}
	bool operator<=(const Date &secondobj)
	{
		if (this->year != secondobj.year)
			return this->year < secondobj.year;

		if (this->month != secondobj.month)
			return this->month < secondobj.month;

		return this->day <= secondobj.day;
	}
	bool operator>(const Date &secondobj)
	{
		if (this->year != secondobj.year)
			return this->year > secondobj.year;

		if (this->month != secondobj.month)
			return this->month > secondobj.month;

		return this->day > secondobj.day;
	}
	bool operator<(const Date &secondobj)
	{
		if (this->year != secondobj.year)
			return this->year < secondobj.year;

		if (this->month != secondobj.month)
			return this->month < secondobj.month;

		return this->day < secondobj.day;
	}
	bool operator==(const Date &secondobj)
	{
		return (this->year == secondobj.year) &&
			   (this->month == secondobj.month) &&
			   (this->day == secondobj.day);
	}
	Date operator++(int)
	{
		Date t = *this;
		day++;

		if (day > Month_days(year, month))
		{
			day = 1;
			if (++month > 12)
			{
				month = 1;
				year++;
			}
		}

		return t;
	}
	int operator-(const Date &secondobj) const
	{
		return abs(year_days(year, month, day) - year_days(secondobj.year, secondobj.month, secondobj.day));
	}
	friend ostream &operator<<(ostream &os, const Date &date)
	{
		if (date.year < 1000)
			os << '0';
		if (date.year < 100)
			os << '0';
		if (date.year < 10)
			os << '0';
		os << date.year << '-';
		if (date.month < 10)
			os << '0';
		os << date.month << '-';
		if (date.day < 10)
			os << '0';
		os << date.day;

		return os;
	}
};

class Event
{
	private:
	string name;
	Date date;
	Time start_hour, end_hour;
	public:
	Event(Date date, Time start_hour, Time end_hour, string eventName)
	{
		this->date = date;
		this->start_hour = start_hour;
		this->end_hour = end_hour;
		this->name = eventName;
	}
	~Event() {}
	string getName()
	{
		return this->name;
	}
	Date getDate()
	{
		return this->date;
	}
	Time getStartHour()
	{
		return this->start_hour;
	}
	Time getEndHour()
	{
		return this->end_hour;
	}
	void setName(string eventName)
	{
		this->name = eventName;
	}
	void setDate(Date date)
	{
		this->date = date;
	}
	void setStartHour(Time start_hour)
	{
		this->start_hour = start_hour;
	}
	void setEndHour(Time end_hour)
	{
		this->end_hour = end_hour;
	}
};

class Day
{
public:
	int count_events;
	vector<Event *> day;
	Date date;
	Day(Date date)
	{
		this->date = date;
		this->count_events = 0;
		this->day = {};
	}
	~Day()
	{
	}
	int addEvent(Time start_hour, Time end_hour, string eventName)
	{
		if (start_hour >= end_hour)
			return -1;
		int event_index = 0;
		for (auto event : this->day)
		{
			if (event->getStartHour() >= end_hour)
				break;
			else if (event->getEndHour() > start_hour)
				return -1;
			event_index++;
		}
		int d = 0;
		if (event_index > 0 && (start_hour - this->day[event_index - 1]->getEndHour()) < 30)
			return -1;
		else if (event_index < ((int)this->day.size() - 1) && (this->day[event_index + 1]->getStartHour() - end_hour) < 30)
			return -1;
		auto *t = new Event(this->date, start_hour, end_hour, eventName);
		this->day.insert(this->day.begin() + event_index, t);
		this->count_events++;
		return 1;
	}
	int deleteEvent(Time start_hour, string eventName)
	{
		int index = 0;
		for (auto event : this->day)
		{
			if (event->getName() == eventName && event->getStartHour() == start_hour)
				break;
			index++;
		}
		if (this->day.size() == index)
			return -1;
		else
		{
			delete this->day[index];
			this->day.erase(this->day.begin() + index);
		}
		this->count_events--;
		return 1;
	}
	int showEvents()
	{
		cout << this->count_events << endl;
		for (auto event : this->day)
			cout << event->getName() << ' ' << event->getStartHour() << ' ' << event->getEndHour() << endl;
		return 1;
	}
};
class Convention;
class Venue
{
	private:
	string name;
	string country;
	int capacity;
	public:
	static vector<Venue *> venues;
	vector<string> location;
	vector<Day *> calendar;
	vector<Convention *> conventionslist;
	Venue(string venueName, string country, vector<string> location, int capacity)
	{
		this->name = venueName;
		this->country = country;
		this->capacity = capacity;
		this->location.assign(location.begin(), location.end());
		venues.push_back(this);
	}
	~Venue()
	{
		conventionslist.clear();
		calendar.clear();
	}

	Venue()
	{
		this->name = "";
		this->country = "";
		this->capacity = 0;
		venues.push_back(this);
	}
	string getName()
	{
		return this->name;
	}
	string getCountry()
	{
		return this->country;
	}
	int getCapacity()
	{
		return this->capacity;
	}
	void setName(string venueName)
	{
		this->name = venueName;
	}
	void setCountry(string country)
	{
		this->country = country;
	}
	void setCapacity(int capacity)
	{
		this->capacity = capacity;
	}
	int isValidReservation(Date startDate, Date endDate);
	static int showVenues(vector<string> &location_input)
	{
		int venues_count = 0;
		string output = "";

		for (auto venu : venues)
		{
			bool matches = true;

			for (int i = 0; i < 5; ++i)
			{
				if (!location_input[i].empty() && location_input[i] != venu->location[i])
				{
					matches = false;
					break;
				}
			}

			if (matches)
			{
				output += venu->name + " " + venu->location[0] + ":" + venu->location[1] + ":" + venu->location[2] + ":" + venu->location[3] + ":" + venu->location[4] + " " + to_string(venu->capacity) + "\n";
				venues_count++;
			}
		}

		cout << venues_count << endl
			 << output;
		return 1;
	}

	static int venueSearch(string venu, string country, Venue *&p)
	{
		for (auto venue : Venue::venues)
		{
			if (venue->name == venu && venue->country == country)
			{
				p = venue;
				return 1;
			}
		}

		return -1;
	}

	int showCalendar(Date startDate, Date endDate)
	{
		int total_events = 0;

		for (const auto &day : this->calendar)
		{
			if (day->date >= startDate && day->date <= endDate)
			{
				total_events += day->count_events;
			}
		}

		cout << total_events << endl;

		Date currentDate = startDate;
		for (const auto &day : this->calendar)
		{
			if (day->date >= startDate && day->date <= endDate)
			{

				while (currentDate < day->date)
				{
					cout << currentDate++ << " 0" << endl;
				}
				cout << day->date << ' ';
				day->showEvents();
				currentDate++;
			}
		}
		while (currentDate <= endDate)
		{
			cout << currentDate << " 0" << endl;
			currentDate++;
		}

		return 1;
	}
	int showEvents(Date date)
	{
		int day_index = 0;

		for (const auto &day : this->calendar)
		{
			if (day->date > date)
			{
				cout << 0 << endl;
				return 1;
			}
			if (day->date == date)
			{
				break;
			}
			++day_index;
		}

		if (day_index < this->calendar.size() && this->calendar[day_index]->date == date)
		{
			return this->calendar[day_index]->showEvents();
		}
		else
		{
			cout << 0 << endl;
			return 1;
		}
	}
};

class Convention
{
	private:
	string type;
	string name;
	Date startDate, endDate;

public:
	static vector<Convention *> conventions;
	vector<Venue *> venues;
	
	Convention(string name, string type, Date startDate, Date endDate)
	{
		this->venues = {};
		this->name = name;
		this->type = type;
		this->startDate = startDate;
		this->endDate = endDate;
		Convention::conventions.push_back(this);
	}
	Convention()
	{
		this->venues = {};
		this->name = "";
		this->type = "";
		this->startDate = Date();
		this->endDate = Date();
		Convention::conventions.push_back(this);
	}
	~Convention() {}
	string getName()
	{
		return this->name;
	}
	string getType()
	{
		return this->type;
	}
	Date getStartDate()
	{
		return this->startDate;
	}
	Date getEndDate()
	{
		return this->endDate;
	}
	void setName(string name)
	{
		this->name = name;
	}
	void setType(string type)
	{
		this->type = type;
	}
	void setStartDate(Date startDate)
	{
		this->startDate = startDate;
	}
	void setEndDate(Date endDate)
	{
		this->endDate = endDate;
	}
	static int ConventionSearch(string name, Convention *&p)
	{
		for (auto conv : conventions)
		{
			if (conv->name == name)
			{
				p = conv;
				return 1;
			}
		}
		return -1;
	}
	int reserveVenue(Venue &venu)
	{
		if (venu.isValidReservation(this->startDate, this->endDate) == 1)
		{
			venu.conventionslist.push_back(this);
		}
		else
		{
			return -1;
		}
		this->venues.push_back(&venu);
		return 1;
	}
	int freeVenue(Venue &venu)
	{
		int index = 0;
		for (auto venue : this->venues)
		{
			if (venue->getName() == venu.getName() && venue->getCountry() == venu.getCountry())
				break;
			index++;
		}
		if (index == this->venues.size())
			return -1;
		this->venues.erase(this->venues.begin() + index);
		for (int i = 0; i < venu.calendar.size(); i++)
		{
			Day *day = venu.calendar[i];
			if (day->date >= this->startDate && day->date <= this->endDate)
			{
				for (auto event : day->day)
				{
					day->deleteEvent(event->getStartHour(), event->getName());
				}
				delete venu.calendar[i];
				venu.calendar.erase(venu.calendar.begin() + i);
				i--;
			}
		}
		index = 0;
		for (auto conv : venu.conventionslist)
		{
			if (conv->name == this->name)
				break;
			index++;
		}
		venu.conventionslist.erase(venu.conventionslist.begin() + index);
		return 1;
	}
	int showReserved()
	{
		int venues_count = 0;
		string output = "";
		for (auto venu : this->venues)
		{
			output += venu->getName() + " " + venu->location[0] + ":" + venu->location[1] + ":" + venu->location[2] + ":" + venu->location[3] + ":" + venu->location[4] + " " + to_string(venu->getCapacity()) + "\n";
			venues_count++;
		}
		cout << venues_count << endl<< output;
		return 1;
	}
	int addEvent(Venue &venu, Date date, Time start_hour, Time end_hour, string eventName)
	{
		bool flag = false;
		for (auto venue : this->venues)
		{
			if (venu.getName() == venue->getName() && venu.getCountry() == venue->getCountry())
			{
				flag = true;
				break;
			}
		}
		if (!flag)
			return -1;
		int index = 0;
		flag = false;
		for (auto day : venu.calendar)
		{
			if (day->date == date)
				break;
			if (day->date > date)
			{
				flag = true;
				break;
			}
			index++;
		}
		int d = 0;

		if (index > 0 && (date - venu.calendar[index - 1]->date) == 1)
		{
			Time prevEnd = venu.calendar[index - 1]->day.back()->getEndHour();
			int startTime = start_hour.getHour() * 60 + start_hour.getMinute();
			int endTime = (prevEnd.getHour() == 24) ? 0 : (23 - prevEnd.getHour()) * 60 + (60 - prevEnd.getMinute());
			d = startTime + endTime;
			if (d < 30)
				return -1;
		}

		d = 0;

		if (index < static_cast<int>(venu.calendar.size()) - 1 && (venu.calendar[index + 1]->date - date) == 1)
		{
			Time nextStart = venu.calendar[index + 1]->day.front()->getStartHour();
			int endTime = end_hour.getHour() * 60 + end_hour.getMinute();
			int startTime = (nextStart.getHour() == 24) ? 0 : (23 - nextStart.getHour()) * 60 + (60 - nextStart.getMinute());
			d = startTime - endTime;
			if (d < 30)
				return -1;
		}

		bool dayAdded = false;
		if (flag || venu.calendar.empty() || index == static_cast<int>(venu.calendar.size()))
		{
			Day *newDay = new Day(date);
			venu.calendar.insert(venu.calendar.begin() + index, newDay);
			dayAdded = true;
		}

		int result = venu.calendar[index]->addEvent(start_hour, end_hour, eventName);
		if (result != 1 && dayAdded)
		{
			delete venu.calendar[index];
			venu.calendar.erase(venu.calendar.begin() + index);
		}

		return result;
	}
	int deleteEvent(Venue &venu, Date date, Time start_hour, string eventName)
	{
		bool flag = false;
		for (auto venue : this->venues)
		{
			if (venu.getName() == venue->getName() && venu.getCountry() == venue->getCountry())
			{
				flag = true;
				break;
			}
		}
		if (flag == false)
			return -1;
		int day_index = 0;
		for (auto day : venu.calendar)
		{
			if (day->date > date)
				return -1;
			else if (day->date == date)
				break;
			day_index++;
		}

		if (day_index == venu.calendar.size())
			return -1;
		int ans = venu.calendar[day_index]->deleteEvent(start_hour, eventName);
		if (ans != 1)
			return -1;
		if (venu.calendar[day_index]->count_events == 0)
		{
			delete venu.calendar[day_index];
			venu.calendar.erase(venu.calendar.begin() + day_index);
		}
		return 1;
	}
	int showCalendar(Venue &venu)
	{
		int index = 0;
		for (auto venue : this->venues)
		{
			if (venu.getName() == venue->getName() && venu.getCountry() == venue->getCountry())
				break;
			index++;
		}
		if (index == this->venues.size())
			return -1;
		return venu.showCalendar(this->startDate, this->endDate);
	}
};
vector<Venue *> Venue::venues;
int Venue::isValidReservation(Date startDate, Date endDate)
{
	for (auto conv : this->conventionslist)
		if (startDate <= conv->getEndDate() && endDate >= conv->getStartDate())
			return -1;

	return 1;
}
vector<Convention *> Convention::conventions;
int getdetails(vector<string> &a)
{
	string input, word;
	a.clear();
	getline(cin, input);
	if (input.empty())
		return -1;
	bool inQuotes = false, isNumber = false, isWord = false;
	int count = 0;
	for (int i = 0; i < input.length(); i++)
	{
		char ch = input[i];
		if ((ch != ' ' || inQuotes) && count < 8)
		{
			if (ch == '\"')
			{
				if (isWord || isNumber)
					return -1;
				if (inQuotes)
				{
					inQuotes = false;
					a.push_back(word);
					word.clear();
					count++;
				}
				else
				{
					inQuotes = true;
					word += '\"';
				}
			}
			else
			{
				if (isNumber && (ch < '0' || ch > '9'))
					return -1;
				if (!isNumber)
				{
					if (ch >= '0' && ch <= '9' && !inQuotes && !isWord)
					{
						isNumber = true;
					}
					else if (!inQuotes)
					{
						isWord = true;
					}
				}
				word += ch;
			}
		}
		else if (ch == ' ')
		{
			if (isNumber || isWord)
			{
				a.push_back(word);
				word.clear();
				isNumber = false;
				isWord = false;
				count++;
			}
		}
		else if (count >= 8)
			return -1;
	}

	if (!word.empty())
	{
		a.push_back(word);
		count++;
	}

	while (a.size() < 8)
	{
		a.push_back("");
	}

	return 1;
}

int year_days(int year, int month, int day)
{
	int total_days = day;
	for (int i = 0; i < year; ++i)
	{
		total_days += (isLeapYear(i) ? 366 : 365);
	}
	for (int j = 1; j < month; ++j)
	{
		total_days += Month_days(year, j);
	}
	return total_days;
}
bool isLeapYear(int year)
{
	if (year % 4 == 0)
	{
		if (year % 100 != 0 || year % 400 == 0)
		{
			return true;
		}
	}
	return false;
}

int Month_days(int year, int month)
{
	switch (month)
	{
	case 2:
		if (isLeapYear(year))
			return 29;
		else
			return 28;
	case 4:
	case 6:
	case 9:
	case 11:
		return 30;
	default:
		return 31;
	}
}

int isValidDate(const string &date, Date *&p)
{

	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return -1;

	int year = stoi(date.substr(0, 4));
	int month = stoi(date.substr(5, 2));
	int day = stoi(date.substr(8, 2));

	if (month < 1 || month > 12 || day < 1 || day > Month_days(year, month))
		return -1;

	time_t t = time(nullptr);
	tm *now = localtime(&t);
	int currentYear = now->tm_year + 1900;
	int currentMonth = now->tm_mon + 1;
	int currentDay = now->tm_mday;

	if (year < currentYear ||
		(year == currentYear && month < currentMonth) ||
		(year == currentYear && month == currentMonth && day < currentDay))
	{
		return -1;
	}

	p = new Date(year, month, day);
	return 1;
}

int isValidTime(const string &time, Time *&p)
{
	if (time.length() != 5 || time[2] != ':')
		return -1;
	for (int i = 0; i < time.length(); ++i)
	{
		if (i != 2 && !isdigit(time[i]))
			return -1;
	}
	int hour = stoi(time.substr(0, 2));
	int minute = stoi(time.substr(3, 2));
	if ((hour == 24 && minute != 0) || hour > 23 || minute > 59 || minute % 15 != 0)
		return -1;
	p = new Time(hour, minute);
	return 1;
}

int isValidAddress(string address, vector<string> &address_arr, bool flag)
{

	string location = "";
	string city = "";
	string state = "";
	string postalCode = "";
	string country = "";
	int count = 0;
	if (!flag)
		count++;
	address_arr.clear();
	for (auto x : address)
	{
		if (x != ':')
		{
			if (count == 0)
				location += x;
			else if (count == 1)
				city += x;
			else if (count == 2)
				state += x;
			else if (count == 3)
				postalCode += x;
			else if (count == 4)
				country += x;
		}
		else
		{
			count++;
		}
	}
	if (count != 4)
		return -1;
	address_arr.resize(5);
	address_arr = {location, city, state, postalCode, country};
	return 1;
}

int main()
{
	vector<string> a(8);
	int ans;
	bool flag;
	while (true)
	{
		ans = getdetails(a);
		flag = true;
		if (ans != 1)
		{
			handle_error();
		}
		else if (a[0] == "addEvent")
		{

			bool flag = false;
			for (int i = 1; i < 8; i++)
			{
				if (a[i].empty() || a[i][0] != '\"')
				{
					handle_error();
					flag = true;
					break;
				}
				a[i].erase(0, 1);
			}
			if (flag)
				continue;
			Convention *conv;
			Venue *venu;
			Date *date;
			Time *start, *end;
			if (conv->ConventionSearch(a[1], conv) != 1 || venu->venueSearch(a[2], a[3], venu) != 1 || isValidDate(a[4], date) != 1 || isValidTime(a[5], start) != 1 || isValidTime(a[6], end) != 1 || conv->addEvent(*venu, *date, *start, *end, a[7]) != 1)
			{
				handle_error();
				continue;
			}
			cout << "0" << endl;
		}
		else if (a[0] == "showEvents")
		{
			if (a[1].empty() || a[1][0] != '\"' || a[2].empty() || a[2][0] != '\"' || a[3].empty() || a[3][0] != '\"')
			{
				handle_error();
				continue;
			}
			flag = true;
			for (int i = 4; i < 6; i++)
				if (a[i] != "")
				{
					handle_error();
					flag = false;
					break;
				}
			if (flag)
			{
				for (int i = 1; i < 4; i++)
					a[i].erase(0, 1);
				Venue *venu;
				Date *date;
				if (venu->venueSearch(a[1], a[2], venu) != 1 || isValidDate(a[3], date) != 1 || venu->showEvents(*date) != 1)
				{
					handle_error();
					continue;
				}
			}
		}
		else if (a[0] == "deleteEvent")
		{
			bool flag = false;
			for (int i = 1; i < 7; i++)
			{
				if (a[i].empty() || a[i][0] != '\"')
				{
					handle_error();
					flag = true;
					break;
				}
				a[i].erase(0, 1);
			}
			if (flag)
				continue;
			Convention *conv;
			Venue *venu;
			Date *date;
			Time *time;
			if (conv->ConventionSearch(a[1], conv) != 1 || venu->venueSearch(a[2], a[3], venu) != 1 || isValidDate(a[4], date) != 1 || isValidTime(a[5], time) != 1 || conv->deleteEvent(*venu, *date, *time, a[6]) != 1)
			{
				handle_error();
				continue;
			}

			cout << "0" << endl;
		}
		else if (a[0] == "showCalendar")
		{

			if (a[1].empty() || a[1][0] != '\"' || a[2].empty() || a[2][0] != '\"' || a[3].empty() || a[3][0] != '\"')
			{
				handle_error();
				continue;
			}

			flag = false;
			for (int i = 4; i < 8; i++)
			{
				if (!a[i].empty())
				{
					handle_error();
					flag = true;
					break;
				}
			}
			if (flag)
			{
				continue;
			}
			for (int i = 1; i <= 3; i++)
				a[i].erase(0, 1);
			Convention *conv;
			Venue *venu;
			if (conv->ConventionSearch(a[1], conv) != 1 || venu->venueSearch(a[2], a[3], venu) != 1 || conv->showCalendar(*venu) != 1)
			{
				handle_error();
				continue;
			}
		}

		else if (a[0] == "addVenue")
		{

			if (a[1].empty() || a[1][0] != '\"' || a[2].empty() || a[2][0] != '\"' || a[3].empty() || a[3][0] < '0' || a[3][0] > '9')
			{
				handle_error();
				continue;
			}
			flag = true;
			for (int i = 0; i < a[3].length(); i++)
				if (a[3][i] < '0' || a[3][i] > '9')
				{
					handle_error();
					flag = false;
					break;
				}

			if (flag)
			{
				a[1].erase(0, 1);
				a[2].erase(0, 1);
				vector<string> location(5, "");
				if (isValidAddress(a[2], location) != 1)
				{
					handle_error();
					continue;
				}
				for (auto add : location)
				{
					if (add.empty())
					{
						flag = false;
						handle_error();
						break;
					}
				}
				if (!flag)
					continue;

				new Venue(a[1], location[4], location, stoi(a[3]));
				cout << "0" << endl;
			}
		}
		else if (a[0] == "showVenues")
		{

			if (a[1].empty() || a[1][0] != '\"')
			{
				handle_error();
				continue;
			}
			for (int i = 2; i < 8; i++)
				if (a[i] != "")
				{
					handle_error();
					flag = false;
					break;
				}

			if (flag)
			{

				a[1].erase(0, 1);
				vector<string> location(5, "");
				if (isValidAddress(a[1], location, (bool)false) != 1)
				{
					handle_error();
					continue;
				}

				if (Venue::showVenues(location) != 1)
				{
					handle_error();
					continue;
				}
			}
		}
		else if (a[0] == "deleteVenue")
		{
			flag = true;
			if (a[1].empty() || a[1][0] != '\"' || a[2].empty() || a[2][0] != '\"')
			{
				handle_error();
				continue;
			}
			else
			{
				for (int i = 3; i < 6; i++)
					if (a[i] != "")
					{
						handle_error();
						flag = false;
						break;
					}
			}
			if (!flag)
				continue;

			for (int i = 1; i <= 2; i++)
				a[i].erase(0, 1);
			Venue *venu;
			if (venu->venueSearch(a[1], a[2], venu) != 1 || venu->conventionslist.size() != 0)
			{
				handle_error();
				continue;
			}
			int i;
			for (i = 0; i < venu->venues.size(); i++)
			{
				if (venu->getName() == a[1] && venu->getCountry() == a[2])
					break;
			}
			venu->venues.erase(venu->venues.begin() + i);
			delete venu;
			cout << "0" << endl;
		}
		else if (a[0] == "reserveVenue")
		{

			if (a[1].empty() || a[1][0] != '\"' || a[2].empty() || a[2][0] != '\"' || a[3].empty() || a[3][0] != '\"')
			{
				handle_error();
				continue;
			}

			flag = false;
			for (int i = 4; i < 8; i++)
			{
				if (!a[i].empty())
				{
					handle_error();
					flag = true;
					break;
				}
			}

			if (flag)
				continue;
			for (int i = 1; i <= 3; i++)
				a[i].erase(0, 1);

			Convention *conv;
			Venue *venu;
			if (conv->ConventionSearch(a[3], conv) != 1 || venu->venueSearch(a[1], a[2], venu) != 1 || conv->reserveVenue(*venu) != 1)
			{
				handle_error();
				continue;
			}
			else
				cout << 0 << endl;
		}
		else if (a[0] == "freeVenue")
		{
			flag = false;
			if (a[1].empty() || a[1][0] != '\"' || a[2].empty() || a[2][0] != '\"' || a[3].empty() || a[3][0] != '\"')
			{
				handle_error();
				continue;
			}
			for (int i = 4; i < 8; i++)
			{
				if (!a[i].empty())
				{
					handle_error();
					flag = true;
					break;
				}
			}
			if (flag)
				continue;
			for (int i = 1; i <= 3; i++)
				a[i].erase(0, 1);
			Convention *conv;
			Venue *venu;
			if (conv->ConventionSearch(a[3], conv) != 1 || venu->venueSearch(a[1], a[2], venu) != 1 || conv->freeVenue(*venu) != 1)
			{
				handle_error();
				continue;
			}
			else
				cout << 0 << endl;
		}
		else if (a[0] == "showReserved")
		{
			flag = false;
			if (a[1].empty() || a[1][0] != '\"')
			{
				handle_error();
				continue;
			}
			for (int i = 2; i < 8; i++)
			{
				if (!a[i].empty())
				{
					handle_error();
					flag = true;
					break;
				}
			}
			if (flag)
			{
				continue;
			}
			Convention *conv;
			a[1].erase(0, 1);
			if (conv->ConventionSearch(a[1], conv) != 1 || conv->showReserved() != 1)
			{
				handle_error();
				continue;
			}
		}
		else if (a[0] == "addCongregation")
		{
			bool flag = false;
			for (int i = 1; i < 5; i++)
			{
				if (a[i].empty() || a[i][0] != '\"')
				{
					handle_error();
					flag = true;
					break;
				}
				a[i].erase(0, 1);
			}
			if (flag)
				continue;
			for (int i = 5; i < 8; i++)
			{
				if (a[i] != "")
				{
					handle_error();
					flag = true;
					break;
				}
			}
			if (flag)
				continue;
			Date *startDate = nullptr, *endDate = nullptr;
			if (isValidDate(a[3], startDate) != 1 || isValidDate(a[4], endDate) != 1)
			{
				handle_error();
				continue;
			}
			else if (startDate->getYear() > endDate->getYear() || (startDate->getYear() == endDate->getYear()&& (startDate->getMonth()> endDate->getMonth()|| (startDate->getMonth() == endDate->getMonth() && startDate->getDay() >= endDate->getDay()))) )
			{
				handle_error();
				continue;
			}

			new Convention(a[1], a[2], *startDate, *endDate);
			cout << 0 << endl;
			delete startDate;
			delete endDate;
		}
		else if (a[0] == "deleteCongregation")
		{

			if (a[1].empty() || a[1][0] != '\"')
			{
				handle_error();
				continue;
			}

			bool flag = false;
			for (int i = 2; i < 8; i++)
			{
				if (!a[i].empty())
				{
					handle_error();
					flag = true;
					break;
				}
			}
			if (flag)
				continue;
			a[1].erase(0, 1);
			Convention *conv;
			if (conv->ConventionSearch(a[1], conv) != 1)
			{
				handle_error();
				continue;
			}
			int index = 0;
			for (auto conv : conv->conventions)
			{
				if (conv->getName() == a[1])
					break;
				index++;
			}
			conv->conventions.erase(conv->conventions.begin() + index);
			while (!conv->venues.empty())
			{
				conv->freeVenue(*conv->venues[0]);
			}
			delete conv;
			cout << 0 << endl;
		}
		else if (a[0] == "showCongregations")
		{
			bool flag = false;
			for (int i = 1; i < 8; i++)
			{
				if (!a[i].empty())
				{
					handle_error();
					flag = true;
					break;
				}
			}
			if (flag)
				break;
			cout << Convention::conventions.size() << endl;
			for (auto conv : Convention::conventions)
			{
				cout << conv->getName() << ' ' << conv->getType() << ' ' << conv->getStartDate() << ' ' << conv->getEndDate() << endl;
			}
		}
		else if (a[0] == "End")
			return 0;
		else
			handle_error();
	}
}
