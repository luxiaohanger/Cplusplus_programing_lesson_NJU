#include <bits/stdc++.h>
using namespace std;

void add(string str,array<int,26>& book) {
    for(char c:str) {
        book[c-'a']++;
    }
    return;
}

string query(array<int,26> book) {
   string ans;
    int max=0;
    for(int i=0;i<26;i++) {
        //when book[i]==0 don`t let it in
        if(book[i]==0)continue;
        if(book[i]>max) {
            max=book[i];
            ans.clear();
            ans+=char(i+'a');
        }else if(book[i]==max) {
            ans+=char(i+'a');
        }
    }
    if(max==0) {
        ans+="null";
    }
    return ans;
}
int main() {
    string str;
   array<int,26> book {};

   int q=0;
    cin>>q;
   string cmd;
    while (q--) {
     cin>>cmd;
        if(cmd=="add") {
            cin>>str;
            add(str,book);
        }else if(cmd=="query") {
            string ans=query(book);
           cout<<ans<<endl;
        }
    }
    return 0;
}
