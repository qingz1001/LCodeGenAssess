#include <stdio.h>
#include <stdlib.h>

#define MAX_N 2000001

int n, m;
int a[MAX_N];
int deque[MAX_N];
int front = 0, rear = 0;

void solve() {
    for (int i = 1; i <= n; i++) {
        while (front < rear && deque[front] < i - m + 1) {
            front++;
        }
        while (front < rear && a[deque[rear - 1]] >= a[i]) {
            rear--;
        }
        deque[rear++] = i;
        
        if (i == 1) {
            printf("0\n");
        } else if (i <= m) {
            printf("%d\n", a[deque[front]]);
        } else {
            printf("%d\n", a[deque[front]]);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    solve();
    
    return 0;
}