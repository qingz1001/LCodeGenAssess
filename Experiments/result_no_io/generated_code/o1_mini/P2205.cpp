#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

typedef struct {
    ll pos;
    int delta;
} Event;

int compare_events(const void *a, const void *b) {
    Event *ea = (Event *)a;
    Event *eb = (Event *)b;
    if (ea->pos < eb->pos) return -1;
    if (ea->pos > eb->pos) return 1;
    return ea->delta - eb->delta;
}

int main(){
    int N, K;
    scanf("%d %d", &N, &K);
    Event *events = malloc(sizeof(Event) * 2 * N);
    int e = 0;
    ll current = 0;
    for(int i=0;i<N;i++){
        ll dist;
        char dir;
        scanf("%lld %c", &dist, &dir);
        ll next;
        if(dir == 'L') next = current - dist;
        else next = current + dist;
        if(current < next){
            events[e].pos = current;
            events[e++].delta = 1;
            events[e].pos = next;
            events[e++].delta = -1;
        }
        else{
            events[e].pos = next;
            events[e++].delta = 1;
            events[e].pos = current;
            events[e++].delta = -1;
        }
        current = next;
    }
    qsort(events, e, sizeof(Event), compare_events);
    ll total = 0;
    ll prev = events[0].pos;
    int coats = 0;
    for(int i=0;i<e;i++){
        ll pos = events[i].pos;
        if(pos > prev && coats >= K){
            total += pos - prev;
        }
        coats += events[i].delta;
        prev = pos;
    }
    printf("%lld\n", total);
    free(events);
    return 0;
}