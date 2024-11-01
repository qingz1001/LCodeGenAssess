#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    int rooms = 0;
    int count_1 = 0, count_2 = 0;
    
    for (int i = 0; i < n; i++) {
        if (a[i] == 1) {
            count_1++;
            count_2 = 0;
        } else {
            count_2++;
            count_1 = 0;
        }
        
        if (count_1 > m || count_2 > m) {
            rooms++;
            count_1 = 0;
            count_2 = 0;
            i--;
        }
    }
    
    rooms++;
    
    printf("%d\n", rooms);
    
    return 0;
}