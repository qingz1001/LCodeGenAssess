#include <stdio.h>
#include <stdlib.h>

#define MAXN 200001
#define MAXVAL 1500000000

int main() {
    int n;
    scanf("%d", &n);
    int count[MAXVAL + 1] = {0};

    for (int i = 0; i < n; ++i) {
        int num;
        scanf("%d", &num);
        count[num]++;
    }

    for (int i = 1; i <= MAXVAL; ++i) {
        if (count[i] > 0) {
            printf("%d %d\n", i, count[i]);
        }
    }

    return 0;
}