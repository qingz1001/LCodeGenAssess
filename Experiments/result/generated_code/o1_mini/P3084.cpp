#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pos;
    int type; // +1 for start, -1 for end
} Event;

// Comparator for qsort
int cmp(const void *a, const void *b){
    Event *ea = (Event *)a;
    Event *eb = (Event *)b;
    if(ea->pos != eb->pos)
        return ea->pos - eb->pos;
    // If same position, start events come before end events
    return eb->type - ea->type;
}

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    Event *events = (Event *)malloc(sizeof(Event)*2*M);
    for(int i=0;i<M;i++){
        int a, b;
        scanf("%d %d", &a, &b);
        events[2*i].pos = a;
        events[2*i].type = 1; // start
        events[2*i+1].pos = b+1;
        events[2*i+1].type = -1; // end
    }
    qsort(events, 2*M, sizeof(Event), cmp);
    int current = 0, max_overlap = 0;
    for(int i=0;i<2*M;i++){
        current += events[i].type;
        if(current > max_overlap)
            max_overlap = current;
    }
    free(events);
    long long answer = (long long)M - (long long)(max_overlap -1);
    if(answer > N){
        printf("-1\n");
    }
    else{
        printf("%lld\n", answer);
    }
    return 0;
}