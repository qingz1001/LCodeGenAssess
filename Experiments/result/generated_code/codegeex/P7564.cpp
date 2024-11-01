#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 2800
#define MAX_Q 3000000
#define MAX_T 1000000000

struct Customer {
    int T, A, B, C;
};

struct Query {
    int P, X;
};

struct Event {
    int type; // 1 for start, -1 for end
    int time;
    int pos;
    int index;
};

int compareEvents(const void *a, const void *b) {
    struct Event *eventA = (struct Event *)a;
    struct Event *eventB = (struct Event *)b;
    if (eventA->time != eventB->time) {
        return eventA->time - eventB->time;
    } else if (eventA->type != eventB->type) {
        return eventA->type - eventB->type;
    } else if (eventA->pos != eventB->pos) {
        return eventA->pos - eventB->pos;
    } else {
        return eventA->index - eventB->index;
    }
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
        events[eventCount++] = (struct Event){1, customers[i].T, customers[i].A, i};
        events[eventCount++] = (struct Event){-1, customers[i].T, customers[i].B, i};
    }

    for (int i = 0; i < Q; i++) {
        events[eventCount++] = (struct Event){0, queries[i].P, queries[i].X, i + N};
    }

    qsort(events, eventCount, sizeof(struct Event), compareEvents);

    // TODO: Implement the algorithm to solve the problem

    return 0;
}