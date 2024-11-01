#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DIGITS 20

int main(){
    char input[100];
    fgets(input, sizeof(input), stdin);
    // Remove newline if present
    size_t len = strlen(input);
    if(input[len-1] == '\n') input[len-1] = '\0';
    
    char *plus = strchr(input, '+');
    if(!plus){
        return 0;
    }
    *plus = '\0';
    char *A_str = input;
    char *B_str = plus +1;
    
    // Function to split digits and reverse
    int digitsA[MAX_DIGITS], lenA=0;
    int digitsB[MAX_DIGITS], lenB=0;
    
    // Split A
    char *token = strtok(A_str, ",");
    while(token && lenA < MAX_DIGITS){
        digitsA[lenA++] = atoi(token);
        token = strtok(NULL, ",");
    }
    // Reverse A
    for(int i=0; i<lenA/2; i++){
        int temp = digitsA[i];
        digitsA[i] = digitsA[lenA-1-i];
        digitsA[lenA-1-i] = temp;
    }
    
    // Split B
    token = strtok(B_str, ",");
    while(token && lenB < MAX_DIGITS){
        digitsB[lenB++] = atoi(token);
        token = strtok(NULL, ",");
    }
    // Reverse B
    for(int i=0; i<lenB/2; i++){
        int temp = digitsB[i];
        digitsB[i] = digitsB[lenB-1-i];
        digitsB[lenB-1-i] = temp;
    }
    
    // First 20 primes
    int primes[MAX_DIGITS] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71};
    
    int result[MAX_DIGITS+1];
    int lenR=0;
    int carry=0;
    int n = lenA > lenB ? lenA : lenB;
    for(int i=0; i<n || carry; i++){
        int a = i < lenA ? digitsA[i] : 0;
        int b = i < lenB ? digitsB[i] : 0;
        int base = i < MAX_DIGITS ? primes[i] : 2; // default base 2
        int s = a + b + carry;
        result[lenR++] = s % base;
        carry = s / base;
    }
    
    // Reverse result
    for(int i=0; i<lenR/2; i++){
        int temp = result[i];
        result[i] = result[lenR-1-i];
        result[lenR-1-i] = temp;
    }
    
    // Print result
    for(int i=0; i<lenR; i++){
        printf("%d", result[i]);
        if(i != lenR-1){
            printf(",");
        }
    }
    return 0;
}