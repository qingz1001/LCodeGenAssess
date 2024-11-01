#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_N 100
#define MAX_OUTPUT 100

int n, s;
int64_t count = 0;
int sequence[MAX_N];
int output_count = 0;

void generate_sequence(int index, int sum) {
    if (index == n) {
        if (sum == s) {
            count++;
            if (output_count < MAX_OUTPUT) {
                for (int i = 0; i < n; i++) {
                    printf("%d ", sequence[i]);
                }
                printf("\n");
                output_count++;
            }
        }
        return;
    }
    
    if (index == 0) {
        sequence[index] = 0;
        generate_sequence(index + 1, 0);
    } else {
        sequence[index] = sequence[index - 1] + 1;
        generate_sequence(index + 1, sum + sequence[index]);
        
        sequence[index] = sequence[index - 1] - 1;
        generate_sequence(index + 1, sum + sequence[index]);
    }
}

int main() {
    scanf("%d %d", &n, &s);
    
    generate_sequence(0, 0);
    
    printf("%llu\n", (uint64_t)count);
    
    return 0;
}