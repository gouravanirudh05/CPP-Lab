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
    struct Event *next;   // Pointer to the next event.
};
/** The Location struct is used to store all the information related to the Location where the events are conducted
 *  It includes information like the name of the stadium, the name of the location and the capacity of the stadium,
 * Each location had a list of events represented using a linked list of events
 */
struct Location
{
    char stadium[100];  // The name of the arena or stadium
    char location[100]; // The name of the location where the arena or stadium is located
    int capacity;       // Capactiy of the arena or stadium
    struct Event *list; // Pointer to the head of the event linked list.
};
struct Location *locations[100]; // This is an array of locations
int count = 0;                   // This is used to keep track of the number of venues added
int findpos(char *stadium)
{
    // This function returns the position of the venue from the array  with the matching name
    for (int i = 0; i < count; i++)
    {
        if (strcmp(locations[i]->stadium, stadium) == 0)
        {
            return i; // Position of the venue in the list of locations
        }
    }
    return -1; // Returning -1 if the venue is not found
}
void addVenue(char *stadium, char *location, int capacity)
{
    // This function is used to add a venue to the list of locations
    if (count >= 100) // Assumption is that we can at max have 100 venues so memory is getting allocated accordingly
    {
        printf("-1\n");
        printf("Error\n"); // Error as no more memory is available
        return;
    }
    if (findpos(stadium) != -1) // Error if venue with same name already exists in the list
    {
        printf("-1\n");
        printf("Error\n");
        return;
    }

    struct Location *nvenue = (struct Location *)malloc(sizeof(struct Location)); // Allocating memory for a newvenue
    // Copying all the detais into their respective elements in the struct
    strcpy(nvenue->stadium, stadium);
    strcpy(nvenue->location, location);
    nvenue->capacity = capacity;
    nvenue->list = NULL;
    locations[count++] = nvenue;
    printf("0\n"); // Success message
}

void delVenue(char *stadium)
{
    // This function deletes the venue with the the matching name from the list if it exists in the list
    int pos = findpos(stadium); 
    if (pos == -1)// Stadium is not found in the list
    {
        printf("-1\n");
        printf("Error\n"); 
        return;
    }

    // Freeing all events in the linked list corresponding to that stadium name
    struct Event *curr = locations[pos]->list;
    while (curr != NULL)
    {
        // Iterating through the Linked list
        struct Event *t = curr;
        curr = curr->next;
        free(t); // Free each event node
    }

    free(locations[pos]); // Free the venue in the list that is present as a node
    // As one venue is deleted in the list of location we need to shift the reset to get rid of the vacancy created
    for (int i = pos; i < count - 1; i++)
    {
        locations[i] = locations[i + 1]; // Shift remaining venues after deleting
    }

    count--;       // Count is decreased on deleting a venue
    printf("0\n"); // Success message
}

void showVenues()
{
    // This function prints the details of all the venues from the list of venues
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
    if (pos == -1) // If there is no stadium with the stadiumname mentioned
    {
        printf("-1\n");
        printf("Error\n"); 
        return;
    }
    //Error checking as the day is 0-24 and date is 1-30
    if (begin < 0 || end > 24 || begin >= end || date < 1 || date > 30)
    {
        printf("-1\n");
        printf("Error\n"); // Error if the date or time is invalid
        return;
    }

    struct Location *venue = locations[pos];
    struct Event *nevent = (struct Event *)malloc(sizeof(struct Event));//Creating a node at a venue
    if (!nevent)
    {
        printf("-1\n");
        printf("Error\n"); // Error if memory allocation fails
        return;
    }
    // Storing all the data in the linked list of the event
    nevent->date = date;
    nevent->begin = begin;
    nevent->end = end;
    strcpy(nevent->event_name, event_name);
    nevent->next = NULL;
    // Checking if there are any overlapping events
    struct Event *curr = venue->list;
    while (curr != NULL)
    {
        if (curr->date == date &&
            ((begin < curr->end && end > curr->begin)))
        {
            // Error if overlapping events found
            printf("-1\n");
            printf("Error\n");
            free(nevent); // Freeing the allocated memory for the nodes
            return;
        }
        curr = curr->next;
    }
    // Inserting the events in the sorted order of date and time
    if (venue->list == NULL || (venue->list->date > date) || (venue->list->date == date && venue->list->begin > begin))
    {

        nevent->next = venue->list;
        venue->list = nevent;
    }
    else
    {
        struct Event *curr = venue->list;
        while (curr->next != NULL && (curr->next->date < date || (curr->next->date == date && curr->next->begin <= begin)))
        {
            curr = curr->next;
        }
        nevent->next = curr->next;
        curr->next = nevent;
    }
    printf("0\n"); // Success mesage
}

void delEvent(char *stadium, int date, int begin, char *event_name)
{
    // This function deletes an event from the particular stadium
    int pos = findpos(stadium);
    if (pos == -1)
    {
        printf("-1\n");
        printf("Error\n"); // Error if the venue is not found
        return;
    }
    struct Location *venue = locations[pos];
    struct Event *curr = venue->list;
    struct Event *prev = NULL;

    // Searching  for the event to delete
    while (curr != NULL)
    {   //Comparing all the details of the event to delet it
        if (curr->date == date && curr->begin == begin && strcmp(curr->event_name, event_name) == 0)
        {
            if (prev == NULL)
            {
                venue->list = curr->next; // Remove the first event
            }
            else
            {
                prev->next = curr->next; // Remove the event from the middle or end
            }
            free(curr);
            printf("0\n"); // Success message
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("-1\n");
    printf("Error \n"); // Error if the event is not found
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
    struct Event *curr = venue->list;
    int events = 0;

    // Count events for the specified date
    while (curr != NULL)
    {
        if (curr->date == date)
        {
            events++;
        }
        curr = curr->next;
    }

    printf("%d\n", events); // Print the count of events
    curr = venue->list;

    // Printing detils of events for the specified date
    while (curr != NULL)
    {
        if (curr->date == date)
        {
            printf("%s %d %d\n", curr->event_name, curr->begin, curr->end);
        }
        curr = curr->next;
    }
}

void showCalendar(char *stadium)
{
    // This function prints the calendar for the specified stadium
    int pos = findpos(stadium);
    if (pos == -1)
    {
        printf("-1\n");
        printf("Error\n"); // Error if the venue is not found
        return;
    }

    struct Location *venue = locations[pos];
    int eventcount = 0;
    int events[30] = {0}; // Array to count events for each day

    // Counting events for each day
    struct Event *curr = venue->list;
    while (curr != NULL)
    {
        events[curr->date - 1]++;
        eventcount++;
        curr = curr->next;
    }

    // Printing  the total number of events
    printf("%d\n", eventcount);

    // Printing the number of events per day
    for (int i = 0; i < 30; i++)
    {
        printf("%d %d\n", i + 1, events[i]);
        curr = venue->list;

        // Printing detais of events for the current day
        while (curr != NULL)
        {
            // Iterating through the linked list of events
            if (curr->date == i + 1)
            {
                printf("%s %d %d\n", curr->event_name, curr->begin, curr->end);
            }
            curr = curr->next;
        }
    }
}

int main()
{  
    //This function takes in the input and extracts the commands and all the details and calls the functions respectively
    char command[100]; // This is the command string
    char x[100][50];   // Array to store details of each command
    while (fgets(command, sizeof(command), stdin))
    {

        int i = 0, j = 0, flag = 0, length = 0; // Flag is used to determine if a double quote was encountered
        while (command[i] != '\0' && command[i] != '\n')
        {
            if (command[i] == '"')
            {
                flag = !flag; // Negating the flag when a doublequote is encountered
            }
            else if (isspace(command[i]) && !flag)
            {
                if (j > 0)
                {
                    x[length][j] = '\0'; // To end a word
                 length++;
                    j = 0; // Reset pos for the next word
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
                    int capacity = atoi(x[i + 3]); // converting the capacity string to integer
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
                // Deleting an event at a location specified
                if (length == 5)
                {
                    char *venue = x[i + 1];
                    int date = atoi(x[i + 2]);
                    int begin= atoi(x[i + 3]);
                    char *event = x[i + 4];
                    delEvent(venue, date, begin, event);
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