#include <stdio.h>
#include <stdlib.h>

typedef struct Interval {
    int start;
    int end;
} Interval;

int compare(const void *a, const void *b) {
    Interval *intervalA = (Interval *)a;
    Interval *intervalB = (Interval *)b;
    if (intervalA->start == intervalB->start) {
        return intervalA->end - intervalB->end;
    }
    return intervalA->start - intervalB->start;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    Interval intervals[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &intervals[i].start, &intervals[i].end);
    }
    qsort(intervals, n, sizeof(Interval), compare);
    
    int left = 0, right = n - 1;
    int minCost = -1;
    while (left <= right) {
        int count = 0;
        int maxLen = 0, minLen = 1000000000;
        for (int i = left; i <= right; i++) {
            if (intervals[i].end >= intervals[left].start) {
                count++;
                maxLen = (maxLen < intervals[i].end - intervals[i].start) ? intervals[i].end - intervals[i].start : maxLen;
                minLen = (minLen > intervals[i].end - intervals[i].start) ? intervals[i].end - intervals[i].start : minLen;
            }
        }
        if (count >= m) {
            if (minCost == -1 || minCost > maxLen - minLen) {
                minCost = maxLen - minLen;
            }
            left++;
        } else {
            right--;
        }
    }
    printf("%d\n", minCost);
    return 0;
}