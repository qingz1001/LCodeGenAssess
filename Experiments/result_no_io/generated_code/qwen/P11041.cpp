#include <stdio.h>

int main() {
    int count = 0;
    long long num = 0;

    while (count < 202420242024) {
        num++;
        if (num % 20 == 0 || num % 24 == 0) {
            count++;
        }
    }

    printf("%lld\n", num);
    return 0;
}