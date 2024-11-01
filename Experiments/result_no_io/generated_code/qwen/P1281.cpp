#include <stdio.h>

int main() {
    int m, k;
    scanf("%d %d", &m, &k);
    
    int pages[m];
    for (int i = 0; i < m; i++) {
        scanf("%d", &pages[i]);
    }
    
    int total_pages = 0;
    for (int i = 0; i < m; i++) {
        total_pages += pages[i];
    }
    
    int max_pages_per_person = total_pages / k;
    if (total_pages % k != 0) {
        max_pages_per_person++;
    }
    
    int current_pages = 0;
    int start = 0;
    for (int i = 0; i < k; i++) {
        while (current_pages + pages[start] <= max_pages_per_person) {
            current_pages += pages[start];
            start++;
        }
        
        printf("%d %d\n", start - 1, start - 1);
        
        current_pages -= pages[start - 1];
    }
    
    return 0;
}