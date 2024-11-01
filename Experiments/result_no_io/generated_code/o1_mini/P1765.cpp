#include <stdio.h>
#include <string.h>

int main(){
    char s[201];
    if(fgets(s, sizeof(s), stdin)!=NULL){
        int press =0;
        int presses[256]={0};
        // key 2: 'a','b','c'
        presses['a'] =1; presses['b']=2; presses['c']=3;
        // key3: 'd','e','f'
        presses['d']=1; presses['e']=2; presses['f']=3;
        // key4: 'g','h','i'
        presses['g']=1; presses['h']=2; presses['i']=3;
        // key5: 'j','k','l'
        presses['j']=1; presses['k']=2; presses['l']=3;
        // key6: 'm','n','o'
        presses['m']=1; presses['n']=2; presses['o']=3;
        // key7: 'p','q','r','s'
        presses['p']=1; presses['q']=2; presses['r']=3; presses['s']=4;
        // key8: 't','u','v'
        presses['t']=1; presses['u']=2; presses['v']=3;
        // key9: 'w','x','y','z'
        presses['w']=1; presses['x']=2; presses['y']=3; presses['z']=4;
        // key0: ' '
        presses[' ']=1;
        // remove possible newline
        size_t len = strlen(s);
        if(len>0 && s[len-1]=='\n') s[len-1]='\0';
        for(int i=0;s[i]!='\0';i++){
            press += presses[(unsigned char)s[i]];
        }
        printf("%d\n", press);
    }
    return 0;
}