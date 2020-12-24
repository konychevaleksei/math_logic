//Метод Квайна
//Верхний регистр - отрицание
#include<bits/stdc++.h>
using namespace std;

struct implicant {
    string I;
    bool U = 0;
    vector<int> A;
};

string varInscriptions;

void setvarInscriptions(int n) {
    varInscriptions = "";
    for (int i = 0; i < n; i++)
        varInscriptions += 'a' + i;
}

string findImplicants(int bitmask, int bitSum) {
    string res = "";

    for (int i = bitSum - 1; i >= 0; i--) {
        res.push_back(varInscriptions[bitSum - i - 1]);
        if (!((bitmask >> i) & 1))
            res.back() = toupper(res.back());
    }

    return res;
}

vector<implicant> setVectorToZero(const string& f, int amOfTerms, int n) {
    vector<implicant> res;

    implicant curImpl;
    for (int i = 0; i < amOfTerms; i++) {
        if (f[i] == '0')
            continue;
        curImpl.I = findImplicants(i, n);
        res.push_back(curImpl);
    }

    return res;
}

bool areSimilar(string& a, string& b) {
    for (int i = 0; i < a.size(); i++) {
        if (tolower(a[i]) != tolower(b[i]))
            return 0;
    }
    return 1;
}

int areBoreders(string& a, string& b) {
    int cnt = 0, res = 0;

    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) {
            cnt++;
            res = i + 1;
        }
        if (cnt > 1) {
            res = 0;
            break;
        }
    }

    return res;
}

bool count(vector<implicant>& a, implicant b) {
    for (int i = 0; i < a.size(); i++)
        if (a[i].I == b.I)
            return 1;
    return 0;
}

vector<implicant> quineConcatenation(vector<implicant>& a) {
    vector<implicant> res;
    bool similarityCheck;
    int borderingCheck;
    implicant curImpl;

    for (int i = 0; i < a.size() - 1; i++) {
        for (int j = i + 1; j < a.size(); j++) {
            similarityCheck = areSimilar(a[i].I, a[j].I);
            borderingCheck = areBoreders(a[i].I, a[j].I);
            if (similarityCheck && borderingCheck) {
                borderingCheck--;
                curImpl.A.clear();
                curImpl.A = a[i].A;
                for (int z = 0; z < a[j].A.size(); z++)
                    curImpl.A.push_back(a[j].A[z]);

                a[i].U = a[j].U = 1;
                curImpl.I = a[i].I.substr(0, borderingCheck);
                curImpl.I += a[i].I.substr(borderingCheck + 1);
                if (!count(res, curImpl))
                    res.push_back(curImpl);
            }
        }
    }

    return res;
}

string beautify(vector<string>& a) {
    string res = "";

    res += a[0];
    for (int j = 1; j < a.size(); j++)
        res += " v " + a[j];

    res += "\n";
    return res;
}

int main() {
    freopen("in.txt", "r", stdin);
    int n;
    string f;
    cin >> n >> f;
    int amOfTerms = (1 << n), am1 = 0;
    if (f.size() != amOfTerms) {
        cout << "Invalid input! Error!\n";
        return 0;
    }
    for (int i = 0; i < f.size(); i++)
        if (f[i] == '1')
            am1++;

    //Проверка на константный ответ
    if (am1 == amOfTerms) {
        cout << 1;
        return 0;
    }
    else if (am1 == 0) {
        cout << 0;
        return 0;
    }

    setvarInscriptions(n); //Установка алфавита
    vector<vector<implicant>> tableConcatenation; //Таблица склеек

    vector<implicant> cube = setVectorToZero(f, amOfTerms, n);
    amOfTerms = cube.size();
    for (int i = 0; i < amOfTerms; i++)
        cube[i].A.push_back(i);

    do {
        tableConcatenation.push_back(cube);
        cube.clear();
        cube = quineConcatenation(tableConcatenation.back());
    } while (!cube.empty());

    vector<implicant> primary; //Непомеченные импликанты
    for (int i = 0; i < tableConcatenation.size(); i++) {
        for (int j = 0; j < tableConcatenation[i].size(); j++) {
            if (!tableConcatenation[i][j].U) {
                primary.push_back(tableConcatenation[i][j]);
            }
        }
    }

    int numPrim = primary.size();
    vector<vector<bool>> tableCoverage(numPrim, vector<bool>(amOfTerms, false)); //Таблица покрытия
    for (int i = 0; i < numPrim; i++)
        for (int j = 0; j < primary[i].A.size(); j++)
            tableCoverage[i][primary[i].A[j]] = 1;

    vector<bool> check(amOfTerms);
    vector<int> bitmaskans;
    // Перебор всех подмножеств простых импликантов при помощи битовых масок
    for (int bitmask = 1; bitmask < (1 << numPrim); bitmask++) {
        int cnt = 0;
        check = vector<bool>(amOfTerms, 0);
        for (int i = 0; i < numPrim; i++) {
            if (((bitmask >> i) & 1)) {
                for (int j = 0; j < amOfTerms; j++) {
                    if (tableCoverage[i][j] && !check[j]) {
                        cnt++;
                        check[j] = 1;
                        if (cnt == amOfTerms) {
                            bitmaskans.push_back(bitmask);
                        }
                    }
                }
            }
        }
    }
    // Вычисление количества переменных в формуле
    vector<int> cnt(bitmaskans.size());
    for (int i = 0; i < bitmaskans.size(); i++) {
        for (int j = 0; j < numPrim; j++) {
            if (((bitmaskans[i] >> j) & 1)) {
                cnt[i] += primary[j].I.size();
            }
        }
    }

    int mn = *min_element(cnt.begin(), cnt.end()); //Поиск минимального количества
    vector<vector<string>> ans;
    vector<string> curans;
    //Выборка только тех формул, которые минимальны
    for (int i = 0; i < bitmaskans.size(); i++) {
        if (cnt[i] != mn)
            continue;

        curans.clear();
        for (int j = 0; j < numPrim; j++) {
            if ((bitmaskans[i] >> j) & 1) {
                curans.push_back(primary[j].I);
            }
        }
        ans.push_back(curans);
    }
    //Построение и вывод ответа
    for (int i = 0; i < ans.size(); i++)
        cout << beautify(ans[i]);


    return 0;
}
