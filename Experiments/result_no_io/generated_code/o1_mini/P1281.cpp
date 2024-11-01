#include <stdio.h>
#include <stdlib.h>

long long max(long long a, long long b){
    return a > b ? a : b;
}

long long min(long long a, long long b){
    return a < b ? a : b;
}

int main(){
    int m, k;
    scanf("%d %d", &m, &k);
    long long pages[m+1];
    for(int i=1;i<=m;i++) scanf("%lld", &pages[i]);
    
    long long left = pages[1], right = 0;
    for(int i=1;i<=m;i++){
        if(pages[i] > left) left = pages[i];
        right += pages[i];
    }
    
    // Binary search to find minimal maximum
    while(left < right){
        long long mid = left + (right - left)/2;
        long long sum = 0;
        int cnt = 1;
        for(int i=1;i<=m;i++){
            if(sum + pages[i] > mid){
                cnt++;
                sum = pages[i];
            }
            else{
                sum += pages[i];
            }
        }
        if(cnt <= k) right = mid;
        else left = mid +1;
    }
    
    // Now assign the books
    long long threshold = left;
    int start[m+1];
    int endk[m+1];
    for(int i=1;i<=m;i++) start[i] = 0;
    for(int i=1;i<=m;i++) endk[i] = 0;
    
    int person = k;
    long long sum =0;
    for(int i=m;i>=1;i--){
        if(sum + pages[i] > threshold || i < person){
            endk[person] = m - (m - i);
            start[person] = i;
            m = i-1;
            person--;
            sum = pages[i];
        }
        else{
            sum += pages[i];
        }
    }
    for(int i=1;i<=k;i++){
        if(endk[i]==0){
            endk[i] = m;
            start[i] = m;
        }
        printf("%d %d\n", start[i], endk[i]);
    }
    return 0;
}