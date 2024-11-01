#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long ull;

int cmp_ull(const void* a, const void* b) {
    ull aa = *(ull*)a;
    ull bb = *(ull*)b;
    if (aa < bb) return -1;
    else if (aa > bb) return 1;
    else return 0;
}

int upper_bound_ull(ull* arr, int n, ull key) {
    int left = 0, right = n;
    while(left < right){
        int mid = left + (right - left) / 2;
        if(arr[mid] > key){
            right = mid;
        }
        else{
            left = mid + 1;
        }
    }
    return left;
}

int main(){
    int n, m;
    if(scanf("%d %d", &n, &m)!=2){
        return 1;
    }
    ull *A = (ull*)malloc(sizeof(ull)*n);
    ull *B = (ull*)malloc(sizeof(ull)*n);
    for(int i=0;i<n;i++){
        ull a, b;
        if(scanf("%llu %llu", &a, &b)!=2){
            return 1;
        }
        A[i] = a;
        B[i] = a + b;
    }
    qsort(A, n, sizeof(ull), cmp_ull);
    qsort(B, n, sizeof(ull), cmp_ull);
    for(int i=0;i<m;i++){
        ull x, y;
        if(scanf("%llu %llu", &x, &y)!=2){
            return 1;
        }
        ull l = x;
        ull r = x + y;
        int cnt1 = upper_bound_ull(A, n, r);
        int cnt2 = upper_bound_ull(B, n, x);
        printf("%d\n", cnt1 - cnt2);
    }
    free(A);
    free(B);
    return 0;
}