#include "node.h"

Node *  buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t q;
  //push char elements into queue
  for(unsigned i =0;i<257;i++){
    if(counts[i]!=0){
      q.push(new Node(i,counts[i]));
    }
  }
  while(q.size()!=1){
    Node * temp1=q.top();
    q.pop();//remove the top
    Node * temp2=q.top();
    q.pop();//remove
    Node * temp3=new Node(temp1,temp2);
    q.push(temp3);
  }
  Node * ans = q.top();
  return ans;
}  
