#include <stdio.h>
#include <stdlib.h>

#define MAXN 50005

typedef struct {
    int year;
    int rain;
} Data;

Data data[MAXN];
int n, m;
int year[MAXN];
int rain[MAXN];
int min_rain[MAXN];
int max_rain[MAXN];

void init() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &data[i].year, &data[i].rain);
        year[i] = data[i].year;
        rain[i] = data[i].rain;
    }
    scanf("%d", &m);
}

void build() {
    min_rain[0] = rain[0];
    max_rain[0] = rain[0];
    for (int i = 1; i < n; i++) {
        min_rain[i] = rain[i];
        max_rain[i] = rain[i];
        for (int j = 0; j < i; j++) {
            if (year[j] < year[i]) {
                min_rain[i] = min_rain[i] < min_rain[j] ? min_rain[i] : min_rain[j];
                max_rain[i] = max_rain[i] > max_rain[j] ? max_rain[i] : max_rain[j];
            }
        }
    }
}

int find(int x) {
    int left = 0, right = n - 1, mid;
    while (left <= right) {
        mid = (left + right) / 2;
        if (year[mid] == x) return mid;
        else if (year[mid] < x) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int main() {
    init();
    build();
    for (int i = 0; i < m; i++) {
        int Y, X;
        scanf("%d %d", &Y, &X);
        int idx_Y = find(Y);
        int idx_X = find(X);
        if (idx_Y == -1 || idx_X == -1) {
            printf("maybe\n");
        } else if (rain[idx_X] >= rain[idx_Y]) {
            printf("false\n");
        } else {
            bool flag = true;
            for (int j = idx_Y + 1; j < idx_X; j++) {
                if (min_rain[j] >= rain[idx_X]) {
                    flag = false;
                    break;
                }
            }
            if (flag) printf("true\n");
            else printf("false\n");
        }
    }
    return 0;
}