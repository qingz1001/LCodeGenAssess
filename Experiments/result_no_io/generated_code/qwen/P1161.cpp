#include <stdio.h>
#include <stdlib.h>

#define MAX_N 5000
#define MAX_T 2000000

int main() {
    int n;
    scanf("%d", &n);

    int count[MAX_T + 1] = {0};
    for (int i = 0; i < n; i++) {
        double a;
        int t;
        scanf("%lf %d", &a, &t);
        for (int j = 1; j <= t; j++) {
            int index = (int)(j * a);
            if (index > MAX_T) break;
            count[index]++;
        }
    }

    int result = -1;
    for (int i = 1; i <= MAX_T; i++) {
        if (count[i] == 1) {
            result = i;
            break;
        }
    }

    printf("%d\n", result);

    return 0;
}