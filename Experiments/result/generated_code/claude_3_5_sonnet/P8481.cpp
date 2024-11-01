#include <stdio.h>

int n, q;
int num[1<<20];

int find(int x) {
    int l = 0, r = n-1, cnt = 0;
    while (l < r) {
        cnt++;
        int mid1 = (l + r) / 2;
        int mid2 = (l + r + 1) / 2;
        if (num[mid1] >= x) {
            r = mid1;
        } else if (num[mid2] < x) {
            l = mid2 + 1;
        } else {
            l = mid1 + 1;
            r = mid2;
        }
    }
    return cnt;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &num[i]);
    }
    
    scanf("%d", &q);
    while (q--) {
        int x;
        scanf("%d", &x);
        printf("%d\n", find(x));
    }
    
    return 0;
}