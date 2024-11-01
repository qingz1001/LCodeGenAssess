#include <stdio.h>
#include <stdlib.h>

#define MAXN 50005
#define MAXM 10005

typedef struct {
    int year;
    int rain;
} Data;

int compare(const void *a, const void *b) {
    return ((Data *)a)->year - ((Data *)b)->year;
}

int main() {
    int n, m;
    scanf("%d", &n);
    Data data[MAXN];
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &data[i].year, &data[i].rain);
    }
    qsort(data, n, sizeof(Data), compare);

    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        int Y, X;
        scanf("%d %d", &Y, &X);
        int j = 0;
        while (j < n && data[j].year < Y) ++j;
        if (j == n || data[j].year != Y) {
            printf("maybe\n");
            continue;
        }
        int max_rain = data[j].rain;
        int k = j + 1;
        while (k < n && data[k].year < X) {
            if (data[k].rain > max_rain) {
                printf("false\n");
                goto next_query;
            }
            max_rain = data[k].rain;
            ++k;
        }
        if (k == n || data[k].year != X) {
            printf("maybe\n");
        } else {
            printf("true\n");
        }
next_query:;
    }

    return 0;
}