#include <stdio.h>
#include <stdlib.h>

#define MAXN 300

int parent[MAXN + 1][2]; // 存储每个妖怪的父母的索引
double similarity[MAXN + 1]; // 存储每个妖怪的基因相似程度

// 递归计算妖怪的基因相似程度
void calculate_similarity(int current) {
    if (similarity[current] != -1) return;
    if (parent[current][0] == 0 && parent[current][1] == 0) {
        similarity[current] = 0;
    } else {
        calculate_similarity(parent[current][0]);
        calculate_similarity(parent[current][1]);
        similarity[current] = (similarity[parent[current][0]] + similarity[parent[current][1]]) / 2;
    }
}

int main() {
    int n, k, m, a, b, c;
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) {
        similarity[i] = -1; // 初始化基因相似程度为-1，表示未计算
    }
    for (int i = 0; i < k; i++) {
        scanf("%d %d %d", &a, &b, &c);
        parent[a][0] = b;
        parent[a][1] = c;
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        if (similarity[a] == -1) calculate_similarity(a);
        if (similarity[b] == -1) calculate_similarity(b);
        printf("%.2lf%%\n", similarity[a] * 100);
    }
    return 0;
}