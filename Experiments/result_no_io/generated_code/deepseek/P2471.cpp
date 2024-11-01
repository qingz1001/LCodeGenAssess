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

int binarySearch(Record *arr, int n, int year) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid].year == year) {
            return mid;
        } else if (arr[mid].year < year) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

void solve(int n, int m) {
    qsort(records, n, sizeof(Record), compare);

    for (int i = 0; i < m; i++) {
        int Y, X;
        scanf("%d %d", &Y, &X);

        int idxY = binarySearch(records, n, Y);
        int idxX = binarySearch(records, n, X);

        if (idxY == -1 && idxX == -1) {
            printf("maybe\n");
        } else if (idxY == -1) {
            int maxRain = -1;
            for (int j = idxX - 1; j >= 0 && records[j].year > Y; j--) {
                if (records[j].rain > maxRain) {
                    maxRain = records[j].rain;
                }
            }
            if (maxRain >= records[idxX].rain) {
                printf("false\n");
            } else {
                printf("maybe\n");
            }
        } else if (idxX == -1) {
            int maxRain = -1;
            for (int j = idxY + 1; j < n && records[j].year < X; j++) {
                if (records[j].rain > maxRain) {
                    maxRain = records[j].rain;
                }
            }
            if (maxRain >= records[idxY].rain) {
                printf("false\n");
            } else {
                printf("maybe\n");
            }
        } else {
            if (records[idxX].rain > records[idxY].rain) {
                printf("false\n");
            } else {
                int maxRain = -1;
                for (int j = idxY + 1; j < idxX; j++) {
                    if (records[j].rain > maxRain) {
                        maxRain = records[j].rain;
                    }
                }
                if (maxRain >= records[idxX].rain) {
                    printf("false\n");
                } else {
                    printf("true\n");
                }
            }
        }
    }
}

int main() {
    int n, m;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &records[i].year, &records[i].rain);
    }
    scanf("%d", &m);
    solve(n, m);
    return 0;
}