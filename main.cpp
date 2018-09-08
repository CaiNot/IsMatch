#include <iostream>
#include <string>
#include <queue>

using namespace std;

bool canMatch(string &s, string &lastWord, int checkPoint) {
    int length = lastWord.size(), sLength = s.size();
    int i = checkPoint, j = 0;
    for (; j < length && i < sLength; j++, i++) {
        if (s[i] != lastWord[j] && lastWord[j] != '.') {
            return false;
        }
    }
    if (j == length)
        return true;
    else return false;
}

bool isMatch(string s, string p) {
    string lastWord = "", tempWord = "",
            sTemp = "", lastTarget = "";
    queue<string> pQueue;
    int pLength = p.size(), sLength = s.size();

    for (int i = 0; i < pLength; i++) {
        if (p[i] == '.' || p[i] == '*') {
            if (tempWord != "") {
                pQueue.push(tempWord);
            }
            if (p[i] == '*') {
                if (i + 1 < pLength) {
                    if (p[i + 1] == tempWord[tempWord.size() - 1]) {
                        tempWord = p[i];
                        pQueue.push(tempWord);
                        i++;
                        tempWord = "";
                        continue;
                    }
                }
            }
            tempWord = p[i];
            pQueue.push(tempWord);

            tempWord = "";
        } else tempWord += p[i];
    }
    if (tempWord != "")
        pQueue.push(tempWord);
    int checkPoint = 0, lastPoint = 0;

    while (!pQueue.empty()) {
        tempWord = pQueue.front();
        pQueue.pop();
        if (tempWord == ".") {
            checkPoint++;
        } else if (tempWord == "*") {
            sTemp = lastWord.substr(0, lastWord.size() - 1);
            if (canMatch(s, sTemp, checkPoint)) {
                checkPoint += sTemp.size();
            }
            lastPoint = checkPoint;
            int lastLength = lastWord.size();
            for (int i = 0; i < lastLength; i++) {
                if (lastPoint == checkPoint) {
                    sTemp = lastWord.substr(i, lastWord.size());
                    while (canMatch(s, sTemp, checkPoint)) {
                        checkPoint += sTemp.size();
                    }
                } else {
                    break;
                }
            }
        } else {
            if (pQueue.empty() || pQueue.front() != "*") {
                if (canMatch(s, tempWord, checkPoint)) {
                    checkPoint += tempWord.size();
                } else return false;
            }
        }
        if (tempWord == "*")
            lastWord = "";
        else lastWord = tempWord;
        if (checkPoint >= sLength)
//        {
//            while (!pQueue.empty()){
//                tempWord=pQueue.front();
//                pQueue.pop();
//                string nextWord="";
//                if(!pQueue.empty()){
//                    nextWord=pQueue.front();
//                    if(nextWord=="*"){
//                        pQueue.pop();
//                    }
//                }
//            }
//        }
            return pQueue.empty();
    }
    return checkPoint >= sLength;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    cout << isMatch("aaa", "ab*a*c*a") << endl;
    cout << isMatch("aaa", "ab*ac*a") << endl;

    cout << isMatch("aa", "a") << endl;
    cout << isMatch("aa", "a*") << endl;
    cout << isMatch("aa", ".*") << endl;
    cout << isMatch("aaa", "a*a") << endl;
    cout << isMatch("mississippi", "mis*is*p*.") << endl;
    cout << isMatch("mississippi", "mis*is*ip*.") << endl;
    cout << isMatch("ab", "ab*c") << endl;

    return 0;
}