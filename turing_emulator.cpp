#include <bits/stdc++.h>
using namespace std;

/*
Contents of input.txt file
##############################
6 3 baaaa
_ _N0 _N0 _N0 _N0 - -
a aR2 aR3 aN0 bL5 - bN0
b bR2 bR4 aL6 bN0 aN0 -
##############################
*/

const int N = 1e8;

vector<char> r(N, '_');
int s = 1, i = N / 2, n, k, mni = i, mxi = i;
string st, line;
char bst;

map<char, int> mp = {{'R', 1}, {'L', -1}, {'N', 0}};
map<pair<char, int>, string> m;

void execUtil(char let, char dir, int cnd) {
  r[i] = let;

  if (!cnd) {
    for (int j = min(N / 2, mni); j < max(mxi + 1, N / 2 + (int)line.length()); ++j)
      cout << r[j];
    exit(0);
  }

  i += mp[dir], s = cnd;
  mxi = max(mxi, i), mni = min(mni, i);
}

void exec(string x) {
  execUtil(x[0], x[1], x[2] - '0');
}

int main() {
  freopen("input.txt", "r", stdin);

  cin >> n >> k >> line; //number of conditions, alphabet capacity, initial frame
  for (int i = 0; i < k; ++i)
    for (int j = 0; j < n + 1; ++j) {
      cin >> st;
      if (!j)
        bst = st[0];

      if (st != "-" && j) 
        m.insert({{bst, j}, st}); 
    }
      
  for (int j = i; j < i + (int)line.length(); ++j)
    r[j] = line[j - i]; 

  while (1) 
    exec(m[{r[i], s}]);


  return 0;
}