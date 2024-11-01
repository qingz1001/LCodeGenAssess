#include <stdio.h>

// 定义一个结构体来存储数组元素及其索引
typedef struct {
    long long value;
    int index;
} Pair;

// 快速排序的比较函数
int compare(const void *a, const void *b) {
    Pair *pa = (Pair *)a;
    Pair *pb = (Pair *)b;
    return (pa->value > pb->value) - (pa->value < pb->value);
}

int main() {
    int n;
    scanf("%d", &n);

    Pair arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%lld", &arr[i].value);
        arr[i].index = i;
    }

    // 对数组进行排序
    qsort(arr, n, sizeof(Pair), compare);

    // 计算逆序对的数量
    long long ans = 0;
    long long count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i].index < i) {
            count += i - arr[i].index;
        }
    }

    printf("%lld\n", count);
    return 0;
}