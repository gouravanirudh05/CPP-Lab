//#include <bits/stdc++.h>
#include<iostream>
//#include<string.h>
//#include<vector>
using namespace std;

class Event {								//An Event class in a linked list form
	private:					
		string name;						//It stores the name of the Event
		int start;						//Its start time
		int end;						//Its end time
		Event *next;						//Pointer to next Event
	public:
		Event(string Name, int Start, int End){			//Function to create a new event object
			name = Name;
			start = Start;
			end = End;
			next = NULL;
		}
		
		bool compare_name(string x){
			return (name==x);
		}
		
		int getstart(){
			return start;
		}
		
		int getend(){
			return end;
		}
		
		Event* getnext(){
			return next;
		}
		
		void setnext(Event* x){
			next = x;
		}
		
		string getname(){
			return name;
		}
		
};

class Day {								//A day class
	private:
		int number_of_events;					//It stores number of events in the day
		//vector<int> hours = vector<int>(24);			
		int hours[24];						//An array of hours where hours[i] will be 1 if the slot is occupied
		Event *sport;						//A linked list of Events in that day
	public:
		Day(){							//Function to create a new day object
			number_of_events = 0;
			sport = NULL;
		}
		
		bool isfilled(int s, int e){
			for (int i=s;i<e;i++){
				if (hours[i]==1)
					return true;
			}
			return false;
		}
		
		void sethours(int s, int e, int v){
			for (int i=s;i<e;i++)
				hours[i]=v;
		}
		
		void incn(){
			number_of_events++;
		}
		
		void decn(){
			number_of_events--;
		}
		
		int getn(){
			return number_of_events;
		}
		
		Event* getsport(){
			return sport;
		}
		
		void setsport(Event* x){
			sport = x;
		}
};

class Venue {								//A Venue class in a linked list format
	private:
		string name;						//It stores the name of the Venue
		int number_of_events;					//Number of events organised in the venue in the entire month
		int capacity;						//Capacity of the Venue
		string location;					//Location of the Venue
		//vector<Day*> calendar = vector<Day*>(32);		
		Day* calendar[32];					//An array of Days called calendar, which has 31 days 
		Venue * next;						//Pointer to next Venue
	public:
		Venue(string N, string l, int c){			//Function to create a new venue object
			name = N;
			number_of_events = 0;
			capacity = c;
			location = l;
			next = NULL;
			for (int i=0;i<32;i++)				//Creates a day object for all the dates 1 to 31
				calendar[i] = new Day();
		}
		
		bool compare_name(string x){
			return (name==x);
		}
		
		void incn(){
			number_of_events++;
		}
		
		void decn(){
			number_of_events--;
		}
		
		int getn(){
			return number_of_events;
		}
		
		Venue* getnext(){
			return next;
		}
		
		void setnext(Venue* x){
			next = x;
		}
		
		Day* getday(int date){
			return calendar[date];
		}
		
		void setday(int date,Day* x){
			calendar[date]=x;
		}
		
		string getname(){
			return name;
		}
		
		string getloc(){
			return location;
		}
		
		int getcap(){
			return capacity;
		}
};

int number_of_venues=0;                					//Number of venues is set to 0 initially                
Venue* Stadium=NULL;							//Linked list head for venues is set to null

void addVenue(string Name, string Location, int Capacity){		//Function to add a venue to the venues linked list
	Venue* temp = NULL;
	Venue* head = Stadium;
	while (head){							//Loop to traverse the linked list of venues
		if (head->compare_name(Name)){				//Checks if the venue name matches
			cout << "-1\nDuplicate Venue Name" << endl;
			return;
		}
		temp=head;						//temp is used to store previous pointer of head
		head=head->getnext();					//When head reaches null, temp will be at the end of venues list
	}								//Loop ends when no venue name matches
	Venue* newVenue = new Venue(Name, Location, Capacity);		//Create a new Venue object
	if (temp==NULL)
		Stadium = newVenue;					//Condition to add first venue
	else
		temp->setnext(newVenue);				//New venue is added to the end of the venues linked list
	number_of_venues = number_of_venues + 1;			//Update number of events in the venue
	cout << "0" << endl;						//Print 0 for success
	return;
}

void  deleteVenue(string Name){						//Function to delete a given venue from the venues linked list
        if (Stadium==NULL){
		cout << "-1\nVenue Does Not Exist" << endl;		//If the venues linked list head is NULL, it means no venue is added
                return;
	}
	else if (Stadium->compare_name(Name)){				//If the required venue is the head of the venues linked list
		Venue* temp = Stadium;
		Stadium = Stadium->getnext();				//Make the head of the linked list to point to its next Venue
		free(temp);						//Free and delete the required venue pointer
		number_of_venues = number_of_venues - 1;		//Update number of venues after deletion
		cout << "0" << endl;					//Print 0 for succesful deletion
		return;
	}
        else{								//If venues list is not empty, and head is not the required venue
                Venue *l = Stadium->getnext();				//l stored 2nd venue which is next of head pointer
		Venue *m = Stadium;					//m stored head of venues
                while (l!=NULL){					
                        if (l->compare_name(Name)){			//If the required venue is found
                                Venue *temp1 = l;			
                                m->setnext(l->getnext());		//Previous venue's next points to current venue's next
                                l = m->getnext();				
                                free(temp1);				//Free and delete the required venue
				number_of_venues = number_of_venues - 1;//Update number of venues after deletion
				cout << "0" << endl;			//Print 0 for success and return from function
				return;					
                        }							
                        else{						
                                l=l->getnext();				//If Required venue isnt found
                                m=m->getnext();				//continue traversing the linked list
                        }						
                }							
        }								
	cout << "-1\nVenue Does Not Exist" << endl;			//If required venue was never found, print -1 and error message
	return;								
}

void showVenues(){							//Function to show all the venues added so far
	if (number_of_venues == 0){					//If no venue is added
		cout << "0" << endl;					//Print 0 and return from the functoin
		return;
	}
	else{
		cout << number_of_venues << endl;			//Print number of events added
		Venue* head = Stadium;
		while (head){						//Loop to traverse the venues linked list
			cout << head->getname() << " " << head->getloc() << " " << head->getcap() << endl;//Prints name, location and capacity
			head = head->getnext();
		}
		return;
	}
}

int addEvent(string venue_name, int date, int from, int to, string event_name){			//Function to add an Event at a given venue
	Venue* head = Stadium;
	if (head==NULL){									//If venue is not added
		cout << "-1\nVenue Not Added" << endl;
		return -2;
	}
	else{	
		while (head){									//Loop to traverse venues
			if (head->compare_name(venue_name)){					//If venue name matches
				Day* temp = head->getday(date);					//temp stores the required Day
				Day* temp2 = head->getday(date+1);				//temp2 stores next Day for splitting at night
				if (to>from){
					if (temp->isfilled(from, to)){				//If hours[i]=1, some other event is scheduled
						cout << "-1\nSlot Is Already Filled" << endl;
						return -2;
					}
					temp->incn();						//Update number of events in the day and venue
					head->incn();
					temp->sethours(from, to, 1);				//Fill the required hours[i] with 1
					Event* new_event = new Event(event_name, from, to);	//Create a new event object 
					if (!temp->getsport() || to <= temp->getsport()->getstart()){   //If there are no events in the day or
						new_event->setnext(temp->getsport());		//the next event starts after this event ends
						temp->setsport(new_event);			//Add the event at the beginning
						head->setday(date,temp);
						return 0;
					}
					else{
						Event *x = temp->getsport();
						while (x->getnext()){				//Traverse the events linked list
							if (to <= x->getnext()->getstart()){	//Traverse to an event that starts after this
								new_event->setnext(x->getnext());
								x->setnext(new_event);		//insert the new event
								head->setday(date,temp);
								return 0;
							}
							x = x->getnext();
						}
						new_event->setnext(x->getnext());		//If no event starts after this event
						x->setnext(new_event);				//Add this event in the end
						head->setday(date,temp);
						return 0;
					}
				}
				else if (from==to)
					return -2;						//If from and to are same, event takes no time
				else{
					if (temp->isfilled(from, 24) || temp2->isfilled(0, to)){//Check if slot is filled
						cout << "-1\nSlot Is Already Filled" << endl;
						return -2;
					}
					addEvent(venue_name, date, from, 24, event_name);	//Add event in this day from start to 24
					addEvent(venue_name, date+1, 0, to, event_name);	//Add event in next day from 0 to end
					head->decn();						//decrement number of events in venue because
					return 0;	
				}
			}
			head = head->getnext();
		}
	}
	cout << "-1\nVenue Not Added" << endl;							//Print -1 and error message for no venue
        return -2;
}

void deleteEvent(string venue_name, int date, int from, string event_name){			//Function to delete an event
	Venue* head = Stadium;
	int to;
        if (head==NULL){									//If no venue is added
                cout << "-1\nVenue Not Added" << endl;
                return;
        }
        else{
                while (head){									//Traverse the venues linked list
        	        if (head->compare_name(venue_name)){					//If venue name matches
				Day* venue_day = head->getday(date);
				Event* temp = venue_day->getsport();				//get a pointer to events in the given date
				if (temp==NULL){						//If there are no events
					cout << "-1\nEvent Not Added" << endl;
                			return;
				}
				else if (temp->compare_name(event_name)){			//If event name matches
					to = temp->getend();
					if (temp->getstart()!=from){				//If start hour does not match
						cout << "-1\nStart Hour Does Not Match" << endl;
                                                return;
					}
					else{
						venue_day->setsport(temp->getnext());		//Set the event pointer to its next
						free(temp);					//Free and delete the required event
						venue_day->sethours(from, to, 0);		//Set hours[i] to 0 to free the slot
						venue_day->decn();				//Update day's events counter
						head->decn();					//Update venue's events counter
						if (to == 24){					//If event ends at EOD
							Day* next_day = head->getday(date+1);	//Get pointer to next day to check if
												//same event is at the start of next day
												//If yes, delete it
							if (next_day->getsport() && next_day->getsport()->compare_name(event_name)){
								Event* temp1 = next_day->getsport();
								next_day->setsport(next_day->getsport()->getnext());
								next_day->sethours(0, temp1->getend(), 0);
								free(temp1);
								next_day->decn();
							}
						}
						cout << "0" << endl;
                                                return;
					}
				}
				else{
					Event* x = temp;					//x has head of events list
					temp = temp->getnext();					//temp has next of head of events
					while (temp!=NULL){					//Traverse the events list
						if (temp->compare_name(event_name)){		//if event name matches
							to = temp->getend();
							if (temp->getstart()!=from){		//If start hour does not match
								cout << "-1\nStart Hour Does Not Match" << endl;
								return;
							}
							else{					//For correct match
								x->setnext(temp->getnext());	//Update the next pointer of previous event
								free(temp);			//free and delete required event
								venue_day->sethours(from, to, 0);//Same process as above is followed
								venue_day->decn();
								head->decn();
								if (to == 24){
                                                        		Day* next_day = head->getday(date+1);
                                                        		if (next_day->getsport() && next_day->getsport()->compare_name(event_name)){
                                                                		Event* temp1 = next_day->getsport();
                                                                		next_day->setsport(next_day->getsport()->getnext());
                                                                		next_day->sethours(0, temp1->getend(), 0);
                                                                		free(temp1);
                                                                		next_day->decn();
                                                        		}
                                                		}
                                                		cout << "0" << endl;
                                                		return;
							}
						}
						else{
							x = x->getnext();
							temp = temp->getnext();
						}
					}
					cout << "-1\nEvent Not Added At Given Venue" << endl;	//If event was not found, print -1 and error
					return;
				}
			}
			head = head->getnext();
		}
		cout << "-1\nVenue Not Added" << endl;
		return;
	}
}

void showEvents(string venue_name, int date){							//Function to show all events on a given day
	Venue* head = Stadium;
        if (head==NULL){									//If no venue is added
                cout << "-1\nVenue Not Added" << endl;
                return;
        }
        else{
                while (head){									//Traverse the venues linked list
			if (head->compare_name(venue_name)){					//If venue name matches
				Day* venue_day = head->getday(date);				//Get the day pointer for given date
				cout << venue_day->getn() << endl;				//Print number of events in the day
				Event* x = venue_day->getsport();				//Get head pointer of events in the day
				while (x){							//Traverse the events linked list
					cout << x->getname() << " " << x->getstart() << " " << x->getend() << endl;
					x=x->getnext();
				}
				return;
			}
			head = head->getnext();
		}
		cout << "-1\nVenue Not Added" << endl;						//Print -1 and error message for no venue
                return;
	}
}

void showCalendar(string venue_name){								//Function to show calendar
	Venue* head = Stadium;
        if (head==NULL){									//If no venue is added
                cout << "-1\nVenue Not Added" << endl;
                return;
        }
        else{	
                while (head){									//Traverse the venues linked list
                        if (head->compare_name(venue_name)){					//If venue name matches
				cout << head->getn() << endl;					//Print the number of events in the venue
				for (int i=1;i<31;i++){						//for all 30 days
                                	Day* venue_day = head->getday(i);			
                                        cout << i << " " << venue_day->getn() << endl;		//Print the date and the number of events
                                        Event* x = venue_day->getsport();			//Get a pointer to events linked list
                                        while (x){						//Traverse the events linked list
                                               	cout << x->getname() << " " << x->getstart() << " " << x->getend() << endl;
                                               	x=x->getnext();
                                        }
				}
				return;
                        }
                        head = head->getnext();
                }
                cout << "-1\nVenue Not Added" << endl;						//Print -1 and error message for no venue
                return;
        }
}

int main(){
	string input, t;									//Input command string, and string t for junk
	char temp;										//temp character to get in between characters
	while (1){
		cout << "----------------------------------------------------------------------" << endl;
		//cout << "addVenue\ndeleteVenue\nshowVenues" << endl;
		//cout << "addEvent\ndeleteEvent\nshowEvents\nshowCalendar\nend\n\nType Your Choice: ";
		cin >> input;									//Get the input from std::in
		//printf("\n");
		if ("addVenue" == input){							//if input is addvenue
			string name, location;
			int capacity;
			temp = getchar();							//takes space
			temp = getchar();							//takes a double quote
			if (temp!='"'){
				cout << "-1\n You did not enter valid parameters" << endl;
				getline(cin, t);
				continue;
			}
			getline(cin, name, '"');						//get name until a double quote is seen
			temp = getchar();
			temp = getchar();
			if (temp!='"'){
				cout << "-1\nYou did not enter valid parameters" << endl;
				getline(cin, t);
				continue;
			}
			getline(cin, location, '"');						//get location until a double quote is seen
			temp = getchar();
			cin >> capacity;							//get capacity
			addVenue(name,location,capacity);
		}
		else if ("delVenue" == input){							//if input is delvenue
			string name;
			temp = getchar();
			temp = getchar();
			getline(cin, name, '"');
			deleteVenue(name);
		}
		else if ("showVenues" == input)							//if input is showVenues
			showVenues();
		else if ("addEvent" == input){							//if input is addEvent
			string venuename, eventname;
			int date, from, to;
			temp = getchar();
			temp = getchar();
			getline(cin, venuename, '"');
			temp = getchar();
			cin >> date >> from >> to;
			temp = getchar();
			temp = getchar();
			getline(cin, eventname, '"');
			if (date<=0 || date>=31){						//Check if date is within range
				cout << "-1\nInvalid Date" << endl;
				continue;	
			}
			if (from<0 || from>23 || to<0 || to>24 || from == to){			//Check if hours are within range
				cout << "-1\nInvalid Hours" << endl;
				continue;
			}
			int a = addEvent(venuename,date,from,to,eventname);
			if (a==0)
				cout << "0" << endl;
		}
		else if ("delEvent" == input){							//if input is delEvent
			string venuename, eventname;
			int date, from;
			temp = getchar();
			temp = getchar();
			getline(cin, venuename, '"');
			cin >> date >> from;
			temp = getchar();
			temp = getchar();
			getline(cin, eventname, '"');
			if (date<=0 || date>=31){						//Check if date is within range
				cout << "-1\nInvalid Date" << endl;
				continue;	
			}
			if (from<0 || from>23){
				cout << "-1\nInvalid Hour" << endl;				//Check if hours are within range
				continue;
			}
			deleteEvent(venuename, date, from, eventname);
		}
		else if ("showEvents" == input){						//if input is showEvents
			string venuename;
			int date;
			temp = getchar();
			temp = getchar();
			getline(cin, venuename, '"');
			cin >> date;
			if (date<=0 || date>=31){						//Check if date is within range
				cout << "-1\nInvalid Date" << endl;			
				continue;	
			}
			showEvents(venuename, date);
		}
		else if ("showCalendar" == input){						//if input is showCalendar
			string venuename;
			temp = getchar();
			temp = getchar();
			getline(cin, venuename, '"');
			showCalendar(venuename);
		}
		else if ("End" == input)							//if input is End
			break;
		else
			cout << "-1\nInvalid Choice" << endl;					//if input is something else
		//cout << endl;
	}
	return 0;
}

