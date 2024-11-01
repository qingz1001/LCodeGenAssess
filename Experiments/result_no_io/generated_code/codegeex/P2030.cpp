#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 255
#define MAX_NAMES 10000

char names[MAX_NAMES][MAX_NAME_LENGTH + 1];
int n, m;

int countPlayingTimes(char *s) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (strncmp(s, names[i], strlen(s)) == 0) {
            count++;
        }
    }
    return count;
}

int countPossibleArrangements() {
    int count = 0;
    for (int i = 1; i < n; i++) {
        count += (i == 1 || i == n - 1) ? 2 : 3;
    }
    return count;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", names[i]);
    }

    int totalPlayingTimes = 0;
    for (int i = 0; i < m; i++) {
        char s[MAX_NAME_LENGTH + 1];
        scanf("%s", s);
        totalPlayingTimes += countPlayingTimes(s);
    }

    int possibleArrangements = countPossibleArrangements();

    printf("%d\n%d\n", totalPlayingTimes, possibleArrangements);

    return 0;
}