#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXP 10000007

typedef struct {
    int s, e, p;
} Task;

typedef struct {
    int x, a, b, c;
} Query;

Task tasks[MAXN];
Query queries[MAXN];
long long prioritySum[MAXN];
int priorityCount[MAXN];

int cmp(const void *a, const void *b) {
    return ((Task *)a)->p - ((Task *)b)->p;
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &tasks[i].s, &tasks[i].e, &tasks[i].p);
    }

    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &queries[i].x, &queries[i].a, &queries[i].b, &queries[i].c);
    }

    qsort(tasks, m, sizeof(Task), cmp);

    memset(prioritySum, 0, sizeof(prioritySum));
    memset(priorityCount, 0, sizeof(priorityCount));

    for (int i = 0; i < m; i++) {
        for (int j = tasks[i].s; j <= tasks[i].e; j++) {
            prioritySum[j] += tasks[i].p;
            priorityCount[j]++;
        }
    }

    long long pre = 1;
    for (int i = 0; i < n; i++) {
        int x = queries[i].x;
        int k = 1 + (queries[i].a * pre + queries[i].b) % queries[i].c;

        if (k > priorityCount[x]) {
            pre = prioritySum[x];
        } else {
            long long sum = 0;
            int count = 0;
            for (int j = 0; j < m; j++) {
                if (tasks[j].s <= x && x <= tasks[j].e) {
                    sum += tasks[j].p;
                    count++;
                    if (count == k) break;
                }
            }
            pre = sum;
        }
        printf("%lld\n", pre);
    }

    return 0;
}