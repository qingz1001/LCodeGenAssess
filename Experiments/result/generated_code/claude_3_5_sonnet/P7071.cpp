#include <stdio.h>

#define MAX_POWERS 30

void findExcellentPartition(int n) {
    int powers[MAX_POWERS] = {0};
    int count = 0;
    int sum = 0;

    for (int i = 30; i >= 1; i--) {
        int power = 1 << i;
        if (sum + power <= n) {
            powers[count++] = power;
            sum += power;
        }
    }

    if (sum == n) {
        for (int i = 0; i < count; i++) {
            printf("%d", powers[i]);
            if (i < count - 1) {
                printf(" ");
            }
        }
        printf("\n");
    } else {
        printf("-1\n");
    }
}

int main() {
    int n;
    scanf("%d", &n);
    findExcellentPartition(n);
    return 0;
}