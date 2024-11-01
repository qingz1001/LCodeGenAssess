#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SOLUTIONS 1000

int solutions[MAX_SOLUTIONS][3];
int solution_count = 0;

bool used[10] = {false};

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int compare(const void *a, const void *b) {
    const int *x = (const int *)a;
    const int *y = (const int *)b;
    return x[0] - y[0];
}

void generate_numbers(int depth, int num[], int A, int B, int C) {
    if (depth == 9) {
        int x = num[0] * 100 + num[1] * 10 + num[2];
        int y = num[3] * 100 + num[4] * 10 + num[5];
        int z = num[6] * 100 + num[7] * 10 + num[8];
        
        if ((long long)x * B == (long long)y * A && (long long)y * C == (long long)z * B) {
            solutions[solution_count][0] = x;
            solutions[solution_count][1] = y;
            solutions[solution_count][2] = z;
            solution_count++;
        }
        return;
    }
    
    for (int i = 1; i <= 9; i++) {
        if (!used[i]) {
            used[i] = true;
            num[depth] = i;
            generate_numbers(depth + 1, num, A, B, C);
            used[i] = false;
        }
    }
}

int main() {
    int A, B, C;
    scanf("%d %d %d", &A, &B, &C);
    
    int num[9];
    generate_numbers(0, num, A, B, C);
    
    if (solution_count == 0) {
        printf("No!!!\n");
    } else {
        qsort(solutions, solution_count, sizeof(solutions[0]), compare);
        for (int i = 0; i < solution_count; i++) {
            printf("%d %d %d\n", solutions[i][0], solutions[i][1], solutions[i][2]);
        }
    }
    
    return 0;
}