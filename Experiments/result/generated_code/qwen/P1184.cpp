#include <stdio.h>
#include <string.h>

#define MAX_N 25
#define MAX_M 1000001

int main() {
    int n, m;
    char places[MAX_N][100];
    char locations[MAX_M][100];
    int count = 0;

    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; ++i) {
        scanf("%s", places[i]);
    }

    for (int i = 0; i < m; ++i) {
        scanf("%s", locations[i]);
        for (int j = 0; j < n; ++j) {
            if (strcmp(places[j], locations[i]) == 0) {
                count++;
                break;
            }
        }
    }

    printf("%d\n", count);

    return 0;
}