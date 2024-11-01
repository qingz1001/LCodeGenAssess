#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_N 100
#define MOD 18446744073709551616ULL  // 2^64

typedef unsigned long long ull;

ull count = 0;
int sequences[100][MAX_N];
int seq_count = 0;

void generate_sequences(int n, int s, int current_sum, int index, int* current_seq) {
    if (index == n) {
        if (current_sum == s) {
            if (seq_count < 100) {
                for (int i = 0; i < n; i++) {
                    sequences[seq_count][i] = current_seq[i];
                }
                seq_count++;
            }
            count = (count + 1) % MOD;
        }
        return;
    }

    if (index == 0) {
        current_seq[index] = 0;
        generate_sequences(n, s, current_sum, index + 1, current_seq);
    } else {
        int prev = current_seq[index - 1];
        if (current_sum + prev + 1 <= s) {
            current_seq[index] = prev + 1;
            generate_sequences(n, s, current_sum + prev + 1, index + 1, current_seq);
        }
        if (current_sum + prev - 1 <= s) {
            current_seq[index] = prev - 1;
            generate_sequences(n, s, current_sum + prev - 1, index + 1, current_seq);
        }
    }
}

int main() {
    int n, s;
    scanf("%d %d", &n, &s);

    int current_seq[MAX_N];
    generate_sequences(n, s, 0, 0, current_seq);

    printf("%llu\n", count);
    for (int i = 0; i < seq_count; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", sequences[i][j]);
        }
        printf("\n");
    }

    return 0;
}