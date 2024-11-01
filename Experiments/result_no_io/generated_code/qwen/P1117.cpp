#include <stdio.h>
#include <string.h>

#define MAXN 30005

int T;
char S[MAXN];

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%s", S);
        int n = strlen(S);
        long long ans = 0;

        for (int len = 1; len <= n; len++) {
            for (int i = 0; i + len * 2 - 1 < n; i++) {
                int mid = i + len;
                if (S[mid] == S[mid + len]) {
                    int cntA = 0, cntB = 0;
                    for (int j = i; j < mid; j++) {
                        if (S[j] == S[i])
                            cntA++;
                        else
                            cntB++;
                    }
                    if (cntA > 0 && cntB > 0)
                        ans += cntA * cntB;
                }
            }
        }

        printf("%lld\n", ans);
    }
    return 0;
}