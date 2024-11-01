#include <stdio.h>
#include <stdint.h>

typedef long long ll;

// Function to compute integer square root using binary search
ll integer_sqrt(ll t){
    if(t ==0) return 0;
    ll l=0, r=300000;
    ll res=0;
    while(l <= r){
        ll m = l + (r - l) / 2;
        ll m_sq = m * m;
        if(m_sq == t){
            return m;
        }
        if(m_sq < t){
            res = m;
            l = m +1;
        }
        else{
            r = m -1;
        }
    }
    return res;
}

int main(){
    int N;
    scanf("%d", &N);
    // Allocate output buffer: each output is '0\n' or '1\n'
    // Maximum N=1.5e6, so buffer size 3*N to be safe
    char *output = (char*)malloc(3LL*N +1);
    int pos =0;
    for(int i=0;i<N;i++){
        ll A;
        scanf("%lld", &A);
        if(A ==1){
            output[pos++] = '1';
            output[pos++] = '\n';
            continue;
        }
        ll t = 8*(A-1) +1;
        ll s = integer_sqrt(t);
        if(s*s == t){
            output[pos++] = '1';
            output[pos++] = '\n';
        }
        else{
            output[pos++] = '0';
            output[pos++] = '\n';
        }
    }
    fwrite(output, sizeof(char), pos, stdout);
    free(output);
    return 0;
}