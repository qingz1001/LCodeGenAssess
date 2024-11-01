#include <stdio.h>
#include <stdlib.h>

#define MAXN 400001

int main() {
    int n;
    scanf("%d", &n);
    
    int a[MAXN], b[MAXN];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &a[i], &b[i]);
    }
    
    int intersections[MAXN];
    for (int i = 0; i < n; i++) {
        intersections[i] = 0;
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] > a[j]) {
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
                
                temp = b[i];
                b[i] = b[j];
                b[j] = temp;
            }
            
            if ((a[i] < a[j] && a[j] < b[i] && b[i] < b[j]) ||
                (a[j] < a[i] && a[i] < b[j] && b[j] < b[i])) {
                intersections[i]++;
                intersections[j]++;
            }
        }
    }
    
    int maxIntersections = 0;
    for (int i = 0; i < n; i++) {
        if (intersections[i] > maxIntersections) {
            maxIntersections = intersections[i];
        }
    }
    
    printf("%d\n", maxIntersections + 1);
    
    return 0;
}