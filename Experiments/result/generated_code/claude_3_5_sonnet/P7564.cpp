#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 2800
#define MAX_Q 3000000

typedef long long ll;

struct Customer {
    int t, a, b, c;
};

struct Event {
    int type; // 0: start, 1: end
    int time;
    int pos;
    int idx;
};

struct Customer customers[MAX_N];
struct Event events[MAX_N * 2];
int n, q;

int cmp(const void *a, const void *b) {
    struct Event *ea = (struct Event *)a;
    struct Event *eb = (struct Event *)b;
    if (ea->time != eb->time) return ea->time - eb->time;
    if (ea->type != eb->type) return ea->type - eb->type;
    return ea->pos - eb->pos;
}

ll solve(int start_time, int start_pos) {
    int event_count = 0;
    for (int i = 0; i < n; i++) {
        if (customers[i].t >= start_time) {
            events[event_count++] = (struct Event){0, customers[i].t, customers[i].a, i};
            events[event_count++] = (struct Event){1, customers[i].t + abs(customers[i].b - customers[i].a), customers[i].b, i};
        }
    }
    
    qsort(events, event_count, sizeof(struct Event), cmp);
    
    ll max_profit = 0;
    ll current_profit = 0;
    int current_pos = start_pos;
    int current_time = start_time;
    
    for (int i = 0; i < event_count; i++) {
        struct Event e = events[i];
        int time_diff = e.time - current_time;
        int pos_diff = abs(e.pos - current_pos);
        
        if (time_diff >= pos_diff) {
            if (e.type == 0) {
                current_profit += (ll)customers[e.idx].c * abs(customers[e.idx].b - customers[e.idx].a);
            }
            if (current_profit > max_profit) {
                max_profit = current_profit;
            }
            current_pos = e.pos;
            current_time = e.time;
        }
        
        if (e.type == 1) {
            current_profit -= (ll)customers[e.idx].c * abs(customers[e.idx].b - customers[e.idx].a);
        }
    }
    
    return max_profit;
}

int main() {
    scanf("%d %d", &n, &q);
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &customers[i].t, &customers[i].a, &customers[i].b, &customers[i].c);
    }
    
    for (int i = 0; i < q; i++) {
        int p, x;
        scanf("%d %d", &p, &x);
        printf("%lld\n", solve(p, x));
    }
    
    return 0;
}