#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h> //This is inluded to use the function issspace

/** The Event struct is used to store all the information related to the Event with details of eventname
 * date,the time the event begins and the time the event ends
 */
struct Event
{
    char event_name[100]; // The name of the event
    int date;             // The date of the event
    int begin;            // The time the event begins
    int end;              // the time the event ends
    struct Event *next;   // Pointer to the next event
};
/** The Location struct is used to store all the information related to the Location where the events are conducted
 *  It includes information like the name of the stadium, the name of the location and the capacity of the stadium,
 * Each location had a list of events represented using a linked list of events
 */
struct Location
{
    char stadium[100];       // The name of the arena or stadium
    char location[100];      // The name of the location where the arena or stadium is located
    int capacity;            // Capactiy of the arena or stadium
    struct Event *eventlist; // Pointer to the head of the event linked list.
};

struct Location *locations[100]; // This is an array of locations
int count = 0;                   // This is used to keep track of the number of venues added
int findpos(char *stadium)
{
    // This function returns the position of the venue from the array by matching stadiumname
    for (int i = 0; i < count; i++)
    {
        if (strcmp(locations[i]->stadium, stadium) == 0)
        {
            return i; // Position of the venue is returned
        }
    }
    return -1; // Returning -1 if the venue is not found
}
void addVenue(char *stadium, char *location, int capacity)
{
    // This function is used to add a venue to the list of locations
    if (count >= 100)
    {
        printf("-1\n");
        printf("Error\n"); // Assumption is that we have only 100 venues at max so error if it has more venues
        return;
    }
    if (findpos(stadium) != -1)
    {
        printf("-1\n");
        printf("Error\n"); // Error if a venue with the same name already exists
        return;
    }

    struct Location *nvenue = (struct Location *)malloc(sizeof(struct Location)); // Allocating memory for the new venue that is getting addeed
    strcpy(nvenue->stadium, stadium);                                             // Copying the stadium name
    strcpy(nvenue->location, location);                                           // Copying the location
    nvenue->capacity = capacity;                                                  // Copying the capacity of the stadium
    nvenue->eventlist = NULL;                                                     // Initialize the event list as empty
    locations[count++] = nvenue;                                                  // Adding  the new venue to the array and increment the count
    printf("0\n");                                                                // Success message
}

void delVenue(char *stadium)
{
    // This function deletes the venue with the the matching stadium name from the list if it exists in the list
    int pos = findpos(stadium);
    if (pos == -1) // Stadium is not found in the list
    {
        printf("-1\n");
        printf("Error\n"); // Error if the stadium to be deleted is not in the list
        return;
    }

    // Freeing all events in the linked list corresponding to that stadium name
    struct Event *current = locations[pos]->eventlist;
    while (current != NULL)
    { // Iterating through the Linked list
        struct Event *t = current;
        current = current->next;
        free(t); // Free each event node
    }
    free(locations[pos]); // Free the venue in the eventlist that is present as a node

    // As one venue is deleted in the list of location we need to shift the reset to get rid of the vacancy created
    for (int i = pos; i < count - 1; i++)
    {
        locations[i] = locations[i + 1]; // Shift remaining venues after deleting
    }

    count--;       // Count is decreased on deleting a venue
    printf("0\n"); // Success
}

void showVenues()
{
    // This function prints the added stadiums from the list of venues
    printf("%d\n", count); // Total number of venues present in the list
    for (int i = 0; i < count; i++)
    {
        printf("%s %s %d\n", locations[i]->stadium, locations[i]->location, locations[i]->capacity);
    }
}

void addEvent(char *stadium, int date, int begin, int end, char *event_name)
{
    // This function adds a new event to a corresponding stadium
    int pos = findpos(stadium);
    if (pos == -1) // If there is no stadium with the stadium mentioned
    {
        printf("-1\n");
        printf("Error\n"); // Error if the venue is not found
        return;
    }

    if (begin < 0 || end > 24 || begin >= end || date < 1 || date > 30)
    {
        printf("-1\nError\n"); // Error if the date or time is invalid
        return;
    }

    struct Location *venue = locations[pos];
    struct Event *newevent = (struct Event *)malloc(sizeof(struct Event));
    // Storing all the data in the linked list of the event
    newevent->date = date;
    newevent->begin = begin;
    newevent->end = end;
    strcpy(newevent->event_name, event_name);
    newevent->next = NULL;
    // Checking if there are any overlapping events
    struct Event *current = venue->eventlist;
    while (current != NULL)
    {
        if (current->date == date && ((begin < current->end && end > current->begin)))
        {
            // Error if overlapping events found
            printf("-1\n");
            printf("Error\n");
            free(newevent); // Free the allocated memory before returning
            return;
        }
        current = current->next;
    }

    // Inserting  the new event into the linked list in sorted order by date and begin
    if (venue->eventlist == NULL || (venue->eventlist->date > date) || (venue->eventlist->date == date && venue->eventlist->begin > begin))
    {
        // Insert at the beginning of the list if it is empty or the new event should be first
        newevent->next = venue->eventlist;
        venue->eventlist = newevent;
    }
    else
    {
        while (current->next != NULL && (current->next->date < date || (current->next->date == date && current->next->begin <= begin)))
        {
            current = current->next;
        }
        // Inserting the new event after the current node
        newevent->next = current->next;
        current->next = newevent;
    }
    printf("0\n"); // Success message
}

void delEvent(char *stadium, int date, int begin, char *event_name)
{
    // This function deletes the event with event_name = event_name held at venue_name, on date = date, starting at begin.

    int pos = findpos(stadium);
    if (pos == -1) // If there is no matching venue found
    {
        printf("-1\n");
        printf("Error\n"); // Error if the venue is not found
        return;
    }
    struct Location *venue = locations[pos];
    struct Event *current = venue->eventlist;
    struct Event *prev = NULL;

    // Searching for the event to be deleted
    while (current != NULL)
    {
        if (current->date == date && current->begin == begin && strcmp(current->event_name, event_name) == 0)
        {
            if (prev == NULL)
            {
                venue->eventlist = current->next; // Removing the first event
            }
            else
            {
                prev->next = current->next; // Removing the event from the middle or end
            }
            free(current);
            printf("0\n"); // Success message
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("-1\n");
    printf("Error\n"); // Error if the event is not found
}

void showEvents(char *stadium, int date)
{
    // This function prints all events for a specified date at a given venue.
    int pos = findpos(stadium);
    if (pos == -1)
    {
        printf("-1\n");
        printf("Error\n"); // Error if the venue is not found
        return;
    }

    struct Location *venue = locations[pos];
    struct Event *current = venue->eventlist;
    int events = 0;

    // Counting the  events for the specified date
    while (current != NULL)
    {
        if (current->date == date)
        {
            events++;
        }
        current = current->next;
    }
    printf("%d\n", events); // Printing the count of events
    current = venue->eventlist;
    // Printing  details of events for a particular date
    while (current != NULL)
    {
        if (current->date == date)
        {
            printf("%s %d %d\n", current->event_name, current->begin, current->end);
        }
        current = current->next;
    }
}
void showCalendar(char *stadium)
{
    // This function prints a calendar of events for a venue with name = venue_name, showing the number of events for each day of the month (here a month is considered to be of 30 days). It also prints the x of each event for the corresponding day.

    int pos = findpos(stadium);
    if (pos == -1) // If the stadium mentioned is not present in the venue list
    {
        printf("-1\n");
        printf("Error\n"); // Error if the venue is not found
        return;
    }

    struct Location *venue = locations[pos];
    int eventcount = 0;
    int perday[30] = {0}; // Array to count events for each day
    // Count events for each day
    struct Event *current = venue->eventlist;
    while (current != NULL)
    {
        perday[current->date - 1]++;
        eventcount++;
        current = current->next;
    }
    // Printing the total number of events
    printf("%d\n", eventcount);
    for (int i = 0; i < 30; i++)
    {
        printf("%d %d\n", i + 1, perday[i]);
        current = venue->eventlist;
        while (current != NULL)
        {
            if (current->date == i + 1)
            {
                printf("%s %d %d\n", current->event_name, current->begin, current->end);
            }
            current = current->next;
        }
    }
}

int main()
{
    char command[100]; // This is the command string
    char x[100][50];   // Array to store details of each command
    while (fgets(command, sizeof(command), stdin))//Fetches each line of imput from the input file
    {

        int i = 0, j = 0, flag = 0, length = 0;
        while (command[i] != '\0' && command[i] != '\n')
        {
            if (command[i] == '"')
            {
                flag = !flag; // Negating the flag when a quote is encountered
            }
            else if (isspace(command[i]) && !flag)
            {
                if (j > 0)
                {
                    x[length][j] = '\0'; // Appending the character to show end of word
                    length++;
                    j = 0;
                }
            }
            else
            {
                x[length][j] = command[i];
                j++;
            }
            i++;
        }
        if (j > 0)
        {
            x[length][j] = '\0';
            length++;
        }
        for (int i = 0; i < length; i++)
        {
            if (strcmp(x[i], "addVenue") == 0)
            {
                // Adding a new venue
                if (length == 4)
                {
                    char *stadium = x[i + 1];
                    char *venue = x[i + 2];
                    int capacity = atoi(x[i + 3]);
                    addVenue(stadium, venue, capacity);
                }
                else
                {
                    printf("-1\n");
                    printf("Error\n");
                }
            }
            else if (strcmp(x[i], "delVenue") == 0)
            {
                // Deleting a venue
                if (length == 2)
                {
                    char *venue = x[i + 1];
                    delVenue(venue);
                }
                else
                {
                    printf("-1\n");
                    printf("Error\n");
                }
            }
            else if (strcmp(x[i], "showVenues") == 0)
            {
                // Showing all the venue information
                if (length == 1)
                {
                    showVenues();
                }
                else
                {
                    printf("-1\n");
                    printf("Error\n");
                }
            }

            else if (strcmp(x[i], "addEvent") == 0)
            {
                // Adding a new event
                if (length == 6)
                {
                    char *venue = x[i + 1];
                    int date = atoi(x[i + 2]);
                    int begin = atoi(x[i + 3]);
                    int end = atoi(x[i + 4]);
                    char *event = x[i + 5];
                    addEvent(venue, date, begin, end, event);
                }
                else
                {
                    printf("-1\n");
                    printf("Error\n");
                }
            }
            else if (strcmp(x[i], "delEvent") == 0)
            {
                // Delete an event at a location specified
                if (length == 5)
                {
                    char *venue = x[i + 1];
                    int begin = atoi(x[i + 2]);
                    int end = atoi(x[i + 3]);
                    char *event = x[i + 4];
                    delEvent(venue, begin, end, event);
                }
                else
                {
                    printf("-1\n");
                    printf("Error\n");
                }
            }
            else if (strcmp(x[i], "showEvents") == 0)
            {
                // Show events for a specific venue and date
                if (length == 3)
                {
                    char *venue = x[i + 1];
                    int date = atoi(x[i + 2]);
                    showEvents(venue, date);
                }
                else
                {
                    printf("-1\n");
                    printf("Error\n");
                }
            }
            else if (strcmp(x[i], "showCalendar") == 0)
            {
                // Extracting the command to show the calendar information
                if (length == 2)
                {
                    char *venue = x[i + 1];
                    showCalendar(venue);
                }
                else
                {
                    printf("-1\n");
                    printf("Error\n");
                }
            }
            else if (strcmp(x[i], "End") == 0)
            {
                // Ending the program when End is encountered
                break;
                return 0;
            }
        }
    }
}