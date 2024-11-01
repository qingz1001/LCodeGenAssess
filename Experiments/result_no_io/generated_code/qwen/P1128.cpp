#include <stdio.h>
#include <math.h>

int main() {
    int n;
    scanf("%d", &n);

    int m = 1;
    while (1) {
        int count = 0;
        for (int i = 1; i <= sqrt(m); i++) {
            if (m % i == 0) {
                count += 2;
                if (i * i == m) {
                    count -= 1;
                }
            }
        }
        if (count == n) {
            break;
        }
        m++;
    }

    printf("%d\n", m);
    return 0;
}