#include <bits/stdc++.h>
using namespace std;

const int N = 55;
int vis[N] = {1000}, slen;

set<char> symbols = {'!', '|', '*', '+', '^', '@', '=', '#'};
multimap<pair<int, int>, string> res;

void bfs(string s, int col, char sym) {
  for (int i = 0; i < s.length(); ++i) {
    if (vis[i] % 50 != 0)
      continue;

    if (s[i] == sym) {
      vis[i] += col;
      for (int j = i + 1;; ++j) {
        if (j == s.length() || symbols.count(s[j]) && s[j] != sym && s[j] != '!' || s[j] == ')' || vis[j] % 50 != 0)
          break;
        vis[j] += col;
      }
      for (int j = i - 1;; --j) {
        if (j == -1 || symbols.count(s[j]) && s[j] != sym && s[j] != '!' || s[j] == '(' || vis[j] % 50 != 0)
          break;
        vis[j] += col;
      }
    }
  }
}

void indexAssesment(string s) {
  int t = 0, L = 0;
  for (int i = 0; i < s.length(); ++i) {
    if (s[i] == '(') {
      vis[i] = t;
      t -= 50;
    }
    else if (s[i] == ')') {
      t += 50;
      vis[i] = t;
    }
    else
      vis[i] = t;
  }

  bfs(s, 1, '*');
  bfs(s, 2, '+');
  bfs(s, 3, '^');
  bfs(s, 4, '|');
  bfs(s, 5, '#');
  bfs(s, 6, '@');
  bfs(s, 7, '=');

  for (int i = 1; i < s.length(); ++i)
    if (s[i] == '(' && s[i - 1] == '!')
      vis[i - 1] = vis[i], vis[i]++;

}

bool checkBracketBalance(string s) {
  int bal = 0;
  for (auto i : s) {
    if (i == '(')
      bal++;

    if (i == ')')
      bal--;
  }

  if (bal)
    return 1;

  return 0;
}

bool checkNegativeAndBrackets(string s, int l, int r, string dp) {
  for (int i = 1; i < s.length(); ++i)
    if (s[i] == '!' && isalpha(s[i - 1]))
      return 1;

  for (int i = 1; i < s.length(); ++i)
    if (s[i] == ')' && symbols.count(s[i - 1]))
      return 1;

  for (int i = 0; i < s.length() - 1; ++i)
    if (s[i] == '(' && symbols.count(s[i + 1]) && s[i + 1] != '!')
      return 1;

  if ((symbols.count(s[0]) && s[0] != '!') || symbols.count(s[(int)s.length() - 1]))
    return 1;

  if (l && dp[l - 1] == '(' && r != dp.length() - 1 && dp[r + 1] == ')')
    return 1;

  //if (s[0] == '(' && s[(int)s.length() - 1] == ')')
  //  return 1;

  return 0;
}

void isFormula(int l, int r, string s, string dp) {
  bool f1 = checkBracketBalance(s), f2 = 0, f3 = checkNegativeAndBrackets(s, l, r, dp);

  bool cur = isalpha(s[0]);

  int mxId = vis[l];
  int mnId = vis[l];
  for (int i = 1; i < s.length(); ++i) {
    if (s[i] == '(' || s[i] == ')' || s[i] == '!' || s[i] == ' ')
      continue;

    if ((cur && !isalpha(s[i]) && symbols.count(s[i])) || (!cur && isalpha(s[i])))
      cur = !cur;
    else {
      f2 = 1;
      break;
    }

    mxId = max(mxId, vis[l + i]);
    mnId = min(mnId, vis[l + i]);
  }

  bool f4 = 0;
  if (mxId != mnId && (l && vis[l - 1] == vis[l] || r != slen - 1 && vis[r + 1] == vis[r]) && s[0] != '(')
    f4 = 1;

  if (!f1 && !f2 && !f3 && !f4)
    res.insert({{mxId, (int)s.length()}, s});

}

int main() {
  cout << "При вводе с клавиатуры используйте следующие обозначения:" << endl
  << "! - отрицание" << endl
  << "| - штрих Шеффера" << endl
  << "# - стрелка Пирса" << endl
  << "* - конъюнкция" << endl
  << "+ - дизъюнкция" << endl
  << "^ - сумма по модулю 2" << endl
  << "@ - имликация" << endl
  << "= - эквивалентность" << endl << endl
  << "Введите формулу:" << endl;

  string s;
  cin >> s;

  slen = s.length();
  indexAssesment(s);

  for (int i = 0; i < s.length(); ++i)
    for (int j = i; j < s.length(); ++j)
      isFormula(i, j, s.substr(i, j - i + 1), s);

  if (res.empty())
    puts("Не формула");
  else {
    puts("Подформулы данной формулы:");
    for (auto i : res)
      cout << i.second << endl;
  }

  cout << s << endl;
  for (int i = 0; i < s.length(); ++i)
    cout << vis[i] << " ";
  //a@(b*!c)



  return 0;
}
