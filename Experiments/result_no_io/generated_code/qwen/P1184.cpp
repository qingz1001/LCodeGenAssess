#include <stdio.h>
#include <string.h>

#define MAX_N 20
#define MAX_M 1000000
#define MAX_LEN 100

int main() {
    int n, m;
    char places[MAX_N][MAX_LEN];
    char locations[MAX_M][MAX_LEN];
    int count = 0;

    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; ++i) {
        scanf("%s", places[i]);
    }

    for (int j = 0; j < m; ++j) {
        scanf("%s", locations[j]);
        for (int k = 0; k < n; ++k) {
            if (strcmp(places[k], locations[j]) == 0) {
                count++;
                break;
            }
        }
    }

    printf("%d\n", count);

    return 0;
}