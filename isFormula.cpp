#include <bits/stdc++.h>
using namespace std;

set<char> symbols = {'!', '|', '*', '+', '^', '@', '='};

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

bool checkNegativeAndBrackets(string s) {
  for (int i = 1; i < s.length(); ++i)
    if (s[i] == '!' && isalpha(s[i - 1]))
      return 1;

  for (int i = 1; i < s.length(); ++i)
    if (s[i] == ')' && symbols.count(s[i - 1]))
      return 1;

  for (int i = 0; i < s.length() - 1; ++i)
    if (s[i] == '(' && symbols.count(s[i + 1]))
      return 1;

  if ((symbols.count(s[0]) && s[0] != '!') || symbols.count(s[(int)s.length() - 1]))
    return 1;

  if (s[0] == '(' && s[(int)s.length() - 1] == ')')
    return 1;

  return 0;
}

bool isFormula(string s) {
  bool f1 = checkBracketBalance(s), f2 = 0, f3 = checkNegativeAndBrackets(s);

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

  if (!f1 && !f2 && !f3)
    return 1;
  else
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

  string s;
  cin >> s;

  if (isFormula(s))
    puts("Формула");
  else
    puts("Не формула");

  return 0;
}
