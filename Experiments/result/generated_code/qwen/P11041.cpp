#include <stdio.h>

int main() {
    int count = 0;
    for (long long i = 1; ; i++) {
        if ((i % 20 == 0 || i % 24 == 0)) {
            count++;
            if (count == 202420242024) {
                printf("%lld\n", i);
                break;
            }
        }
    }
    return 0;
}