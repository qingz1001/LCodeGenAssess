#include <stdio.h>
#include <stdlib.h>

int main(){
    int n, A, B, C;
    unsigned int a0;
    if(scanf("%d %d %d %d %u", &n, &A, &B, &C, &a0)!=5){
        return 1;
    }
    unsigned int* a = (unsigned int*)malloc((n+1) * sizeof(unsigned int));
    if(a == NULL){
        return 1;
    }
    a[1] = a0 % C + 1;
    for(int i=2;i<=n;i++){
        a[i] = ((unsigned long long)a[i-1] * A + B) % 100000001;
        a[i] = a[i] % C + 1;
    }
    double sum=0.0;
    unsigned int last = a[n];
    for(int j=1; j<=n; j++){
        unsigned int gx_ans = (j ==1) ? last : a[j-1];
        if(gx_ans <= a[j]){
            sum += 1.0 / (double)a[j];
        }
    }
    printf("%.3lf\n", sum);
    free(a);
    return 0;
}