#include<iostream>
using namespace std;

bool check(int left,int right,int traget,int* S) {
    return S[right+1]-S[left]>=traget;
}

int* checklen(int len,int traget,int* S,int n) {
    int* index=new int [2]();
    for(int i=0;i<=n-len;i++) {
        //i----left i+len-1---right
        if(check(i,i+len-1,traget,S)) {
            index[0]=i;
            index[1]=i+len-1;
            break;
        }
    }
    //otherwise index==0
   return index;
}

int main() {
  int n=0;
    cin>>n;
    int* arr=new int[n]();
    for(int i=0;i<n;i++)cin>>arr[i];
    //提前计算前n项和
    int* S=new int[n+1]();
    S[1]=arr[0];
    for(int i=2;i<=n;i++) {
        S[i]=S[i-1]+arr[i-1];
    }
    int target=0;
    cin>>target;
    //len---2分长度，检验
    int left=1;
    int right=n;
    if(!check(0,n-1,target,S)){
        cout<<0;
        return 0;
    }else if(arr[0]>=target) {
        cout<<0;
        return 0;
    }
    int mid=(left+right)/2;
    int* index;
    while(left!=right) {
       //[left,right]
        index=checklen(mid,target,S,n);
        if(index[1]!=0)right=mid;
        else left=mid+1;
        mid=(left+right)/2;
    }
    index=checklen(mid,target,S,n);
    if(index[0]==index[1])cout<<index[0];
    else cout<<index[0]+index[1];
   delete[] arr;
    return 0;
}
