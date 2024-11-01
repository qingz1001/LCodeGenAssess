#include <stdio.h>
#include <string.h>
#include <ctype.h>

int char_to_val(char c){
    if(isdigit(c)) return c - '0';
    else return c - 'A' + 10;
}

char val_to_char(int val){
    if(val < 10) return '0' + val;
    else return 'A' + (val - 10);
}

int main(){
    int n, m;
    char num[20];
    scanf("%d", &n);
    scanf("%s", num);
    scanf("%d", &m);
    
    // Convert to decimal
    long dec = 0;
    for(int i=0; num[i]; i++){
        dec = dec * n + char_to_val(num[i]);
    }
    
    // Handle zero
    if(dec == 0){
        printf("0");
        return 0;
    }
    
    // Convert to base m
    char res[20];
    int idx = 0;
    while(dec > 0){
        int rem = dec % m;
        res[idx++] = val_to_char(rem);
        dec /= m;
    }
    
    // Print in reverse
    for(int i=idx-1;i>=0;i--){
        putchar(res[i]);
    }
    return 0;
}