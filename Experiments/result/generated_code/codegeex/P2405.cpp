#include <stdio.h>
#include <string.h>

#define MAX_SIZE 10001

int main() {
    char m[MAX_SIZE];
    int n;
    scanf("%s%d", m, &n);

    int len = strlen(m);
    int result = 0;
    int power = 1;

    for (int i = 0; i < len; i++) {
        int digit = m[i] - '0';
        while (digit >= n) {
            digit -= n;
            power++;
        }
        result += power;
    }

    printf("%d\n", result);
    return 0;
}