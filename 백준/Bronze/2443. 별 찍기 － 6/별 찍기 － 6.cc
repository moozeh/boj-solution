#include<bits/stdc++.h>
#define fastio std::ios_base::sync_with_stdio(false); std::cin.tie(nullptr);std::cout.tie(nullptr);
#define endl '\n'
using namespace std;
using pii = pair<int, int>;
using psi = pair<string, int>;
using pss = pair<string, string>;
using pis = pair<int, string>;
using pci = pair<char, int>;
using pic = pair<int, char>;
using qi = queue<int>;
using qpii = queue<pii>;
using vi = vector<int>;
using vvi = vector<vector<int>>;

int main(){
    fastio
    int n; cin>>n;
    for(int i=0; i<n; ++i) {
        for(int j=0; j<i; ++j) {
            cout<<' ';
        }
        for(int j=0; j<2*(n - i) - 1; ++j) {
            cout<<'*';
        }
        cout<<endl;
    }
}