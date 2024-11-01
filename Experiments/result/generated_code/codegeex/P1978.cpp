#include <stdio.h>
#include <stdlib.h>

// 定义一个结构体来存储每个元素及其是否被标记
typedef struct {
    long long value;
    int marked;
} Element;

// 比较函数，用于qsort排序
int compare(const void *a, const void *b) {
    return (*(Element *)a).value - (*(Element *)b).value;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    Element *elements = (Element *)malloc(n * sizeof(Element));
    for (int i = 0; i < n; i++) {
        scanf("%lld", &elements[i].value);
        elements[i].marked = 0;
    }

    // 对元素进行排序
    qsort(elements, n, sizeof(Element), compare);

    int count = 0;
    for (int i = 0; i < n; i++) {
        if (!elements[i].marked) {
            count++;
            for (int j = i + 1; j < n; j++) {
                if (elements[j].value % elements[i].value == 0) {
                    elements[j].marked = 1;
                }
            }
        }
    }

    printf("%d\n", count);

    free(elements);
    return 0;
}