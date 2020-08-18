#include <iostream>
using namespace std;
//logic  any power of two will only have a single 1 ints binary representation
// 16 is input represented as 10000 we riht shift and add last digit to count if count is greater than one its false 
bool ispowoftwo(int n){
    if(n<=0){
        return false;
    }
    int num=0;
    while(n>=0){
        //checking last bit is one or zero
        num+=(n&1);
        //right shift
        n=n>>1;
        if(num>1){
            return false;
        }

    }
    return true;
}
int main(){
    int no;
    cin>>no;
    int res=0;
    int temp;
    for(int i=0; i<no; i++){
        cin>>temp;
      if(ispowoftwo(temp)){
          res++;
      }
    }
     cout<<res<<endl;
    return 0;
}
