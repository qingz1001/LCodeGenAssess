#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 80001

typedef struct {
    int pos;
    int height;
    int type;
} Event;

Event events[MAXN];
int eventCount = 0;

int compare(const void* a, const void* b) {
    Event* ea = (Event*)a;
    Event* eb = (Event*)b;
    if (ea->pos != eb->pos) return ea->pos - eb->pos;
    return eb->type - ea->type;
}

int max(int a, int b) {
    return a > b ? a : b;
}

long long solve() {
    qsort(events, eventCount, sizeof(Event), compare);
    
    long long result = 0;
    int prevPos = 0;
    int maxHeight = 0;
    
    for (int i = 0; i < eventCount; i++) {
        result += (long long)(events[i].pos - prevPos) * maxHeight;
        
        if (events[i].type == 1) {
            maxHeight = max(maxHeight, events[i].height);
        } else {
            int newMaxHeight = 0;
            for (int j = i; j < eventCount && events[j].pos == events[i].pos; j++) {
                if (events[j].type == 1) {
                    newMaxHeight = max(newMaxHeight, events[j].height);
                }
            }
            maxHeight = newMaxHeight;
        }
        
        prevPos = events[i].pos;
    }
    
    return result;
}

int main() {
    int n;
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        int a, b, h;
        scanf("%d %d %d", &a, &b, &h);
        
        events[eventCount++] = (Event){a, h, 1};
        events[eventCount++] = (Event){b, h, -1};
    }
    
    printf("%lld\n", solve());
    
    return 0;
}