#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_L 100005
#define MAX_T 31

int L, T, O;
int color[MAX_L];
int count[MAX_T];

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void color_range(int A, int B, int C) {
    if (A > B) swap(&A, &B);
    for (int i = A; i <= B; i++) {
        color[i] = C;
    }
}

int count_colors(int A, int B) {
    if (A > B) swap(&A, &B);
    memset(count, 0, sizeof(count));
    int unique = 0;
    for (int i = A; i <= B; i++) {
        if (count[color[i]] == 0) {
            unique++;
        }
        count[color[i]]++;
    }
    return unique;
}

int main() {
    scanf("%d %d %d", &L, &T, &O);
    
    // Initialize all colors to 1
    for (int i = 1; i <= L; i++) {
        color[i] = 1;
    }
    
    for (int i = 0; i < O; i++) {
        char op;
        int A, B, C;
        scanf(" %c", &op);
        if (op == 'C') {
            scanf("%d %d %d", &A, &B, &C);
            color_range(A, B, C);
        } else if (op == 'P') {
            scanf("%d %d", &A, &B);
            printf("%d\n", count_colors(A, B));
        }
    }
    
    return 0;
}