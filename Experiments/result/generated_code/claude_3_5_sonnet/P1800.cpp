#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_M 100

int n, m;
int d1[MAX_N], d2[MAX_N];

int check(int days) {
    long long total1 = 0, total2 = 0;
    for (int i = 0; i < n; i++) {
        int modules1 = days / d1[i];
        int modules2 = days / d2[i];
        int remaining = (days - modules1 * d1[i]) / d2[i] + (days - modules2 * d2[i]) / d1[i];
        total1 += modules1;
        total2 += modules2;
        total1 += remaining / 2;
        total2 += remaining - remaining / 2;
    }
    return total1 >= m && total2 >= m;
}

int binary_search() {
    int left = 0, right = m * 100;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (check(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &d1[i], &d2[i]);
    }
    
    int result = binary_search();
    printf("%d\n", result);
    
    return 0;
}