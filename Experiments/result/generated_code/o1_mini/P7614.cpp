#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int index;
} Number;

// Comparator for descending order
int cmp_desc(const void *a, const void *b){
    Number *n1 = (Number*)a;
    Number *n2 = (Number*)b;
    if(n2->value != n1->value)
        return n2->value - n1->value;
    else
        return n1->index - n2->index;
}

int cmp_asc(const void *a, const void *b){
    return (*(int*)a - *(int*)b);
}

int main(){
    Number nums[8];
    for(int i=0;i<8;i++){
        scanf("%d", &nums[i].value);
        nums[i].index = i+1;
    }
    qsort(nums,8,sizeof(Number), cmp_desc);
    int sum=0;
    int selected[5];
    for(int i=0;i<5;i++){
        sum += nums[i].value;
        selected[i] = nums[i].index;
    }
    qsort(selected,5,sizeof(int), cmp_asc);
    printf("%d\n", sum);
    for(int i=0;i<5;i++){
        printf("%d%c", selected[i], i<4?' ':'\n');
    }
    return 0;
}