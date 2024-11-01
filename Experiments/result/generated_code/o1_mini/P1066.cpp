#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Maximum n and m
#define MAX_N 512
#define MAX_M 512
// Maximum digits for combinations and sum
#define MAX_DIGITS 205
#define SUM_DIGITS 400

// Function to add two numeric strings a and b, store result in res
void add_strings(const char *a, const char *b, char *res) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    int carry = 0;
    int i = len_a - 1;
    int j = len_b - 1;
    int pos = 0;
    char tmp[SUM_DIGITS];

    while(i >=0 || j >=0 || carry){
        int digit_a = (i >=0) ? a[i]-'0' : 0;
        int digit_b = (j >=0) ? b[j]-'0' : 0;
        int sum = digit_a + digit_b + carry;
        tmp[pos++] = '0' + (sum %10);
        carry = sum /10;
        i--;
        j--;
    }
    // Reverse tmp to get res
    for(int x=0; x<pos; x++) {
        res[x] = tmp[pos-1 -x];
    }
    res[pos] = '\0';
}

int main(){
    int k, w;
    scanf("%d %d", &k, &w);
    int base = 1 << k;
    // Precompute bits[d1]
    int bits[513];
    for(int d=1; d<base; d++){
        int b = 0;
        int tmp = d;
        while(tmp >0){
            tmp >>=1;
            b++;
        }
        bits[d] = b;
    }
    // Initialize C[n][m]
    char C[MAX_N+1][MAX_M+1][MAX_DIGITS];
    // Initialize all to "0"
    for(int n=0; n<=base-1; n++){
        for(int m=0; m<=n; m++){
            C[n][m][0] = '0';
            C[n][m][1] = '\0';
        }
    }
    // C(0,0) = "1"
    C[0][0][0] = '1';
    C[0][0][1] = '\0';
    // Fill the table
    for(int n=1; n<=base-1; n++){
        C[n][0][0] = '1';
        C[n][0][1] = '\0';
        for(int m=1; m<=n; m++){
            if(m == n){
                C[n][m][0] = '1';
                C[n][m][1] = '\0';
            }
            else{
                char temp1[MAX_DIGITS], temp2[MAX_DIGITS];
                strcpy(temp1, C[n-1][m]);
                strcpy(temp2, C[n-1][m-1]);
                char res[MAX_DIGITS];
                add_strings(temp1, temp2, res);
                strcpy(C[n][m], res);
            }
        }
    }
    // Initialize answer to "0"
    char ans[SUM_DIGITS];
    ans[0] = '0';
    ans[1] = '\0';
    // Iterate over d1
    for(int d1=1; d1 < base; d1++){
        int b = bits[d1];
        int n = base -1 - d1;
        if(n <0) continue;
        // Calculate m_max
        if(w < b) continue;
        int m_max = (w - b)/k +1;
        if(m_max > n+1) m_max = n+1;
        if(m_max <2) continue;
        for(int m=2; m<=m_max; m++){
            if(m-1 > n) continue;
            // Add C[n][m-1} to ans
            if(C[n][m-1][0] == '0' && C[n][m-1][1]=='\0') continue;
            char new_ans[SUM_DIGITS];
            add_strings(ans, C[n][m-1], new_ans);
            strcpy(ans, new_ans);
        }
    }
    // Remove leading zeros
    int start =0;
    while(ans[start] == '0' && ans[start+1] != '\0') start++;
    printf("%s\n", ans + start);
    return 0;
}