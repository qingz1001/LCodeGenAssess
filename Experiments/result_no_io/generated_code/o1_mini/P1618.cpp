#include <stdio.h>
#include <stdlib.h>

struct triple {
    int n1, n2, n3;
};

int compare(const void *a, const void *b) {
    struct triple *ta = (struct triple *)a;
    struct triple *tb = (struct triple *)b;
    if (ta->n1 != tb->n1)
        return ta->n1 - tb->n1;
    if (ta->n2 != tb->n2)
        return ta->n2 - tb->n2;
    return ta->n3 - tb->n3;
}

int main(){
    int A, B, C;
    if(scanf("%d %d %d", &A, &B, &C)!=3){
        return 0;
    }

    // Calculate k_min and k_max
    int k_min = 1;
    int k_max = 999;

    // Ceiling division for k_min
    int tmp = (100 + A -1)/A;
    if(tmp > k_min) k_min = tmp;
    tmp = (100 + B -1)/B;
    if(tmp > k_min) k_min = tmp;
    tmp = (100 + C -1)/C;
    if(tmp > k_min) k_min = tmp;

    // Floor division for k_max
    tmp = 999 / A;
    if(tmp < k_max) k_max = tmp;
    tmp = 999 / B;
    if(tmp < k_max) k_max = tmp;
    tmp = 999 / C;
    if(tmp < k_max) k_max = tmp;

    struct triple solutions[1000];
    int count =0;

    for(int k = k_min; k <= k_max; k++){
        int n1 = k*A;
        int n2 = k*B;
        int n3 = k*C;

        // Check if all numbers are three-digit
        if(n1 < 100 || n1 > 999 || n2 < 100 || n2 > 999 || n3 < 100 || n3 > 999)
            continue;

        int mask =0;
        int valid =1;
        int nums[3] = {n1, n2, n3};
        for(int i=0;i<3 && valid;i++){
            int num = nums[i];
            for(int j=0; j<3 && valid; j++){
                int digit = num %10;
                if(digit ==0 || (mask & (1 << digit))){
                    valid =0;
                }
                mask |= (1 << digit);
                num /=10;
            }
        }
        if(valid && mask == 0x3FE){
            solutions[count].n1 = n1;
            solutions[count].n2 = n2;
            solutions[count].n3 = n3;
            count++;
        }
    }

    if(count ==0){
        printf("No!!!");
        return 0;
    }

    qsort(solutions, count, sizeof(struct triple), compare);

    for(int i=0;i<count;i++){
        printf("%d %d %d\n", solutions[i].n1, solutions[i].n2, solutions[i].n3);
    }

    return 0;
}