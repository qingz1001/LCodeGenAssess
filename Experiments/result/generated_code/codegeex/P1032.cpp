#include <stdio.h>
#include <string.h>

#define MAX_RULES 6
#define MAX_LENGTH 20
#define MAX_STEPS 10

char A[MAX_LENGTH + 1], B[MAX_LENGTH + 1];
char rules[MAX_RULES][MAX_LENGTH + 1][MAX_LENGTH + 1];

int match(char *source, char *pattern, int start) {
    int i, j;
    for (i = start, j = 0; source[i] != '\0' && pattern[j] != '\0'; i++, j++) {
        if (source[i] != pattern[j]) return -1;
    }
    return (pattern[j] == '\0') ? i : -1;
}

int transform(char *source, char *result, int start) {
    int i, j, k, m, n;
    for (i = 0; i < MAX_RULES; i++) {
        m = match(source, rules[i][0], start);
        if (m != -1) {
            n = strlen(rules[i][0]);
            for (j = 0, k = m; j < n; j++, k++) result[k] = '\0';
            strcat(result, rules[i][1]);
            strcat(result, source + m + n);
            return 1;
        }
    }
    return 0;
}

int main() {
    int i, j, steps = 0;
    char result[MAX_LENGTH * 2 + 1];

    scanf("%s%s", A, B);
    while (scanf("%s%s", rules[steps][0], rules[steps][1]) == 2) steps++;

    strcpy(result, A);
    for (i = 0; i < MAX_STEPS; i++) {
        if (strcmp(result, B) == 0) {
            printf("%d\n", i);
            return 0;
        }
        if (transform(result, result, 0) == 0) break;
    }

    printf("NO ANSWER!\n");
    return 0;
}