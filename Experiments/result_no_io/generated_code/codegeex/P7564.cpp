#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_N 2800
#define MAX_Q 3000000
#define MAX_T 1000000000
#define MAX_X 1000000000
#define MAX_L 1000000000

typedef long long ll;

struct Customer {
    int T;
    int A;
    int B;
    int C;
};

struct Query {
    int P;
    int X;
};

struct Event {
    int t;
    int x;
    int c;
    int type;
};

int compareEvents(const void *a, const void *b) {
    struct Event *eventA = (struct Event *)a;
    struct Event *eventB = (struct Event *)b;
    if (eventA->t != eventB->t) {
        return eventA->t - eventB->t;
    }
    if (eventA->type != eventB->type) {
        return eventA->type - eventB->type;
    }
    return eventB->x - eventA->x;
}

int main() {
    int N, Q;
    scanf("%d %d", &N, &Q);

    struct Customer customers[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d %d", &customers[i].T, &customers[i].A, &customers[i].B, &customers[i].C);
    }

    struct Query queries[MAX_Q];
    for (int i = 0; i < Q; i++) {
        scanf("%d %d", &queries[i].P, &queries[i].X);
    }

    struct Event events[2 * N + 2 * Q];
    int eventCount = 0;

    for (int i = 0; i < N; i++) {
        events[eventCount++] = (struct Event){customers[i].T, customers[i].A, customers[i].C / 2, 1};
        events[eventCount++] = (struct Event){customers[i].T, customers[i].B, customers[i].C / 2, -1};
    }

    for (int i = 0; i < Q; i++) {
        events[eventCount++] = (struct Event){queries[i].P, queries[i].X, 0, 0};
    }

    qsort(events, eventCount, sizeof(struct Event), compareEvents);

    ll dp[MAX_X + 1];
    memset(dp, 0, sizeof(dp));

    ll maxProfit = 0;
    for (int i = 0; i < eventCount; i++) {
        if (events[i].type == 0) {
            maxProfit = dp[events[i].x] + events[i].c;
        } else {
            dp[events[i].x] += events[i].type * events[i].c;
        }
    }

    for (int i = 0; i < Q; i++) {
        printf("%lld\n", maxProfit);
    }

    return 0;
}