#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_LEN 1005
#define MAX_MOD 51

int dp_min[MAX_LEN][MAX_MOD];
int dp_max[MAX_LEN][MAX_MOD];

int main() {
    char num[MAX_LEN];
    int m;
    scanf("%s%d", num, &m);

    int len = strlen(num);
    memset(dp_min, 0x3f, sizeof(dp_min));
    memset(dp_max, -1, sizeof(dp_max));
    dp_min[0][0] = dp_max[0][0] = 0;

    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < i; ++j) {
            long long product = 0;
            for (int k = j + 1; k <= i; ++k) {
                product = product * 10 + (num[k] - '0');
                if (product >= m) break;
                for (int mod = 0; mod < m; ++mod) {
                    int new_mod_min = (dp_min[j][mod] * product) % m;
                    int new_mod_max = (dp_max[j][mod] * product) % m;
                    dp_min[i + 1][new_mod_min] = new_mod_min;
                    dp_max[i + 1][new_mod_max] = new_mod_max;
                }
            }
        }
        for (int mod = 0; mod < m; ++mod) {
            int new_mod = (dp_min[i][mod] * 10 + num[i + 1] - '0') % m;
            dp_min[i + 1][new_mod] = new_mod;
            new_mod = (dp_max[i][mod] * 10 + num[i + 1] - '0') % m;
            dp_max[i + 1][new_mod] = new_mod;
        }
    }

    int min_mod = INT_MAX, min_k = INT_MAX;
    int max_mod = 0, max_k = INT_MAX;

    for (int mod = 0; mod < m; ++mod) {
        if (dp_min[len][mod] < min_mod) {
            min_mod = dp_min[len][mod];
            min_k = len - 1;
        } else if (dp_min[len][mod] == min_mod) {
            min_k = len - 1;
        }
        if (dp_max[len][mod] > max_mod) {
            max_mod = dp_max[len][mod];
            max_k = len - 1;
        } else if (dp_max[len][mod] == max_mod) {
            max_k = len - 1;
        }
    }

    printf("%d %d %d %d\n", min_mod, min_k, max_mod, max_k);
    return 0;
}