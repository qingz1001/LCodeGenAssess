#include <stdio.h>

int main() {
    int n, m, type;
    scanf("%d %d %d", &n, &m, &type);
    
    int t[100], q[100];
    int count = 0;
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &t[i]);
    }
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &q[i]);
        if (t[i] == 1 && q[i] == 1) {
            count++;
        }
    }
    
    int total_bottles;
    if (count >= m) {
        total_bottles = n - count + m;
    } else {
        total_bottles = n;
    }
    
    printf("%d\n", total_bottles);
    
    return 0;
}