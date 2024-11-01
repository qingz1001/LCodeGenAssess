#include <stdio.h>
#include <string.h>

// 比较两个字符串的字典序
int compare(const char *a, const char *b) {
    return strcmp(a, b);
}

// 计算 Q(N, K)
int calculateQ(int N, int K) {
    char num[11];
    char kStr[11];
    sprintf(kStr, "%d", K);
    int count = 0;

    for (int i = 1; i <= N; i++) {
        sprintf(num, "%d", i);
        if (compare(num, kStr) < 0) {
            count++;
        }
    }

    return count + 1;
}

// 找到最小的 N 使得 Q(N, K) = M
int findMinN(int K, int M) {
    int low = K;
    int high = 1000000000; // 假设一个足够大的上限
    int mid;

    while (low < high) {
        mid = (low + high) / 2;
        if (calculateQ(mid, K) < M) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    if (calculateQ(low, K) == M) {
        return low;
    } else {
        return 0;
    }
}

int main() {
    int K, M;
    scanf("%d %d", &K, &M);

    int result = findMinN(K, M);
    printf("%d\n", result);

    return 0;
}