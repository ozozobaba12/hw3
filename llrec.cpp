#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************


void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot){
   
   
    smaller=nullptr;
    larger=nullptr;
    
    
    if (head == nullptr){
        return;
    }
    
      Node* Next=head->next;
    
    if (head->val <= pivot) {
        smaller=head; 
        head=Next;       
        
        llpivot(head, smaller->next, larger, pivot);
    } 
    
    else {
        larger=head;
        head=Next;   
        llpivot(head, smaller, larger->next, pivot);
    }
    
    
    head = nullptr;

}