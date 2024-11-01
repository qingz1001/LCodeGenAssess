#include <stdio.h>
#include <stdlib.h>

#define MAX_C 100001

int main(){
    int N, L;
    scanf("%d %d", &N, &L);
    int *freq = (int*)calloc(MAX_C+1, sizeof(int));
    int c;
    for(int i=0;i<N;i++){
        scanf("%d", &c);
        if(c <= MAX_C)
            freq[c]++;
        else
            freq[MAX_C]++;
    }
    // Compute suff[c] = number of papers with citation >=c
    int *suff = (int*)calloc(MAX_C+2, sizeof(int));
    suff[MAX_C+1] = 0;
    for(int i=MAX_C;i>=0;i--){
        suff[i] = suff[i+1] + freq[i];
    }
    // Binary search for h
    int left =0, right = N + L;
    while(left < right){
        int mid = left + (right - left +1)/2;
        if(mid > MAX_C+1){
            // suff[mid] =0
            // Check if 0 + something >=mid, likely false
            // So set right = mid -1
            right = mid -1;
            continue;
        }
        int A = (mid <= MAX_C) ? suff[mid] : 0;
        int B = (mid-1 >=0 && mid-1 <= MAX_C) ? freq[mid-1] :0;
        if(A >= mid){
            left = mid;
        }
        else{
            // Compute min(B, L)
            int add = (B < L) ? B : L;
            if(A + add >= mid){
                left = mid;
            }
            else{
                right = mid -1;
            }
        }
    }
    printf("%d\n", left);
    free(freq);
    free(suff);
    return 0;
}