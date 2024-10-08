#include<iostream>//Including all the header files required
#include<cstring>

using namespace std;
// Class to represent an Event with all the event details as attributes
class Event
{
    private://All the attributes are defined private
    int date;//This is the date of the event (1-30)
    int begin;//This is the start of the event (0-24)
    int end; //This is the end of the event (0-24)
    string eventname;//This is the name of the event
    Event *next;//This is the next event to be added to the event list which is a linked list

public:
    Event()//Default constructor
    {
        this->date = 0;
        this->begin = 0;
        this->end = 0;
        this->next = NULL;
        this->eventname="";
    }
    
    Event(int date, int begin, int end, string name)
    {   
        //Parametrised constructor to store all the parameters to the event object
        this->date =date;// This is the date of the event
        this->begin = begin;// This is the begin of the event
        this->end = end;// This is the end of the event
        this->eventname=name;// This is the name of the event
        this->next = NULL;// This is the next event to be added to the event which is set to NULL
    }
    ~Event(){
        //This is the destructor that deletes the dynamically allocated memory for the event object
    }
    //Getter and setter functions for the event object as we have private attributes
    int getdate()
    {   //This returns the date of the event
        return this->date;
    }
    int getbegin()
    {
        //This returns the begin hour of the event
        return this->begin;
    }
    int getend()
    {   //This returns the end hour of the event
        return this->end;
    }
    string geteventname()
    {  
        //This returns the name of the event
        return this->eventname;
    }
    Event *getnext()
    {   //This returns the pointer to the next Event object in the linked list
        return this->next;
    }

    void setdate(int date)
    {
        //This sets the date
        this->date = date;
    }
    void setbegin(int begin)
    {
        //This sets the begin hour of the event
        this->begin = begin;
    }
    void setend(int end)
    {   
        //This sets the end hour of the event
        this->end = end;
    }
    void seteventname(string name)
    {
        //This sets the name of the event
        this->eventname=name;
    }
    void setnext(Event *nextEvent)
    {
        //This sets the pointer to the next Event object in the linked list
        this->next = nextEvent;
    }
};


class Location
{
    //Location class has stadium name,the location name,capacity of the stadium and the pointer list to the next event at the venue as the attributes
    //All these attributes are private to prevent direct access to them from outside the class.
private:
    string stadium;// This is the name of the stadium
    string location;//This is the name of the location of the stadium
    int capacity;//This is the capacity of the stadium
    Event *list;//This is the pointer to the next event at the stadium 
public:
    Location()
    {
        //Default constructor to intialize the location attributes with default values 
        this->capacity = 0;//This is the capacity of the stadium
        this->list = NULL;//This is the pointer to the next event at the venue
        this->stadium="";//This is the name of the stadium
        this->location="";//This is the name of the location
    }
    Location(string stadium, string location, int capacity)
    { 
        //Parametrized constructor to initialize the location attributes with the  values when object is created
        this->stadium=stadium;//This is the name of the stadium 
        this->location=location;//This is the name of the location
        this->capacity = capacity;//This is the capacity of the stadium
        this->list = NULL;//This is the pointer to the next event at the venue
    }
    ~Location() 
    { //Destuctor to destroy the location object 
    while (list) {
        Event *temp = list;
        list = list->getnext();
        delete temp; 
    }
}
    //Getter and setter functions for the location object as we have private attributes 
    string getstadium()
    { 
        //This function returns the name of the stadium
        return this->stadium;
    }
    string getlocation()
    {   
        //This function returns the name of the location
        return this->location;
    }
    int getCapacity()
    {
        //This function returns the capacity of the stadium
        return this->capacity;
    }
    Event *getlist()
    {
        //This is a pointer to the event list at a venue
        return this->list;
    }

    void setVenueName(string stadium)
    {
        //This is used to set the value of the stadium
        this->stadium=stadium;
    }
    void setLocation(string location)
    {
        //This is used to set the value of the location
        this->location=location;
    }
    void setCapacity(int capacity)
    {
        //This is used to set the value of the capacity of the stadium
        this->capacity = capacity;
    }
    void setlist(Event *list)
    {
        //This is used to set the pointer of the event list
        this->list = list;
    }
};

class Scheduler
{  
    //Scheduler class has an array of pointers to Location objects and an integer count to keep track of the number of venues.
    private:
    Location *locations[50];//  Array of pointers to 50 Location class objects
    int count;//This is used to keep track of venues added
    int findpos(string stadium)
    {    
        //This function finds the position of the venue in the array based on its stadium name
        for (int i = 0; i < count; i++)
        {   //Iterating through the array of Location objects
            if (stadium==locations[i]->getstadium())
            {  
                //Matching the stadium name 
                return i;//Returning the position of the Location object in the array 
            }
        }
        return -1;//Not found
    }

public:
    Scheduler() 
    {   
        //Default constructor to initialize the count to 0
        this->count=0;
    }
    ~Scheduler()
    {
        //Destructor to destroy all the Location objects when the Scheduler object is destroyed
        for (int i = 0; i < count; i++)
        {
            delete locations[i];
        }
    }
    void addVenue(string stadium, string location, int capacity)
    {
        //This function adds the venue to the list of location objects
        if (count >= 50)//Maxium number of location objects allowed is 50
        {
           cout<<-1<<endl<<"Error"<<endl;//Trying to add more than 50
            return;
        }

        if (findpos(stadium) != -1)
        {
           cout<<-1<<endl<<"Error"<<endl;//this Location object not found in the list of location objects
            return;
        }

        locations[count] = new Location(stadium, location, capacity);//Create a new location object
        count++;//Add the location object to the list
        cout << "0" << endl;//Successfully added
    }
    void delVenue(string name)
    {   
        //This function deletes the venue from the list of location objects
        int pos = findpos(name);//Find the location object in the list of location objects
        if (pos == -1)
        {
            //Location object not found in the list of location objects
           cout<<-1<<endl<<"Error"<<endl;
            return;
        }
        delete locations[pos];//Delete the location object from the list
        for (int i = pos; i < count - 1; i++)
        {
            locations[i] = locations[i + 1];//Swapping to make up for the position that was deleted
        }

        count--;//One Venue got deleted
        cout << "0" << endl;//Success message
    }

    void showVenues()
    {   
        //This function shows the list of venues along with their details
        cout << count << "\n";
        for (int i = 0; i < count; i++)
        {
            cout << locations[i]->getstadium() << " " << locations[i]->getlocation() << " " << locations[i]->getCapacity() << endl;
        }
    }

    void addEvent(string stadium, int date, int begin, int end, string eventname)
    {   
        //This function adds an event to the list of events at a venue
        int pos = findpos(stadium);//Finding if the Venue exists
        if (pos == -1)//Venue not found
        {
           cout<<-1<<endl<<"Error"<<endl;
            return;
        }
        if (date<1||date>30||begin<0||end>24||begin>=end)
        { 
            //Invalid date or time
           cout<<-1<<endl<<"Error"<<endl;
            return;
        }
        Event *newEvent = new Event(date, begin, end, eventname);// Creating a new object of type Event
        Event *curr = locations[pos]->getlist();
        while (curr != NULL)
        {  
            //Checking if there are any clashes between the events
            if ((curr->getdate() == date) && (begin < curr->getend()) && (end > curr->getbegin()))
            {
               cout<<-1<<endl<<"Error"<<endl;
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

    void delEvent(string stadium, int date, int begin, string eventname)
    {   
        //This function deletes an event from the list of events at a venue
        int pos = findpos(stadium);//find the position of the event
        if (pos == -1)
        {
           cout<<-1<<endl<<"Error"<<endl;
            return;
        }

        Event *curr = locations[pos]->getlist();
        Event *prev = NULL;

        while (curr != NULL)
        {
            if (curr->getdate() == date && curr->getbegin() == begin && curr->geteventname()==eventname)
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

       cout<<-1<<endl<<"Error"<<endl;
    }

    void showEvents(string stadium, int date)
    {   
        //This function shows the events at a stadium on a given date
        int pos = findpos(stadium);
        if (pos == -1)
        { 
           cout<<-1<<endl<<"Error"<<endl;
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

    void showCalendar(string stadium)
    {
        // Find the position of the stadium in the list of locations
        int pos = findpos(stadium);
        if (pos == -1)
        {
            //  If the stadium is not found, print an error and return
           cout<<-1<<endl<<"Error"<<endl;
            return;
        }
        // variables to count the total number of events and events per day
        int eventcount = 0;
        int events[30] = {0};
        // head of the linked list of events for the specified location
        Event *curr = locations[pos]->getlist();
        while (curr != NULL)
        {
            // Traverse the linked list to count events and store them in the `events` array
            events[curr->getdate() - 1]++;
            eventcount++;
            curr = curr->getnext();
        }

         cout << eventcount << "\n";
         // Loop through each day of the month (1 to 30)
        for (int i = 0; i < 30; i++)
        {   
            // the day number and the number of events on that day
            cout << i + 1 << " " << events[i] << "\n";
            curr = locations[pos]->getlist();
            while (curr != NULL)
            {   
                 // If the event occurs on the current day, print its details
                if (curr->getdate() == i + 1)
                {
                    cout << curr->geteventname() << " " << curr->getbegin() << " " << curr->getend() << "\n";
                }
                 curr = curr->getnext();// Move to the next event in the list
            }
        }
    }
};

int main()
{
    Scheduler scheduler;//Creating an instance of the scheduler
//This function takes in the input and extracts the commands and all the details and calls the functions respectively
    char command[100];// This is the command string
    char d[100][100];// Array to store details of each command
    while (fgets(command, sizeof(command), stdin))
    {
        int i = 0, j = 0;
        int flag = 0;// Flag is used to determine if a double quote was encountered
        int length = 0;

        while (command[i] != '\0' && command[i] != '\n')
        {
            if (command[i] == '"')
            {
                flag = !flag;// Negating the flag when a doublequote is encountered
            }
            else if (isspace(command[i]) && !flag)
            {
                if (j > 0)
                {
                    d[length][j] = '\0';// To end a word
                    length++;
                    j = 0;// Reset pos for the next word
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
           
          if (strcmp(d[i], "addVenue") == 0)
            { 
                  // Adding a new venue

                if (length == 4)
                {
                    scheduler.addVenue(d[i + 1], d[i + 2], atoi(d[i + 3]));
                }
                else
                {
                    cout<<-1<<endl<<"Error"<<endl;
                }
            }
            else if (strcmp(d[i], "showVenues") == 0)
            {
                // Showing all the venue information
                if (length == 1)
                {
                    scheduler.showVenues();
                }
                else
                {
                    cout<<-1<<endl<<"Error"<<endl;
                }
            }
            else if (strcmp(d[i], "delVenue") == 0)
            {
                // Deleting a venue
                if (length == 2)
                {
                    scheduler.delVenue(d[i + 1]);
                }
                else
                {
                    cout<<-1<<endl<<"Error"<<endl;
                }
            }
            else if (strcmp(d[i], "addEvent") == 0)
            {
                // Adding a new event
                if (length == 6)
                {
                    scheduler.addEvent(d[i + 1], atoi(d[i + 2]), atoi(d[i + 3]), atoi(d[i + 4]), d[i + 5]);
                }
                else
                {
                    cout<<-1<<endl<<"Error"<<endl;
                }
            }
            else if (strcmp(d[i], "delEvent") == 0)
            {
                 // Deleting an event at a location specified
                if (length == 5)
                {
                    scheduler.delEvent(d[i + 1], atoi(d[i + 2]), atoi(d[i + 3]), d[i + 4]);
                }
                else
                {
                    cout<<-1<<endl<<"Error"<<endl;
                }
            }
            else if (strcmp(d[i], "showEvents") == 0)
            {
                // Show events for a specific venue and date
                if (length == 3)
                {
                    scheduler.showEvents(d[i + 1], atoi(d[i + 2]));
                }
                else
                {
                    cout<<-1<<endl<<"Error"<<endl;
                }
            }
            else if (strcmp(d[i], "showCalendar") == 0)
            {
                // Extracting the command to show the calendar information
                if (length == 2)
                {
                    scheduler.showCalendar(d[i + 1]);
                }
                else
                {
                    cout<<-1<<endl<<"Error"<<endl;
                }
            }
            else if (strcmp(d[i], "End") == 0)
            {   
                 // Ending the program when End is encountered
                break;
                return 0;
            }
        }
    }

    return 0;
}
