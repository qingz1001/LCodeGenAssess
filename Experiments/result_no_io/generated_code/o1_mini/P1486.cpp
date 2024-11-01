#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef pair<int, int> pii;

// Ordered set with pair<int, int> to handle duplicates
typedef tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> ordered_set_t;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    ll min_wage;
    cin >> n >> min_wage;
    ordered_set_t os;
    ll global_offset = 0;
    ll total_left = 0;
    int unique_id = 0;
    while(n--){
        char cmd;
        ll k;
        cin >> cmd >> k;
        if(cmd == 'I'){
            ll actual_wage = k;
            if(actual_wage >= min_wage){
                ll stored_wage = actual_wage - global_offset;
                os.insert({(int)stored_wage, unique_id++});
            }
        }
        else if(cmd == 'A'){
            global_offset += k;
        }
        else if(cmd == 'S'){
            global_offset -= k;
            ll threshold = min_wage - global_offset;
            if(threshold > 0){
                // Find the first wage >= threshold
                // All wages < threshold need to be removed
                pii search_pair = {(int)threshold, 0};
                auto it = os.lower_bound(search_pair);
                ll cnt = distance(os.begin(), it);
                total_left += cnt;
                // Erase all elements before it
                os.erase(os.begin(), it);
            }
            else{
                // threshold <=0, no one leaves
            }
        }
        else if(cmd == 'F'){
            ll size = os.size();
            if(k > size){
                cout << "-1\n";
            }
            else{
                // k-th largest is (size -k)-th smallest
                auto it = os.find_by_order(size - k);
                ll wage = it->first + global_offset;
                cout << wage << "\n";
            }
        }
    }
    cout << total_left;
}