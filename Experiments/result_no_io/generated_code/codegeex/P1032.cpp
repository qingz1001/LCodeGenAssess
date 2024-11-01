#include <stdio.h>
#include <string.h>

#define MAX_RULES 6
#define MAX_LENGTH 20
#define MAX_STEPS 10

char A[MAX_LENGTH + 1], B[MAX_LENGTH + 1];
char rules[MAX_RULES][MAX_LENGTH + 1][MAX_LENGTH + 1];
int steps = 0;

void transform(char *input, char *output) {
    for (int i = 0; i < MAX_RULES; i++) {
        char *pos = strstr(input, rules[i][0]);
        if (pos != NULL) {
            int len = strlen(rules[i][0]);
            strncpy(output, input, pos - input);
            output[pos - input] = '\0';
            strcat(output, rules[i][1]);
            strcat(output, pos + len);
            return;
        }
    }
    strcpy(output, input);
}

int main() {
    scanf("%s%s", A, B);
    int rule_count = 0;
    while (scanf("%s%s", rules[rule_count][0], rules[rule_count][1]) == 2) {
        rule_count++;
    }

    char current[MAX_LENGTH + 1];
    strcpy(current, A);

    while (steps < MAX_STEPS) {
        transform(current, current);
        steps++;
        if (strcmp(current, B) == 0) {
            printf("%d\n", steps);
            return 0;
        }
    }

    printf("NO ANSWER!\n");
    return 0;
}