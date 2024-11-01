#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to reverse a string in place
void reverse_str(char *str, int len){
    int i=0, j=len-1;
    char temp;
    while(i < j){
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}

// Function to add a small number (0-24) to a big number represented as a string
char* add_small(char *num, int small){
    int len = strlen(num);
    char *result = (char*)malloc(len + 10);
    strcpy(result, num);
    reverse_str(result, len);
    int carry = small;
    for(int i=0;i<len;i++){
        int digit = result[i]-'0' + carry;
        result[i] = (digit %10) + '0';
        carry = digit /10;
        if(carry ==0) break;
    }
    if(carry){
        sprintf(result + len, "%d", carry);
    }
    reverse_str(result, strlen(result));
    return result;
}

// Function to multiply two big numbers represented as strings
char* multiply(char *num1, char *num2){
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int size = len1 + len2;
    int *temp = (int*)calloc(size, sizeof(int));
    char *result = (char*)malloc(size +1);
    // Reverse the strings for ease of calculation
    char *n1 = strdup(num1);
    char *n2 = strdup(num2);
    reverse_str(n1, len1);
    reverse_str(n2, len2);
    for(int i=0;i<len1;i++){
        for(int j=0;j<len2;j++){
            temp[i+j] += (n1[i]-'0')*(n2[j]-'0');
        }
    }
    // Handle carry
    for(int i=0;i<size;i++){
        if(temp[i] >=10){
            temp[i+1] += temp[i]/10;
            temp[i] %=10;
        }
    }
    // Convert to string
    int pos = size;
    while(pos >0 && temp[pos-1]==0) pos--;
    if(pos ==0){
        result[0]='0';
        result[1]='\0';
    }
    else{
        for(int i=0;i<pos;i++) result[i] = temp[pos-1-i] + '0';
        result[pos] = '\0';
    }
    free(n1);
    free(n2);
    free(temp);
    return result;
}

// Function to divide a big number by a small number (24) and return the result as a string
char* divide_by_small(char *num, int divisor){
    int len = strlen(num);
    char *result = (char*)malloc(len +1);
    int carry =0;
    int pos =0;
    for(int i=0;i<len;i++){
        int current = carry *10 + (num[i]-'0');
        result[pos++] = (current / divisor) + '0';
        carry = current % divisor;
    }
    // Remove leading zeros
    int start=0;
    while(start < pos-1 && result[start]=='0') start++;
    result[pos] = '\0';
    return strdup(result + start);
}

int main(){
    char n[100005];
    scanf("%s", n);
    // Compute n+4, n+3, n+2, n+1
    char *n1 = add_small(n,1);
    char *n2 = add_small(n,2);
    char *n3 = add_small(n,3);
    char *n4 = add_small(n,4);
    // Multiply (n+4)*(n+3)
    char *mul1 = multiply(n4, n3);
    // Multiply result with (n+2)
    char *mul2 = multiply(mul1, n2);
    free(mul1);
    // Multiply result with (n+1)
    char *mul3 = multiply(mul2, n1);
    free(mul2);
    // Divide by 24
    char *final = divide_by_small(mul3, 24);
    free(mul3);
    // Remove any leading zeros
    int len = strlen(final);
    int start=0;
    while(start < len-1 && final[start]=='0') start++;
    printf("%s\n", final + start);
    free(n1);
    free(n2);
    free(n3);
    free(n4);
    free(final);
    return 0;
}