#include<stdio.h>
#include<string.h>

int main(){
    char s[20];
    scanf("%s",s);
    int digits[9];
    int idx =0;
    for(int i=0;i<strlen(s);i++){
        if(s[i]!='-'){
            if(idx<9){
                digits[idx++] = s[i]-'0';
            }
        }
    }
    int sum=0;
    for(int i=0;i<9;i++){
        sum += digits[i]*(i+1);
    }
    int rem = sum%11;
    char check;
    if(rem ==10) check='X';
    else check = '0' + rem;
    if(s[strlen(s)-1]==check){
        printf("Right");
    }
    else{
        s[strlen(s)-1]=check;
        printf("%s",s);
    }
}