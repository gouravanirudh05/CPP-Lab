// #include <bits/stdc++.h>
#include<iostream>
#include<cstring>//Including all the header files
using namespace std;
class Event
{
private:
    int date;
    int begin;
    int end;
    char eventname[100];
    Event *next;

public:
    Event()
    {
        this->date = 0;
        this->begin = 0;
        this->end = 0;
        this->next = NULL;
        strcpy(this->eventname, "");
    }

    void initialize(int d, int begin, int end, char *name)
    {
        this->date = d;
        this->begin = begin;
        this->end = end;
        strcpy(this->eventname, name);
        this->next = NULL;
    }

    int getdate()
    {
        return this->date;
    }
    int getbegin()
    {

        return this->begin;
    }
    int getend()
    {

        return this->end;
    }
    char *geteventname()
    {

        return this->eventname;
    }
    Event *getnext()
    {

        return this->next;
    }

    void setdate(int d)
    {

        this->date = d;
    }
    void setbegin(int begin)
    {

        this->begin = begin;
    }
    void setend(int end)
    {

        this->end = end;
    }
    void seteventname(char *name)
    {

        strcpy(this->eventname, name);
    }
    void setnext(Event *nextEvent)
    {

        this->next = nextEvent;
    }
};

class Location
{
private:
    char stadium[100];
    char location[100];
    int capacity;
    Event *list;

public:
    Location()
    {
        this->capacity = 0;
        this->list = NULL;
        strcpy(this->stadium, "");
        strcpy(this->location, "");
    }
    void initialize(char *name, char *loc, int cap)
    {
        strcpy(this->stadium, name);
        strcpy(this->location, loc);
        this->capacity = cap;
        this->list = NULL;
    }
    char *getstadium()
    {
        return this->stadium;
    }
    char *getlocation()
    {
        return this->location;
    }
    int getCapacity()
    {

        return this->capacity;
    }
    Event *getlist()
    {

        return this->list;
    }

    void setVenueName(char *name)
    {

        strcpy(this->stadium, name);
    }
    void setLocation(char *loc)
    {

        strcpy(this->location, loc);
    }
    void setCapacity(int cap)
    {

        this->capacity = cap;
    }
    void setlist(Event *list)
    {

        this->list = list;
    }
};

class Main
{
private:
    Location *locations[50];
    int count;

    int findpos(char *name)
    {
        for (int i = 0; i < count; i++)
        {
            if (strcmp(name, locations[i]->getstadium()) == 0)
            {
                return i;
            }
        }
        return -1;
    }

public:
    Main() 
    {
        this->count=0;
    }
    void addVenue(char *name, char *location, int capacity)
    {

        if (count >= 50)
        {
            cout << "-1\nError" << endl;
            return;
        }

        if (findpos(name) != -1)
        {
            cout << "-1\nError" << endl;
            return;
        }

        locations[count] = new Location();
        locations[count]->initialize(name, location, capacity);
        count++;
        cout << "0" << endl;
    }

    void delVenue(char *name)
    {
        int pos = findpos(name);
        if (pos == -1)
        {
            cout << "-1\nError" << endl;
            return;
        }

        delete locations[pos];
        for (int i = pos; i < count - 1; i++)
        {
            locations[i] = locations[i + 1];
        }

        count--;
        cout << "0" << endl;
    }

    void showVenues()
    {
        if (count == 0)
        {
            cout << "0" << endl;
            return;
        }

        cout << count << "\n";
        for (int i = 0; i < count; i++)
        {
            cout << locations[i]->getstadium() << " " << locations[i]->getlocation() << " " << locations[i]->getCapacity() << endl;
        }
    }

    void addEvent(char *stadium, int date, int begin, int end, char *eventname)
    {
        int pos = findpos(stadium);
        if (pos == -1)
        {
            cout << "-1\nError" << endl;
            return;
        }

        if (date < 1 || date > 30 || begin < 0 || end > 24 || begin >= end)
        {
            cout << "-1\nError" << endl;
            return;
        }

        Event *newEvent = new Event();
        newEvent->initialize(date, begin, end, eventname);

        Event *curr = locations[pos]->getlist();
        while (curr != NULL)
        {
            if ((curr->getdate() == date) && (begin < curr->getend()) && (end > curr->getbegin()))
            {
                cout << "-1\nError" << endl;
                return;
            }
            curr = curr->getnext();
        }

        if ((locations[pos]->getlist() == NULL) || (locations[pos]->getlist()->getdate() > date) || (locations[pos]->getlist()->getdate() == date && locations[pos]->getlist()->getbegin() > begin))
        {

            newEvent->setnext(locations[pos]->getlist());
            locations[pos]->setlist(newEvent);
        }
        else
        {

            Event *curr = locations[pos]->getlist();
            while (curr->getnext() != NULL && ((curr->getnext()->getdate() < date) || (curr->getnext()->getdate() == date && curr->getnext()->getbegin() <= begin)))
            {
                curr = curr->getnext();
            }
            newEvent->setnext(curr->getnext());
            curr->setnext(newEvent);
        }
        cout << "0" << endl;
    }

    void delEvent(char *stadium, int date, int begin, char *eventname)
    {
        int pos = findpos(stadium);
        if (pos == -1)
        {
            cout << "-1\nError" << endl;
            return;
        }

        Event *curr = locations[pos]->getlist();
        Event *prev = NULL;

        while (curr != NULL)
        {
            if (curr->getdate() == date && curr->getbegin() == begin && strcmp(curr->geteventname(), eventname) == 0)
            {
                if (prev == NULL)
                {

                    locations[pos]->setlist(curr->getnext());
                }
                else
                {

                    prev->setnext(curr->getnext());
                }
                delete curr;
                cout << "0" << endl;
                return;
            }
            prev = curr;
            curr = curr->getnext();
        }

        cout << "-1\nError" << endl;
    }

    void showEvents(char *stadium, int date)
    {
        int pos = findpos(stadium);
        if (pos == -1)
        {
            cout << "-1\nError" << endl;
            return;
        }

        int eventcount = 0;
        Event *curr = locations[pos]->getlist();

        while (curr != NULL)
        {
            if (curr->getdate() == date)
            {
                eventcount++;
            }
            curr = curr->getnext();
        }

        cout << eventcount << "\n";

        curr = locations[pos]->getlist();
        while (curr != NULL)
        {
            if (curr->getdate() == date)
            {

                cout << curr->geteventname() << " " << curr->getbegin() << " " << curr->getend() << "\n";
            }
            curr = curr->getnext();
        }
    }

    void showCalendar(char *stadium)
    {
        int pos = findpos(stadium);
        if (pos == -1)
        {
            cout << "-1\nError" << endl;
            return;
        }

        int eventcount = 0;
        int events[30] = {0};

        Event *curr = locations[pos]->getlist();
        while (curr != NULL)
        {
            events[curr->getdate() - 1]++;
            eventcount++;
            curr = curr->getnext();
        }

        cout << eventcount << "\n";

        for (int i = 0; i < 30; i++)
        {
            cout << i + 1 << " " << events[i] << "\n";
            curr = locations[pos]->getlist();

            while (curr != NULL)
            {
                if (curr->getdate() == i + 1)
                {
                    cout << curr->geteventname() << " " << curr->getbegin() << " " << curr->getend() << "\n";
                }
                curr = curr->getnext();
            }
        }
    }
};

int main()
{
    Main system;

    char command[100];
    char d[100][100];
    int length = 0;

    while (fgets(command, sizeof(command), stdin))
    {
        int i = 0, j = 0;
        int flag = 0;
        length = 0;

        while (command[i] != '\0' && command[i] != '\n')
        {
            if (command[i] == '"')
            {
                flag = !flag;
            }
            else if (isspace(command[i]) && !flag)
            {
                if (j > 0)
                {
                    d[length][j] = '\0';
                    length++;
                    j = 0;
                }
            }
            else
            {

                d[length][j] = command[i];
                j++;
            }
            i++;
        }

        if (j > 0)
        {
            d[length][j] = '\0';
            length++;
        }

        for (int i = 0; i < length; i++)
        {
            if (strcmp(d[i], "showVenues") == 0)
            {

                if (length == 1)
                {
                    system.showVenues();
                }
                else
                {
                    cout<<-1<<endl<<"Error"<<endl;
                }
            }
            else if (strcmp(d[i], "addVenue") == 0)
            {

                if (length == 4)
                {
                    system.addVenue(d[i + 1], d[i + 2], atoi(d[i + 3]));
                }
                else
                {
                    cout<<-1<<endl<<"Error"<<endl;
                }
            }
            else if (strcmp(d[i], "delVenue") == 0)
            {

                if (length == 2)
                {
                    system.delVenue(d[i + 1]);
                }
                else
                {
                    cout<<-1<<endl<<"Error"<<endl;
                }
            }
            else if (strcmp(d[i], "addEvent") == 0)
            {

                if (length == 6)
                {
                    system.addEvent(d[i + 1], atoi(d[i + 2]), atoi(d[i + 3]), atoi(d[i + 4]), d[i + 5]);
                }
                else
                {
                    cout<<-1<<endl<<"Error"<<endl;
                }
            }
            else if (strcmp(d[i], "delEvent") == 0)
            {

                if (length == 5)
                {
                    system.delEvent(d[i + 1], atoi(d[i + 2]), atoi(d[i + 3]), d[i + 4]);
                }
                else
                {
                    cout<<-1<<endl<<"Error"<<endl;
                }
            }
            else if (strcmp(d[i], "showEvents") == 0)
            {

                if (length == 3)
                {
                    system.showEvents(d[i + 1], atoi(d[i + 2]));
                }
                else
                {
                    cout<<-1<<endl<<"Error"<<endl;
                }
            }
            else if (strcmp(d[i], "showCalendar") == 0)
            {

                if (length == 2)
                {
                    system.showCalendar(d[i + 1]);
                }
                else
                {
                    cout<<-1<<endl<<"Error"<<endl;
                }
            }
            else if (strcmp(d[i], "End") == 0)
            {
                break;
                return 0;
            }
        }
    }

    return 0;
}
