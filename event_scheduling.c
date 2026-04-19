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

int main(){
	
}
