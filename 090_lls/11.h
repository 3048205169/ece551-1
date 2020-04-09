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
    Node * current = head;
    Node *temp=rhs.head;
    for(int i=0;i<size;i++){
      T res=temp->data;
      current=new Node(0,NULL,current);
      current=current->next;
      temp=temp->next;
    }
    tail=current;
  }
  LinkedList & operator=(const LinkedList & rhs){
    if(this !=&rhs){
      LinkedList tmp(rhs);
      while(head!=NULL){
	Node * temp=head->next;
	delete head;
	head =temp;
      }
      head=temp.head;
      tail=temp.tail;
      size=temp.size;
    }
    return *this;
  }
  void addFront(const T &item){
    head=new Node(T,head,NULL);
    if(tail==NULL){
      tail=head;
    }
    size++;
  }
  void addBack(const T &item){
    tail=new Node(T,NULL,tail);
    if(head==NULL){
      head=tail;
    }
    size++;
  }
  int find(const T &item){
    Node * current=head;
    //record number
    int temp=0;
    while(current->data!=item && current!=NULL){
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
    int pos = find(item);
    if (pos == -1) {
      return false;
    }
    else{
    Node ** current =& head;
    while((*current)->data!=item&&(*current!=NULL)){
      current=&(*current)->next;
    }
    if(*current==head){
      head=(*current)->next;
      current->next->prev=NULL;
      delete current;
    }
    else{
      Node *temp1=(*current)->next;
      Node *temp2=(*current)->prev;
      delete current;
      temp2->next=temp1;
      temp1->prev=temp2;
    }
    return EXIT_SUCCESS;
    }
  }
  T& operator[](int index){
    try{
      Node * current=head;
      for(int i=0;i<index;i++){
	current=current->next;
      }
    }
    catch(std::exception &e){
      std::cout << e.what() << std::endl;
    }
    return current->data;
  }
   const T& operator[](int index) const{
    try{
      Node * current=head;
      for(int i=0;i<index;i++){
	current=current->next;
      }
    }
    catch(std::exception &e){
      std::cout << e.what() << std::endl;
    }
    return current->data;
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
