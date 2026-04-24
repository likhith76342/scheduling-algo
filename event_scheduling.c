#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
	int start;
	int end;
}Event;

//Compare function (sorts using end time) 
int compare(const void *a, const void *b) {
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;

    if (e1->end == e2->end) {
        return e1->start - e2->start;
    }
    return e1->end - e2->end;
}


int toMinutes(int hour, int minute) {
    return hour * 60 + minute;
}

void printTime(int totalMinutes) {
    int hour = totalMinutes / 60;
    int minute = totalMinutes % 60;
    printf("%02d:%02d", hour, minute);
}

void inputEvents(Event events[], int n) {
    int sh, sm, eh, em;

    for (int i = 0; i < n; i++) {
        printf("Enter event %d start time (HH:MM): ", i + 1);
        scanf("%d:%d", &sh, &sm);

        printf("Enter event %d end time (HH:MM): ", i + 1);
        scanf("%d:%d", &eh, &em);

        if (sh < 0 || sh > 23 || sm < 0 || sm > 59 ||
            eh < 0 || eh > 23 || em < 0 || em > 59) {
            printf("Invalid time entered.\n");
            exit(1);
        }

        events[i].start = toMinutes(sh, sm);
        events[i].end = toMinutes(eh, em);

        if (events[i].end < events[i].start) {
            printf("End time must be greater than or equal to start time.\n");
            exit(1);
        }
    }
}

void displayEvents(Event events[], int n, const char *message) {
    printf("\n%s\n", message);
    for (int i = 0; i < n; i++) {
        printf("Event %2d -> Start: ", i + 1);
        printTime(events[i].start);
        printf(", End: ");
        printTime(events[i].end);
        printf("\n");
    }
    printf("\n");
}

// Greedy activity selection
int eventSelection(Event events[], int n) {
    int count = 0;
    int last_end = -1;

    printf("Selected non-overlapping events:\n");

    for (int i = 0; i < n; i++) {
        if (events[i].start >= last_end) {
            printTime(events[i].start);
            printf(" - ");
            printTime(events[i].end);
            printf("\n");

            last_end = events[i].end;
            count++;
        }
    }

    printf("\n");
    return count;
}

int main() {
    int n;

    printf("Enter number of events: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number of events.\n");
        return 1;
    }

    Event *events = (Event *)malloc(n * sizeof(Event));
    if (events == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    inputEvents(events, n);

    displayEvents(events, n, "Events before sorting:");

    qsort(events, n, sizeof(Event), compare);

    displayEvents(events, n, "Events after sorting by end time:");

    int maxEvents = eventSelection(events, n);

    printf("Maximum number of non-overlapping events that can be scheduled: %d\n", maxEvents);

    free(events);
    return 0;
}
What changed
Removed generateRandomEvents() and srand()/time() because events are now entered manually instead of generated randomly.

Stored time as total minutes internally, which makes comparison and overlap checking simple and correct for 24-hour times like 13:15 and 18:40.

Added printTime() so output is shown back in HH:MM 24-hour format using zero-padded printing like %02d:%02d.

Example input
text
Enter number of events: 4
Enter event 1 start time (HH:MM): 09:00
Enter event 1 end time (HH:MM): 10:30
Enter event 2 start time (HH:MM): 10:00
Enter event 2 end time (HH:MM): 11:00
Enter event 3 start time (HH:MM): 11:00
Enter event 3 end time (HH:MM): 12:00
Enter event 4 start time (HH:MM): 09:30
Enter event 4 end time (HH:MM): 10:00
Important note
Your original comparator logic for qsort() was already basically correct, and using const void * with casting inside the compare function is the normal C pattern for qsort().

If you want, I can also give you:

a simpler version without functions,

a version using strings like "09:30",

or a version that supports events crossing midnight.

Follow-ups


Complete Activity Selection algorithm using this sorting


How to implement the greedy selection after sorting


Test cases for Activity Selection with sample inputs


Common mistakes in qsort compare functions for structs


Time complexity of qsort for activity selection



int main(){
	int n;

    printf("Enter number of events: ");
    scanf("%d", &n);

    Event *events = (Event *)malloc(n * sizeof(Event));
    if (events == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    srand(time(NULL));

    generateRandomEvents(events, n, 100, 20);

    displayEvents(events, n, "Randomly generated events before sorting:");

    qsort(events, n, sizeof(Event), compare);

    displayEvents(events, n, "Events after sorting by end time:");

    int maxEvents = eventSelection(events, n);

    printf("Maximum number of non-overlapping events that can be scheduled: %d\n", maxEvents);

    free(events);
    return 0;
}
