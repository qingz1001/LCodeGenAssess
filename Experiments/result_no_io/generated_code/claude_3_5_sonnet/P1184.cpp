#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PLACES 20
#define MAX_NAME_LENGTH 100

int n, m;
char places[MAX_PLACES][MAX_NAME_LENGTH];

int is_convenient(char *place) {
    for (int i = 0; i < n; i++) {
        if (strcmp(places[i], place) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    scanf("%d %d", &n, &m);
    getchar(); // 消耗换行符

    for (int i = 0; i < n; i++) {
        fgets(places[i], MAX_NAME_LENGTH, stdin);
        places[i][strcspn(places[i], "\n")] = 0; // 去除换行符
    }

    int count = 0;
    char her_place[MAX_NAME_LENGTH];

    for (int i = 0; i < m; i++) {
        fgets(her_place, MAX_NAME_LENGTH, stdin);
        her_place[strcspn(her_place, "\n")] = 0; // 去除换行符
        if (is_convenient(her_place)) {
            count++;
        }
    }

    printf("%d\n", count);

    return 0;
}