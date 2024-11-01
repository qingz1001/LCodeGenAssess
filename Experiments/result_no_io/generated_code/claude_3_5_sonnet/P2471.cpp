#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 50000

typedef struct {
    int year;
    int rainfall;
} Record;

Record records[MAX_N];
int n;

int compare(const void *a, const void *b) {
    return ((Record*)a)->year - ((Record*)b)->year;
}

char* check_rainfall(int Y, int X) {
    int i, j;
    int X_index = -1, Y_index = -1;
    int max_rainfall = 0;

    for (i = 0; i < n; i++) {
        if (records[i].year == X) X_index = i;
        if (records[i].year == Y) Y_index = i;
        if (X_index != -1 && Y_index != -1) break;
    }

    if (X_index == -1) return "maybe";
    if (Y_index == -1) Y_index = 0;

    if (Y_index > X_index) return "false";

    for (j = Y_index; j <= X_index; j++) {
        if (records[j].rainfall > max_rainfall) {
            max_rainfall = records[j].rainfall;
        }
    }

    if (records[X_index].rainfall < max_rainfall) return "false";
    if (Y_index == X_index || records[X_index].rainfall > records[Y_index].rainfall) return "true";
    
    for (j = Y_index + 1; j < X_index; j++) {
        if (records[j].rainfall >= records[X_index].rainfall) return "false";
    }

    return "true";
}

int main() {
    int m, i;
    int Y, X;

    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d %d", &records[i].year, &records[i].rainfall);
    }

    qsort(records, n, sizeof(Record), compare);

    scanf("%d", &m);
    for (i = 0; i < m; i++) {
        scanf("%d %d", &Y, &X);
        printf("%s\n", check_rainfall(Y, X));
    }

    return 0;
}