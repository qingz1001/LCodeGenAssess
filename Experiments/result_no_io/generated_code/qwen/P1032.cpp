#include <stdio.h>
#include <string.h>

#define MAX_LEN 21
#define MAX_RULES 6

int min(int a, int b) {
    return (a < b) ? a : b;
}

int transform(char *A, char *B, char rules[MAX_RULES][MAX_LEN][MAX_LEN], int num_rules) {
    if (strcmp(A, B) == 0) {
        return 0;
    }
    if (strlen(A) > strlen(B)) {
        return -1;
    }

    for (int i = 0; i < num_rules; i++) {
        char *pos = strstr(A, rules[i][0]);
        while (pos != NULL) {
            char temp[MAX_LEN];
            strcpy(temp, A);
            strncpy(temp + (pos - A), rules[i][1], strlen(rules[i][1]));
            temp[pos - A + strlen(rules[i][1])] = '\0';
            int result = transform(temp, B, rules, num_rules);
            if (result >= 0) {
                return 1 + result;
            }
            pos = strstr(pos + 1, rules[i][0]);
        }
    }
    return -1;
}

int main() {
    char A[MAX_LEN], B[MAX_LEN];
    scanf("%s %s", A, B);

    char rules[MAX_RULES][MAX_LEN][MAX_LEN];
    int num_rules = 0;

    while (scanf("%s %s", rules[num_rules][0], rules[num_rules][1]) != EOF) {
        num_rules++;
        if (num_rules >= MAX_RULES) break;
    }

    int steps = transform(A, B, rules, num_rules);
    if (steps >= 0 && steps <= 10) {
        printf("%d\n", steps);
    } else {
        printf("NO ANSWER!\n");
    }

    return 0;
}