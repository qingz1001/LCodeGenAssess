#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to convert binary string to decimal
long long binary_to_decimal(char *s) {
    long long res = 0;
    for(int i=0; s[i]; i++) {
        res = res * 2 + (s[i] - '0');
    }
    return res;
}

// Function to convert ternary string to decimal
long long ternary_to_decimal(char *s) {
    long long res = 0;
    for(int i=0; s[i]; i++) {
        res = res * 3 + (s[i] - '0');
    }
    return res;
}

int main(){
    char s2[35], s3[35];
    scanf("%s %s", s2, s3);
    
    // Generate all possible N from s2 by flipping one bit
    int len2 = strlen(s2);
    long long candidates2[35];
    int count2 = 0;
    for(int i=0; i<len2; i++){
        char original = s2[i];
        s2[i] = (s2[i] == '0') ? '1' : '0';
        if(s2[0] == '1'){
            candidates2[count2++] = binary_to_decimal(s2);
        }
        s2[i] = original;
    }
    
    // Generate all possible N from s3 by changing one digit
    int len3 = strlen(s3);
    long long candidates3[70];
    int count3 = 0;
    for(int i=0; i<len3; i++){
        char original = s3[i];
        for(char d='0'; d<='2'; d++){
            if(d != original){
                if(i == 0 && d == '0') continue;
                s3[i] = d;
                candidates3[count3++] = ternary_to_decimal(s3);
            }
        }
        s3[i] = original;
    }
    
    // Find the intersection
    for(int i=0; i<count2; i++){
        for(int j=0; j<count3; j++){
            if(candidates2[i] == candidates3[j]){
                printf("%lld\n", candidates2[i]);
                return 0;
            }
        }
    }
    return 0;
}