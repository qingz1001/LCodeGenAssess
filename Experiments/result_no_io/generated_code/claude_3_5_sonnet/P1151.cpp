#include <stdio.h>

int main() {
    int K;
    scanf("%d", &K);

    int count = 0;
    for (int i = 10000; i <= 30000; i++) {
        int sub1 = i / 100;
        int sub2 = (i / 10) % 1000;
        int sub3 = i % 1000;

        if (sub1 % K == 0 && sub2 % K == 0 && sub3 % K == 0) {
            printf("%d\n", i);
            count++;
        }
    }

    if (count == 0) {
        printf("No\n");
    }

    return 0;
}