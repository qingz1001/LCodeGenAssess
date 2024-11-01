#include <stdio.h>

int main() {
    int K;
    scanf("%d", &K);

    int found = 0;
    for (int i = 10000; i <= 30000; i++) {
        int sub1 = i / 100;
        int sub2 = (i / 10) % 100;
        int sub3 = i % 100;

        if (sub1 % K == 0 && sub2 % K == 0 && sub3 % K == 0) {
            printf("%d\n", i);
            found = 1;
        }
    }

    if (!found) {
        printf("No\n");
    }

    return 0;
}