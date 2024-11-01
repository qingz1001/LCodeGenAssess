#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool canTurnOffAllLights(int n, int k, int L, const char *s) {
    int operations = 0;
    for (int i = 0; i < n; ) {
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

int findMinL(int n, int k, const char *s) {
    int left = 1, right = n, mid;
    while (left < right) {
        mid = (left + right) / 2;
        if (canTurnOffAllLights(n, k, mid, s)) {
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
        int n, k;
        scanf("%d %d", &n, &k);
        char s[200001];
        scanf("%s", s);
        printf("%d\n", findMinL(n, k, s));
    }
    return 0;
}