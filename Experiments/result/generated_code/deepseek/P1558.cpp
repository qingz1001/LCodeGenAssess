#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_L 100000
#define MAX_T 30

int color[MAX_L];

void paint(int A, int B, int C) {
    if (A > B) {
        int temp = A;
        A = B;
        B = temp;
    }
    for (int i = A - 1; i < B; i++) {
        color[i] = C;
    }
}

int countColors(int A, int B) {
    if (A > B) {
        int temp = A;
        A = B;
        B = temp;
    }
    int count[MAX_T + 1] = {0};
    for (int i = A - 1; i < B; i++) {
        count[color[i]] = 1;
    }
    int uniqueColors = 0;
    for (int i = 1; i <= MAX_T; i++) {
        if (count[i]) {
            uniqueColors++;
        }
    }
    return uniqueColors;
}

int main() {
    int L, T, O;
    scanf("%d %d %d", &L, &T, &O);
    
    // Initialize the color board with color 1
    for (int i = 0; i < L; i++) {
        color[i] = 1;
    }
    
    char operation[2];
    int A, B, C;
    for (int i = 0; i < O; i++) {
        scanf("%s", operation);
        if (operation[0] == 'C') {
            scanf("%d %d %d", &A, &B, &C);
            paint(A, B, C);
        } else if (operation[0] == 'P') {
            scanf("%d %d", &A, &B);
            printf("%d\n", countColors(A, B));
        }
    }
    
    return 0;
}