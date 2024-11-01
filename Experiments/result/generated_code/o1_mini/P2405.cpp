#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to remove leading zeros, returns "0" if all zeros
void remove_leading_zeros(char* num) {
    int len = strlen(num);
    int pos = 0;
    while (pos < len-1 && num[pos] == '0') pos++;
    if (pos > 0) {
        memmove(num, num + pos, len - pos +1);
    }
}

// Function to divide num by n, store quotient in q and remainder in r
void divide_by_n(const char* num, int n, char* q, int* r) {
    int len = strlen(num);
    int rem = 0;
    int qi = 0;
    for(int i=0;i<len;i++){
        if(num[i] < '0' || num[i] > '9') continue;
        int digit = num[i] - '0';
        rem = rem * 10 + digit;
        if(qi >0 || rem >=n){
            q[qi++] = (rem /n) + '0';
            rem = rem %n;
        }
        else{
            // Skip leading zeros
        }
    }
    if(qi ==0){
        q[qi++] = '0';
    }
    q[qi] = '\0';
    *r = rem;
}

// Function to increment num string by 1
void increment_string(char* num) {
    int len = strlen(num);
    int carry = 1;
    for(int i=len-1;i>=0;i--){
        int digit = num[i] - '0' + carry;
        if(digit >=10){
            num[i] = '0';
            carry =1;
        }
        else{
            num[i] = digit + '0';
            carry =0;
            break;
        }
    }
    if(carry){
        // Shift right and add '1' at the beginning
        memmove(num+1, num, len+1);
        num[0] = '1';
    }
}

int main(){
    char m[10005];
    scanf("%s", m);
    int n;
    scanf("%d", &n);
    if(n ==0){
        printf("0");
        return 0;
    }
    int count =0;
    char q[10005];
    while(!(strcmp(m, "0") ==0)){
        divide_by_n(m, n, q, &(int){0});
        int rem;
        divide_by_n(m, n, q, &rem);
        int digit;
        if(rem > n/2){
            digit = rem - n;
            increment_string(q);
        }
        else{
            digit = rem;
        }
        if(digit !=0){
            count++;
        }
        strcpy(m, q);
        remove_leading_zeros(m);
    }
    printf("%d", count);
    return 0;
}