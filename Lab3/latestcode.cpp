#include <iostream>
#include <ctime>//To access the current date and time
#include <string>
#include <vector>
using namespace std;
//Protoypes of the global functions which will be used later
int getdetails(vector<string> &a);//This function will return the details of the command
int year_days(int year, int month, int day);//This function will return the the number of days
bool isLeapYear(int year);//This function will return true if the year is leap
int Month_days(int year, int month);//This function returns the number of days in the month
int isValidAddress(string address, vector<string> &, bool found = true);//matches the conditions of the address and returns true
void handle_error()
{
	//This function returns the error message
	cout << -1 << endl
		 << "Error" << endl;
}
class Convention;
class Time
{
	/**
	 * This class represents a time object with hours and minutes.
	 */
	private:
	int hour, minute;
	public:
	Time(int hour, int minute)
	{
		//Parametrised constructor for initialization
		this->hour = hour;
		this->minute = minute;
	}
	Time()
	{
		//Default constructor to initialize the time to 00:00
		this->hour = 0;
		this->minute = 0;
	}
	~Time() {
		//Destructor to clean up the memory
	}

	//Getter methods for all the private attributes of the class Time
	int getHour() 
	{ 
		return this->hour; 
	}
	int getMinute()
	{
		return this->minute;
	}
	//Setter methods for all the private attributes of the class Time
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
		//Function to add check relation between two time objects
		bool ans = (this->hour > secondobj.hour || (this->hour == secondobj.hour && this->minute >= secondobj.minute));
		return ans;
	}
	bool operator>(Time &secondobj)
	{
		//Function to check if first object is greater than second
		bool ans = (this->hour > secondobj.hour || this->minute > secondobj.minute);
		return ans;
	}
	bool operator==(Time &secondobj)
	{
		//Function to check if two objects are equal
		bool ans = (this->hour == secondobj.hour && this->minute == secondobj.minute);
		return ans;
	}
	int operator-(const Time &secondobj)const 
	{
		//Function to find the difference between two time objects in minutes
		int ans = (((this->hour - secondobj.hour) * 60) + this->minute - secondobj.minute);
		return ans;
	}
	friend ostream &operator<<(ostream &os, const Time &time)
	{
		//Function to print the time object in the format HH:MM
		if (time.hour < 10)
			os << '0'; //Printing zero if the hour is less than 10
		os << time.hour << ':';
		if (time.minute < 10)
			os << '0';//Printing zero if the minute is less than 10
		os << time.minute;
		return os;
	}
};

class Date
{
	/**
	 * This Class represents a date
	 */
	private:
	int year, month, day;
	public:
	Date(int year, int month, int day)
	{ 
		//Parametrised constructor for initialization
		this->day = day;
		this->month = month;
		this->year = year;
	}
	Date()
	{
		//Default constructor to initialize the date to 00/00/00
		this->day = 0;
		this->month = 0;
		this->year = 0;
	}
	~Date() {
		//Destructor to clean up the memory
	}
	//Getter methods for all the private attributes of the class Date
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
	//Setter methods for all the private attributes of the class Date
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
		//Function to check if the first object is greater than or equal to the second
		if (this->year != secondobj.year)//First object is compared base on the year
			return this->year > secondobj.year;

		if (this->month != secondobj.month)//If the year of both the objects are the same ,then comparing the month
			return this->month > secondobj.month;
		return this->day >= secondobj.day;//if month is also same then comparing the day
	}
	bool operator<=(const Date &secondobj)
	{
		//Function to check if the first object is less than or equal to the second
		if (this->year != secondobj.year)//First object is compared base on the year
			return this->year < secondobj.year;

		if (this->month != secondobj.month)//If the year of both the objects are the same then compare based on month
			return this->month < secondobj.month;

		return this->day <= secondobj.day;//If month is also same then we are using the day to compare
	}
	bool operator>(const Date &secondobj)
	{
		//Function to compare if the first object is greater than  the second
		if (this->year != secondobj.year)//First comparing based on the year
			return this->year > secondobj.year;

		if (this->month != secondobj.month)//IF year is the same then comparing based on the month
			return this->month > secondobj.month;

		return this->day > secondobj.day;//If day is the same then comparing based on the day
	}
	bool operator<(const Date &secondobj)
	{
		//Function to compare if the first object is less than  the second
		if (this->year != secondobj.year)//First comparing based on the year
			return this->year < secondobj.year;

		if (this->month != secondobj.month)//IF year is the same then comparing based on the month
			return this->month < secondobj.month;

		return this->day < secondobj.day;//If month is also same then comparing based on day
	}
	bool operator==(const Date &secondobj)
	{
		//Function to check if two objects are equal
		bool ans= (this->year == secondobj.year) &&	//Checking is the year,month and day are the same
			   (this->month == secondobj.month) &&
			   (this->day == secondobj.day);
		return ans;
	}
	Date operator++(int)
	{	
		//Function to increment the date 
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
		//Function to find the difference between two dates in days
		return abs(year_days(year, month, day) - year_days(secondobj.year, secondobj.month, secondobj.day));
	}
	friend ostream &operator<<(ostream &os, const Date &date)
	{
		//Function to print the date object in the format YYYY-MM-DD
		if (date.year < 1000)
			os << '0';//date.year
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
	/**
	 * This class represents a single event with Date and Time fields from the class Time and Date
	 */
	private:
	string name;
	Date date;
	Time start_hour, end_hour;
	public:
	Event(Date date, Time start_hour, Time end_hour, string eventName)
	{
		//Parametrised constructor for initialization
		this->date = date;
		this->start_hour = start_hour;
		this->end_hour = end_hour;
		this->name = eventName;
	}
	~Event() {
		//Destructor to clean up the memory
	}
	//Getter methods for all the private attributes of the class Event
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
	//Setter methods for all the private attributes of the class Event
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
	/**
	 * This class represents a day of the week with the date from the Class Date
	 */
public:
	int count_events;// Number of events in the dday
	vector<Event *> day;//List of events for the day
	Date date;
	Day(Date date)
	{
		//Parametrized constructor for initialization
		this->date = date;
		this->count_events = 0;
		this->day = {};
	}
	~Day()
	{
		//Destructor to clean up the memory
        for (auto event : this->day)
            delete event;
	}
	int addEvent(Time start_hour, Time end_hour, string eventName)
	{
		//Function to add an event to the day
		if (start_hour >= end_hour)//Invalid time as the start_hour cannot be less than end_hour
			return -1;
		int event_index = 0;//index
		for (auto event : this->day)
		{   
			//Iterating through the events in the day
			if (event->getStartHour() >= end_hour)//Invalid time as the start_hour cannot be greater than end
				break;
			else if (event->getEndHour() > start_hour)//
				return -1;
			event_index++;//index
		}
		int d = 0;
		if (event_index > 0 && (start_hour - this->day[event_index - 1]->getEndHour()) < 30)
			return -1;
		else if (event_index < ((int)this->day.size() - 1) && (this->day[event_index + 1]->getStartHour() - end_hour) < 30)
			return -1;
		Event *t = new Event(this->date, start_hour, end_hour, eventName);//Creating a new Event object
		this->day.insert(this->day.begin() + event_index, t);// Inserting a new Event into the day	
		this->count_events++;//Number of events increased by 1
		return 1;
	}
	int deleteEvent(Time start_hour, string eventName)
	{
		//Function to delete an event 
		int index = 0;//Index of the event
		for (auto event : this->day)
		{	
			//Iterating through the events in the day
			if (event->getName() == eventName && event->getStartHour() == start_hour)//If the event matches
				break;
			index++;
		}
		if (this->day.size() == index)//If event is not present
			return -1;
		else
		{
			delete this->day[index];//Delete
			this->day.erase(this->day.begin() + index); // Removing the event
		}
		this->count_events--;//Decrease count of events
		return 1;
	}
	int showEvents()
	{
		//Function to show the events of a day
		cout << this->count_events << endl;//Numver of events for the day
		for (auto event : this->day)
			cout << event->getName() << ' ' << event->getStartHour() << ' ' << event->getEndHour() << endl;
		return 1;
	}
};

class Venue
{
	/**
	 * This is a class that represents a venue
	 */
	private:
	string name;
	string country;
	int capacity;
	public:
	static vector<Venue *> venues;// vector list of venues
	vector<string> location;
	vector<Day *> calendar;
	vector<Convention *> conventionslist;//lost of conventions
	Venue(string venueName, string country, vector<string> location, int capacity)
	{
		//Parametrized constructor for initialization
		this->name = venueName;
		this->country = country;
		this->capacity = capacity;
		this->location.assign(location.begin(), location.end());
		venues.push_back(this);
	}
	~Venue()
	{
		//Destructor to clean up the memory
		conventionslist.clear();
		calendar.clear();
	}

	Venue()
	{
		//Default constructor to initialize the default venue
		this->name = "";
		this->country = "";
		this->capacity = 0;
		venues.push_back(this);
	}
	//Getter methods for the venue
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
	//Setter methods for the private members
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
	int isValidReservation(Date startDate, Date endDate);// Returns if the reservation is valid
	static int showVenues(vector<string> &location_input)
	{
		// Function to show venues based on location
		int venues_count = 0;// Number of venues
		string output = "";// Output venue
		for (auto venu : venues)
		{   
			// Checking if the venue location matches the input location
			bool matches = true;
			for (int i = 0; i < 5; ++i)
			{
				// Checking if the venue location matches 
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
		// Function to find a venue by name and country
		for (auto venue : Venue::venues)
		{ 
			// Iterating through the list of venues
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
		int total_events = 0;//Total events
		for (const auto &day : this->calendar)
		{
			// Iterating through the calendar of the venue
			if (day->date >= startDate && day->date <= endDate)
			{
				total_events += day->count_events;//Total
			}
		}
		cout << total_events << endl;
		Date currentDate = startDate;//	
		for (auto &day : this->calendar)
		{
			// Iterating through the calendar of the venue
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
			// printing the events for the current date
			cout << currentDate << " 0" << endl;
			currentDate++;
		}
		return 1;
	}
	int showEvents(Date date)
	{
		// Function to show events for a given date
		int day_index = 0;// index
		for (const auto &day : this->calendar)
		{
			// Iterating through the calendar of the venue
			if (day->date > date)
			{
				cout << 0 << endl;
				return 1;
			}
			if (day->date == date)
				break;
			++day_index;
		}
		if (day_index < this->calendar.size() && this->calendar[day_index]->date == date)
			return this->calendar[day_index]->showEvents();
		else
		{
			cout << 0 << endl;
			return 1;
		}
	}
};

class Convention
{
	/** 
	 * This class represents  a convention 
	 */
	private:
	string type;
	string name;
	Date startDate, endDate;

public:
	static vector<Convention *> conventions;// list of conventions
	vector<Venue *> venues;// list of venues for a convention
	
	Convention(string name, string type, Date startDate, Date endDate)
	{
		// Parametrized constructor for initialization
		this->venues = {};
		this->name = name;
		this->type = type;
		this->startDate = startDate;
		this->endDate = endDate;
		conventions.push_back(this);
	}
	Convention()
	{
		// Default constructor to initialize the default convention
		this->venues = {};
		this->name = "";
		this->type = "";
		this->startDate = Date();
		this->endDate = Date();
		conventions.push_back(this);
	}
	~Convention() {
		// Destructor to clean up the memory
        venues.clear();
	}
	// Getter methods for the convention
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
	// Setter methods for the private members
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
		// Function to find a convention by name
		for (auto conv : conventions)
		{
			// Iterating through the list of conventions
			if (conv->name == name)// matching convention
			{
				p = conv;
				return 1;
			}
		}
		return -1;// no matching
	}
	int reserveVenue(Venue &venu)
	{
		// Function to reserve a venue for a convention
		if (venu.isValidReservation(this->startDate, this->endDate) == 1)// Checking if that is a valid reservation
		{
			venu.conventionslist.push_back(this);// Adding the venue to the list of venues
		}
		else//Not a vali reservation
			return -1;
		this->venues.push_back(&venu);//Adding the venue to the list of venues
		return 1;
	}
	int freeVenue(Venue &venu)
	{
		// Function to free a venue for a convention
		int index = 0;
		for (auto venue : this->venues)
		{	
			// Iterating through the list of venues
			if (venue->getName() == venu.getName() && venue->getCountry() == venu.getCountry())
				break;
			index++;
		}
		if (index == this->venues.size())
			return -1;
		this->venues.erase(this->venues.begin() + index);//remove duplicates
		for (int i = 0; i < venu.calendar.size(); i++)
		{
			// Iterating through the calendar of the venue
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
		// Function to show reserved venues for a convention
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
		// Function to add an event to a venue for a convention
		bool found = false;
		for (auto venue : this->venues)
		{
			if (venu.getName() == venue->getName() && venu.getCountry() == venue->getCountry())
			{
				found = true;
				break;
			}
		}
		if (!found)
			return -1;
		int index = 0;
		found = false;
		for (auto day : venu.calendar)
		{
			if (day->date == date)
				break;
			if (day->date > date)
			{
				found = true;
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
		if (found || venu.calendar.empty() || index == static_cast<int>(venu.calendar.size()))
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
		bool found = false;
		for (auto venue : this->venues)
		{
			if (venu.getName() == venue->getName() && venu.getCountry() == venue->getCountry())
			{
				found = true;
				break;
			}
		}
		if (found == false)
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
	bool inQuotes = false;
	bool isNumber = false;
	bool isWord = false;
	int count = 0;
	a.clear();
	string input, command;
	getline(cin, input);
	if (input.empty())
		return -1;
	for (int i = 0; i < input.length(); i++)
	{
		if ((inQuotes||input[i] != ' ') && count < 8)
		{
			if (input[i] == '\"')
			{
				if (isWord || isNumber)
					return -1;
				if (inQuotes)
				{
					a.push_back(command);
					command.clear();
					count++;
					inQuotes = false;
				}
				else
				{
					inQuotes = true;
					command += '\"';
				}
			}
			else
			{
				if (isNumber && (input[i] < '0' || input[i] > '9'))
					return -1;
				if (!isNumber)
				{
					if (input[i] >= '0' && input[i] <= '9' && !inQuotes && !isWord)
					{
						isNumber = true;
					}
					else if (!inQuotes)
					{
						isWord = true;
					}
				}
				command += input[i];
			}
		}
		else if (input[i] == ' ')
		{
			if (isNumber || isWord)
			{
				a.push_back(command);
				command.clear();
				isNumber = false;
				isWord = false;
				count++;
			}
		}
		else if (count >= 8)
			return -1;
	}
	if (!command.empty())
	{
		a.push_back(command);
		count++;
	}
	while (a.size() < 8)
		a.push_back("");
	return 1;
}

int year_days(int year, int month, int day)
{
	int total_days = day;
	for (int i = 0; i < year; ++i)
	{
		if(isLeapYear(i))
		total_days+=366;
		else
		total_days+=365;
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

int isValidAddress(string address, vector<string> &address_arr, bool found)
{

	string location = "";
	string city = "";
	string state = "";
	string postalCode = "";
	string country = "";
	int count = 0;
	if (!found)
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
	bool found;
	while (true)
	{
		ans = getdetails(a);
		found = true;
		if (ans != 1)
		{
			handle_error();
		}
		else if (a[0] == "addEvent")
		{

			bool found = false;
			for (int i = 1; i < 8; i++)
			{
				if (a[i].empty() || a[i][0] != '\"')
				{
					handle_error();
					found = true;
					break;
				}
				a[i].erase(0, 1);
			}
			if (found)
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
			found = true;
			for (int i = 4; i < 6; i++)
				if (a[i] != "")
				{
					handle_error();
					found = false;
					break;
				}
			if (found)
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
			bool found = false;
			for (int i = 1; i < 7; i++)
			{
				if (a[i].empty() || a[i][0] != '\"')
				{
					handle_error();
					found = true;
					break;
				}
				a[i].erase(0, 1);
			}
			if (found)
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
			if (a[1].empty() ||a[2].empty()|| a[3].empty()|| a[1][0] != '\"' || a[2][0] != '\"'  || a[3][0] != '\"')
			{
				handle_error();
				continue;
			}
			found = false;
			for (int i = 4; i < 8; i++)
			{
				if (!a[i].empty())
				{
					handle_error();
					found = true;
					break;
				}
			}
			if (found)
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
			found = true;
			for (int i = 0; i < a[3].length(); i++)
				if (a[3][i] < '0' || a[3][i] > '9')
				{
					handle_error();
					found = false;
					break;
				}

			if (found)
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
						found = false;
						handle_error();
						break;
					}
				}
				if (!found)
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
					found = false;
					break;
				}

			if (found)
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
			found = true;
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
						found = false;
						break;
					}
			}
			if (!found)
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

			found = false;
			for (int i = 4; i < 8; i++)
			{
				if (!a[i].empty())
				{
					handle_error();
					found = true;
					break;
				}
			}
			if (found)
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
			found = false;
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
					found = true;
					break;
				}
			}
			if (found)
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
			found = false;
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
					found = true;
					break;
				}
			}
			if (found)
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
			bool found = false;
			for (int i = 1; i < 5; i++)
			{
				if (a[i].empty() || a[i][0] != '\"')
				{
					handle_error();
					found = true;
					break;
				}
				a[i].erase(0, 1);
			}
			if (found)
				continue;
			for (int i = 5; i < 8; i++)
			{
				if (a[i] != "")
				{
					handle_error();
					found = true;
					break;
				}
			}
			if (found)
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

			bool found = false;
			for (int i = 2; i < 8; i++)
			{
				if (!a[i].empty())
				{
					handle_error();
					found = true;
					break;
				}
			}
			if (found)
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
			bool found = false;
			for (int i = 1; i < 8; i++)
			{
				if (!a[i].empty())
				{
					handle_error();
					found = true;
					break;
				}
			}
			if (found)
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
