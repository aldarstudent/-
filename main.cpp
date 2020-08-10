#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>

using namespace std;

class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        if (events.count(year) == 0) {
            events[year].second = "";
        }
        events[year].first = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
        if (events.count(year) == 0) {
            events[year].first = "";
        }
        events[year].second = last_name;
    }
    string GetFullName(int year) {
        if (events.empty() || year < (*events.begin()).first) {
            return "Incognito";
        }
        string CurName = "", CurLast = "";

        for (const auto& i : events) {
            if (i.first <= year && i.second.first != "") {
                CurName = i.second.first;
            }
            if (i.first <= year && i.second.second != "") {
                CurLast = i.second.second;
            }
        }
        if (CurName == "") {
            return CurLast + " with unknown first name";
        } else if (CurLast == "") {
            return CurName + " with unknown last name";
        } else {
            return CurName + " " + CurLast;
        }
    }
    string GetFullNameWithHistory(int year) {
        string CurName, CurLast;
        vector<string> names, last;
        if (events.empty() || year < (*events.begin()).first) {
            return "Incognito";
        }
        // for names
        for (const auto &i : events) {
            if (i.first <= year && i.second.first != "") {
                if (i.second.first != CurName && CurName != "") {
                    names.push_back(CurName);
                }
                CurName = i.second.first;
            }
        }
        // for surnames
        for (const auto &i : events) {
            if (i.first <= year && i.second.second != "") {
                if (i.second.second != CurLast && CurLast != "") {
                    last.push_back(CurLast);
                }
                CurLast = i.second.second;
            }
        }
        string n_res, s_res;
        if (!last.empty()) {
            s_res += " (" + last[last.size() - 1];
            if (last.size() > 1) {
                for (int i = last.size() - 1; i > 0; --i) {
                    s_res += ", " + last[i - 1];
                }
            }
            s_res += ")";
        }
        if (!names.empty()) {
            n_res += " (" + names[names.size() - 1];
            if (names.size() > 1) {
                for (int i = names.size() - 1; i > 0; --i) {
                    n_res += ", " + names[i - 1];
                }
            }
            n_res += ")";
        }
        if (CurName == "") {
            return CurLast + s_res + " with unknown first name";
        } else if (CurLast == "") {
            return CurName + n_res + " with unknown last name";
        } else {
            return CurName + n_res + " " + CurLast + s_res ;
        }
    }

private:
    map<int, pair<string, string>> events;
};

int main() {
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1990, "Polina");
    person.ChangeLastName(1990, "Volkova-Sergeeva");
    cout << person.GetFullNameWithHistory(1990) << endl;

    person.ChangeFirstName(1966, "Pauline");
    cout << person.GetFullNameWithHistory(1966) << endl;

    person.ChangeLastName(1960, "Sergeeva");
    for (int year : {1960, 1967}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeLastName(1961, "Ivanova");
    cout << person.GetFullNameWithHistory(1967) << endl;

    return 0;
}

