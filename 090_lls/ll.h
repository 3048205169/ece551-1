#ifndef _LL_H_
#define _LL_H_
#include <cstdlib>
#include <exception>
#include <assert.h>
#include <iostream>
//YOUR CODE GOES HERE
#include<cstdlib>
template<typename T>
class LinkedList{
 private:
  class Node{
  public:
    T data;
    Node * next;
    Node * prev;
  Node(const T &item,Node * a,Node *b):data(item),next(a),prev(b){}
  };
  Node * head;
  Node * tail;
  size_t size;
 public:
 LinkedList():head(NULL),tail(NULL),size(0){}
 LinkedList(const LinkedList &rhs):head(NULL), tail(NULL),size(rhs.size){
 Node * temp = rhs.tail;
    while (temp != NULL) {
      this->addFront(temp->data);
      temp = temp->prev;
    }
  }
  LinkedList & operator=(const LinkedList & rhs){
if (this != &rhs) {
      LinkedList tmp(rhs);
      //delete old data
      while (head != NULL) {
        Node * dummy = head->next;
        delete head;
        head = dummy;
      }

      head = tmp.head;
      tail = tmp.tail;
      size = tmp.size;

      tmp.head = NULL;
      tmp.tail = NULL;
      tmp.size = 0;
    }
    return *this;
  }
  void addFront(const T &item){
    head=new Node(item,head,NULL);
    if(tail==NULL){
      tail=head;
    }
    else{
      head->next->prev=head;
    }
    size++;
  }
  void addBack(const T &item){
    tail=new Node(item,NULL,tail);
    if(head==NULL){
      head=tail;
    }
    else{
      tail->prev->next=tail;
    }
    size++;
  }
  int find(const T &item){
    Node * current=head;
    //record number
    if(head==NULL){
      return -1;
    }
    
    int temp=0;
    while(current!=NULL&&current->data!=item){
      temp++;
      current=current->next;
    }
    //check if there is item in the list
    if(current==NULL){
      return -1;
    }
    else{
      return temp;
    }
    
  }
  bool remove(const T &item){
    Node * current=head;
    int a = find(item);
    if(a==-1){
      return false;
    }
    if(current==NULL){
      return false;
    }
    while(current!=NULL && current->data!=item){
      current=current->next;
    }
    if(current==head && current ==tail){
      head = NULL;
      tail =NULL;
    }
    else if(current==head){
      head=current->next;
      current->next->prev=NULL;
    }
    else if(current==NULL){
      return false;
    }
    else if(current == tail){
      tail=current->prev;
      current->prev->next=NULL;
      
    }
    else{
      current->prev->next=current->next;
      current->next->prev=current->prev;
      
    }
    delete current;
    size--;
    return true;


  }
  T& operator[](int index){
    try{
      Node * current=head;
      for(int i=0;i<index;i++){
	current=current->next;
      }
      return current->data;
    }
    catch(std::exception &e){
      std::cout << e.what() << std::endl;
    }
    
  }
  const T& operator[](int index) const{
    try{
      Node * current=head;
      for(int i=0;i<index;i++){
	current=current->next;
      }
      return current->data;
    }
    catch(std::exception &e){
      std::cout << e.what() << std::endl;
    }
   }
  int getSize() const { return size; }
  ~LinkedList(){
    while(head!=NULL){
      Node * temp=head->next;
      delete head;
      head=temp;
    }
    tail=NULL;
    size=0;
  }
};



#endif
