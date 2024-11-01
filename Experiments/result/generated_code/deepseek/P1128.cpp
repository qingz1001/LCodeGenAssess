#include <stdio.h>
#include <math.h>

int main() {
    int n;
    scanf("%d", &n);

    int m = 1;
    int factors = 1;

    while (factors < n) {
        m++;
        factors = 1;
        int temp = m;
        for (int i = 2; i * i <= temp; i++) {
            int count = 0;
            while (temp % i == 0) {
                temp /= i;
                count++;
            }
            factors *= (count + 1);
        }
        if (temp > 1) {
            factors *= 2;
        }
    }

    printf("%d\n", m);
    return 0;
}