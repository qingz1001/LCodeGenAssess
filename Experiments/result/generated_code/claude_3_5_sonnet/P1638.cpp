#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000001
#define MAX_M 2001

int n, m;
int paintings[MAX_N];
int painter_count[MAX_M];

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &paintings[i]);
    }
    
    int left = 0, right = 0;
    int unique_painters = 0;
    int min_left = 0, min_right = n - 1;
    
    while (right < n) {
        if (painter_count[paintings[right]] == 0) {
            unique_painters++;
        }
        painter_count[paintings[right]]++;
        
        while (unique_painters == m) {
            if (right - left < min_right - min_left) {
                min_left = left;
                min_right = right;
            }
            
            painter_count[paintings[left]]--;
            if (painter_count[paintings[left]] == 0) {
                unique_painters--;
            }
            left++;
        }
        
        right++;
    }
    
    printf("%d %d\n", min_left + 1, min_right + 1);
    
    return 0;
}