#include <stdio.h>
#include <math.h>

#define MAX_N 1000

long long sequence[MAX_N + 1];

void generate_sequence(int k, int n) {
    int index = 1;
    int power = 0;
    long long max_value = 0;

    while (index <= n) {
        long long current_power = pow(k, power);
        
        for (long long i = max_value + 1; i <= max_value + current_power && index <= n; i++) {
            sequence[index++] = i;
        }

        max_value += current_power;
        power++;
    }
}

int main() {
    int k, n;
    scanf("%d %d", &k, &n);

    generate_sequence(k, n);

    printf("%lld\n", sequence[n]);

    return 0;
}