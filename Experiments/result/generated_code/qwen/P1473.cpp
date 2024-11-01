#include <stdio.h>
#include <stdlib.h>

#define MAX_N 9

int n;
char expression[MAX_N * 2 + 1];

void generate(int index, int sum) {
    if (index == n) {
        if (sum == 0) {
            printf("%s\n", expression);
        }
        return;
    }

    // Add '+'
    expression[index * 2] = '+';
    expression[index * 2 + 1] = ' ';
    generate(index + 1, sum + (index + 1));

    // Add '-'
    expression[index * 2] = '-';
    expression[index * 2 + 1] = ' ';
    generate(index + 1, sum - (index + 1));

    // Add space
    expression[index * 2] = ' ';
    expression[index * 2 + 1] = ' ';
    generate(index + 1, sum);
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        expression[i * 2] = '1' + i;
        expression[i * 2 + 1] = ' ';
    }

    generate(1, 1);

    return 0;
}