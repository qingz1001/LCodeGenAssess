#include <stdio.h>
#include <string.h>

#define MAX_N 20
#define MAX_M 1000000

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    char convenient_places[MAX_N][100];
    for (int i = 0; i < n; i++) {
        scanf("%s", convenient_places[i]);
    }

    char her_place[MAX_M][100];
    int count = 0;
    for (int i = 0; i < m; i++) {
        scanf("%s", her_place[i]);
        for (int j = 0; j < n; j++) {
            if (strcmp(her_place[i], convenient_places[j]) == 0) {
                count++;
                break;
            }
        }
    }

    printf("%d\n", count);

    return 0;
}