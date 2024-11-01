#include <stdio.h>
#include <string.h>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, k;
        scanf("%d %d", &n, &k);
        char s[200001];
        scanf("%s", s);

        int left = 1, right = n, result = 0;
        while (left <= right) {
            int mid = (left + right) / 2;
            int count = 0;
            int i = 0;
            while (i < n) {
                if (s[i] == '1') {
                    count++;
                    i += mid;
                } else {
                    i++;
                }
            }
            if (count <= k) {
                result = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        printf("%d\n", result);
    }
    return 0;
}