#include <stdio.h>
#include <string.h>

int main(){
    int press_counts[128] = {0};
    // Initialize mapping
    // 'a' to 'c' => 1,2,3
    press_counts['a'] = 1;
    press_counts['b'] = 2;
    press_counts['c'] = 3;
    // 'd' to 'f'
    press_counts['d'] =1;
    press_counts['e'] =2;
    press_counts['f'] =3;
    // 'g' to 'i'
    press_counts['g']=1;
    press_counts['h']=2;
    press_counts['i']=3;
    // 'j' to 'l'
    press_counts['j']=1;
    press_counts['k']=2;
    press_counts['l']=3;
    // 'm' to 'o'
    press_counts['m']=1;
    press_counts['n']=2;
    press_counts['o']=3;
    // 'p' to 's'
    press_counts['p']=1;
    press_counts['q']=2;
    press_counts['r']=3;
    press_counts['s']=4;
    // 't' to 'v'
    press_counts['t']=1;
    press_counts['u']=2;
    press_counts['v']=3;
    // 'w' to 'z'
    press_counts['w']=1;
    press_counts['x']=2;
    press_counts['y']=3;
    press_counts['z']=4;
    // ' ' = space
    press_counts[' ']=1;
    
    char s[201];
    // Read the line
    fgets(s, 201, stdin);
    // Remove newline if present
    int len = strlen(s);
    if(len > 0 && s[len-1] == '\n') s[len-1] = '\0';
    // Sum the presses
    int total =0;
    for(int i=0; s[i]!='\0';i++) {
        total += press_counts[s[i]];
    }
    printf("%d", total);
}