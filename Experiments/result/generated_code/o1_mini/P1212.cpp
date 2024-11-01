#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int w;
    int h;
} rect;

typedef struct {
    int p;
    int q;
} pq_pair;

// Comparator for qsort: first by p ascending, then by q ascending
int compare_pairs(const void* a, const void* b) {
    pq_pair *pa = (pq_pair*)a;
    pq_pair *pb = (pq_pair*)b;
    if (pa->p != pb->p)
        return pa->p - pb->p;
    return pa->q - pb->q;
}

int main(){
    rect original[4];
    for(int i=0;i<4;i++) {
        scanf("%d %d", &original[i].w, &original[i].h);
    }
    
    int min_area = 1000000;
    pq_pair pairs[100];
    int pair_count = 0;
    
    // Iterate through all orientation combinations
    for(int mask=0; mask<16; mask++) {
        rect current[4];
        for(int i=0;i<4;i++) {
            if(mask & (1<<i)) {
                current[i].w = original[i].h;
                current[i].h = original[i].w;
            }
            else{
                current[i].w = original[i].w;
                current[i].h = original[i].h;
            }
        }
        
        // All in a row
        {
            int total_w = current[0].w + current[1].w + current[2].w + current[3].w;
            int max_h = current[0].h;
            if(current[1].h > max_h) max_h = current[1].h;
            if(current[2].h > max_h) max_h = current[2].h;
            if(current[3].h > max_h) max_h = current[3].h;
            int area = total_w * max_h;
            if(area < min_area){
                min_area = area;
                pair_count = 0;
                int p = total_w < max_h ? total_w : max_h;
                int q = total_w < max_h ? max_h : total_w;
                pairs[pair_count].p = p;
                pairs[pair_count].q = q;
                pair_count++;
            }
            else if(area == min_area){
                int p = total_w < max_h ? total_w : max_h;
                int q = total_w < max_h ? max_h : total_w;
                int exists = 0;
                for(int k=0;k<pair_count;k++) {
                    if(pairs[k].p == p && pairs[k].q == q){
                        exists = 1;
                        break;
                    }
                }
                if(!exists){
                    pairs[pair_count].p = p;
                    pairs[pair_count].q = q;
                    pair_count++;
                }
            }
        }
        
        // All in a column
        {
            int max_w = current[0].w;
            if(current[1].w > max_w) max_w = current[1].w;
            if(current[2].w > max_w) max_w = current[2].w;
            if(current[3].w > max_w) max_w = current[3].w;
            int total_h = current[0].h + current[1].h + current[2].h + current[3].h;
            int area = max_w * total_h;
            if(area < min_area){
                min_area = area;
                pair_count = 0;
                int p = max_w < total_h ? max_w : total_h;
                int q = max_w < total_h ? total_h : max_w;
                pairs[pair_count].p = p;
                pairs[pair_count].q = q;
                pair_count++;
            }
            else if(area == min_area){
                int p = max_w < total_h ? max_w : total_h;
                int q = max_w < total_h ? total_h : max_w;
                int exists = 0;
                for(int k=0;k<pair_count;k++) {
                    if(pairs[k].p == p && pairs[k].q == q){
                        exists = 1;
                        break;
                    }
                }
                if(!exists){
                    pairs[pair_count].p = p;
                    pairs[pair_count].q = q;
                    pair_count++;
                }
            }
        }
        
        // Two rows: {0,1} vs {2,3}
        {
            int row1_w = current[0].w + current[1].w;
            int row1_h = current[0].h > current[1].h ? current[0].h : current[1].h;
            int row2_w = current[2].w + current[3].w;
            int row2_h = current[2].h > current[3].h ? current[2].h : current[3].h;
            int total_w = row1_w > row2_w ? row1_w : row2_w;
            int total_h = row1_h + row2_h;
            int area = total_w * total_h;
            if(area < min_area){
                min_area = area;
                pair_count = 0;
                int p = total_w < total_h ? total_w : total_h;
                int q = total_w < total_h ? total_h : total_w;
                pairs[pair_count].p = p;
                pairs[pair_count].q = q;
                pair_count++;
            }
            else if(area == min_area){
                int p = total_w < total_h ? total_w : total_h;
                int q = total_w < total_h ? total_h : total_w;
                int exists = 0;
                for(int k=0;k<pair_count;k++) {
                    if(pairs[k].p == p && pairs[k].q == q){
                        exists = 1;
                        break;
                    }
                }
                if(!exists){
                    pairs[pair_count].p = p;
                    pairs[pair_count].q = q;
                    pair_count++;
                }
            }
        }
        
        // Two rows: {0,2} vs {1,3}
        {
            int row1_w = current[0].w + current[2].w;
            int row1_h = current[0].h > current[2].h ? current[0].h : current[2].h;
            int row2_w = current[1].w + current[3].w;
            int row2_h = current[1].h > current[3].h ? current[1].h : current[3].h;
            int total_w = row1_w > row2_w ? row1_w : row2_w;
            int total_h = row1_h + row2_h;
            int area = total_w * total_h;
            if(area < min_area){
                min_area = area;
                pair_count = 0;
                int p = total_w < total_h ? total_w : total_h;
                int q = total_w < total_h ? total_h : total_w;
                pairs[pair_count].p = p;
                pairs[pair_count].q = q;
                pair_count++;
            }
            else if(area == min_area){
                int p = total_w < total_h ? total_w : total_h;
                int q = total_w < total_h ? total_h : total_w;
                int exists = 0;
                for(int k=0;k<pair_count;k++) {
                    if(pairs[k].p == p && pairs[k].q == q){
                        exists = 1;
                        break;
                    }
                }
                if(!exists){
                    pairs[pair_count].p = p;
                    pairs[pair_count].q = q;
                    pair_count++;
                }
            }
        }
        
        // Two rows: {0,3} vs {1,2}
        {
            int row1_w = current[0].w + current[3].w;
            int row1_h = current[0].h > current[3].h ? current[0].h : current[3].h;
            int row2_w = current[1].w + current[2].w;
            int row2_h = current[1].h > current[2].h ? current[1].h : current[2].h;
            int total_w = row1_w > row2_w ? row1_w : row2_w;
            int total_h = row1_h + row2_h;
            int area = total_w * total_h;
            if(area < min_area){
                min_area = area;
                pair_count = 0;
                int p = total_w < total_h ? total_w : total_h;
                int q = total_w < total_h ? total_h : total_w;
                pairs[pair_count].p = p;
                pairs[pair_count].q = q;
                pair_count++;
            }
            else if(area == min_area){
                int p = total_w < total_h ? total_w : total_h;
                int q = total_w < total_h ? total_h : total_w;
                int exists = 0;
                for(int k=0;k<pair_count;k++) {
                    if(pairs[k].p == p && pairs[k].q == q){
                        exists = 1;
                        break;
                    }
                }
                if(!exists){
                    pairs[pair_count].p = p;
                    pairs[pair_count].q = q;
                    pair_count++;
                }
            }
        }
        
        // Two columns: {0,1} vs {2,3}
        {
            int col1_w = (current[0].w > current[1].w) ? current[0].w : current[1].w;
            int col1_h = current[0].h + current[1].h;
            int col2_w = (current[2].w > current[3].w) ? current[2].w : current[3].w;
            int col2_h = current[2].h + current[3].h;
            int total_w = col1_w + col2_w;
            int total_h = (col1_h > col2_h) ? col1_h : col2_h;
            int area = total_w * total_h;
            if(area < min_area){
                min_area = area;
                pair_count = 0;
                int p = total_w < total_h ? total_w : total_h;
                int q = total_w < total_h ? total_h : total_w;
                pairs[pair_count].p = p;
                pairs[pair_count].q = q;
                pair_count++;
            }
            else if(area == min_area){
                int p = total_w < total_h ? total_w : total_h;
                int q = total_w < total_h ? total_h : total_w;
                int exists = 0;
                for(int k=0;k<pair_count;k++) {
                    if(pairs[k].p == p && pairs[k].q == q){
                        exists = 1;
                        break;
                    }
                }
                if(!exists){
                    pairs[pair_count].p = p;
                    pairs[pair_count].q = q;
                    pair_count++;
                }
            }
        }
        
        // Two columns: {0,2} vs {1,3}
        {
            int col1_w = (current[0].w > current[2].w) ? current[0].w : current[2].w;
            int col1_h = current[0].h + current[2].h;
            int col2_w = (current[1].w > current[3].w) ? current[1].w : current[3].w;
            int col2_h = current[1].h + current[3].h;
            int total_w = col1_w + col2_w;
            int total_h = (col1_h > col2_h) ? col1_h : col2_h;
            int area = total_w * total_h;
            if(area < min_area){
                min_area = area;
                pair_count = 0;
                int p = total_w < total_h ? total_w : total_h;
                int q = total_w < total_h ? total_h : total_w;
                pairs[pair_count].p = p;
                pairs[pair_count].q = q;
                pair_count++;
            }
            else if(area == min_area){
                int p = total_w < total_h ? total_w : total_h;
                int q = total_w < total_h ? total_h : total_w;
                int exists = 0;
                for(int k=0;k<pair_count;k++) {
                    if(pairs[k].p == p && pairs[k].q == q){
                        exists = 1;
                        break;
                    }
                }
                if(!exists){
                    pairs[pair_count].p = p;
                    pairs[pair_count].q = q;
                    pair_count++;
                }
            }
        }
        
        // Two columns: {0,3} vs {1,2}
        {
            int col1_w = (current[0].w > current[3].w) ? current[0].w : current[3].w;
            int col1_h = current[0].h + current[3].h;
            int col2_w = (current[1].w > current[2].w) ? current[1].w : current[2].w;
            int col2_h = current[1].h + current[2].h;
            int total_w = col1_w + col2_w;
            int total_h = (col1_h > col2_h) ? col1_h : col2_h;
            int area = total_w * total_h;
            if(area < min_area){
                min_area = area;
                pair_count = 0;
                int p = total_w < total_h ? total_w : total_h;
                int q = total_w < total_h ? total_h : total_w;
                pairs[pair_count].p = p;
                pairs[pair_count].q = q;
                pair_count++;
            }
            else if(area == min_area){
                int p = total_w < total_h ? total_w : total_h;
                int q = total_w < total_h ? total_h : total_w;
                int exists = 0;
                for(int k=0;k<pair_count;k++) {
                    if(pairs[k].p == p && pairs[k].q == q){
                        exists = 1;
                        break;
                    }
                }
                if(!exists){
                    pairs[pair_count].p = p;
                    pairs[pair_count].q = q;
                    pair_count++;
                }
            }
        }
        
        // Three rows: group of 3 and 1
        for(int single=0; single<4; single++) {
            int group_w = 0;
            int group_h = 0;
            for(int i=0;i<4;i++) {
                if(i != single){
                    group_w += current[i].w;
                    if(current[i].h > group_h) group_h = current[i].h;
                }
            }
            int single_w = current[single].w;
            int single_h = current[single].h;
            int total_w = (group_w > single_w) ? group_w : single_w;
            int total_h = group_h + single_h;
            int area = total_w * total_h;
            if(area < min_area){
                min_area = area;
                pair_count = 0;
                int p = total_w < total_h ? total_w : total_h;
                int q = total_w < total_h ? total_h : total_w;
                pairs[pair_count].p = p;
                pairs[pair_count].q = q;
                pair_count++;
            }
            else if(area == min_area){
                int p = total_w < total_h ? total_w : total_h;
                int q = total_w < total_h ? total_h : total_w;
                int exists = 0;
                for(int k=0;k<pair_count;k++) {
                    if(pairs[k].p == p && pairs[k].q == q){
                        exists = 1;
                        break;
                    }
                }
                if(!exists){
                    pairs[pair_count].p = p;
                    pairs[pair_count].q = q;
                    pair_count++;
                }
            }
        }
        
        // Three columns: group of 3 and 1
        for(int single=0; single<4; single++) {
            int group_w = 0;
            int group_h = 0;
            for(int i=0;i<4;i++) {
                if(i != single){
                    if(current[i].w > group_w) group_w = current[i].w;
                    group_h += current[i].h;
                }
            }
            int single_w = current[single].w;
            int single_h = current[single].h;
            int total_w = group_w + single_w;
            int total_h = (group_h > single_h) ? group_h : single_h;
            int area = total_w * total_h;
            if(area < min_area){
                min_area = area;
                pair_count = 0;
                int p = total_w < total_h ? total_w : total_h;
                int q = total_w < total_h ? total_h : total_w;
                pairs[pair_count].p = p;
                pairs[pair_count].q = q;
                pair_count++;
            }
            else if(area == min_area){
                int p = total_w < total_h ? total_w : total_h;
                int q = total_w < total_h ? total_h : total_w;
                int exists = 0;
                for(int k=0;k<pair_count;k++) {
                    if(pairs[k].p == p && pairs[k].q == q){
                        exists = 1;
                        break;
                    }
                }
                if(!exists){
                    pairs[pair_count].p = p;
                    pairs[pair_count].q = q;
                    pair_count++;
                }
            }
        }
    }
    
    // Collect all pairs with min_area
    pq_pair final_pairs[100];
    int final_count = 0;
    for(int mask=0; mask<16; mask++) {
        rect current[4];
        for(int i=0;i<4;i++) {
            if(mask & (1<<i)) {
                current[i].w = original[i].h;
                current[i].h = original[i].w;
            }
            else{
                current[i].w = original[i].w;
                current[i].h = original[i].h;
            }
        }
        
        // All in a row
        {
            int total_w = current[0].w + current[1].w + current[2].w + current[3].w;
            int max_h = current[0].h;
            if(current[1].h > max_h) max_h = current[1].h;
            if(current[2].h > max_h) max_h = current[2].h;
            if(current[3].h > max_h) max_h = current[3].h;
            int area = total_w * max_h;
            if(area == min_area){
                int p = total_w < max_h ? total_w : max_h;
                int q = total_w < max_h ? max_h : total_w;
                // Check uniqueness
                int exists = 0;
                for(int k=0;k<final_count;k++) {
                    if(final_pairs[k].p == p && final_pairs[k].q == q){
                        exists = 1;
                        break;
                    }
                }
                if(!exists){
                    final_pairs[final_count].p = p;
                    final_pairs[final_count].q = q;
                    final_count++;
                }
            }
        }
        
        // All in a column
        {
            int max_w = current[0].w;
            if(current[1].w > max_w) max_w = current[1].w;
            if(current[2].w > max_w) max_w = current[2].w;
            if(current[3].w > max_w) max_w = current[3].w;
            int total_h = current[0].h + current[1].h + current[2].h + current[3].h;
            int area = max_w * total_h;
            if(area == min_area){
                int p = max_w < total_h ? max_w : total_h;
                int q = max_w < total_h ? total_h : max_w;
                // Check uniqueness
                int exists = 0;
                for(int k=0;k<final_count;k++) {
                    if(final_pairs[k].p == p && final_pairs[k].q == q){
                        exists = 1;
                        break;
                    }
                }
                if(!exists){
                    final_pairs[final_count].p = p;
                    final_pairs[final_count].q = q;
                    final_count++;
                }
            }
        }
        
        // Two rows: {0,1} vs {2,3}
        {
            int row1_w = current[0].w + current[1].w;
            int row1_h = current[0].h > current[1].h ? current[0].h : current[1].h;
            int row2_w = current[2].w + current[3].w;
            int row2_h = current[2].h > current[3].h ? current[2].h : current[3].h;
            int total_w = row1_w > row2_w ? row1_w : row2_w;
            int total_h = row1_h + row2_h;
            int area = total_w * total_h;
            if(area == min_area){
                int p = total_w < total_h ? total_w : total_h;
                int q = total_w < total_h ? total_h : total_w;
                int exists = 0;
                for(int k=0;k<final_count;k++) {
                    if(final_pairs[k].p == p && final_pairs[k].q == q){
                        exists = 1;
                        break;
                    }
                }
                if(!exists){
                    final_pairs[final_count].p = p;
                    final_pairs[final_count].q = q;
                    final_count++;
                }
            }
        }
        
        // Two rows: {0,2} vs {1,3}
        {
            int row1_w = current[0].w + current[2].w;
            int row1_h = current[0].h > current[2].h ? current[0].h : current[2].h;
            int row2_w = current[1].w + current[3].w;
            int row2_h = current[1].h > current[3].h ? current[1].h : current[3].h;
            int total_w = row1_w > row2_w ? row1_w : row2_w;
            int total_h = row1_h + row2_h;
            int area = total_w * total_h;
            if(area == min_area){
                int p = total_w < total_h ? total_w : total_h;
                int q = total_w < total_h ? total_h : total_w;
                int exists = 0;
                for(int k=0;k<final_count;k++) {
                    if(final_pairs[k].p == p && final_pairs[k].q == q){
                        exists = 1;
                        break;
                    }
                }
                if(!exists){
                    final_pairs[final_count].p = p;
                    final_pairs[final_count].q = q;
                    final_count++;
                }
            }
        }
        
        // Two rows: {0,3} vs {1,2}
        {
            int row1_w = current[0].w + current[3].w;
            int row1_h = current[0].h > current[3].h ? current[0].h : current[3].h;
            int row2_w = current[1].w + current[2].w;
            int row2_h = current[1].h > current[2].h ? current[1].h : current[2].h;
            int total_w = row1_w > row2_w ? row1_w : row2_w;
            int total_h = row1_h + row2_h;
            int area = total_w * total_h;
            if(area == min_area){
                int p = total_w < total_h ? total_w : total_h;
                int q = total_w < total_h ? total_h : total_w;
                int exists = 0;
                for(int k=0;k<final_count;k++) {
                    if(final_pairs[k].p == p && final_pairs[k].q == q){
                        exists = 1;
                        break;
                    }
                }
                if(!exists){
                    final_pairs[final_count].p = p;
                    final_pairs[final_count].q = q;
                    final_count++;
                }
            }
        }
        
        // Two columns: {0,1} vs {2,3}
        {
            int col1_w = (current[0].w > current[1].w) ? current[0].w : current[1].w;
            int col1_h = current[0].h + current[1].h;
            int col2_w = (current[2].w > current[3].w) ? current[2].w : current[3].w;
            int col2_h = current[2].h + current[3].h;
            int total_w = col1_w + col2_w;
            int total_h = (col1_h > col2_h) ? col1_h : col2_h;
            int area = total_w * total_h;
            if(area == min_area){
                int p = total_w < total_h ? total_w : total_h;
                int q = total_w < total_h ? total_h : total_w;
                int exists = 0;
                for(int k=0;k<final_count;k++) {
                    if(final_pairs[k].p == p && final_pairs[k].q == q){
                        exists = 1;
                        break;
                    }
                }
                if(!exists){
                    final_pairs[final_count].p = p;
                    final_pairs[final_count].q = q;
                    final_count++;
                }
            }
        }
        
        // Two columns: {0,2} vs {1,3}
        {
            int col1_w = (current[0].w > current[2].w) ? current[0].w : current[2].w;
            int col1_h = current[0].h + current[2].h;
            int col2_w = (current[1].w > current[3].w) ? current[1].w : current[3].w;
            int col2_h = current[1].h + current[3].h;
            int total_w = col1_w + col2_w;
            int total_h = (col1_h > col2_h) ? col1_h : col2_h;
            int area = total_w * total_h;
            if(area == min_area){
                int p = total_w < total_h ? total_w : total_h;
                int q = total_w < total_h ? total_h : total_w;
                int exists = 0;
                for(int k=0;k<final_count;k++) {
                    if(final_pairs[k].p == p && final_pairs[k].q == q){
                        exists = 1;
                        break;
                    }
                }
                if(!exists){
                    final_pairs[final_count].p = p;
                    final_pairs[final_count].q = q;
                    final_count++;
                }
            }
        }
        
        // Two columns: {0,3} vs {1,2}
        {
            int col1_w = (current[0].w > current[3].w) ? current[0].w : current[3].w;
            int col1_h = current[0].h + current[3].h;
            int col2_w = (current[1].w > current[2].w) ? current[1].w : current[2].w;
            int col2_h = current[1].h + current[2].h;
            int total_w = col1_w + col2_w;
            int total_h = (col1_h > col2_h) ? col1_h : col2_h;
            int area = total_w * total_h;
            if(area == min_area){
                int p = total_w < total_h ? total_w : total_h;
                int q = total_w < total_h ? total_h : total_w;
                int exists = 0;
                for(int k=0;k<final_count;k++) {
                    if(final_pairs[k].p == p && final_pairs[k].q == q){
                        exists = 1;
                        break;
                    }
                }
                if(!exists){
                    final_pairs[final_count].p = p;
                    final_pairs[final_count].q = q;
                    final_count++;
                }
            }
        }
        
        // Three rows: group of 3 and 1
        for(int single=0; single<4; single++) {
            int group_w = 0;
            int group_h = 0;
            for(int i=0;i<4;i++) {
                if(i != single){
                    group_w += current[i].w;
                    if(current[i].h > group_h) group_h = current[i].h;
                }
            }
            int single_w = current[single].w;
            int single_h = current[single].h;
            int total_w = (group_w > single_w) ? group_w : single_w;
            int total_h = group_h + single_h;
            int area = total_w * total_h;
            if(area == min_area){
                int p = total_w < total_h ? total_w : total_h;
                int q = total_w < total_h ? total_h : total_w;
                int exists = 0;
                for(int k=0;k<final_count;k++) {
                    if(final_pairs[k].p == p && final_pairs[k].q == q){
                        exists = 1;
                        break;
                    }
                }
                if(!exists){
                    final_pairs[final_count].p = p;
                    final_pairs[final_count].q = q;
                    final_count++;
                }
            }
        }
        
        // Three columns: group of 3 and 1
        for(int single=0; single<4; single++) {
            int group_w = 0;
            int group_h = 0;
            for(int i=0;i<4;i++) {
                if(i != single){
                    if(current[i].w > group_w) group_w = current[i].w;
                    group_h += current[i].h;
                }
            }
            int single_w = current[single].w;
            int single_h = current[single].h;
            int total_w = group_w + single_w;
            int total_h = (group_h > single_h) ? group_h : single_h;
            int area = total_w * total_h;
            if(area == min_area){
                int p = total_w < total_h ? total_w : total_h;
                int q = total_w < total_h ? total_h : total_w;
                int exists = 0;
                for(int k=0;k<final_count;k++) {
                    if(final_pairs[k].p == p && final_pairs[k].q == q){
                        exists = 1;
                        break;
                    }
                }
                if(!exists){
                    final_pairs[final_count].p = p;
                    final_pairs[final_count].q = q;
                    final_count++;
                }
            }
        }
    }
    
    // Remove duplicates and sort
    pq_pair unique_pairs[100];
    int unique_count = 0;
    for(int i=0;i<pair_count;i++) {
        int exists = 0;
        for(int j=0;j<unique_count;j++) {
            if(pairs[i].p == unique_pairs[j].p && pairs[i].q == unique_pairs[j].q){
                exists = 1;
                break;
            }
        }
        if(!exists){
            unique_pairs[unique_count] = pairs[i];
            unique_count++;
        }
    }
    
    // Sort the unique_pairs
    qsort(unique_pairs, unique_count, sizeof(pq_pair), compare_pairs);
    
    // Print the result
    printf("%d\n", min_area);
    for(int i=0;i<unique_count;i++) {
        printf("%d %d\n", unique_pairs[i].p, unique_pairs[i].q);
    }
    
    return 0;
}