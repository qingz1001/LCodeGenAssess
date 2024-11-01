#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int index;
} Number;

int cmp_desc(const void* a, const void* b) {
    Number* na = (Number*)a;
    Number* nb = (Number*)b;
    return nb->value - na->value;
}

int cmp_asc(const void* a, const void* b) {
    return (*(int*)a) - (*(int*)b);
}

int main(){
    Number numbers[8];
    for(int i=0;i<8;i++){
        scanf("%d", &numbers[i].value);
        numbers[i].index = i+1;
    }
    qsort(numbers, 8, sizeof(Number), cmp_desc);
    int sum=0;
    int selected_indices[5];
    for(int i=0;i<5;i++){
        sum += numbers[i].value;
        selected_indices[i] = numbers[i].index;
    }
    qsort(selected_indices, 5, sizeof(int), cmp_asc);
    printf("%d\n", sum);
    for(int i=0;i<5;i++){
        printf("%d", selected_indices[i]);
        if(i<4) printf(" ");
    }
    printf("\n");
    return 0;
}