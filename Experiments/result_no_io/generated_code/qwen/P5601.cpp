#include <stdio.h>
#include <string.h>

#define MAX_N 100
#define MAX_Q 100
#define MAX_S 100

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    char problems[MAX_N][MAX_S + 1];
    char answers[MAX_N][MAX_S + 1];

    for (int i = 0; i < n; ++i) {
        scanf("%s %s", problems[i], answers[i]);
    }

    char questions[MAX_Q][MAX_S + 1];
    char options[MAX_Q][4][MAX_S + 1];

    for (int i = 0; i < q; ++i) {
        scanf("%s %s %s %s %s", questions[i], options[i][0], options[i][1], options[i][2], options[i][3]);
    }

    for (int i = 0; i < q; ++i) {
        for (int j = 0; j < n; ++j) {
            if (strcmp(problems[j], questions[i]) == 0) {
                for (int k = 0; k < 4; ++k) {
                    if (strcmp(options[i][k], answers[j]) == 0) {
                        printf("%c\n", 'A' + k);
                        break;
                    }
                }
                break;
            }
        }
    }

    return 0;
}