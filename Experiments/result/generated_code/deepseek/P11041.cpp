#include <stdio.h>

int main() {
    long long target = 202420242024;
    long long count = 0;
    long long num = 20;

    while (count < target) {
        if (num % 20 == 0 || num % 24 == 0) {
            count++;
            if (count == target) {
                printf("%lld\n", num);
                break;
            }
        }
        num++;
    }

    return 0;
}