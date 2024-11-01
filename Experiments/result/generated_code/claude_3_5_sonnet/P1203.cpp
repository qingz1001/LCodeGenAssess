#include <stdio.h>
#include <string.h>

#define MAX_N 350

int n;
char necklace[MAX_N*2 + 1];

int count(int start, char color) {
    int cnt = 0;
    for (int i = start; i < start + n; i++) {
        if (necklace[i] == color || necklace[i] == 'w')
            cnt++;
        else
            break;
    }
    return cnt;
}

int main() {
    scanf("%d", &n);
    scanf("%s", necklace);
    
    strncpy(necklace + n, necklace, n);
    necklace[2*n] = '\0';
    
    int max_beads = 0;
    for (int i = 0; i < n; i++) {
        int left = count(i, 'r');
        left += count(i + left, 'b');
        
        int right = count(i + n - 1, 'r');
        right += count(i + n - 1 - right, 'b');
        
        int total = left + right;
        if (total > n) total = n;
        if (total > max_beads) max_beads = total;
    }
    
    printf("%d\n", max_beads);
    return 0;
}