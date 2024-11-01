#include <stdio.h>
#include <string.h>

#define MAX_N 10

int N;
char expression[MAX_N * 2];
char operators[] = {' ', '+', '-'};

void generate(int pos, int value, int lastNum) {
    if (pos == N) {
        if (value == 0) {
            printf("%s\n", expression);
        }
        return;
    }

    int currentNum = pos + 1;
    for (int i = 0; i < 3; i++) {
        expression[pos * 2 - 1] = operators[i];
        expression[pos * 2] = currentNum + '0';

        if (operators[i] == ' ') {
            int newNum = lastNum * 10 + currentNum;
            if (pos == 1) {
                generate(pos + 1, newNum, newNum);
            } else {
                generate(pos + 1, value - lastNum + newNum, newNum);
            }
        } else if (operators[i] == '+') {
            generate(pos + 1, value + currentNum, currentNum);
        } else {
            generate(pos + 1, value - currentNum, -currentNum);
        }
    }
}

int main() {
    scanf("%d", &N);

    expression[0] = '1';
    for (int i = 1; i < N; i++) {
        expression[i * 2] = i + 1 + '0';
    }
    expression[N * 2 - 1] = '\0';

    generate(1, 1, 1);

    return 0;
}