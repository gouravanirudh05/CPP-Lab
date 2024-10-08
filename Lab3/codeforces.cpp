#include <iostream>
#include <string>

using namespace std;

// Event Class
class Event {
private:
    string eventName;
    string date;
    string startTime;
    string endTime;
    Event* next;

public:
    Event(string eventName, string date, string startTime, string endTime) {
        this->eventName = eventName;
        this->date = date;
        this->startTime = startTime;
        this->endTime = endTime;
        this->next = nullptr;
    }

    // Validation methods
    bool validTime(string time) {
        if (time.length() != 5 || time[2] != ':')
            return false;
        int hour = stoi(time.substr(0, 2));
        int minute = stoi(time.substr(3));
        return (hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59 && (minute % 15 == 0));
    }

    bool validDate(string date) {
        if (date.length() != 10 || date[4] != '-' || date[7] != '-')
            return false;
        int year = stoi(date.substr(0, 4));
        int month = stoi(date.substr(5, 2));
        int day = stoi(date.substr(8, 2));
        if (month < 1 || month > 12 || day < 1 || day > 31)
            return false;
        if (month == 4 || month == 6 || month == 9 || month == 11)
            return day <= 30;
        if (month == 2) {
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
                return day <= 29;
            else
                return day <= 28;
        }
        return true;
    }

    bool validEvent() {
        return validTime(this->startTime) && validTime(this->endTime) && validDate(this->date);
    }

    // Getters and Setters
    Event* getNext() {
        return next;
    }

    void setNext(Event* next) {
        this->next = next;
    }

    string getDate() {
        return date;
    }

    string getStartTime() {
        return startTime;
    }

    string getEventName() {
        return eventName;
    }

    string getEndTime() {
        return endTime;
    }
};

// Venue Class
class Venue {
private:
    string venueName;
    string address;
    int capacity;
    Event* events;
    Venue* next;

public:
    Venue(string venueName, string address, int capacity) {
        this->venueName = venueName;
        this->address = address;
        this->capacity = capacity;
        this->events = nullptr;
        this->next = nullptr;
    }

    ~Venue() {
        while (events != nullptr) {
            Event* temp = events;
            events = events->getNext();
            delete temp;
        }
    }

    // Add an event to the venue
    bool addEvent(Event* event) {
        if (!event->validEvent())
            return false;

        if (!events) {
            events = event;
            return true;
        }

        Event* curr = events;
        Event* prev = nullptr;

        while (curr) {
            if (curr->getDate() == event->getDate() && curr->getStartTime() == event->getStartTime()) {
                return false; // Event at this time already exists
            }
            if (curr->getDate() == event->getDate() && curr->getStartTime() > event->getStartTime()) {
                break;
            }
            prev = curr;
            curr = curr->getNext();
        }

        if (prev == nullptr) {
            event->setNext(events);
            events = event;
        } else {
            event->setNext(curr);
            prev->setNext(event);
        }

        return true;
    }

    // Delete an event from the venue
    bool deleteEvent(string eventName, string date, string startTime) {
        Event* curr = events;
        Event* prev = nullptr;

        while (curr) {
            if (curr->getEventName() == eventName && curr->getDate() == date && curr->getStartTime() == startTime) {
                if (prev == nullptr) {
                    events = curr->getNext();
                } else {
                    prev->setNext(curr->getNext());
                }
                delete curr;
                return true;
            }
            prev = curr;
            curr = curr->getNext();
        }

        return false;
    }

    // Show all events on a given date
    void showEvents(string date) {
        Event* curr = events;
        int count = 0;

        while (curr) {
            if (curr->getDate() == date) {
                if (count == 0) {
                    cout << "Events on " << date << ":\n";
                }
                cout << "Event Name: " << curr->getEventName() << ", Start Time: " << curr->getStartTime() << ", End Time: " << curr->getEndTime() << endl;
                count++;
            }
            curr = curr->getNext();
        }

        if (count == 0) {
            cout << "No events found on " << date << endl;
        }
    }

    // Getters and Setters
    Venue* getNext() {
        return next;
    }

    void setNext(Venue* next) {
        this->next = next;
    }

    string getVenueName() {
        return venueName;
    }

    string getAddress() {
        return address;
    }

    int getCapacity() {
        return capacity;
    }

    Event* getEvents() {
        return events;
    }
};

// Venue Manager Class
class VenueManager {
private:
    Venue* venues;

public:
    VenueManager() {
        venues = nullptr;
    }

    ~VenueManager() {
        while (venues != nullptr) {
            Venue* temp = venues;
            venues = venues->getNext();
            delete temp;
        }
    }

    // Add a venue to the manager
    bool addVenue(string venueName, string address, int capacity) {
        Venue* newVenue = new Venue(venueName, address, capacity);
        if (!venues) {
            venues = newVenue;
            return true;
        }

        Venue* curr = venues;
        while (curr->getNext()) {
            if (curr->getVenueName() == venueName) {
                delete newVenue;
                return false; // Venue name must be unique
            }
            curr = curr->getNext();
        }

        if (curr->getVenueName() == venueName) {
            delete newVenue;
            return false; // Venue name must be unique
        }

        curr->setNext(newVenue);
        return true;
    }

    // Delete a venue
    bool deleteVenue(string venueName) {
        Venue* curr = venues;
        Venue* prev = nullptr;

        while (curr) {
            if (curr->getVenueName() == venueName) {
                if (prev == nullptr) {
                    venues = curr->getNext();
                } else {
                    prev->setNext(curr->getNext());
                }
                delete curr;
                return true;
            }
            prev = curr;
            curr = curr->getNext();
        }

        return false;
    }

    // Show all venues
    void showVenues() {
        Venue* curr = venues;
        if (!curr) {
            cout << "No venues available." << endl;
            return;
        }

        while (curr) {
            cout << "Venue Name: " << curr->getVenueName() << ", Address: " << curr->getAddress() << ", Capacity: " << curr->getCapacity() << endl;
            curr = curr->getNext();
        }
    }

    // Find a venue by name
    Venue* findVenue(string venueName) {
        Venue* curr = venues;
        while (curr) {
            if (curr->getVenueName() == venueName) {
                return curr;
            }
            curr = curr->getNext();
        }
        return nullptr;
    }
};

// Congregation Class
class Congregation {
private:
    string name;
    string type;
    string startDate;
    string endDate;
    Congregation* next;

public:
    Congregation(string name, string type, string startDate, string endDate) {
        this->name = name;
        this->type = type;
        this->startDate = startDate;
        this->endDate = endDate;
        this->next = nullptr;
    }

    ~Congregation() {}

    // Getters and Setters
    Congregation* getNext() {
        return next;
    }

    void setNext(Congregation* next) {
        this->next = next;
    }

    string getName() {
        return name;
    }

    string getType() {
        return type;
    }

    string getStartDate() {
        return startDate;
    }

    string getEndDate() {
        return endDate;
    }
};

// Congregation Manager Class
class CongregationManager {
private:
    Congregation* congregations;

public:
    CongregationManager() {
        congregations = nullptr;
    }

    ~CongregationManager() {
        while (congregations != nullptr) {
            Congregation* temp = congregations;
            congregations = congregations->getNext();
            delete temp;
        }
    }

    // Add a congregation
    bool addCongregation(string name, string type, string startDate, string endDate) {
        Congregation* newCongregation = new Congregation(name, type, startDate, endDate);
        if (!congregations) {
            congregations = newCongregation;
            return true;
        }

        Congregation* curr = congregations;
        while (curr->getNext()) {
            if (curr->getName() == name) {
                delete newCongregation;
                return false; // Congregation name must be unique
            }
            curr = curr->getNext();
        }

        if (curr->getName() == name) {
            delete newCongregation;
            return false; // Congregation name must be unique
        }

        curr->setNext(newCongregation);
        return true;
    }

    // Delete a congregation
    bool deleteCongregation(string name) {
        Congregation* curr = congregations;
        Congregation* prev = nullptr;

        while (curr) {
            if (curr->getName() == name) {
                if (prev == nullptr) {
                    congregations = curr->getNext();
                } else {
                    prev->setNext(curr->getNext());
                }
                delete curr;
                return true;
            }
            prev = curr;
            curr = curr->getNext();
        }

        return false;
    }

    // Show all congregations
    void showCongregations() {
        Congregation* curr = congregations;
        if (!curr) {
            cout << "No congregations available." << endl;
            return;
        }

        while (curr) {
            cout << "Congregation Name: " << curr->getName() << ", Type: " << curr->getType()
                 << ", Start Date: " << curr->getStartDate() << ", End Date: " << curr->getEndDate() << endl;
            curr = curr->getNext();
        }
    }

    // Find a congregation by name
    Congregation* findCongregation(string name) {
        Congregation* curr = congregations;
        while (curr) {
            if (curr->getName() == name) {
                return curr;
            }
            curr = curr->getNext();
        }
        return nullptr;
    }
};

// Main function
int main() {
    VenueManager venueManager;
    CongregationManager congregationManager;

    // Example usage
    venueManager.addVenue("Main Hall", "123 Street", 500);
    venueManager.addVenue("Conference Room", "456 Avenue", 100);
    venueManager.showVenues();

    congregationManager.addCongregation("Community Gathering", "Social", "2024-09-01", "2024-09-07");
    congregationManager.showCongregations();

    Venue* venue = venueManager.findVenue("Main Hall");
    if (venue) {
        Event* event = new Event("Opening Ceremony", "2024-09-01", "10:00", "12:00");
        if (venue->addEvent(event)) {
            cout << "Event added successfully!" << endl;
        } else {
            cout << "Failed to add event." << endl;
        }
    }

    venue->showEvents("2024-09-01");

    return 0;
}
