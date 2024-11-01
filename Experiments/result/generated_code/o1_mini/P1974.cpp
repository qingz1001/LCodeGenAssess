#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 10001
#define MAX_DIGITS 50000

typedef struct {
    char digits[MAX_DIGITS];
} BigInt;

// Initialize BigInt with "1"
void init_bigint(BigInt *num) {
    memset(num->digits, '0', MAX_DIGITS);
    num->digits[0] = '1';
    num->digits[1] = '\0';
}

// Compare two BigInts, return 1 if a > b, -1 if a < b, 0 if equal
int compare_bigint(const char *a, const char *b) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    if(len_a > len_b) return 1;
    if(len_a < len_b) return -1;
    return strcmp(a, b);
}

// Multiply two BigInts represented as strings
void multiply(const char *a, const char *b, char *result) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    int *temp = calloc(len_a + len_b, sizeof(int));
    for(int i = len_a -1; i >=0; i--){
        for(int j = len_b -1; j >=0; j--){
            int mul = (a[i]-'0') * (b[j]-'0');
            int sum = temp[i+j+1] + mul;
            temp[i+j] += sum / 10;
            temp[i+j+1] = sum % 10;
        }
    }
    int pos =0;
    while(pos < len_a + len_b && temp[pos]==0) pos++;
    if(pos == len_a + len_b){
        strcpy(result, "0");
    }
    else{
        int idx=0;
        for(; pos < len_a + len_b; pos++) result[idx++] = temp[pos] + '0';
        result[idx] = '\0';
    }
    free(temp);
}

// Add 1 to a BigInt string
void add_one(char *num) {
    int len = strlen(num);
    int carry = 1;
    for(int i = len -1; i >=0 && carry; i--){
        if(num[i] == '9'){
            num[i] = '0';
        }
        else{
            num[i] +=1;
            carry =0;
        }
    }
    if(carry){
        memmove(num+1, num, len+1);
        num[0] = '1';
    }
}

// Copy source to destination
void copy_str(char *dest, const char *src){
    strcpy(dest, src);
}

int main(){
    int n;
    scanf("%d", &n);
    if(n ==0){
        printf("0");
        return 0;
    }
    BigInt dp[MAX_N];
    for(int i=1;i<=n;i++) {
        init_bigint(&dp[i]);
    }
    for(int i=2;i<=n;i++){
        char temp_result[MAX_DIGITS] = "";
        for(int k=1;k<=i-1;k++){
            char product[MAX_DIGITS];
            multiply(dp[k].digits, dp[i -k].digits, product);
            // Add 1
            add_one(product);
            if(compare_bigint(product, temp_result) >0 || temp_result[0] == '0'){
                copy_str(temp_result, product);
            }
        }
        copy_str(dp[i].digits, temp_result);
    }
    printf("%s", dp[n].digits);
    return 0;
}