#include <stdio.h>
#include <string.h>

#define MAX_A 201

int main(){
    char A[MAX_A];
    scanf("%s", A);
    int m = strlen(A);
    int lps[m];
    lps[0] = 0;
    for(int i=1;i<m;i++){
        int j = lps[i-1];
        while(j >0 && A[i] != A[j]){
            j = lps[j-1];
        }
        if(A[i]==A[j]){
            j++;
        }
        lps[i]=j;
    }
    int found = 0;
    long long pos =0;
    long long k =0;
    int current_lps =0;
    for(long long i=1;;i++){
        char num[20];
        sprintf(num, "%lld", i);
        int len = strlen(num);
        for(int d=0;d<len;d++){
            pos++;
            while(current_lps >0 && num[d] != A[current_lps]){
                current_lps = lps[current_lps-1];
            }
            if(num[d]==A[current_lps]){
                current_lps++;
            }
            if(current_lps == m){
                k = pos - m +1;
                printf("%lld\n", k);
                return 0;
            }
        }
        if(pos > 10000000){
            break;
        }
    }
    return 0;
}