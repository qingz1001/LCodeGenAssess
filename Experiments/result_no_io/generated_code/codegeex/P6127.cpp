#include <stdio.h>
#include <string.h>

#define MAX_N 6
#define MAX_EXPRESSION_LENGTH 100

char propositions[MAX_N + 1];
char truth_table[1 << MAX_N][MAX_N + 2];
char result[MAX_N + 1];
int n;

void generate_truth_table() {
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            truth_table[i][j] = (i & (1 << j)) ? 'T' : 'F';
        }
        truth_table[i][n] = '\0';
    }
}

void generate_propositions() {
    for (int i = 0; i < n; i++) {
        propositions[i] = 'a' + i;
    }
    propositions[n] = '\0';
}

void generate_result() {
    for (int i = 0; i < n; i++) {
        result[i] = '!';
        result[i + 1] = propositions[i];
    }
    result[n] = '\0';
}

void print_expression() {
    printf("%s", result);
}

int main() {
    scanf("%d", &n);
    generate_truth_table();
    generate_propositions();
    generate_result();

    for (int i = 0; i < (1 << n); i++) {
        if (truth_table[i][n] == 'F') {
            printf("%s", result);
        }
    }

    print_expression();
    return 0;
}