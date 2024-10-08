#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
class Time
{
public:
	int hour, minute;

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
	bool operator>=(const Time &other);
	bool operator>(const Time &other);
	bool operator==(const Time &other);
	int operator-(const Time &other) const;
	friend ostream &operator<<(ostream &os, const Time &time);
};

class Date
{
public:
	int year, month, day;
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

	bool operator>=(const Date &other);
	bool operator<=(const Date &other);
	bool operator>(const Date &other);
	bool operator<(const Date &other);
	bool operator==(const Date &other);
	Date operator++(int);
	int operator-(const Date &other) const;
	friend ostream &operator<<(ostream &os, const Date &date);
};

class Event
{
public:
	Event(Date date, Time fromHour, Time toHour, string eventName);

	string name;
	Date date;
	Time fromHour, toHour;
};

class Day
{
public:
	Day(Date date);

	int addEvent(Time fromHour, Time toHour, string eventName);
	int deleteEvent(Time fromHour, string eventName);
	int showEvents();

	int numOfEvents;
	vector<Event *> day;
	Date date;
};

class Congregation;

class Venue
{
public:
	static vector<Venue *> venues;
	static int showVenues(vector<string> &inputLocation);
	static int searchVenue(string ven, string country, Venue *&ptr);

	Venue(string venueName, string country, vector<string> location, int capacity);

	int showCalendar(Date startDate, Date endDate);
	int checkReservation(Date startDate, Date endDate);
	int showEvents(Date date);

	string name;
	string country;
	vector<string> location;
	int capacity;
	vector<Day *> calendar;
	// vector of congregations that reserved this venue
	vector<Congregation *> congregations;
};

class Congregation
{
public:
	static vector<Congregation *> congregates;
	static int searchCongregate(string name, Congregation *&ptr);
	Congregation(string name, string type, Date startDate, Date endDate);

	// venue methods
	int reserveVenue(Venue &ven);
	int freeVenue(Venue &ven);
	int showReserved();

	// event methods
	int addEvent(Venue &ven, Date date, Time fromHour, Time toHour, string eventName);
	int deleteEvent(Venue &ven, Date date, Time fromHour, string eventName);
	int showCalendar(Venue &ven);

	vector<Venue *> venues;
	string type;
	string name;
	Date startDate, endDate;
};

int tokenize(vector<string> &arr);
int daysFromYear0(int year, int month, int day);
bool isLeapYear(int year);
int daysInMonth(int year, int month);
int checkDate(string date, Date *&ptr);
int checkTime(string time, Time *&ptr);
int checkAddress(string address, vector<string> &, bool flag = true);
bool Time::operator>(const Time &other)
{
	return (this->hour > other.hour || this->minute > other.minute);
}

bool Time::operator>=(const Time &other)
{
	return (this->hour > other.hour || (this->hour == other.hour && this->minute >= other.minute));
}

bool Time::operator==(const Time &other)
{
	return (this->hour == other.hour && this->minute == other.minute);
}

int Time::operator-(const Time &other) const
{
	return (((this->hour - other.hour) * 60) + this->minute - other.minute);
}

ostream &operator<<(ostream &os, const Time &time)
{
	os << setw(2) << setfill('0') << time.hour << ':'
	   << setw(2) << setfill('0') << time.minute;
	return os;
}
bool Date::operator>=(const Date &other)
{
	if (this->year > other.year)
		return true;
	else if (this->year < other.year)
		return false;

	if (this->month > other.month)
		return true;
	else if (this->month < other.month)
		return false;

	if (this->day >= other.day)
		return true;
	else
		return false;
}

bool Date::operator<=(const Date &other)
{
	if (this->year < other.year)
		return true;
	else if (this->year > other.year)
		return false;

	if (this->month < other.month)
		return true;
	else if (this->month > other.month)
		return false;

	if (this->day <= other.day)
		return true;
	else
		return false;
}

bool Date::operator>(const Date &other)
{
	if (this->year > other.year)
		return true;
	else if (this->year < other.year)
		return false;

	if (this->month > other.month)
		return true;
	else if (this->month < other.month)
		return false;

	if (this->day > other.day)
		return true;
	else
		return false;
}

bool Date::operator<(const Date &other)
{
	if (this->year < other.year)
		return true;
	else if (this->year > other.year)
		return false;

	if (this->month < other.month)
		return true;
	else if (this->month > other.month)
		return false;

	if (this->day < other.day)
		return true;
	else
		return false;
}

bool Date::operator==(const Date &other)
{
	return this->year == other.year && this->day == other.day && this->month == other.month;
}

Date Date::operator++(int)
{
	Date temp = *this; // Save current state

	// Increment the day by one
	day++;

	// Handle month and year overflow
	if (day > daysInMonth(year, month))
	{
		day = 1;
		month++;
		if (month > 12)
		{
			month = 1;
			year++;
		}
	}

	return temp; // Return the old value
}

int Date::operator-(const Date &other) const
{
	return abs(daysFromYear0(year, month, day) - daysFromYear0(other.year, other.month, other.day));
}

ostream &operator<<(ostream &os, const Date &date)
{
	os << setw(4) << setfill('0') << date.year << '-'
	   << setw(2) << setfill('0') << date.month << '-'
	   << setw(2) << setfill('0') << date.day;
	return os;
}

Event::Event(Date date, Time fromHour, Time toHour, string eventName)
{
	this->date = date;
	this->fromHour = fromHour;
	this->toHour = toHour;
	this->name = eventName;
}

Day::Day(Date date)
{
	this->date = date;
	this->numOfEvents = 0;
	this->day = {};
}

int Day::addEvent(Time fromHour, Time toHour, string eventName)
{
	if (fromHour >= toHour)
		return -1; // incorrect format

	int indexToAddEvent = 0;
	for (auto event : this->day)
	{
		if (event->fromHour >= toHour)
		{
			break;
		}
		else if (event->toHour > fromHour)
			return -1; // cannot allocate time for event

		indexToAddEvent++;
	}

	// checking if gap is maintained
	int diff = 0;
	if (indexToAddEvent > 0 && (fromHour - this->day[indexToAddEvent - 1]->toHour) < 30)
	{
		return -1;
	}
	else if (indexToAddEvent < ((int)this->day.size() - 1) && (this->day[indexToAddEvent + 1]->fromHour - toHour) < 30)
	{
		return -1;
	}

	// creating event
	Event *temp = new Event(this->date, fromHour, toHour, eventName);
	this->day.insert(this->day.begin() + indexToAddEvent, temp);

	this->numOfEvents++;

	return 1; // operation finished successfully
}

int Day::deleteEvent(Time fromHour, string eventName)
{
	int index = 0;
	for (auto event : this->day)
	{
		if (event->name == eventName && event->fromHour == fromHour)
		{
			break;
		}
		index++;
	}

	if (this->day.size() == index)
		return -1; // event does not exist
	else
	{
		delete this->day[index];
		this->day.erase(this->day.begin() + index);
	}

	this->numOfEvents--;
	return 1; // operation finished successfully
}

int Day::showEvents()
{
	// printing number of events
	cout << this->numOfEvents << endl;
	for (auto event : this->day)
		cout << event->name << ' ' << event->fromHour << ' ' << event->toHour << endl;

	return 1; // operation finished successfully
}

// instantiating empty vector
vector<Venue *> Venue::venues = {};

int Venue::showVenues(vector<string> &inputLocation)
{
	int numOfVen = 0;
	string out = "";
	// collecting and counting valid venues
	for (auto ven : Venue::venues)
	{
		if (
			(inputLocation[0].empty() ? true : inputLocation[0] == ven->location[0]) &&
			(inputLocation[1].empty() ? true : inputLocation[1] == ven->location[1]) &&
			(inputLocation[2].empty() ? true : inputLocation[2] == ven->location[2]) &&
			(inputLocation[3].empty() ? true : inputLocation[3] == ven->location[3]) &&
			(inputLocation[4].empty() ? true : inputLocation[4] == ven->location[4]))
		{
			out += ven->name + " " + ven->location[0] + ":" + ven->location[1] + ":" + ven->location[2] + ":" + ven->location[3] + ":" + ven->location[4] + " " + to_string(ven->capacity) + "\n";
			numOfVen++;
		}
	}

	// printing venues
	cout << numOfVen << endl
		 << out;

	return 1; // finished successfully
}

int Venue::searchVenue(string ven, string country, Venue *&ptr)
{
	for (auto venue : Venue::venues)
	{
		if (venue->name == ven && venue->country == country)
		{
			ptr = venue;
			return 1; // operation finished successfully
		}
	}

	return -1; // couldn't find venue
}

Venue::Venue(string venueName, string country, vector<string> location, int capacity)
{
	this->name = venueName;
	this->country = country;
	this->capacity = capacity;
	this->location.assign(location.begin(), location.end());

	// adding venue to vector
	Venue::venues.push_back(this);
}

int Venue::showCalendar(Date startDate, Date endDate)
{
	// calculating total number of events
	int totalNumOfEvent = 0;
	for (auto day : this->calendar)
		if (day->date >= startDate && day->date <= endDate)
			totalNumOfEvent += day->numOfEvents;

	// printing events
	cout << totalNumOfEvent << endl;
	for (auto day : this->calendar)
	{
		if (day->date >= startDate && day->date <= endDate)
		{
			while (day->date - startDate >= 1)
				cout << startDate++ << " 0" << endl;
			cout << startDate++ << ' ';
			day->showEvents();
		}
	}

	return 1; // operation finished successfully
}

int Venue::checkReservation(Date startDate, Date endDate)
{
	// checks if the dates are free
	for (auto cong : this->congregations)
		if (startDate <= cong->endDate && endDate >= cong->startDate)
			return -1; // not free

	return 1; // free
}

int Venue::showEvents(Date date)
{
	// fetching day
	int indexOfDay = 0;
	for (auto day : this->calendar)
	{
		if (day->date > date)
		{
			cout << 0 << endl; // day does not exist
			return 1;
		}
		else if (day->date == date)
			break;
		indexOfDay++;
	}

	// returning operation status
	return this->calendar[indexOfDay]->showEvents();
}

vector<Congregation *> Congregation::congregates = {};

int Congregation::searchCongregate(string name, Congregation *&ptr)
{
	for (auto cong : Congregation::congregates)
	{
		if (cong->name == name)
		{
			ptr = cong;
			return 1;
		}
	}

	// couldn't find congregate
	return -1;
}

Congregation::Congregation(string name, string type, Date startDate, Date endDate)
{
	this->venues = {};
	this->name = name;
	this->type = type;
	this->startDate = startDate;
	this->endDate = endDate;

	// adding the congregate to the vector
	Congregation::congregates.push_back(this);
}

int Congregation::reserveVenue(Venue &ven)
{
	if (ven.checkReservation(this->startDate, this->endDate) == 1)
	{
		ven.congregations.push_back(this);
	}
	else
	{
		return -1; // cannot reserve venue
	}

	this->venues.push_back(&ven);

	return 1; // finished successfully
}

int Congregation::freeVenue(Venue &ven)
{
	// finding venue
	int index = 0;
	for (auto venue : this->venues)
	{
		if (venue->name == ven.name && venue->country == ven.country)
			break;
		index++;
	}

	if (index == this->venues.size())
		return -1; // cannot find venue

	// removing venue
	this->venues.erase(this->venues.begin() + index);

	// removing events
	for (int i = 0; i < ven.calendar.size(); i++)
	{
		Day *day = ven.calendar[i];
		if (day->date >= this->startDate && day->date <= this->endDate)
		{
			for (auto event : day->day)
			{
				day->deleteEvent(event->fromHour, event->name);
			}
			delete ven.calendar[i];
			ven.calendar.erase(ven.calendar.begin() + i);
			i--;
		}
	}

	// removing conregation from venue
	index = 0;
	for (auto cong : ven.congregations)
	{
		if (cong->name == this->name)
			break;
		index++;
	}

	ven.congregations.erase(ven.congregations.begin() + index);

	return 1;
}

int Congregation::showReserved()
{
	// over-complicated the task :P
	int numOfVen = 0;
	string out = "";
	for (auto ven : this->venues)
	{
		out += ven->name + " " + ven->location[0] + ":" + ven->location[1] + ":" + ven->location[2] + ":" + ven->location[3] + ":" + ven->location[4] + " " + to_string(ven->capacity) + "\n";
		numOfVen++;
	}

	cout << numOfVen << endl
		 << out;

	return 1; // finished successfully
}

int Congregation::addEvent(Venue &ven, Date date, Time fromHour, Time toHour, string eventName)
{
	// checking if venue exists
	bool flag = false;
	for (auto venue : this->venues)
	{
		if (ven.name == venue->name && ven.country == venue->country)
		{
			flag = true;
			break;
		}
	}

	if (!flag)
		return -1; // venue does not exist

	// fetching day
	int index = 0;
	flag = false; // if day exists for not
	for (auto day : ven.calendar)
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

	// checking if 30 minute time interval is maintained
	int diff = 0;
	if (index > 0 && (date - ven.calendar[index - 1]->date) == 1)
	{
		Time before = ven.calendar[index - 1]->day[ven.calendar[index - 1]->day.size() - 1]->toHour;
		diff += (fromHour.minute + 60 * fromHour.hour);
		if (before.hour == 24)
			diff += 0;
		else
			diff += (23 - before.hour) * 60 + (60 - before.minute);

		if (diff < 30)
			return -1;
	}
	diff = 0;
	if (index < ((int)ven.calendar.size() - 1) && (ven.calendar[index + 1]->date - date) == 1)
	{
		Time after = ven.calendar[index + 1]->day[0]->fromHour;
		diff += (after.hour * 60 + after.minute);
		if (toHour.hour == 24)
		{
			diff += 0;
		}
		else
		{
			diff += (23 - toHour.hour) * 60 + (60 - toHour.minute);
		}

		if (diff < 30)
			return -1;
	}

	// day does not exist
	bool createdDay = false;
	if (flag || ven.calendar.empty() || index == ven.calendar.size())
	{
		Day *temp = new Day(date);
		ven.calendar.insert(ven.calendar.begin() + index, temp);
		createdDay = true;
	}

	// if operation failed deleting day
	int isSuccess = ven.calendar[index]->addEvent(fromHour, toHour, eventName);
	if (isSuccess != 1 && createdDay)
	{
		delete ven.calendar[index];
		ven.calendar.erase(ven.calendar.begin() + index);
	}

	// returning operation status
	return isSuccess;
}

int Congregation::deleteEvent(Venue &ven, Date date, Time fromHour, string eventName)
{
	// checking if venue exists
	bool flag = false;
	for (auto venue : this->venues)
	{
		if (ven.name == venue->name && ven.country == venue->country)
		{
			flag = true;
			break;
		}
	}

	if (flag == false)
		return -1; // venue does not exist

	// fetching day
	int indexOfDay = 0;
	for (auto day : ven.calendar)
	{
		if (day->date > date)
			return -1; // day does not exist
		else if (day->date == date)
			break;
		indexOfDay++;
	}

	if (indexOfDay == ven.calendar.size())
		return -1; // day does not exist

	// returning operation status
	int isSuccess = ven.calendar[indexOfDay]->deleteEvent(fromHour, eventName);
	if (isSuccess != 1)
		return -1;

	// deleting day if no events are scheduled
	if (ven.calendar[indexOfDay]->numOfEvents == 0)
	{
		delete ven.calendar[indexOfDay];
		ven.calendar.erase(ven.calendar.begin() + indexOfDay);
	}

	return 1;
}

int Congregation::showCalendar(Venue &ven)
{
	// does venue exist in the congregation?
	int index = 0;
	for (auto venue : this->venues)
	{
		if (ven.name == venue->name && ven.country == venue->country)
			break;
		index++;
	}

	if (index == this->venues.size())
		return -1; // venue does not exist

	// returning operation status
	return ven.showCalendar(this->startDate, this->endDate);
}

int tokenize(vector<string> &arr)
{
	// string to hold the line
	string in, word;

	arr.assign(8, "");

	getline(cin, in); // taking line

	// checking for invalid inputs
	if (in[0] == ' ')
		return -1; // failure

	bool flag = false, strflag = false,
		 intflag = false; // three flags for the 3 types of input, command, string
						  // and integer
	int count = 0;		  // to count the number of words, max is 6
	for (int y = 0; y < in.length(); y++)
	{
		char x = in[y]; // selecting that character
		if ((x != ' ' || strflag) && count < 8)
		{
			if (x == '\"')
			{						 // starting of a string
				if (flag || intflag) // other flags need to be off
					return -1;

				if (strflag) // turning off string flag
				{
					strflag = false;
					arr[count++] = word;
					word = "";
				}
				else
				{
					strflag = true; // turning flag on
					word += "\"";	// so that I can identify that it is a string
				}
			}
			else
			{
				if (intflag && (x < '0' || x > '9'))
				{ // checking if its an integer if intflag is on
					return -1;
				}
				else if (intflag == false)
				{
					if ((x > '0' && x < '9') && strflag == false && flag == false)
					{ // checking if we are reading an integer
						intflag = true;
					}
					else if (strflag == false) // checking if we are reading a command
						flag = true;
				}
				word += x; // then we are reading a string
			}
		}
		else if (x == ' ')
		{ // if its a space then we need to turn one flag off
			if (intflag)
			{
				arr[count++] = word;
				word = "";
				intflag = false;
			}
			else if (flag)
			{
				arr[count++] = word;
				word = "";
				flag = false;
			}
		}
		else if (count >= 8) // if count is exceeded error
			return -1;
	}

	if (word != "") // appending the last word
		arr[count++] = word;

	return 1; // successfully
}

int daysFromYear0(int year, int month, int day)
{
	int days = day;
	for (int y = 0; y < year; ++y)
	{
		days += (isLeapYear(y) ? 366 : 365);
	}
	for (int m = 1; m < month; ++m)
	{
		days += daysInMonth(year, m);
	}
	return days;
}

bool isLeapYear(int year)
{
	return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

int daysInMonth(int year, int month)
{
	if (month == 2)
	{ // February
		return (isLeapYear(year)) ? 29 : 28;
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11)
	{ // April, June, September, November
		return 30;
	}
	else
	{ // All other months
		return 31;
	}
}

int checkDate(string date, Date *&ptr)
{
	// this function checks if the date is in the correct format
	string year = "", month = "", day = "";

	if (date.length() != 10) // the format is "YYYY-MM-DD"
		return -1;

	for (int i = 0; i < 4; i++)
	{
		if (date[i] < '0' || date[i] > '9')
			return -1; // its not an integer, error!
		year += date[i];
	}

	if (date[4] != '-')
		return -1; // incorrect format

	for (int i = 5; i < 7; i++)
	{
		if (date[i] < '0' || date[i] > '9')
			return -1; // its not an integer, error!
		month += date[i];
	}

	if (date[7] != '-')
		return -1; // incorrect format

	for (int i = 8; i < 10; i++)
	{
		if (date[i] < '0' || date[i] > '9')
			return -1; // its not an integer, error!
		day += date[i];
	}

	// checking if year, month and day are valid
	int yearInt = stoi(year), monthInt = stoi(month), dayInt = stoi(day);

	if (monthInt <= 0 || monthInt > 12 || dayInt <= 0 || dayInt > daysInMonth(yearInt, monthInt))
		return -1; // invalid date

	if (yearInt <= 2024 && monthInt <= 8 && dayInt <= 31)
		return -1; // invalid date

	ptr = new Date(yearInt, monthInt, dayInt);

	return 1; // format is correct
}

int checkTime(string time, Time *&ptr)
{
	// this function checks if the time is in the correct format
	int hourInt, minuteInt;

	if (time.length() != 5) // the format is "HH:MM"
		return -1;

	try
	{
		hourInt = stoi(time.substr(0, 2));
		minuteInt = stoi(time.substr(3, 2));
	}
	catch (invalid_argument)
	{
		return -1; // error; could not convert to integer
	}

	if (time[2] != ':')
		return -1; // incorrect format

	if (hourInt == 24 && minuteInt != 0)
	{
		return -1;
	}
	else if (hourInt > 23 || minuteInt > 59 || minuteInt % 15 != 0)
		return -1; // incorrect format

	ptr = new Time(hourInt, minuteInt);

	return 1; // all formats are correct
}

int checkAddress(string address, vector<string> &addressSplit, bool flag)
{
	// this function checks if the given address is in the correct format
	string location = "", city = "", state = "", postalCode = "", country = "";
	int counter = 0; // to count the number of ':' encountered
	if (!flag)
		counter++;
	addressSplit.assign(5, "");

	for (auto c : address)
	{
		if (c != ':')
		{
			if (counter == 0)
				location += c;
			else if (counter == 1)
				city += c;
			else if (counter == 2)
				state += c;
			else if (counter == 3)
				postalCode += c;
			else if (counter == 4)
				country += c;
		}
		else
		{
			counter++;
		}
	}

	if (counter != 4)
		return -1; // error, incorrect format

	// assigninig the address
	addressSplit.resize(5);
	addressSplit[0] = location;
	addressSplit[1] = city;
	addressSplit[2] = state;
	addressSplit[3] = postalCode;
	addressSplit[4] = country;

	return 1; // operation finished successfully
}

int main(void)
{
	vector<string> arr(8); // this will hold the input
	int isSuccess;
	bool flag;

	while (1)
	{
		// taking input
		isSuccess = tokenize(arr);
		flag = true;

		if (isSuccess != 1)
		{
			cout << "-1\nError" << endl;
		}
		else if (arr[0] == "End")
			return 0;

		else if (arr[0] == "addCongregation")
		{
			// checking input
			bool flag = false;
			for (int i = 1; i < 5; i++)
			{
				if (arr[i].empty() || arr[i][0] != '\"')
				{
					cout << "-1\nError" << endl;
					flag = true;
					break;
				}
				arr[i].erase(0, 1);
			}

			if (flag)
				continue;

			for (int i = 5; i < 8; i++)
			{
				if (arr[i] != "")
				{
					cout << "-1\nError" << endl;
					cout << "l" << endl;
					flag = true;
					break;
				}
			}

			if (flag)
				continue;

			// checking date
			Date *startDate = NULL, *endDate = NULL;
			if (checkDate(arr[3], startDate) != 1 || checkDate(arr[4], endDate) != 1)
			{
				cout << "-1\nError" << endl;
				continue;
			}
			else if (startDate->year > endDate->year || (startDate->year == endDate->year && (startDate->month > endDate->month || (startDate->month == endDate->month && startDate->day >= endDate->day))))
			{
				cout << "-1\nError" << endl;
				continue;
			}

			// creating new congregate
			new Congregation(arr[1], arr[2], *startDate, *endDate);
			cout << 0 << endl;
			delete startDate;
			delete endDate;
		}
		else if (arr[0] == "deleteCongregation")
		{
			// checking input
			if (arr[1].empty() || arr[1][0] != '\"')
			{
				cout << "-1\nError" << endl;
				continue;
			}

			bool flag = false;
			for (int i = 2; i < 8; i++)
			{
				if (!arr[i].empty())
				{
					cout << "-1\nError" << endl;
					flag = true;
					break;
				}
			}

			if (flag)
				continue;

			arr[1].erase(0, 1);
			Congregation *cong;
			if (Congregation::searchCongregate(arr[1], cong) != 1)
			{
				cout << "-1\nError" << endl;
				continue;
			}

			int index = 0;
			for (auto cong : Congregation::congregates)
			{
				if (cong->name == arr[1])
					break;
				index++;
			}
			Congregation::congregates.erase(Congregation::congregates.begin() + index);

			while (!cong->venues.empty())
			{
				cong->freeVenue(*cong->venues[0]);
			}

			delete cong;
			cout << 0 << endl;
		}
		else if (arr[0] == "showCongregations")
		{
			// checking input
			bool flag = false;
			for (int i = 1; i < 8; i++)
			{
				if (!arr[i].empty())
				{
					cout << "-1\nError" << endl;
					flag = true;
					break;
				}
			}

			if (flag)
			{
				break;
			}

			cout << Congregation::congregates.size() << endl;
			for (auto cong : Congregation::congregates)
			{
				cout << cong->name << ' ' << cong->type << ' ' << cong->startDate << ' ' << cong->endDate << endl;
			}
		}
		else if (arr[0] == "addVenue")
		{
			// checking if input is correct
			if (arr[1].empty() || arr[1][0] != '\"' || arr[2].empty() || arr[2][0] != '\"' || arr[3].empty() || arr[3][0] < '0' || arr[3][0] > '9')
			{
				cout << "-1\nError" << endl;
				continue;
			}

			// checking integer
			flag = true;
			for (int i = 0; i < arr[3].length(); i++)
				if (arr[3][i] < '0' || arr[3][i] > '9')
				{
					cout << "-1\nError" << endl;
					flag = false;
					break;
				}

			if (flag)
			{
				// removing the string identifier
				arr[1].erase(0, 1);
				arr[2].erase(0, 1);

				// converting location to its format
				vector<string> location(5, "");
				if (checkAddress(arr[2], location) != 1)
				{
					cout << "-1\nError" << endl;
					continue;
				}

				// checking address
				for (auto add : location)
				{
					if (add.empty())
					{
						flag = false;
						cout << "-1\nError" << endl;
						break;
					}
				}
				if (!flag)
					continue;

				new Venue(arr[1], location[4], location, stoi(arr[3]));
				cout << "0" << endl;
			}
		}
		else if (arr[0] == "showVenues")
		{
			// checking input
			if (arr[1].empty() || arr[1][0] != '\"')
			{
				cout << "-1\nError" << endl;
				continue;
			}
			for (int i = 2; i < 8; i++)
				if (arr[i] != "")
				{
					cout << "-1\nError" << endl;
					flag = false;
					break;
				}

			if (flag)
			{
				// getting location
				arr[1].erase(0, 1);
				vector<string> location(5, "");
				if (checkAddress(arr[1], location, (bool)false) != 1)
				{
					cout << "-1\nError" << endl;
					continue;
				}

				if (Venue::showVenues(location) != 1)
				{
					cout << "-1\nError" << endl;
					continue;
				}
			}
		}
		else if (arr[0] == "deleteVenue")
		{
			// checking input
			flag = true;
			if (arr[1].empty() || arr[1][0] != '\"' || arr[2].empty() || arr[2][0] != '\"')
			{
				cout << "-1\nError" << endl;
				continue;
			}
			else
			{
				for (int i = 3; i < 6; i++)
					if (arr[i] != "")
					{
						cout << "-1\nError" << endl;
						flag = false;
						break;
					}
			}

			if (!flag)
			{
				continue;
			}

			// removing the string identifier
			arr[1].erase(0, 1);
			arr[2].erase(0, 1);

			// fetching venue and checking if its reserved
			Venue *ven;
			if (Venue::searchVenue(arr[1], arr[2], ven) != 1 || ven->congregations.size() != 0)
			{
				cout << "-1\nError" << endl;
				continue;
			}

			// removing it from the array
			int i;
			for (i = 0; i < Venue::venues.size(); i++)
			{
				if (ven->name == arr[1] && ven->country == arr[2])
					break;
			}
			Venue::venues.erase(Venue::venues.begin() + i);

			// deleting it
			delete ven;

			cout << "0" << endl;
		}
		else if (arr[0] == "reserveVenue")
		{
			// checking input
			if (arr[1].empty() || arr[1][0] != '\"' || arr[2].empty() || arr[2][0] != '\"' || arr[3].empty() || arr[3][0] != '\"')
			{
				cout << "-1\nError" << endl;
				continue;
			}

			flag = false;
			for (int i = 4; i < 8; i++)
			{
				if (!arr[i].empty())
				{
					cout << "-1\nError" << endl;
					flag = true;
					break;
				}
			}

			if (flag)
				continue;

			// removig string identifier
			arr[1].erase(0, 1);
			arr[2].erase(0, 1);
			arr[3].erase(0, 1);

			Congregation *cong;
			Venue *ven;
			if (Congregation::searchCongregate(arr[3], cong) != 1 || Venue::searchVenue(arr[1], arr[2], ven) != 1 || cong->reserveVenue(*ven) != 1)
			{
				cout << "-1\nError" << endl;
				continue;
			}
			else
				cout << 0 << endl;
		}
		else if (arr[0] == "freeVenue")
		{
			// checking input
			if (arr[1].empty() || arr[1][0] != '\"' || arr[2].empty() || arr[2][0] != '\"' || arr[3].empty() || arr[3][0] != '\"')
			{
				cout << "-1\nError" << endl;
				continue;
			}

			flag = false;
			for (int i = 4; i < 8; i++)
			{
				if (!arr[i].empty())
				{
					cout << "-1\nError" << endl;
					flag = true;
					break;
				}
			}

			if (flag)
				continue;

			// removig string identifier
			arr[1].erase(0, 1);
			arr[2].erase(0, 1);
			arr[3].erase(0, 1);

			Congregation *cong;
			Venue *ven;
			if (Congregation::searchCongregate(arr[3], cong) != 1 || Venue::searchVenue(arr[1], arr[2], ven) != 1 || cong->freeVenue(*ven) != 1)
			{
				cout << "-1\nError" << endl;
				continue;
			}
			else
				cout << 0 << endl;
		}
		else if (arr[0] == "showReserved")
		{
			// checking input
			if (arr[1].empty() || arr[1][0] != '\"')
			{
				cout << "-1\nError" << endl;
				continue;
			}

			flag = false;
			for (int i = 2; i < 8; i++)
			{
				if (!arr[i].empty())
				{
					cout << "-1\nError" << endl;
					flag = true;
					break;
				}
			}

			if (flag)
			{
				continue;
			}

			// searching congregate and printing
			Congregation *cong;
			arr[1].erase(0, 1);
			if (Congregation::searchCongregate(arr[1], cong) != 1 || cong->showReserved() != 1)
			{
				cout << "-1\nError" << endl;
				continue;
			}
		}
		else if (arr[0] == "addEvent")
		{
			// checking input
			bool flag = false;
			for (int i = 1; i < 8; i++)
			{
				if (arr[i].empty() || arr[i][0] != '\"')
				{
					cout << "-1\nError" << endl;
					flag = true;
					break;
				}
				arr[i].erase(0, 1);
			}

			if (flag)
				continue;
			Congregation *cong;
			Venue *ven;
			Date *date;
			Time *start, *end;

			if (Congregation::searchCongregate(arr[1], cong) != 1 || Venue::searchVenue(arr[2], arr[3], ven) != 1 || checkDate(arr[4], date) != 1 || checkTime(arr[5], start) != 1 || checkTime(arr[6], end) != 1 || cong->addEvent(*ven, *date, *start, *end, arr[7]) != 1)
			{
				cout << "-1\nError" << endl;
				continue;
			}

			cout << "0" << endl;
		}
		else if (arr[0] == "showEvents")
		{
			// checking input
			if (arr[1].empty() || arr[1][0] != '\"' || arr[2].empty() || arr[2][0] != '\"' || arr[3].empty() || arr[3][0] != '\"')
			{
				cout << "-1\nError" << endl;
				continue;
			}

			// checking if no other input is given
			flag = true;
			for (int i = 4; i < 6; i++)
				if (arr[i] != "")
				{
					cout << "-1\nError" << endl;
					flag = false;
					break;
				}

			if (flag)
			{
				// removing the string identifier
				arr[1].erase(0, 1);
				arr[2].erase(0, 1);
				arr[3].erase(0, 1);

				// showing events
				Venue *ven;
				Date *date;
				if (Venue::searchVenue(arr[1], arr[2], ven) != 1 || checkDate(arr[3], date) != 1 || ven->showEvents(*date) != 1)
				{
					cout << "-1\nError" << endl;
					continue;
				}
			}
		}
		else if (arr[0] == "deleteEvent")
		{
			// checking input
			bool flag = false;
			for (int i = 1; i < 7; i++)
			{
				if (arr[i].empty() || arr[i][0] != '\"')
				{
					cout << "-1\nError" << endl;
					flag = true;
					break;
				}
				arr[i].erase(0, 1);
			}

			if (flag)
				continue;

			// deleting event
			Congregation *cong;
			Venue *ven;
			Date *date;
			Time *time;

			if (Congregation::searchCongregate(arr[1], cong) != 1 || Venue::searchVenue(arr[2], arr[3], ven) != 1 || checkDate(arr[4], date) != 1 || checkTime(arr[5], time) != 1 || cong->deleteEvent(*ven, *date, *time, arr[6]) != 1)
			{
				cout << "-1\nError" << endl;
				continue;
			}

			cout << "0" << endl;
		}
		else if (arr[0] == "showCalendar")
		{
			// checking input
			if (arr[1].empty() || arr[1][0] != '\"' || arr[2].empty() || arr[2][0] != '\"' || arr[3].empty() || arr[3][0] != '\"')
			{
				cout << "-1\nError" << endl;
				continue;
			}

			flag = false;
			for (int i = 4; i < 8; i++)
			{
				if (!arr[i].empty())
				{
					cout << "-1\nError" << endl;
					flag = true;
					break;
				}
			}

			if (flag)
			{
				continue;
			}

			// removing string identifier
			arr[1].erase(0, 1);
			arr[2].erase(0, 1);
			arr[3].erase(0, 1);

			// showing calendar
			Congregation *cong;
			Venue *ven;

			if (Congregation::searchCongregate(arr[1], cong) != 1 || Venue::searchVenue(arr[2], arr[3], ven) != 1 || cong->showCalendar(*ven) != 1)
			{
				cout << "-1\nError" << endl;
				continue;
			}
		}
		else
		{
			cout << "-1\nError" << endl;
		}
	}
}
