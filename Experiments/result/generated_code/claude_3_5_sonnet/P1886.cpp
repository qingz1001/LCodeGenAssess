#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000001

int a[MAX_N];
int deque[MAX_N];
int front = 0, rear = -1;

void push(int i, int* arr) {
    while (front <= rear && arr[deque[rear]] >= arr[i]) {
        rear--;
    }
    deque[++rear] = i;
}

void pop(int i, int k) {
    if (front <= rear && deque[front] <= i - k) {
        front++;
    }
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    // 最小值
    front = 0; rear = -1;
    for (int i = 0; i < n; i++) {
        push(i, a);
        pop(i, k);
        if (i >= k - 1) {
            printf("%d ", a[deque[front]]);
        }
    }
    printf("\n");
    
    // 最大值
    front = 0; rear = -1;
    for (int i = 0; i < n; i++) {
        while (front <= rear && a[deque[rear]] <= a[i]) {
            rear--;
        }
        deque[++rear] = i;
        if (front <= rear && deque[front] <= i - k) {
            front++;
        }
        if (i >= k - 1) {
            printf("%d ", a[deque[front]]);
        }
    }
    printf("\n");
    
    return 0;
}