#include <stdio.h>
#include <string.h>

#define MAX_N 10

int N;
char expr[MAX_N * 2];

void generate(int pos, int sum, int last) {
    if (pos == N) {
        if (sum == 0) {
            printf("%s\n", expr);
        }
        return;
    }

    int num = 0;
    for (int i = pos; i < N; i++) {
        num = num * 10 + (i + 1);

        if (pos > 0) {
            // Add '+'
            expr[pos * 2 - 1] = '+';
            generate(i + 1, sum + num, num);

            // Add '-'
            expr[pos * 2 - 1] = '-';
            generate(i + 1, sum - num, -num);

            // Add ' '
            expr[pos * 2 - 1] = ' ';
            if (last > 0) {
                generate(i + 1, sum - last + last * 10 + num, last * 10 + num);
            } else {
                generate(i + 1, sum - last - ((-last) * 10 + num), -((-last) * 10 + num));
            }
        } else {
            generate(i + 1, num, num);
        }
    }
}

int main() {
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        expr[i * 2] = i + '1';
    }
    expr[N * 2 - 1] = '\0';

    generate(1, 1, 1);

    return 0;
}