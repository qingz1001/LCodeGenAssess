#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int a;
    int b;
} Pair;

int cmp(const void *x, const void *y){
    Pair *p1 = (Pair*)x;
    Pair *p2 = (Pair*)y;
    if(p1->b != p2->b)
        return p1->b - p2->b;
    return p1->a - p2->a;
}

int main(){
    int n, m;
    scanf("%d", &n);
    scanf("%d", &m);
    int max_S = 2 * m * m;
    int size = (max_S / 8) + 2;
    unsigned char *S_bit = (unsigned char*)calloc(size, sizeof(unsigned char));
    if(!S_bit){
        return 1;
    }
    for(int p=0; p<=m; p++){
        int p2 = p*p;
        for(int q=0; q<=m; q++){
            int val = p2 + q*q;
            S_bit[val / 8] |= (1 << (val % 8));
        }
    }
    // Collect all possible a and b
    int capacity = 10000;
    Pair *pairs = (Pair*)malloc(sizeof(Pair)*capacity);
    if(!pairs){
        free(S_bit);
        return 1;
    }
    int count = 0;
    for(int a=0; a<=max_S; a++){
        // Check if a is in S
        if( (S_bit[a / 8] & (1 << (a % 8))) ){
            // Compute max b
            int max_b = (max_S - a)/(n-1);
            for(int b=1; b<=max_b; b++){
                int valid = 1;
                for(int k=0; k<n; k++){
                    int val = a + k*b;
                    if(val > max_S || !(S_bit[val / 8] & (1 << (val % 8)))){
                        valid = 0;
                        break;
                    }
                }
                if(valid){
                    if(count >= capacity){
                        capacity *=2;
                        pairs = realloc(pairs, sizeof(Pair)*capacity);
                        if(!pairs){
                            free(S_bit);
                            return 1;
                        }
                    }
                    pairs[count].a = a;
                    pairs[count].b = b;
                    count++;
                }
            }
        }
    }
    free(S_bit);
    if(count == 0){
        printf("NONE\n");
    }
    else{
        qsort(pairs, count, sizeof(Pair), cmp);
        for(int i=0; i<count && i < 10000; i++){
            printf("%d %d\n", pairs[i].a, pairs[i].b);
        }
    }
    free(pairs);
    return 0;
}