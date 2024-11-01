#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_N 100
#define MAX_M 10000

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    
    int d1[MAX_N], d2[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &d1[i], &d2[i]);
    }
    
    int max_d1 = 0, max_d2 = 0;
    for (int i = 0; i < n; i++) {
        if (d1[i] > max_d1) max_d1 = d1[i];
        if (d2[i] > max_d2) max_d2 = d2[i];
    }
    
    int left = 1, right = MAX_M;
    while (left < right) {
        int mid = (left + right) / 2;
        int count1 = 0, count2 = 0;
        
        for (int i = 0; i < n; i++) {
            count1 += mid / d1[i];
            count2 += mid / d2[i];
        }
        
        if (count1 >= m && count2 >= m) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    printf("%d\n", left);
    return 0;
}