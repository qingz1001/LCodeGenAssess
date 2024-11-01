#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Pair;

int cmp(const void *x, const void *y){
    Pair *p1 = (Pair *)x;
    Pair *p2 = (Pair *)y;
    if(p1->a != p2->a)
        return p1->a - p2->a;
    return p1->b - p2->b;
}

int main(){
    int n;
    scanf("%d", &n);
    Pair *arr = (Pair *)malloc(n * sizeof(Pair));
    for(int i=0;i<n;i++) {
        scanf("%d %d", &arr[i].a, &arr[i].b);
    }
    qsort(arr, n, sizeof(Pair), cmp);
    long long liars = 0;
    int i=0;
    while(i < n){
        int current_a = arr[i].a;
        int current_b = arr[i].b;
        int count = 1;
        i++;
        while(i < n && arr[i].a == current_a && arr[i].b == current_b){
            count++;
            i++;
        }
        long long s_i = (long long)n - (long long)current_a - (long long)current_b;
        if(s_i <=0){
            liars += count;
        }
        else{
            if(count >= s_i){
                liars += (count - s_i);
            }
            else{
                liars += count;
            }
        }
    }
    printf("%lld\n", liars);
    free(arr);
    return 0;
}