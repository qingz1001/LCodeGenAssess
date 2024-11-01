#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 10001
#define MAXM 10001

char carNames[MAXN][256];
int n, m;

// 检查字符串s是否是某个车名的前缀
int isPrefix(char *s, char *carName) {
    int lenS = strlen(s);
    int lenCarName = strlen(carName);
    if (lenS > lenCarName) return 0;
    for (int i = 0; i < lenS; i++) {
        if (s[i] != carName[i]) return 0;
    }
    return 1;
}

// 计算韵韵能玩的次数
int countGames(char **queries, int m) {
    int count = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (isPrefix(queries[i], carNames[j])) {
                count++;
                break;
            }
        }
    }
    return count;
}

// 计算可能的排列数
int countPermutations() {
    int count = 0;
    // 第1辆车的位置不可能是0
    count++;
    // 第n辆车的位置不可能是n+1
    count++;
    // 剩余n-2辆车可以任意摆放
    count *= (n - 2);
    return count;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", carNames[i]);
    }

    char **queries = (char **)malloc(m * sizeof(char *));
    for (int i = 0; i < m; i++) {
        queries[i] = (char *)malloc(256 * sizeof(char));
        scanf("%s", queries[i]);
    }

    int gamesCount = countGames(queries, m);
    int permutationsCount = countPermutations();

    printf("%d\n%d\n", gamesCount, permutationsCount);

    for (int i = 0; i < m; i++) {
        free(queries[i]);
    }
    free(queries);

    return 0;
}