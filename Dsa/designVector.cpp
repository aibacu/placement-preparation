#include <bits/stdc++.h>
using namespace std;

class myvector{
    public:
    int * arr;
    int size;
    int capacity;
    myvector(){
         size=0;
         capacity=1;
        arr= new int[capacity];
    }


    void resize_vector(){
        int capacity=2*capacity;
        int *temp=new int[capacity];
        for(int i=0;i<size;i++){
            temp[i]=arr[i];
        }
        arr=temp;

    }
    int insert(int a){
      if(size==capacity){
        resize_vector();
      }
      arr[size]=a;
      size++;

    }
void printVector(){
    for(int i=0;i<size;i++){
       cout<<arr[i]<<" ";
    }
}
int getsize(){
    return size;
}
int getele(int i){
    if(i<size) return arr[i];
    else return -1;
}
};
int main(){
    myvector v;
    v.insert(1);
    v.insert(2);
    v.insert(1);
    v.insert(2);
    v.insert(1);
    v.insert(2);
    v.insert(1);
    v.insert(2);
   cout<<"size of vecotr is: " <<v.getsize()<<endl;
    v.printVector();
    cout<<"   ele at this index: " <<v.getele(3)<<endl;
    return 0;
}