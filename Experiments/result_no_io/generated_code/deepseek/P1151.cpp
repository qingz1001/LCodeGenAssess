#include <stdio.h>

int main() {
    int K;
    scanf("%d", &K);

    int found = 0;

    for (int num = 10000; num <= 30000; num++) {
        int sub1 = num / 100;
        int sub2 = (num / 10) % 1000;
        int sub3 = num % 1000;

        if (sub1 % K == 0 && sub2 % K == 0 && sub3 % K == 0) {
            printf("%d\n", num);
            found = 1;
        }
    }

    if (!found) {
        printf("No\n");
    }

    return 0;
}