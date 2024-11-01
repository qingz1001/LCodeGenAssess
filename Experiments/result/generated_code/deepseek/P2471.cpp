#include <stdio.h>
#include <stdlib.h>

#define MAXN 50000

typedef struct {
    int year;
    int rain;
} Record;

Record records[MAXN];

int compare(const void *a, const void *b) {
    return ((Record *)a)->year - ((Record *)b)->year;
}

int findYear(int year, int n) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (records[mid].year == year) {
            return mid;
        } else if (records[mid].year < year) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int main() {
    int n, m;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &records[i].year, &records[i].rain);
    }

    qsort(records, n, sizeof(Record), compare);

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int Y, X;
        scanf("%d %d", &Y, &X);

        int idxY = findYear(Y, n);
        int idxX = findYear(X, n);

        if (idxY == -1 && idxX == -1) {
            printf("maybe\n");
        } else if (idxY == -1) {
            if (idxX > 0 && records[idxX].rain > records[idxX - 1].rain) {
                printf("maybe\n");
            } else {
                printf("false\n");
            }
        } else if (idxX == -1) {
            if (idxY < n - 1 && records[idxY + 1].rain < records[idxY].rain) {
                printf("maybe\n");
            } else {
                printf("false\n");
            }
        } else {
            if (records[idxX].rain <= records[idxY].rain) {
                printf("false\n");
            } else {
                int valid = 1;
                for (int j = idxY + 1; j < idxX; j++) {
                    if (records[j].rain >= records[idxX].rain) {
                        valid = 0;
                        break;
                    }
                }
                if (valid) {
                    printf("true\n");
                } else {
                    printf("false\n");
                }
            }
        }
    }

    return 0;
}