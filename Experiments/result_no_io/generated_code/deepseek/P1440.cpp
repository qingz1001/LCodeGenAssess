#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int *a = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    int *min_values = (int *)malloc(n * sizeof(int));
    int *deque = (int *)malloc(n * sizeof(int));
    int front = 0, rear = -1;
    
    for (int i = 0; i < n; i++) {
        while (front <= rear && deque[front] < i - m + 1) {
            front++;
        }
        
        while (front <= rear && a[deque[rear]] >= a[i]) {
            rear--;
        }
        
        deque[++rear] = i;
        
        if (i < m - 1) {
            min_values[i] = 0;
        } else {
            min_values[i] = a[deque[front]];
        }
    }
    
    for (int i = 0; i < n; i++) {
        printf("%d\n", min_values[i]);
    }
    
    free(a);
    free(min_values);
    free(deque);
    
    return 0;
}