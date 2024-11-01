#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 2000

int sequence[MAX_N];
bool used[MAX_N];

bool can_form_increasing_subsequence(int n, int start, int count) {
    if (count == n / 2) {
        return true;
    }
    
    int prev = -1;
    for (int i = start; i < n; i++) {
        if (!used[i] && sequence[i] > prev) {
            used[i] = true;
            if (can_form_increasing_subsequence(n, i + 1, count + 1)) {
                return true;
            }
            used[i] = false;
            prev = sequence[i];
        }
    }
    
    return false;
}

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; i++) {
            scanf("%d", &sequence[i]);
            used[i] = false;
        }
        
        if (can_form_increasing_subsequence(n, 0, 0) && 
            can_form_increasing_subsequence(n, 0, 0)) {
            printf("Yes!\n");
        } else {
            printf("No!\n");
        }
    }
    
    return 0;
}