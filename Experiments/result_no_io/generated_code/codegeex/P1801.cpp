#include <stdio.h>
#include <stdlib.h>

// 定义一个结构体来存储数组元素及其原始索引
typedef struct {
    int value;
    int index;
} Element;

// 比较函数，用于qsort排序
int compare(const void *a, const void *b) {
    Element *elementA = (Element *)a;
    Element *elementB = (Element *)b;
    if (elementA->value < elementB->value) {
        return -1;
    } else if (elementA->value > elementB->value) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    Element *array = (Element *)malloc(m * sizeof(Element));
    int *queries = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < m; i++) {
        scanf("%d", &array[i].value);
        array[i].index = i;
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &queries[i]);
    }

    // 对数组进行排序
    qsort(array, m, sizeof(Element), compare);

    // 处理每个查询
    for (int i = 0; i < n; i++) {
        int getIndex = queries[i];
        int outputIndex = array[getIndex - 1].index;
        printf("%d\n", outputIndex);
    }

    free(array);
    free(queries);
    return 0;
}