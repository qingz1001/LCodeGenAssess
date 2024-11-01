#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_C 100001

int main(){
    int N, L;
    scanf("%d %d", &N, &L);
    int *freq = (int*)calloc(MAX_C +1, sizeof(int));
    int c;
    for(int i=0;i<N;i++){
        scanf("%d", &c);
        if(c <= MAX_C){
            freq[c]++;
        }
    }
    // Build suffix sum
    long long *suffix = (long long*)calloc(MAX_C +2, sizeof(long long));
    for(int h=MAX_C; h>=0; h--){
        suffix[h] = freq[h] + suffix[h+1];
    }
    // Binary search
    int low=0, high=MAX_C + L, mid, answer=0;
    while(low <= high){
        mid = low + (high - low)/2;
        long long A;
        if(mid <= MAX_C){
            A = suffix[mid];
        }
        else{
            A =0;
        }
        long long B = (mid-1 >=0 && mid-1 <= MAX_C) ? freq[mid-1] : 0;
        long long total = A + (B < L ? B : L);
        if(total >= mid){
            answer = mid;
            low = mid +1;
        }
        else{
            high = mid -1;
        }
    }
    printf("%d\n", answer);
    free(freq);
    free(suffix);
    return 0;
}