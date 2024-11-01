#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DIGITS 3000
#define MAX_M 80
#define MAX_N 80

typedef struct {
    char digits[MAX_DIGITS]; // digits[0] is least significant digit
} BigInt;

// Initialize BigInt to zero
void init_bigint(BigInt *num) {
    memset(num->digits, '0', MAX_DIGITS);
    num->digits[0] = '0';
    for(int i=1;i<MAX_DIGITS;i++) num->digits[i] = '\0';
}

// Multiply reversed string by 2, result_rev is reversed
void multiply_by_two(char *a_rev, char *result_rev) {
    int carry = 0;
    int i = 0;
    while(a_rev[i] != '\0') {
        int tmp = (a_rev[i] - '0') * 2 + carry;
        result_rev[i] = (tmp % 10) + '0';
        carry = tmp / 10;
        i++;
    }
    if(carry) {
        result_rev[i++] = carry + '0';
    }
    result_rev[i] = '\0';
}

// Multiply reversed string by an integer a_j, result_rev is reversed
void multiply_rev_str_by_int(char *a_rev, int a_j, char *result_rev) {
    int carry = 0;
    int i = 0;
    while(a_rev[i] != '\0') {
        int tmp = (a_rev[i] - '0') * a_j + carry;
        result_rev[i] = (tmp % 10) + '0';
        carry = tmp / 10;
        i++;
    }
    while(a_j && carry) {
        int tmp = carry;
        result_rev[i++] = (tmp % 10) + '0';
        carry = tmp /10;
    }
    if(carry) {
        result_rev[i++] = carry + '0';
    }
    result_rev[i] = '\0';
}

// Add two reversed strings a_rev and b_rev, store in result_rev
void add_rev_str(char *a_rev, char *b_rev, char *result_rev) {
    int carry = 0;
    int i = 0;
    while(a_rev[i] != '\0' || b_rev[i] != '\0') {
        int digit_a = (a_rev[i] != '\0') ? (a_rev[i] - '0') : 0;
        int digit_b = (b_rev[i] != '\0') ? (b_rev[i] - '0') : 0;
        int tmp = digit_a + digit_b + carry;
        result_rev[i] = (tmp %10) + '0';
        carry = tmp /10;
        i++;
    }
    if(carry) {
        result_rev[i++] = carry + '0';
    }
    result_rev[i] = '\0';
}

// Compare two reversed strings a_rev and b_rev
// Returns 1 if a_rev > b_rev, 0 otherwise
int compare_rev_str(char *a_rev, char *b_rev) {
    int len_a = strlen(a_rev);
    int len_b = strlen(b_rev);
    if(len_a > len_b) return 1;
    if(len_a < len_b) return 0;
    for(int i = len_a-1;i>=0;i--){
        if(a_rev[i] > b_rev[i]) return 1;
        if(a_rev[i] < b_rev[i]) return 0;
    }
    return 0;
}

// Copy string src to dest
void copy_rev_str(char *src, char *dest) {
    int i =0;
    while(src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// Max of two reversed strings a_rev and b_rev, store in result_rev
void max_rev_str(char *a_rev, char *b_rev, char *result_rev) {
    if(compare_rev_str(a_rev, b_rev)) {
        copy_rev_str(a_rev, result_rev);
    }
    else {
        copy_rev_str(b_rev, result_rev);
    }
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    int matrix[MAX_N][MAX_M];
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    // Precompute powers of two as reversed strings
    char powers[MAX_M+1][MAX_DIGITS];
    memset(powers, 0, sizeof(powers));
    powers[0][0] = '1';
    powers[0][1] = '\0';
    for(int k=1;k<=m;k++) {
        char temp[MAX_DIGITS] = {0};
        multiply_by_two(powers[k-1], temp);
        strcpy(powers[k], temp);
    }
    // Initialize total_sum as BigInt
    char total_sum_rev[MAX_DIGITS];
    init_bigint((BigInt*)total_sum_rev);
    strcpy(total_sum_rev, "0");
    // Process each row
    for(int row=0; row<n; row++) {
        // Initialize DP table
        char dp[MAX_M][MAX_M][MAX_DIGITS];
        for(int l=0;l<m;l++) {
            for(int r=0;r<m;r++) {
                dp[l][r][0] = '\0';
            }
        }
        // Initialize dp[l][l] = a[l] * 2^m
        char multiplied[MAX_DIGITS] = {0};
        multiply_rev_str_by_int(powers[m], matrix[row][0], multiplied);
        for(int l=0; l<m; l++) {
            multiply_rev_str_by_int(powers[m], matrix[row][l], dp[l][l]);
        }
        // Fill DP
        for(int len=2; len<=m; len++) {
            for(int l=0; l + len -1 < m; l++) {
                int r = l + len -1;
                int step = m - len +1;
                // Left pick: a[l] * 2^step + dp[l+1][r]
                char left_pick[MAX_DIGITS] = {0};
                multiply_rev_str_by_int(powers[step], matrix[row][l], left_pick);
                char temp_sum1[MAX_DIGITS] = {0};
                add_rev_str(left_pick, dp[l+1][r], temp_sum1);
                // Right pick: a[r] * 2^step + dp[l][r-1]
                char right_pick[MAX_DIGITS] = {0};
                multiply_rev_str_by_int(powers[step], matrix[row][r], right_pick);
                char temp_sum2[MAX_DIGITS] = {0};
                add_rev_str(right_pick, dp[l][r-1], temp_sum2);
                // dp[l][r] = max(temp_sum1, temp_sum2)
                char max_sum[MAX_DIGITS] = {0};
                max_rev_str(temp_sum1, temp_sum2, max_sum);
                strcpy(dp[l][r], max_sum);
            }
        }
        // Add dp[0][m-1] to total_sum_rev
        char row_sum_rev[MAX_DIGITS];
        strcpy(row_sum_rev, dp[0][m-1]);
        char new_total[MAX_DIGITS] = {0};
        add_rev_str(total_sum_rev, row_sum_rev, new_total);
        strcpy(total_sum_rev, new_total);
    }
    // Now, print total_sum_rev in correct order
    int len = strlen(total_sum_rev);
    // Remove any leading zeros
    int start = len-1;
    while(start >0 && total_sum_rev[start] == '0') start--;
    for(int i=start;i>=0;i--) {
        printf("%c", total_sum_rev[i]);
    }
    printf("\n");
    return 0;
}