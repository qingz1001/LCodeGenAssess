#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isRunaroundNumber(unsigned long num) {
    char digits[10];
    sprintf(digits, "%lu", num);
    int len = strlen(digits);
    bool visited[10] = {false};
    int pos = 0;

    for (int i = 0; i < len; i++) {
        if (visited[pos] || digits[pos] == '0') return false;
        visited[pos] = true;
        pos = (pos + (digits[pos] - '0')) % len;
    }

    return pos == 0;
}

int main() {
    unsigned long m;
    scanf("%lu", &m);

    while (true) {
        m++;
        if (isRunaroundNumber(m)) {
            printf("%lu\n", m);
            break;
        }
    }

    return 0;
}