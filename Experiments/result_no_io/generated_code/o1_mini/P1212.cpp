#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int w, h;
} Rect;

typedef struct {
    int p, q;
} Pair;

int compare(const void* a, const void* b){
    Pair *pa = (Pair*)a;
    Pair *pb = (Pair*)b;
    if(pa->p != pb->p)
        return pa->p - pb->p;
    return pa->q - pb->q;
}

int main(){
    Rect rect[4];
    for(int i=0;i<4;i++) scanf("%d %d", &rect[i].w, &rect[i].h);
    int minArea = 1<<30;
    Pair pairs[100];
    int cnt=0;
    for(int mask=0; mask<16; mask++){
        Rect r[4];
        for(int i=0;i<4;i++){
            if(mask & (1<<i)){
                r[i].w = rect[i].h;
                r[i].h = rect[i].w;
            }
            else{
                r[i].w = rect[i].w;
                r[i].h = rect[i].h;
            }
        }
        // Scheme 1: all in a row
        {
            int W = r[0].w + r[1].w + r[2].w + r[3].w;
            int H = r[0].h > r[1].h ? (r[0].h > r[2].h ? (r[0].h > r[3].h ? r[0].h : r[3].h) : (r[2].h > r[3].h ? r[2].h : r[3].h)) 
                                      : (r[1].h > r[2].h ? (r[1].h > r[3].h ? r[1].h : r[3].h) : (r[2].h > r[3].h ? r[2].h : r[3].h));
            int area = W * H;
            if(area < minArea){
                minArea = area;
                cnt=0;
            }
            if(area == minArea){
                int p = W < H ? W : H;
                int q = W < H ? H : W;
                int exists=0;
                for(int j=0;j<cnt;j++) if(pairs[j].p == p && pairs[j].q == q){ exists=1; break;}
                if(!exists){
                    pairs[cnt].p = p;
                    pairs[cnt].q = q;
                    cnt++;
                }
            }
        }
        // Scheme 2: all in a column
        {
            int W = r[0].w > r[1].w ? (r[0].w > r[2].w ? (r[0].w > r[3].w ? r[0].w : r[3].w) 
                                      : (r[2].w > r[3].w ? r[2].w : r[3].w)) 
                                      : (r[1].w > r[2].w ? (r[1].w > r[3].w ? r[1].w : r[3].w) 
                                      : (r[2].w > r[3].w ? r[2].w : r[3].w));
            int H = r[0].h + r[1].h + r[2].h + r[3].h;
            int area = W * H;
            if(area < minArea){
                minArea = area;
                cnt=0;
            }
            if(area == minArea){
                int p = W < H ? W : H;
                int q = W < H ? H : W;
                int exists=0;
                for(int j=0;j<cnt;j++) if(pairs[j].p == p && pairs[j].q == q){ exists=1; break;}
                if(!exists){
                    pairs[cnt].p = p;
                    pairs[cnt].q = q;
                    cnt++;
                }
            }
        }
        // Scheme 3: two side by side, two side by side stacked
        for(int split=1; split<(1<<3); split++){
            int w1=0, h1=0, w2=0, h2=0;
            for(int i=0;i<4;i++) {
                if(split & (1<<i)){
                    w1 += r[i].w;
                    if(r[i].h > h1) h1 = r[i].h;
                }
                else{
                    w2 += r[i].w;
                    if(r[i].h > h2) h2 = r[i].h;
                }
            }
            if(split !=0 && (4 - __builtin_popcount(split)) !=0){
                int W = w1 > w2 ? w1 : w2;
                int H = h1 + h2;
                int area = W * H;
                if(area < minArea){
                    minArea = area;
                    cnt=0;
                }
                if(area == minArea){
                    int p = W < H ? W : H;
                    int q = W < H ? H : W;
                    int exists=0;
                    for(int j=0;j<cnt;j++) if(pairs[j].p == p && pairs[j].q == q){ exists=1; break;}
                    if(!exists){
                        pairs[cnt].p = p;
                        pairs[cnt].q = q;
                        cnt++;
                    }
                }
            }
        }
        // Scheme 4: three in a row, one on top or bottom
        for(int i=0;i<4;i++){
            int W = r[i].w;
            int H = r[i].h;
            int sumW=0, maxH=0;
            for(int j=0;j<4;j++) if(j!=i){
                sumW += r[j].w;
                if(r[j].h > maxH) maxH = r[j].h;
            }
            int totalW = W > sumW ? W : sumW;
            int totalH = H + maxH;
            int area = totalW * totalH;
            if(area < minArea){
                minArea = area;
                cnt=0;
            }
            if(area == minArea){
                int p = totalW < totalH ? totalW : totalH;
                int q = totalW < totalH ? totalH : totalW;
                int exists=0;
                for(int j=0;j<cnt;j++) if(pairs[j].p == p && pairs[j].q == q){ exists=1; break;}
                if(!exists){
                    pairs[cnt].p = p;
                    pairs[cnt].q = q;
                    cnt++;
                }
            }
        }
        // Scheme 5: two stacked, two stacked
        for(int split=1; split<(1<<3); split++){
            int w1=0, h1=0, w2=0, h2=0;
            for(int i=0;i<4;i++) {
                if(split & (1<<i)){
                    if(r[i].w > w1) w1 = r[i].w;
                    h1 += r[i].h;
                }
                else{
                    if(r[i].w > w2) w2 = r[i].w;
                    h2 += r[i].h;
                }
            }
            if(split !=0 && (4 - __builtin_popcount(split)) !=0){
                int W = w1 + w2;
                int H = h1 > h2 ? h1 : h2;
                int area = W * H;
                if(area < minArea){
                    minArea = area;
                    cnt=0;
                }
                if(area == minArea){
                    int p = W < H ? W : H;
                    int q = W < H ? H : W;
                    int exists=0;
                    for(int j=0;j<cnt;j++) if(pairs[j].p == p && pairs[j].q == q){ exists=1; break;}
                    if(!exists){
                        pairs[cnt].p = p;
                        pairs[cnt].q = q;
                        cnt++;
                    }
                }
            }
        }
        // Scheme 6: L-shape
        for(int i=0;i<4;i++) {
            for(int j=0;j<4;j++) if(j!=i){
                int W1 = r[i].w + r[j].w;
                int H1 = r[i].h > r[j].h ? r[i].h : r[j].h;
                for(int k=0;k<4;k++) if(k!=i && k!=j){
                    for(int l=0;l<4;l++) if(l!=i && l!=j && l!=k){
                        int W2 = r[k].w;
                        int H2 = r[k].h + r[l].h;
                        int totalW = W1 > W2 ? W1 : W2;
                        int totalH = H1 + (r[l].h > r[k].h ? r[l].h : r[k].h);
                        int area = totalW * totalH;
                        if(area < minArea){
                            minArea = area;
                            cnt=0;
                        }
                        if(area == minArea){
                            int p = totalW < totalH ? totalW : totalH;
                            int q = totalW < totalH ? totalH : totalW;
                            int exists=0;
                            for(int m=0;m<cnt;m++) if(pairs[m].p == p && pairs[m].q == q){ exists=1; break;}
                            if(!exists){
                                pairs[cnt].p = p;
                                pairs[cnt].q = q;
                                cnt++;
                            }
                        }
                    }
                }
            }
        }
    }
    // Now collect unique pairs with minArea
    Pair final_pairs[100];
    int final_cnt=0;
    for(int i=0;i<cnt;i++) final_pairs[i] = pairs[i];
    // Remove duplicates
    qsort(final_pairs, final_cnt, sizeof(Pair), compare);
    // Sort and count unique
    qsort(pairs, cnt, sizeof(Pair), compare);
    // Now collect unique
    Pair unique_pairs[100];
    int unique_cnt=0;
    for(int i=0;i<cnt;i++) {
        if(i==0 || !(pairs[i].p == pairs[i-1].p && pairs[i].q == pairs[i-1].q)){
            unique_pairs[unique_cnt++] = pairs[i];
        }
    }
    // Output
    printf("%d\n", minArea);
    for(int i=0;i<unique_cnt;i++) printf("%d %d\n", unique_pairs[i].p, unique_pairs[i].q);
    return 0;
}