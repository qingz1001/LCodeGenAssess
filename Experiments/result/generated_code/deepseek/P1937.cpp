#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000
#define MAXM 100000

typedef struct {
    int start, end;
} Request;

int compareRequests(const void *a, const void *b) {
    Request *reqA = (Request *)a;
    Request *reqB = (Request *)b;
    if (reqA->end == reqB->end) {
        return reqA->start - reqB->start;
    }
    return reqA->end - reqB->end;
}

int main() {
    int N, M;
    int capacities[MAXN];
    Request requests[MAXM];

    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &capacities[i]);
    }
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &requests[i].start, &requests[i].end);
    }

    qsort(requests, M, sizeof(Request), compareRequests);

    int satisfied_requests = 0;
    int stalls[MAXN] = {0};

    for (int i = 0; i < M; i++) {
        int start = requests[i].start - 1;
        int end = requests[i].end - 1;
        int can_allocate = 1;

        for (int j = start; j <= end; j++) {
            if (stalls[j] >= capacities[j]) {
                can_allocate = 0;
                break;
            }
        }

        if (can_allocate) {
            for (int j = start; j <= end; j++) {
                stalls[j]++;
            }
            satisfied_requests++;
        }
    }

    printf("%d\n", satisfied_requests);

    return 0;
}