#include <stdio.h>
#include <string.h>

#define MAX_N 100

int N;
int coins[MAX_N];
int operations[MAX_N][MAX_N];
int op_count = 0;

void flip(int pos) {
    for (int i = 0; i < N; i++) {
        if (i != pos) {
            coins[i] = 1 - coins[i];
            operations[op_count][i] = 1;
        } else {
            operations[op_count][i] = 0;
        }
    }
    op_count++;
}

int main() {
    scanf("%d", &N);
    
    memset(coins, 0, sizeof(coins));
    memset(operations, 0, sizeof(operations));
    
    for (int i = 0; i < N - 1; i++) {
        flip(i);
    }
    
    printf("%d\n", op_count);
    
    for (int i = 0; i < op_count; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d", coins[j]);
        }
        printf("\n");
    }
    
    return 0;
}