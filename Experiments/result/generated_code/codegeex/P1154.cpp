#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int cows[5000];
    for (int i = 0; i < n; i++) {
        scanf("%d", &cows[i]);
    }

    int max = 0;
    for (int i = 0; i < n; i++) {
        if (cows[i] > max) {
            max = cows[i];
        }
    }

    int k = 1;
    while (1) {
        int flag = 1;
        for (int i = 0; i < n; i++) {
            if (cows[i] % k == 0) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            break;
        }
        k++;
    }

    printf("%d\n", k);
    return 0;
}