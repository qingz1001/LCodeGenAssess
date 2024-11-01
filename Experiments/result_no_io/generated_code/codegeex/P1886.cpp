#include <stdio.h>

#define N 1000001

int n, k;
int a[N], q[N];

void solve_min() {
    int front = 1, rear = 0;
    for (int i = 1; i <= n; i++) {
        while (front <= rear && q[front] < i - k + 1) front++;
        while (front <= rear && a[q[rear]] > a[i]) rear--;
        q[++rear] = i;
        if (i >= k) printf("%d ", a[q[front]]);
    }
    printf("\n");
}

void solve_max() {
    int front = 1, rear = 0;
    for (int i = 1; i <= n; i++) {
        while (front <= rear && q[front] < i - k + 1) front++;
        while (front <= rear && a[q[rear]] < a[i]) rear--;
        q[++rear] = i;
        if (i >= k) printf("%d ", a[q[front]]);
    }
    printf("\n");
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    solve_min();
    solve_max();
    return 0;
}