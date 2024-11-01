#include <stdio.h>
#include <string.h>

#define MAX_N 2000
#define MAX_LEN 30000

int n;
char viruses[MAX_N][MAX_LEN + 1];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", viruses[i]);
    }

    // 使用AC自动机进行匹配
    int root = 0, size = 1;
    int trie[MAX_LEN + 1][2], fail[MAX_LEN + 1];
    memset(trie, 0, sizeof(trie));
    memset(fail, 0, sizeof(fail));

    // 构建Trie树
    for (int i = 0; i < n; i++) {
        int node = root;
        for (int j = 0; j < strlen(viruses[i]); j++) {
            int ch = viruses[i][j] - '0';
            if (!trie[node][ch]) {
                trie[node][ch] = size++;
            }
            node = trie[node][ch];
        }
        fail[node] = -1; // 标记病毒节点
    }

    // 构建失败指针
    int queue[MAX_LEN + 1], front = 0, rear = 0;
    for (int i = 0; i < 2; i++) {
        if (trie[root][i]) {
            queue[rear++] = trie[root][i];
        }
    }
    while (front < rear) {
        int node = queue[front++];
        for (int i = 0; i < 2; i++) {
            if (trie[node][i]) {
                fail[trie[node][i]] = trie[fail[node]][i];
                queue[rear++] = trie[node][i];
            } else {
                trie[node][i] = trie[fail[node]][i];
            }
        }
    }

    // 判断是否存在无限长的安全代码
    int vis[MAX_LEN + 1];
    memset(vis, 0, sizeof(vis));
    int cur = root;
    while (cur != -1 && !vis[cur]) {
        vis[cur] = 1;
        cur = trie[cur][1];
    }
    if (cur == -1) {
        printf("TAK\n");
    } else {
        printf("NIE\n");
    }

    return 0;
}