#include <stdio.h>
#include <string.h>

int main(){
    char isbn[20];
    scanf("%s", isbn);
    int digits[9];
    int idx = 0;
    for(int i=0;i<strlen(isbn);i++) {
        if(isbn[i]!='-'){
            if(idx <9){
                digits[idx++] = isbn[i]-'0';
            }
        }
    }
    int sum=0;
    for(int i=0;i<9;i++) sum += digits[i]*(i+1);
    int rem = sum % 11;
    char correct;
    if(rem ==10) correct = 'X';
    else correct = rem + '0';
    if(isbn[strlen(isbn)-1] == correct){
        printf("Right");
    }
    else{
        isbn[strlen(isbn)-1] = correct;
        printf("%s", isbn);
    }
    return 0;
}