#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXLEN 1100000
#define MAXSTATES (2 * MAXLEN + 5)

typedef struct State {
    int len;
    int link;
    int next[2];
} State;

State st[MAXSTATES];
int sz, last;

void sa_init() {
    st[0].len = 0;
    st[0].link = -1;
    st[0].next[0] = st[0].next[1] = -1;
    sz = 1;
    last = 0;
}

void sa_extend(char c) {
    int c_int = c - '0';
    int curr = sz++;
    st[curr].len = st[last].len + 1;
    st[curr].next[0] = st[curr].next[1] = -1;
    int p = last;
    while (p != -1 && st[p].next[c_int] == -1) {
        st[p].next[c_int] = curr;
        p = st[p].link;
    }
    if (p == -1) {
        st[curr].link = 0;
    }
    else {
        int q = st[p].next[c_int];
        if (st[p].len + 1 == st[q].len) {
            st[curr].link = q;
        }
        else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            st[clone].link = st[q].link;
            st[clone].next[0] = st[q].next[0];
            st[clone].next[1] = st[q].next[1];
            while (p != -1 && st[p].next[c_int] == q) {
                st[p].next[c_int] = clone;
                p = st[p].link;
            }
            st[q].link = st[curr].link = clone;
        }
    }
    last = curr;
}

char buffer[MAXLEN + 5];
int m, n;

int main(){
    // Initialize Suffix Automaton
    sa_init();
    // Read N and M
    if(scanf("%d %d", &n, &m)!=2){
        return 0;
    }
    // Read M standard strings and build SAM
    for(int i=0;i<m;i++){
        if(scanf("%s", buffer)!=1){
            return 0;
        }
        last = 0;
        int len = strlen(buffer);
        for(int j=0; j<len; j++){
            sa_extend(buffer[j]);
        }
    }
    // Allocate memory for dp
    // To handle up to 1e6, use dynamic allocation
    int *dp = (int*)malloc((MAXLEN + 2) * sizeof(int));
    // Process N strings
    for(int test=0; test<n; test++){
        if(scanf("%s", buffer)!=1){
            free(dp);
            return 0;
        }
        int lenA = strlen(buffer);
        // Compute m[i]: max match length ending at i
        int *m_i = (int*)malloc((lenA + 2) * sizeof(int));
        int current = 0;
        int current_len = 0;
        for(int i=0; i<lenA; i++){
            int c = buffer[i] - '0';
            if(st[current].next[c] != -1){
                current = st[current].next[c];
                current_len++;
            }
            else{
                while(current != -1 && st[current].next[c] == -1){
                    current = st[current].link;
                }
                if(current == -1){
                    current = 0;
                    current_len = 0;
                }
                else{
                    current_len = st[current].len + 1;
                    current = st[current].next[c];
                }
            }
            m_i[i+1] = current_len;
        }
        // Binary search for L0
        int left = 1, right = lenA, L0 = 0;
        while(left <= right){
            int mid = left + (right - left) / 2;
            // DP to check if sum of familiar substrings >= ceil(0.9 * lenA)
            // Initialize dp
            dp[0] = 0;
            for(int i=1; i<=lenA; i++){
                dp[i] = dp[i-1];
                if(m_i[i] >= mid){
                    int k = m_i[i];
                    if(k > i) k = i;
                    if(k >= mid){
                        if(dp[i - k] + k > dp[i]){
                            dp[i] = dp[i - k] + k;
                        }
                    }
                }
            }
            // Calculate required sum
            int required = (lenA * 9) / 10;
            if((lenA * 9) % 10 != 0){
                required +=1;
            }
            if(dp[lenA] >= required){
                L0 = mid;
                left = mid +1;
            }
            else{
                right = mid -1;
            }
        }
        printf("%d\n", L0);
        free(m_i);
    }
    free(dp);
    return 0;
}