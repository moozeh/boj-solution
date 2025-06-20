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

int dp[50][50][1 << 6];
int n, m;
int shortest = -1;

char board[50][50];

int dirs[4][2] = {
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0}
};

void backtrack(int y, int x, int key_state) {
    for(int i=0; i<4; ++i) {
        int dy = y + dirs[i][0];
        int dx = x + dirs[i][1];
        if (dy < 0 || dx < 0 || dy >= n || dx >= m) continue;
        if (board[dy][dx] == '#') continue;

        if (board[dy][dx] == '1') {
            if (dp[dy][dx][key_state] == -1 || dp[dy][dx][key_state] > dp[y][x][key_state] + 1) {
                dp[dy][dx][key_state] = dp[y][x][key_state] + 1;
                shortest = (shortest == -1 || dp[dy][dx][key_state] < shortest) ? dp[dy][dx][key_state] : shortest;
            }
            continue;
        }

        if ('a' <= board[dy][dx] && board[dy][dx] <= 'f') {
            // 키를 안가진 상태에서 소문자를 만난 경우
            int target_key = board[dy][dx] - 'a';

            // 키를 가져가는게 최대 이득임
            int taken_key_state = (1 << target_key) | key_state;
            if (dp[dy][dx][taken_key_state] == -1 || dp[dy][dx][taken_key_state] > dp[y][x][key_state] + 1) {
                dp[dy][dx][taken_key_state] = dp[y][x][key_state] + 1;
                backtrack(dy, dx, taken_key_state);
            }
        }

        // 현재 키를 가진 상태의 DP가 있을 경우(?) - 
        if ('A' <= board[dy][dx] && board[dy][dx] <= 'F') {
            int required_key_num = board[dy][dx] - 'A';
            
            int validate = key_state & (1 << required_key_num);
            
            // 키를 가지고 있어야만 한다!
            if (validate) {
                if (dp[dy][dx][key_state] == -1 || dp[dy][dx][key_state] > dp[y][x][key_state] + 1) {
                    dp[dy][dx][key_state] = dp[y][x][key_state] + 1;
                    backtrack(dy, dx, key_state);
                }
            }
        }

        // 그냥 공간이면 dp 갱신될때만 움직이기
        if (board[dy][dx] == '.' || board[dy][dx] == '0') {
            if (dp[dy][dx][key_state] == -1 || dp[dy][dx][key_state] > dp[y][x][key_state] + 1) {
                dp[dy][dx][key_state] = dp[y][x][key_state] + 1;
                backtrack(dy, dx, key_state);
            }
        }
    }
}

int main(){
    fastio
    // a , b , c , d , e , f 비트마스킹

    int x, y;
    memset(dp, -1, sizeof(dp));
    cin>>n>>m;

    for(int i=0; i<n; ++i) {
        string line; cin>>line;
        for(int j=0; j<m; ++j) {
            board[i][j] = line[j];
            if (board[i][j] == '0') {
                y = i;
                x = j;     
            }
        }
    }
    
    dp[y][x][0] = 0;
    backtrack(y, x, 0);
    
    cout<<shortest<<endl;
}