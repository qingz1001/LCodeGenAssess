#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to convert binary string to decimal
long long binary_to_decimal(char *s) {
    long long res = 0;
    for(int i=0;i<strlen(s);i++) {
        res = res * 2 + (s[i] - '0');
    }
    return res;
}

// Function to convert ternary string to decimal
long long ternary_to_decimal(char *s) {
    long long res = 0;
    for(int i=0;i<strlen(s);i++) {
        res = res * 3 + (s[i] - '0');
    }
    return res;
}

int main(){
    char bin_str[35], ter_str[35];
    scanf("%s %s", bin_str, ter_str);
    
    // Generate all possible binary variants
    int bin_len = strlen(bin_str);
    long long bin_vals[35];
    int bin_count = 0;
    for(int i=0;i<bin_len;i++){
        char temp[35];
        strcpy(temp, bin_str);
        temp[i] = (temp[i]=='0') ? '1' : '0';
        bin_vals[bin_count++] = binary_to_decimal(temp);
    }
    
    // Generate all possible ternary variants
    int ter_len = strlen(ter_str);
    long long ter_vals[70];
    int ter_count = 0;
    for(int i=0;i<ter_len;i++){
        for(char repl = '0'; repl <= '2'; repl++){
            if(repl != ter_str[i]){
                char temp[35];
                strcpy(temp, ter_str);
                temp[i] = repl;
                ter_vals[ter_count++] = ternary_to_decimal(temp);
            }
        }
    }
    
    // Compare and find the unique intersection
    for(int i=0;i<bin_count;i++){
        for(int j=0;j<ter_count;j++){
            if(bin_vals[i] == ter_vals[j]){
                printf("%lld\n", bin_vals[i]);
                return 0;
            }
        }
    }
    return 0;
}