#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

int n, Q;
int bottles[MAX_N + 1];

int find_position(int m) {
    int left = 1, right = n;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (bottles[mid] == m) {
            return mid;
        } else if (bottles[mid] < m) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return 0;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &bottles[i]);
    }
    
    scanf("%d", &Q);
    for (int i = 0; i < Q; i++) {
        int m;
        scanf("%d", &m);
        printf("%d\n", find_position(m));
    }
    
    return 0;
}