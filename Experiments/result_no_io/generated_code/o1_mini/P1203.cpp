#include <stdio.h>
#include <string.h>

int main(){
    int n;
    scanf("%d", &n);
    char s_original[351];
    scanf("%s", s_original);
    char s[700];
    strcpy(s, s_original);
    strcat(s, s_original);
    int max = 0;
    for(int i=0;i<n;i++){
        // Collect left
        int left = 0;
        char color1 = 'w';
        for(int j=i; j<i+n; j++){
            if(s[j] != 'w'){
                color1 = s[j];
                break;
            }
        }
        for(int j=i; j<i+n; j++){
            if(s[j] == 'w') {
                left++;
            }
            else {
                if(color1 == 'w') {
                    color1 = s[j];
                    left++;
                }
                else if(s[j] == color1){
                    left++;
                }
                else{
                    break;
                }
            }
        }
        // Collect right
        int right = 0;
        char color2 = 'w';
        for(int j=i-1+n; j>=i-n; j--){
            if(s[j] != 'w'){
                color2 = s[j];
                break;
            }
        }
        for(int j=i-1+n; j>=i-n; j--){
            if(s[j] == 'w') {
                right++;
            }
            else {
                if(color2 == 'w') {
                    color2 = s[j];
                    right++;
                }
                else if(s[j] == color2){
                    right++;
                }
                else{
                    break;
                }
            }
        }
        if(left + right > max){
            if(left + right > n) max = n;
            else max = left + right;
        }
    }
    printf("%d\n", max);
}