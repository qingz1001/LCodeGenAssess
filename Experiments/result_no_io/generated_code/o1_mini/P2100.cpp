#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DIGITS 1005
#define MAX_BITS 3322
#define MOD 100000000

// Function to remove leading zeros
void remove_leading_zeros(char *str) {
    int i = 0;
    while(str[i] == '0' && str[i+1] != '\0') i++;
    if(i > 0){
        memmove(str, str+i, strlen(str+i)+1);
    }
}

// Function to add one to a numeric string
void add_one(char *num) {
    int len = strlen(num);
    int carry = 1;
    for(int i = len-1; i >=0; i--){
        int digit = num[i] - '0' + carry;
        if(digit >=10){
            num[i] = '0';
            carry = 1;
        }
        else{
            num[i] = digit + '0';
            carry = 0;
            break;
        }
    }
    if(carry){
        // Shift right and add '1' at the beginning
        memmove(num+1, num, len+1);
        num[0] = '1';
    }
}

// Function to divide a numeric string by two
// quotient is stored in 'quotient', remainder in 'rem'
void divide_by_two(char *num, char *quotient, int *rem) {
    int len = strlen(num);
    int carry_val = 0;
    int q_pos = 0;
    for(int i = 0; i < len; i++){
        int current = carry_val *10 + (num[i]-'0');
        int q_digit = current /2;
        carry_val = current %2;
        if(q_pos >0 || q_digit !=0){
            quotient[q_pos++] = q_digit + '0';
        }
    }
    if(q_pos ==0){
        quotient[q_pos++] = '0';
    }
    quotient[q_pos] = '\0';
    *rem = carry_val;
}

// Function to convert decimal string to binary bits
int decimal_to_binary(char *num, int *bits){
    char temp[MAX_DIGITS];
    strcpy(temp, num);
    int count =0;
    while(!(strlen(temp)==1 && temp[0]=='0')){
        char quotient[MAX_DIGITS];
        int rem;
        divide_by_two(temp, quotient, &rem);
        bits[count++] = rem;
        strcpy(temp, quotient);
        remove_leading_zeros(temp);
    }
    return count;
}

int main(){
    char n_str[MAX_DIGITS];
    scanf("%s", n_str);
    add_one(n_str);
    int bits[MAX_BITS];
    int bit_size = decimal_to_binary(n_str, bits);
    // Fast doubling
    unsigned int f0 = 0, f1 =1;
    for(int i = bit_size-1; i >=0; i--){
        unsigned long long c = ((unsigned long long)f0 * ((2*(unsigned long long)f1 + MOD - f0) % MOD)) % MOD;
        unsigned long long d = ((unsigned long long)f0 * f0 + (unsigned long long)f1 * f1) % MOD;
        f0 = c;
        f1 = d;
        if(bits[i]){
            unsigned long long tmp = ((unsigned long long)f0 + (unsigned long long)f1) % MOD;
            f0 = f1;
            f1 = tmp;
        }
    }
    // Print without leading zeros
    if(f0 ==0){
        printf("0\n");
    }
    else{
        char res[12];
        sprintf(res, "%u", f0);
        printf("%s\n", res);
    }
    return 0;
}