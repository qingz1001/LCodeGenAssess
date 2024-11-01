#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b){
    int val_a = *(int*)a;
    int val_b = *(int*)b;
    if(val_a < val_b) return -1;
    else if(val_a > val_b) return 1;
    else return 0;
}

int lower_bound(int a[], int m, int b){
    int left = 0, right = m;
    while(left < right){
        int mid = left + (right - left) / 2;
        if(a[mid] < b){
            left = mid + 1;
        }
        else{
            right = mid;
        }
    }
    return left;
}

int main(){
    int m, n;
    if(scanf("%d %d", &m, &n)!=2) return 0;
    int *a = (int*)malloc(sizeof(int)*m);
    for(int i=0;i<m;i++) scanf("%d", &a[i]);
    qsort(a, m, sizeof(int), compare);
    long long sum =0;
    for(int i=0;i<n;i++){
        int b;
        scanf("%d", &b);
        int pos = lower_bound(a, m, b);
        int diff;
        if(pos ==0){
            diff = abs(a[0] - b);
        }
        else if(pos ==m){
            diff = abs(a[m-1] - b);
        }
        else{
            int diff1 = abs(a[pos] - b);
            int diff2 = abs(a[pos-1] - b);
            diff = diff1 < diff2 ? diff1 : diff2;
        }
        sum += diff;
    }
    printf("%lld\n", sum);
    free(a);
    return 0;
}