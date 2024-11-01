#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CAPACITY 21

int a, b, c;
int possibilities[MAX_CAPACITY];
int visited[MAX_CAPACITY][MAX_CAPACITY][MAX_CAPACITY];

void pour(int x, int y, int z) {
    if (visited[x][y][z]) return;
    visited[x][y][z] = 1;
    
    if (x == 0) possibilities[z] = 1;
    
    // A to B
    int amount = (x < b - y) ? x : b - y;
    pour(x - amount, y + amount, z);
    
    // A to C
    amount = (x < c - z) ? x : c - z;
    pour(x - amount, y, z + amount);
    
    // B to A
    amount = (y < a - x) ? y : a - x;
    pour(x + amount, y - amount, z);
    
    // B to C
    amount = (y < c - z) ? y : c - z;
    pour(x, y - amount, z + amount);
    
    // C to A
    amount = (z < a - x) ? z : a - x;
    pour(x + amount, y, z - amount);
    
    // C to B
    amount = (z < b - y) ? z : b - y;
    pour(x, y + amount, z - amount);
}

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    scanf("%d %d %d", &a, &b, &c);
    
    memset(visited, 0, sizeof(visited));
    memset(possibilities, 0, sizeof(possibilities));
    
    pour(0, 0, c);
    
    int count = 0;
    for (int i = 0; i <= c; i++) {
        if (possibilities[i]) {
            count++;
        }
    }
    
    int result[count];
    int index = 0;
    for (int i = 0; i <= c; i++) {
        if (possibilities[i]) {
            result[index++] = i;
        }
    }
    
    qsort(result, count, sizeof(int), compare);
    
    for (int i = 0; i < count; i++) {
        printf("%d", result[i]);
        if (i < count - 1) {
            printf(" ");
        }
    }
    printf("\n");
    
    return 0;
}