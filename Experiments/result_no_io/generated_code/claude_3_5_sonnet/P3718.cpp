#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 100005

char lights[MAX_N];
int n, k;

int check(int m) {
    int ops = 0;
    int count = 0;
    char current = 'X';
    
    for (int i = 0; i < n; i++) {
        if (lights[i] == current) {
            count++;
            if (count > m) {
                ops++;
                count = 1;
                current = (current == 'N') ? 'F' : 'N';
            }
        } else {
            count = 1;
            current = lights[i];
        }
    }
    
    return ops <= k;
}

int main() {
    scanf("%d %d", &n, &k);
    scanf("%s", lights);
    
    int left = 1, right = n;
    int result = n;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (check(mid)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    printf("%d\n", result);
    
    return 0;
}