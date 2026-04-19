#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
	int start;
	int end;
}Event;

/*Compare function (sorts using end time) */
int compare(const void *a, const void *b) {
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;

    if (e1->end == e2->end) {
        return e1->start - e2->start;
    }
    return e1->end - e2->end;
}

/* Generate random events - just to show how the algorithm works in different inputs*/
void generateRandomEvents(Event events[], int n, int maxStartTime, int maxDuration) {
    for (int i = 0; i < n; i++) {
        int start = rand() % maxStartTime;
        int duration = (rand() % maxDuration) + 1;

        events[i].start = start;
        events[i].end = start + duration;
    }
}


/* Display events */
void displayEvents(Event events[], int n, const char *message) {
    printf("%s\n", message);
    for (int i = 0; i < n; i++) {
        printf("Event %2d -> Start: %3d, End: %3d\n", i + 1, events[i].start, events[i].end);
    }
    printf("\n");
}

/* Greedy activity selection */
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
	
}
