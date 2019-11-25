#include <iostream>
#include <cstdio>
#include <map>
#include <cstring>
#include <string>
using namespace std;

int main() {
    char buffer[30], en[11], forei[11];
    map<string, string> dict;
    while (fgets(buffer, sizeof(buffer), stdin)) {
        if (strcmp(buffer, "\n") == 0) break;
        sscanf(buffer, "%s %s", en, forei);
        dict[string(forei)] = string(en);
    }
    while (scanf("%s", buffer) == 1) {
        if (dict.count(buffer)) {
            cout << dict[string(buffer)] << endl; 
        } else {
            cout << "eh" << endl; 
        }
    }
    return 0;
}