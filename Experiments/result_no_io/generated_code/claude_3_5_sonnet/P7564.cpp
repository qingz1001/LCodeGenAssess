#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 2800
#define MAXQ 3000000

typedef long long ll;

typedef struct {
    int t, a, b, c;
} Customer;

typedef struct {
    int p, x;
} Plan;

Customer customers[MAXN];
Plan plans[MAXQ];
int N, Q;

typedef struct {
    int t, x, type, id;
} Event;

Event events[MAXN * 2];
int event_cnt;

int cmp(const void *a, const void *b) {
    Event *ea = (Event *)a;
    Event *eb = (Event *)b;
    if (ea->t != eb->t) return ea->t - eb->t;
    return ea->type - eb->type;
}

ll max(ll a, ll b) {
    return a > b ? a : b;
}

ll solve(int start_time, int start_pos) {
    event_cnt = 0;
    for (int i = 0; i < N; i++) {
        if (customers[i].t >= start_time) {
            events[event_cnt++] = (Event){customers[i].t, customers[i].a, 0, i};
            events[event_cnt++] = (Event){customers[i].t + abs(customers[i].b - customers[i].a), customers[i].b, 1, i};
        }
    }
    qsort(events, event_cnt, sizeof(Event), cmp);

    ll result = 0;
    int curr_pos = start_pos;
    int curr_time = start_time;

    for (int i = 0; i < event_cnt; i++) {
        Event e = events[i];
        if (e.t > curr_time) {
            int dist = abs(e.x - curr_pos);
            int time_diff = e.t - curr_time;
            if (dist <= time_diff) {
                curr_pos = e.x;
                curr_time = e.t;
            } else {
                break;
            }
        }

        if (e.type == 0 && e.x == curr_pos) {
            Customer c = customers[e.id];
            int end_time = c.t + abs(c.b - c.a);
            result = max(result, result + (ll)abs(c.b - c.a) * c.c);
            curr_pos = c.b;
            curr_time = end_time;
        }
    }

    return result;
}

int main() {
    scanf("%d %d", &N, &Q);
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d %d", &customers[i].t, &customers[i].a, &customers[i].b, &customers[i].c);
    }
    for (int i = 0; i < Q; i++) {
        scanf("%d %d", &plans[i].p, &plans[i].x);
    }

    for (int i = 0; i < Q; i++) {
        printf("%lld\n", solve(plans[i].p, plans[i].x));
    }

    return 0;
}