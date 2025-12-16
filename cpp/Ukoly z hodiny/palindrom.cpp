#include <bits/stdc++.h>
using namespace std;

void isPalindrome (string str) {
  
    int left = 0, right = str.size() - 1;
  
    bool flag = true;
 
    while (left < right) {


        if (str[left] != str[right]) {
            flag = false;
            break;
        }
        left++;
        right--;
    }
 
    if (flag)
        cout << "\"" << str
      << "\" je palindrom." << endl;
     
    else
        cout << "\"" << str
      << "\" není palindrom." << endl;
}

int main() {
    string a;
    cout << "napiste slevo pro porovnani:    ";
    cin >> a;   
    isPalindrome(a);        
    return 0;
}