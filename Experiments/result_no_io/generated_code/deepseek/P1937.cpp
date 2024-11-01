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
    int capacity[MAXN + 1];
    Request requests[MAXM];

    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &capacity[i]);
    }
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &requests[i].start, &requests[i].end);
    }

    qsort(requests, M, sizeof(Request), compareRequests);

    int satisfied = 0;
    int used[MAXN + 1] = {0};

    for (int i = 0; i < M; i++) {
        int start = requests[i].start;
        int end = requests[i].end;
        int canAllocate = 1;

        for (int j = start; j <= end; j++) {
            if (used[j] >= capacity[j]) {
                canAllocate = 0;
                break;
            }
        }

        if (canAllocate) {
            for (int j = start; j <= end; j++) {
                used[j]++;
            }
            satisfied++;
        }
    }

    printf("%d\n", satisfied);

    return 0;
}