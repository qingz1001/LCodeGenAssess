#include <stdio.h>
#include <math.h>

int count_factors(int num) {
    int count = 0;
    for (int i = 1; i <= sqrt(num); i++) {
        if (num % i == 0) {
            if (i * i == num) {
                count++;
            } else {
                count += 2;
            }
        }
    }
    return count;
}

int find_min_number_with_n_factors(int n) {
    int m = 1;
    while (1) {
        if (count_factors(m) == n) {
            return m;
        }
        m++;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d\n", find_min_number_with_n_factors(n));
    return 0;
}