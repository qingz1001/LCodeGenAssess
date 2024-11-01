#include <stdio.h>
#include <string.h>

int main(){
    int n;
    scanf("%d", &n);
    char s_input[351];
    scanf("%s", s_input);
    // Duplicate the string to handle circularity
    char s[701];
    strcpy(s, s_input);
    strcat(s, s_input);
    int max_beads = 0;
    for(int break_pt = 0; break_pt < n; break_pt++){
        // Collect to the right
        int right = 0;
        char color_right = 0;
        for(int i = break_pt; i < break_pt + n; i++){
            char c = s[i];
            if(c == 'w'){
                right++;
            }
            else{
                if(color_right == 0){
                    color_right = c;
                    right++;
                }
                else{
                    if(c == color_right){
                        right++;
                    }
                    else{
                        break;
                    }
                }
            }
        }
        // Collect to the left
        int left = 0;
        char color_left = 0;
        for(int i = break_pt -1 + n; i >= break_pt -n; i--){
            char c = s[i];
            if(c == 'w'){
                left++;
            }
            else{
                if(color_left == 0){
                    color_left = c;
                    left++;
                }
                else{
                    if(c == color_left){
                        left++;
                    }
                    else{
                        break;
                    }
                }
            }
        }
        if(left + right > max_beads){
            if(left + right > n){
                max_beads = n;
            }
            else{
                max_beads = left + right;
            }
        }
    }
    printf("%d\n", max_beads);
    return 0;
}