#include <bits/stdc++.h>
using namespace std;

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

int main() {
  cout << "При вводе с клавиатуры используйте следующие обозначения:" << endl 
  << "! - отрицание" << endl
  << "| - штрих Шеффера" << endl
  << "* - конъюнкция" << endl
  << "+ - дизъюнкция" << endl
  << "^ - сумма по модулю 2" << endl
  << "@ - имликация" << endl
  << "= - эквивалентность" << endl << endl
  << "Введите формулу:" << endl;

  set<char> symbols = {'!', '|', '*', '+', '^', '@', '='};

  string s;
  cin >> s;

  bool f1 = checkBracketBalance(s), f2 = 0;
  
  bool cur = isalpha(s[0]);
  for (int i = 1; i < s.length(); ++i) {
    if (s[i] == '(' || s[i] == ')' || s[i] == '!' || s[i] == ' ')
      continue;

    if ((cur && !isalpha(s[i]) && symbols.count(s[i])) || (!cur && isalpha(s[i])))
      cur = !cur;
    else {
      f2 = 1;
      break;
    }
  }

  if (!f1 && !f2) 
    puts("Формула");
  else
    puts("Не формула");

  return 0;
}