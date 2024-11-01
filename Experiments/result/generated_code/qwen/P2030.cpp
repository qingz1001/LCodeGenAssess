#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 255
#define MAX_N 10000
#define MAX_M 10000

int n, m;
char names[MAX_N][MAX_NAME_LENGTH];
char targets[MAX_M][MAX_NAME_LENGTH];

int countPrefixMatches(const char *target) {
    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (strncmp(names[i], target, strlen(target)) == 0) {
            ++count;
        }
    }
    return count;
}

void calculatePermutations() {
    int permutations = 1;
    for (int i = 0; i < n; ++i) {
        int validPositions = 1;
        if (i > 0) validPositions++;
        if (i < n - 1) validPositions++;
        permutations *= validPositions;
    }
    printf("%d\n", permutations);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%s", names[i]);
    }
    for (int i = 0; i < m; ++i) {
        scanf("%s", targets[i]);
    }

    int totalPlays = 0;
    for (int i = 0; i < m; ++i) {
        totalPlays += countPrefixMatches(targets[i]);
    }
    printf("%d\n", totalPlays);

    calculatePermutations();

    return 0;
}