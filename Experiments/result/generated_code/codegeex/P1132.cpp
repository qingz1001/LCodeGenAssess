#include <stdio.h>
#include <string.h>
#include <queue>
#include <map>

using namespace std;

int s, m;
int t[50005];
map<int, int> mp;
int a[7];

void bfs() {
    queue<int> q;
    q.push(s);
    mp[s] = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        int len = 0;
        int num = cur;
        while (num) {
            a[++len] = num % 10;
            num /= 10;
        }
        // 规则1：交换任意两位
        for (int i = 1; i < len; i++) {
            for (int j = i + 1; j <= len; j++) {
                swap(a[i], a[j]);
                int tmp = 0;
                for (int k = len; k; k--) {
                    tmp = tmp * 10 + a[k];
                }
                if (!mp.count(tmp)) {
                    mp[tmp] = mp[cur] + 1;
                    q.push(tmp);
                }
                swap(a[i], a[j]);
            }
        }
        // 规则2：删除任意一位
        for (int i = 1; i <= len; i++) {
            int tmp = 0;
            for (int j = 1; j < i; j++) {
                tmp = tmp * 10 + a[j];
            }
            for (int j = i + 1; j <= len; j++) {
                tmp = tmp * 10 + a[j];
            }
            if (!mp.count(tmp)) {
                mp[tmp] = mp[cur] + 1;
                q.push(tmp);
            }
        }
        // 规则3：在相邻两位之间插入一个数字
        for (int i = 1; i < len; i++) {
            for (int j = a[i] + 1; j < a[i + 1]; j++) {
                int tmp = 0;
                for (int k = len; k; k--) {
                    tmp = tmp * 10 + a[k];
                }
                tmp = tmp * 10 + j;
                if (!mp.count(tmp)) {
                    mp[tmp] = mp[cur] + 1;
                    q.push(tmp);
                }
            }
        }
    }
}

int main() {
    scanf("%d", &s);
    bfs();
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d", &t[i]);
        if (mp.count(t[i])) {
            printf("%d\n", mp[t[i]]);
        } else {
            printf("-1\n");
        }
    }
    return 0;
}