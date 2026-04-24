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
            printf("(%d, %d)\n", events[i].start, events[i].end);
            last_end = events[i].end;
            count++;
        }
    }

    printf("\n");
    return count;
}

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
