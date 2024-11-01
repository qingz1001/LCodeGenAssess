#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b){
    int x = *(int*)a;
    int y = *(int*)b;
    if(x < y) return -1;
    if(x > y) return 1;
    return 0;
}

int main(){
    int m, n;
    scanf("%d %d", &m, &n);
    int *a = (int*)malloc(m * sizeof(int));
    for(int i = 0; i < m; i++) scanf("%d", &a[i]);
    qsort(a, m, sizeof(int), cmp);
    long long sum = 0;
    for(int i = 0; i < n; i++){
        int b;
        scanf("%d", &b);
        int left = 0, right = m -1, best = a[0];
        while(left <= right){
            int mid = left + (right - left)/2;
            if(a[mid] == b){
                best = a[mid];
                break;
            }
            if(a[mid] < b){
                left = mid +1;
            }
            else{
                right = mid -1;
            }
        }
        if(a[left-1] == b || left >= m){
            best = a[left-1];
        }
        else{
            if(left < m){
                if(abs(a[left] - b) < abs(a[left-1] - b)){
                    best = a[left];
                }
                else{
                    best = a[left-1];
                }
            }
            else{
                best = a[left-1];
            }
        }
        sum += abs((long long)best - (long long)b);
    }
    printf("%lld\n", sum);
    free(a);
    return 0;
}