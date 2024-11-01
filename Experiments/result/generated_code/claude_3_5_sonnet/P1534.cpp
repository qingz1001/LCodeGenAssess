#include <stdio.h>

int main() {
    int n, school, extra;
    int unhappiness = 0, total_unhappiness = 0;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &school, &extra);
        
        int total_hours = school + extra;
        unhappiness += total_hours - 8;
        
        if (unhappiness < 0) {
            unhappiness = 0;
        }
        
        total_unhappiness += unhappiness;
    }

    printf("%d\n", total_unhappiness);

    return 0;
}