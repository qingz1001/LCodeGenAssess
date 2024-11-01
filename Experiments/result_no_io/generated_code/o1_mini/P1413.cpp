#include<stdio.h>
#include<stdlib.h>

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
    long long rows[6][2000];
    int counts[6] = {0};
    for(int i=0;i<n;i++){
        int p;
        long long t;
        scanf("%d %lld", &p, &t);
        rows[p-1][counts[p-1]++] = t + 59;
    }
    int total =0;
    for(int i=0;i<6;i++){
        if(counts[i]==0) continue;
        qsort(rows[i], counts[i], sizeof(long long), cmp);
        long long last = -1;
        for(int j=0;j<counts[i];j++){
            if(rows[i][j] > last){
                total++;
                last = rows[i][j];
            }
        }
    }
    printf("%d", total);
}