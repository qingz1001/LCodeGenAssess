#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to remove leading zeros
void remove_leading_zeros(char* num) {
    int len = strlen(num);
    int i = 0;
    while (i < len-1 && num[i] == '0') i++;
    if (i > 0) {
        memmove(num, num+i, len-i+1);
    }
}

// Function to add carry (-1, 0, 1) to the number
void add_carry(char* num, int carry) {
    int len = strlen(num);
    int i = len -1;
    if (carry == 1) {
        while (i >=0 && num[i] == '9') {
            num[i] = '0';
            i--;
        }
        if (i >=0) {
            num[i] +=1;
        } else {
            // Shift right
            memmove(num+1, num, len+1);
            num[0] = '1';
        }
    }
    else if (carry == -1) {
        while (i >=0 && num[i] == '0') {
            num[i] = '9';
            i--;
        }
        if (i >=0) {
            num[i] -=1;
        }
    }
    remove_leading_zeros(num);
}

// Function to divide number by n, returns quotient and remainder
int divide_by_n(char* num, int n, char* quotient) {
    int len = strlen(num);
    int rem = 0;
    int q_pos = 0;
    for(int i=0;i<len;i++) {
        int current = rem *10 + (num[i]-'0');
        quotient[q_pos++] = (current /n) + '0';
        rem = current %n;
    }
    quotient[q_pos] = '\0';
    remove_leading_zeros(quotient);
    return rem;
}

int main(){
    char m[10005];
    scanf("%s", m);
    int n;
    scanf("%d", &n);
    if(strcmp(m, "0") ==0){
        printf("0");
        return 0;
    }
    int count =0;
    char quotient[10005];
    while(strcmp(m, "0") !=0){
        int rem = divide_by_n(m, n, quotient);
        // Determine digit and carry
        int digit, carry;
        if(rem > n/2){
            digit = rem - n;
            carry =1;
        }
        else{
            digit = rem;
            carry =0;
        }
        if(digit !=0) count++;
        // Add carry to quotient
        if(carry !=0){
            add_carry(quotient, carry);
        }
        strcpy(m, quotient);
    }
    printf("%d", count);
}