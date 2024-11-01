#include <stdio.h>
#include <string.h>

#define MAX_N 351

int n;
char necklace[MAX_N * 2];

int count(int start, char color) {
    int count = 0;
    for (int i = start; i < start + n; i++) {
        if (necklace[i] != color && necklace[i] != 'w') break;
        count++;
    }
    return count;
}

int main() {
    scanf("%d", &n);
    scanf("%s", necklace);
    
    strcat(necklace, necklace);
    
    int max_beads = 0;
    for (int i = 0; i < n; i++) {
        int left = count(i, necklace[i] == 'w' ? 'r' : necklace[i]);
        int right = count(i + left, necklace[i + left] == 'w' ? 'b' : necklace[i + left]);
        int total = left + right;
        if (total > max_beads) {
            max_beads = total;
        }
        if (max_beads > n) max_beads = n;
    }
    
    printf("%d\n", max_beads);
    return 0;
}