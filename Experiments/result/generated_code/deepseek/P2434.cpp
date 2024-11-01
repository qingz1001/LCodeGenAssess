#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Interval;

int compareIntervals(const void *a, const void *b) {
    Interval *intervalA = (Interval *)a;
    Interval *intervalB = (Interval *)b;
    if (intervalA->start == intervalB->start) {
        return intervalA->end - intervalB->end;
    }
    return intervalA->start - intervalB->start;
}

int main() {
    int n;
    scanf("%d", &n);

    Interval intervals[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &intervals[i].start, &intervals[i].end);
    }

    // 按照区间的起始点排序，如果起始点相同则按结束点排序
    qsort(intervals, n, sizeof(Interval), compareIntervals);

    Interval result[n];
    int resultCount = 0;

    int currentStart = intervals[0].start;
    int currentEnd = intervals[0].end;

    for (int i = 1; i < n; i++) {
        if (intervals[i].start <= currentEnd) {
            // 当前区间与前一个区间有重叠，合并区间
            if (intervals[i].end > currentEnd) {
                currentEnd = intervals[i].end;
            }
        } else {
            // 当前区间与前一个区间无重叠，保存前一个区间
            result[resultCount].start = currentStart;
            result[resultCount].end = currentEnd;
            resultCount++;
            // 更新当前区间为新的区间
            currentStart = intervals[i].start;
            currentEnd = intervals[i].end;
        }
    }

    // 保存最后一个区间
    result[resultCount].start = currentStart;
    result[resultCount].end = currentEnd;
    resultCount++;

    // 输出结果
    for (int i = 0; i < resultCount; i++) {
        printf("%d %d\n", result[i].start, result[i].end);
    }

    return 0;
}