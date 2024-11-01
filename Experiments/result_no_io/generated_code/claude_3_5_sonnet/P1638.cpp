#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000001
#define MAX_M 2001

int n, m;
int paintings[MAX_N];
int seen[MAX_M];

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &paintings[i]);
    }

    int left = 0, right = 0;
    int count = 0;
    int min_len = n + 1;
    int result_left = 0, result_right = n - 1;

    while (right < n) {
        if (count < m) {
            if (!seen[paintings[right]]) {
                count++;
            }
            seen[paintings[right]]++;
            right++;
        }
        
        while (count == m) {
            if (right - left < min_len) {
                min_len = right - left;
                result_left = left;
                result_right = right - 1;
            }
            
            seen[paintings[left]]--;
            if (seen[paintings[left]] == 0) {
                count--;
            }
            left++;
        }
    }

    printf("%d %d\n", result_left + 1, result_right + 1);

    return 0;
}