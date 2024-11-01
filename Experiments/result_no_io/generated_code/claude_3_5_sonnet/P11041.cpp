#include <stdio.h>

int main() {
    long long n = 202420242024LL;
    long long num = 0;
    long long count = 0;

    while (count < n) {
        num += 4;
        if (num % 20 == 0 || num % 24 == 0) {
            count++;
        }
    }

    printf("%lld\n", num);

    return 0;
}