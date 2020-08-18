#include<iostream>
using namespace std;
//logic bitwise of xor of all numbers gives the  odd ocurreing element 
// Time complexity O(N)
int find(int ar[],int size){

    int res=0;
    for(int i=0; i<size; i++){
        res=res^ar[i];
        //xor every element
    }
    return res;
}
int main(){
int n;
cin>> n;
int num=2*(n+1);
int arr[num];
for(int i=0; i<num; i++){
 cin>>arr[i];
}
    cout<<find(arr,num)<<endl;

}
