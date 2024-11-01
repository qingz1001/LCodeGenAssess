#include <stdio.h>
#include <string.h>

#define MAX_N 200005

char s[MAX_N];
int n, k;

int check(int L) {
    int count = 0, last = -1;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            if (i > last) {
                count++;
                last = i + L - 1;
            }
        }
    }
    return count <= k;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &n, &k);
        scanf("%s", s);
        
        int left = 1, right = n, mid;
        while (left < right) {
            mid = left + (right - left) / 2;
            if (check(mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        
        printf("%d\n", left);
    }
    return 0;
}