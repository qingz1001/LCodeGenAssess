#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_N 20
#define MAX_M 1000000
#define MAX_LEN 100

int main() {
    int n, m;
    char convenient_places[MAX_N][MAX_LEN];
    char her_places[MAX_M][MAX_LEN];
    int count = 0;

    scanf("%d %d", &n, &m);
    getchar(); // consume newline character

    for (int i = 0; i < n; i++) {
        fgets(convenient_places[i], MAX_LEN, stdin);
        convenient_places[i][strcspn(convenient_places[i], "\n")] = 0; // remove newline character
    }

    for (int i = 0; i < m; i++) {
        fgets(her_places[i], MAX_LEN, stdin);
        her_places[i][strcspn(her_places[i], "\n")] = 0; // remove newline character
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (strcmp(her_places[i], convenient_places[j]) == 0) {
                count++;
                break;
            }
        }
    }

    printf("%d\n", count);

    return 0;
}