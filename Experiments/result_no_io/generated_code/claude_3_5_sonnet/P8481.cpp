#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 1048576 // 2^20

int num[MAX_N];
int n, q;

int find_min_count(int x) {
    int l = 0, r = n - 1;
    int count = 0;
    
    while (l < r) {
        int mid_even = (l + r) / 2;
        int mid_odd = (l + r + 1) / 2;
        
        if (num[mid_even] >= x && num[mid_odd] >= x) {
            r = mid_even;
        } else if (num[mid_even] < x && num[mid_odd] < x) {
            l = mid_odd + 1;
        } else {
            return count + 1;
        }
        
        count++;
    }
    
    return count;
}

int main() {
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &num[i]);
    }
    
    scanf("%d", &q);
    
    for (int i = 0; i < q; i++) {
        int x;
        scanf("%d", &x);
        printf("%d\n", find_min_count(x));
    }
    
    return 0;
}