#include <iostream>
#include <string>

using namespace std;

string* format(int k,string s1,int len,int n) {
    string* sf=new string[n+2]();
    int j=0;

    for(int i=0;i<k-1;i++) {
        //第i组
       for(int p=0;p<k;p++) {
           sf[i]+=s1[j];
           j++;
       }
    }
    //第k组长度为len
    for(int p=0;p<len;p++) {
        sf[k-1]+=s1[j];
        j++;
    }
    //
    for(int i=k;i<n;i++) {
        //第i组
        for(int p=0;p<k;p++) {
            sf[i]+=s1[j];
            j++;
        }
    }
    return sf;
}

 bool check(string* sf,int k,int n) {
    for(int i=0;i<n;i++) {
        if(i==k-1)continue;
         int cnt=0;
        for(int p=0;p<k;p++) {
            if(std::isdigit(sf[i][p]))cnt++;
        }
        if(cnt==k||cnt==0)return false;
    }
    return true;
}

int main() {
    string s;
    int k;
    cin>>s>>k;
    string s1;
    int j=0;
    //deal the s-->s1
    for(int i=0;i<s.length();i++) {
        if(s[i]=='-')continue;
        if(s[i]<='z'&&s[i]>='a')s[i]+='A'-'a';
        s1+=(s[i]);
    }
    //
     if(s1.empty()) {
         cout<<"INVALID";
         return 0;
     }
    int len=s1.length()%k;
    int n=s1.length()/k+1;
    if(len==0) {
        len=k;
        n--;
    }
    if(n<k){
        cout<<"INVALID";
        return 0;
    }
    string* ans=format(k,s1,len,n);
    if(!check(ans,k,n)) {
        cout<<"INVALID";
        delete[] ans;
        return 0;
    }

    for(int i=0;i<n;i++) {
        cout<<ans[i];
        if(i!=n-1)cout<<"-";
    }
   delete[] ans;
    return 0;
}