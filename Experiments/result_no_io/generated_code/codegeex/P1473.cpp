#include <stdio.h>
#include <string.h>

int n;
char symbols[100];
int sum;

void generate_sequences(int level, int current_sum) {
    if (level == n) {
        if (current_sum == 0) {
            symbols[n] = '\0';
            printf("%s\n", symbols);
        }
        return;
    }

    // Generate sequences with a space
    symbols[level * 2] = ' ';
    symbols[level * 2 + 1] = '0' + level + 1;
    generate_sequences(level + 1, current_sum);

    // Generate sequences with a plus
    symbols[level * 2] = '+';
    symbols[level * 2 + 1] = '0' + level + 1;
    generate_sequences(level + 1, current_sum + level + 1);

    // Generate sequences with a minus
    symbols[level * 2] = '-';
    symbols[level * 2 + 1] = '0' + level + 1;
    generate_sequences(level + 1, current_sum - (level + 1));
}

int main() {
    scanf("%d", &n);
    symbols[0] = '1';
    generate_sequences(1, 1);
    return 0;
}