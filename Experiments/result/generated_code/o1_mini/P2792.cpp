#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    scanf("%d", &n);
    int *c = (int*)malloc(n * sizeof(int));
    int *m = (int*)malloc(n * sizeof(int));
    double temp;
    for(int i=0;i<n;i++){
        double ci;
        int mi;
        scanf("%lf %d", &ci, &mi);
        c[i] = (int)(ci * 100 + 0.5);
        m[i] = mi;
    }
    int k;
    scanf("%d", &k);
    // Since n <=50 and k<=500, we can store discounts in arrays
    int *A = (int*)malloc(k * sizeof(int));
    int *B = (int*)malloc(k * sizeof(int));
    int *P = (int*)malloc(k * sizeof(int));
    for(int i=0;i<k;i++){
        int a, b;
        double p;
        scanf("%d %d %lf", &a, &b, &p);
        A[i] = a-1; // 0-based index
        B[i] = b-1;
        P[i] = (int)(p * 100 + 0.5);
    }
    long long total =0;
    for(int i=0;i<n;i++){
        if(m[i] >0){
            int min_price = c[i];
            for(int j=0;j<k;j++){
                if(B[j]==i && m[A[j]] >0){
                    if(P[j] < min_price){
                        min_price = P[j];
                    }
                }
            }
            total += (long long)m[i] * min_price;
        }
    }
    printf("%.2lf\n", total / 100.0);
    free(c);
    free(m);
    free(A);
    free(B);
    free(P);
    return 0;
}