#include <bits/stdc++.h>
using namespace std;

class Node{
public:
int val;
Node* next;
  Node(int value){
     val=value;
     next=NULL;
   }
};

class Linklist{
   
    Node* head;
 public:
    Linklist(){
    head=nullptr;
    }

    void insert(int value){
        
          Node* newnode= new Node(value);
        if(head==nullptr){
            head=newnode;
        }
        else{
           Node*temp=head;
           while(temp->next!=NULL){
            temp=temp->next;
           }
           temp->next=newnode;
        }
    }

    void print(){
        Node*temp=head;
           while(temp!=NULL){
            cout<<temp->val<<" ";
            temp=temp->next;
           }
           return;
    }
};


int main (){
    Linklist a;
    a.insert(2);
    a.insert(2);
    a.insert(4);
    a.print();
    return 0;
}