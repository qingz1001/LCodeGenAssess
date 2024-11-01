#include <stdio.h>
#include <stdlib.h>

long long numbers[200000];

int cmp(const void *a, const void *b){
    long long x = *(long long*)a;
    long long y = *(long long*)b;
    if(x < y) return -1;
    else if(x > y) return 1;
    else return 0;
}

int main(){
    int n;
    scanf("%d", &n);
    for(int i=0;i<n;i++) {
        scanf("%lld", &numbers[i]);
    }
    qsort(numbers, n, sizeof(long long), cmp);
    long long current = numbers[0];
    int count =1;
    for(int i=1;i<n;i++){
        if(numbers[i] == current){
            count++;
        }
        else{
            printf("%lld %d\n", current, count);
            current = numbers[i];
            count =1;
        }
    }
    printf("%lld %d\n", current, count);
    return 0;
}