#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b){
    int ia = *(int*)a;
    int ib = *(int*)b;
    if(ia < ib) return -1;
    else if(ia > ib) return 1;
    else return 0;
}

int main(){
    int A, B, N;
    scanf("%d", &A);
    scanf("%d", &B);
    scanf("%d", &N);
    
    int initial[] = {0,990,1010,1970,2030,2940,3060,3930,4060,4970,5030,5990,6010,7000};
    int total = 14 + N;
    int motels[34];
    for(int i=0;i<14;i++) motels[i]=initial[i];
    for(int i=14;i<14+N;i++) scanf("%d", &motels[i]);
    
    qsort(motels, 14+N, sizeof(int), compare);
    
    // Remove duplicates
    int unique[34];
    int count = 0;
    unique[count++] = motels[0];
    for(int i=1;i<14+N;i++) {
        if(motels[i] != unique[count-1]){
            unique[count++] = motels[i];
        }
    }
    
    // Find index of 7000
    int end = -1;
    for(int i=0;i<count;i++) if(unique[i]==7000){end=i; break;}
    if(end==-1){
        printf("0");
        return 0;
    }
    
    unsigned long long dp[34];
    for(int i=0;i<count;i++) dp[i]=0;
    dp[0]=1;
    
    for(int i=0;i<count;i++){
        for(int j=i+1;j<count;j++){
            int dist = unique[j] - unique[i];
            if(dist < A) continue;
            if(dist > B) continue;
            dp[j] += dp[i];
        }
    }
    
    printf("%llu", dp[end]);
    return 0;
}