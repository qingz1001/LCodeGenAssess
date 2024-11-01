#include <stdio.h>
#include <string.h>

#define MAXN 100005
#define MAXK 1000

int n, v[MAXN];
char s[MAXN];

struct Node {
    int l, r;
    int sum, rank;
};

Node nodes[MAXN * MAXK];

void update(int pos, int val) {
    for (nodes[pos].sum += val; pos > 0; pos >>= 1)
        nodes[pos >> 1].sum = nodes[pos].sum + nodes[pos ^ 1].sum;
}

int query(int left, int right) {
    int res = 0;
    for (; left <= right; left++, right--) {
        if ((left & 1))
            res += nodes[left++].sum;
        if (!(right & 1))
            res += nodes[right--].sum;
    }
    return res;
}

int main() {
    scanf("%s", s);
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &v[i]);

    memset(nodes, 0, sizeof(nodes));
    for (int i = 0; i < n; i++) {
        int rank = 0;
        for (int j = i; j >= 0; j--) {
            if (j == i || s[j] < s[j + 1])
                rank++;
            else
                break;
        }
        nodes[i * MAXK + rank] = (Node){i, i, v[i], rank};
        update(i * MAXK + rank, 1);
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int sum = query(i, j);
            int rank = 0;
            for (int k = j; k >= i; k--) {
                if (k == j || s[k] < s[k + 1])
                    rank++;
                else
                    break;
            }
            if (sum == rank) {
                ans++;
                printf("%d %d\n", i + 1, j + 1);
            }
        }
    }

    printf("%d\n", ans);

    return 0;
}