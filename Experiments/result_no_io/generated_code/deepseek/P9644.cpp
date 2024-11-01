#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAXN 200005

int n, k;
char s[MAXN];

bool canTurnOff(int L) {
    int operations = 0;
    int i = 0;
    while (i < n) {
        if (s[i] == '1') {
            operations++;
            if (operations > k) return false;
            i += L;
        } else {
            i++;
        }
    }
    return true;
}

int findMinL() {
    int left = 1, right = n;
    while (left < right) {
        int mid = (left + right) / 2;
        if (canTurnOff(mid)) {
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
        printf("%d\n", findMinL());
    }
    return 0;
}