#include <stdio.h>
#include <string.h>

typedef struct {
    int digits[250]; // digits[0] is least significant digit
    int len; // number of digits
} BigInt;

// Initialize BigInt from string
void initBigInt(BigInt* bi, char* s) {
    int slen = strlen(s);
    bi->len = slen;
    for(int i = 0; i < slen; i++) {
        bi->digits[i] = s[slen - 1 - i] - '0';
    }
    // Remove leading zeros
    while(bi->len > 1 && bi->digits[bi->len -1] == 0) {
        bi->len--;
    }
}

// Compare two BigInts
// Returns 1 if a > b, -1 if a < b, 0 if equal
int compareBigInt(BigInt a, BigInt b) {
    if(a.len > b.len) return 1;
    if(a.len < b.len) return -1;
    for(int i = a.len -1; i >=0; i--){
        if(a.digits[i] > b.digits[i]) return 1;
        if(a.digits[i] < b.digits[i]) return -1;
    }
    return 0;
}

// Multiply two BigInts
void multiplyBigInt(BigInt a, BigInt b, BigInt* res) {
    memset(res->digits, 0, sizeof(res->digits));
    res->len = a.len + b.len;
    for(int i = 0; i < a.len; i++) {
        for(int j = 0; j < b.len; j++) {
            res->digits[i+j] += a.digits[i] * b.digits[j];
        }
    }
    // Handle carry
    for(int i = 0; i < res->len; i++) {
        if(res->digits[i] >= 10) {
            res->digits[i+1] += res->digits[i] / 10;
            res->digits[i] %= 10;
        }
    }
    // Remove leading zeros
    while(res->len >1 && res->digits[res->len-1] ==0) {
        res->len--;
    }
}

// Copy BigInt src to dest
void copyBigInt(BigInt* dest, BigInt src) {
    dest->len = src.len;
    for(int i =0; i < src.len; i++) {
        dest->digits[i] = src.digits[i];
    }
}

// Print BigInt
void printBigInt(BigInt bi) {
    for(int i = bi.len -1; i >=0; i--){
        printf("%d", bi.digits[i]);
    }
}

int main(){
    int N, K;
    scanf("%d %d", &N, &K);
    char S[41];
    scanf("%s", S);
    
    // Precompute all substrings
    BigInt substrs[41][41];
    for(int j =0; j < N; j++) {
        char temp[41];
        int idx =0;
        for(int i =j; i < N; i++) {
            temp[idx++] = S[i];
            temp[idx] = '\0';
            initBigInt(&substrs[j][i+1], temp);
        }
    }
    
    // Initialize DP
    BigInt dp[7][41];
    // Initialize all dp[k][i] to zero
    for(int k =0; k <= K; k++) {
        for(int i =0; i <= N; i++) {
            dp[k][i].len =1;
            dp[k][i].digits[0] =0;
        }
    }
    // Initialize dp[0][i] = substr[0][i]
    for(int i =1; i <= N; i++) {
        copyBigInt(&dp[0][i], substrs[0][i]);
    }
    
    // Fill DP
    for(int k =1; k <= K; k++) {
        for(int i =1; i <= N; i++) {
            // Initialize dp[k][i] to zero
            dp[k][i].len =1;
            dp[k][i].digits[0] =0;
            for(int j =k; j < i; j++) {
                // Multiply dp[k-1][j] with substr[j][i]
                BigInt temp;
                multiplyBigInt(dp[k-1][j], substrs[j][i], &temp);
                // Compare with current dp[k][i]
                if(compareBigInt(temp, dp[k][i]) > 0) {
                    copyBigInt(&dp[k][i], temp);
                }
            }
        }
    }
    
    // Output the result
    printBigInt(dp[K][N]);
    return 0;
}