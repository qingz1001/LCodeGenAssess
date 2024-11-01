#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200005

typedef struct {
    int a;
    int b;
    int c;
} Equation;

Equation equations[MAXN];
int x_values[MAXN];
int x_count = 0;

void parse_equation(char* equation) {
    int a, b, c;
    sscanf(equation, "%dx+%d=%d", &a, &b, &c);
    equations[x_count].a = a;
    equations[x_count].b = b;
    equations[x_count].c = c;
    x_values[x_count++] = (c - b) / a;
}

int main() {
    int n, Q;
    scanf("%d %d", &n, &Q);
    
    for (int i = 0; i < n; i++) {
        char equation[50];
        scanf("%s", equation);
        parse_equation(equation);
    }
    
    // Sort x_values for binary search usage
    qsort(x_values, x_count, sizeof(int), cmpfunc);
    
    int last_x = 0;
    for (int i = 0; i < x_count; i++) {
        if (x_values[i] != last_x) {
            last_x = x_values[i];
            x_values[x_count++] = last_x;
        }
    }
    
    // Process each query
    for (int i = 0; i < Q; i++) {
        int L, R;
        scanf("%d %d", &L, &R);
        
        // Binary search to find the range of x_values within [L, R]
        int left = 0, right = x_count - 1;
        while (left < right) {
            int mid = (left + right) / 2;
            if (x_values[mid] < L) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        int start = (x_values[left] >= L) ? left : left + 1;
        
        left = 0, right = x_count - 1;
        while (left < right) {
            int mid = (left + right + 1) / 2;
            if (x_values[mid] > R) {
                right = mid - 1;
            } else {
                left = mid;
            }
        }
        int end = (x_values[left] <= R) ? left : left - 1;
        
        printf("%d\n", end - start + 1);
    }
    
    return 0;
}