#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long long ull;

ull count = 0;
int n, s;
int sequence[101];

void generate_sequences(int index, int sum) {
    if (index == n) {
        if (sum == s) {
            count++;
            if (count <= 100) {
                for (int i = 0; i < n; i++) {
                    printf("%d ", sequence[i]);
                }
                printf("\n");
            }
        }
        return;
    }

    if (index == 0) {
        sequence[index] = 0;
        generate_sequences(index + 1, sum);
    } else {
        sequence[index] = sequence[index - 1] + 1;
        generate_sequences(index + 1, sum + sequence[index]);
        sequence[index] = sequence[index - 1] - 1;
        generate_sequences(index + 1, sum + sequence[index]);
    }
}

int main() {
    scanf("%d %d", &n, &s);
    generate_sequences(0, 0);
    printf("%llu\n", count);
    return 0;
}