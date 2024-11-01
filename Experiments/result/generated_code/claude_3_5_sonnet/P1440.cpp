#include <stdio.h>
#include <stdlib.h>

#define MAX_N 2000001

int n, m;
int a[MAX_N];
int deque[MAX_N];
int front = 0, rear = -1;

void push(int i) {
    while (front <= rear && a[deque[rear]] >= a[i]) {
        rear--;
    }
    deque[++rear] = i;
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    for (int i = 1; i <= n; i++) {
        if (front <= rear && deque[front] <= i - m) {
            front++;
        }
        
        push(i);
        
        if (i <= m) {
            printf("%d\n", front <= rear ? a[deque[front]] : 0);
        } else {
            printf("%d\n", a[deque[front]]);
        }
    }
    
    return 0;
}