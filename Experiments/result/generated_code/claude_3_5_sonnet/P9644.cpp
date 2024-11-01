#include <stdio.h>
#include <string.h>

#define MAX_N 200005

int n, k;
char s[MAX_N];

int check(int L) {
    int count = 0;
    int i = 0;
    while (i < n) {
        while (i < n && s[i] == '0') i++;
        if (i < n) {
            count++;
            i += L;
        }
    }
    return count <= k;
}

int solve() {
    int left = 1, right = n;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (check(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &n, &k);
        scanf("%s", s);
        printf("%d\n", solve());
    }
    return 0;
}