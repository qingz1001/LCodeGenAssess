#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Maximum values based on constraints
#define MAX_K 6
#define MAX_N 40
#define MAX_DIGITS 300

// Function to compare two numeric strings
// Returns 1 if a > b, -1 if a < b, 0 if equal
int compare_strings(const char *a, const char *b) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    if(len_a > len_b) return 1;
    if(len_a < len_b) return -1;
    return strcmp(a, b);
}

// Function to reverse a string in place
void reverse_str(char *str) {
    int len = strlen(str);
    for(int i=0;i<len/2;i++) {
        char tmp = str[i];
        str[i] = str[len-1-i];
        str[len-1-i] = tmp;
    }
}

// Function to multiply two numeric strings a and b, result is stored in res
void multiply_strings(const char *a, const char *b, char *res) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    int len_res = len_a + len_b;
    int num_a[len_a];
    int num_b[len_b];
    // Initialize number arrays in reverse
    for(int i=0;i<len_a;i++) num_a[i] = a[len_a-1-i] - '0';
    for(int i=0;i<len_b;i++) num_b[i] = b[len_b-1-i] - '0';
    int temp[len_res];
    for(int i=0;i<len_res;i++) temp[i] = 0;
    // Multiply
    for(int i=0;i<len_a;i++) {
        for(int j=0;j<len_b;j++) {
            temp[i+j] += num_a[i] * num_b[j];
        }
    }
    // Handle carry
    for(int i=0;i<len_res;i++) {
        if(temp[i] >= 10) {
            if(i+1 >= len_res) {
                temp[i+1] += temp[i]/10;
                temp[i] %= 10;
            } else {
                temp[i+1] += temp[i]/10;
                temp[i] %= 10;
            }
        }
    }
    // Find the actual length
    int actual_len = len_res;
    while(actual_len >1 && temp[actual_len-1] ==0) actual_len--;
    // Convert to string
    for(int i=0;i<actual_len;i++) {
        res[i] = temp[actual_len-1-i] + '0';
    }
    res[actual_len] = '\0';
}

// Function to extract substring from S[start] to S[end-1] into sub
void get_substring(const char *S, int start, int end, char *sub) {
    int j=0;
    for(int i=start;i<end;i++) {
        sub[j++] = S[i];
    }
    sub[j] = '\0';
}

int main(){
    int N, K;
    scanf("%d %d", &N, &K);
    char S[MAX_N+1];
    scanf("%s", S);
    
    // Initialize DP
    // DP[k][i] will store the max product as string for first i digits with k multiplications
    char DP[MAX_K+1][MAX_N+1][MAX_DIGITS];
    
    // Initialize k=0
    for(int i=1;i<=N;i++) {
        char sub[MAX_N+1];
        get_substring(S, 0, i, sub);
        strcpy(DP[0][i], sub);
    }
    
    // Fill DP
    for(int k=1;k<=K;k++) {
        for(int i=k+1;i<=N;i++) {
            strcpy(DP[k][i], "0");
            for(int j=k; j<=i-1; j++) {
                // Get DP[k-1][j]
                char *prev = DP[k-1][j];
                // Get number from j to i-1
                char num[MAX_N+1];
                get_substring(S, j, i, num);
                // Multiply prev and num
                char product[MAX_DIGITS];
                multiply_strings(prev, num, product);
                // Compare and set
                if(compare_strings(product, DP[k][i]) > 0){
                    strcpy(DP[k][i], product);
                }
            }
        }
    }
    
    // If K=0, the whole number is the product
    if(K ==0){
        printf("%s\n", DP[0][N]);
    }
    else{
        printf("%s\n", DP[K][N]);
    }
    
    return 0;
}