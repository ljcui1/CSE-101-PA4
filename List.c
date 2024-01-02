//-----------------------------------------------------------------------------
// Name: Lia Cui
// CRUZID: ljcui
// Assignment Name: PA4
//
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "List.h"

// private Node type
typedef struct NodeObj* Node;

typedef struct NodeObj {
    void* data;
    Node next;
    Node prev;
} NodeObj;

//Node head = NULL;
//Node tail = NULL;

typedef struct ListObj {
    Node front;
    Node back;
    Node cursor;
    int length;
    int index;
} ListObj;

Node newNode(void* data) {
    Node N = (Node)calloc(1, sizeof(NodeObj));
	assert(N != NULL);
	N->prev = NULL;
	N->data = data;
	N->next = NULL;
	return(N);
    
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

List newList(){
    List L;
    L = calloc(1, sizeof(ListObj));
    assert(L != NULL);
    L->front = L->back = NULL;
    L->length = 0;
    L->index = -1;
    return(L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) { 
      clear(*pL); //fix
      free(*pL);
      *pL = NULL;
      pL = NULL;
   }
}

// Access functions -----------------------------------------------------------
// Returns the number of elements in L.
int length(List L){
    if( L==NULL ){
        printf("List Error: calling length() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return(L->length);
} 
// Returns index of cursor element if defined, -1 otherwise.
int index(List L){
    if( L==NULL ){
        printf("List Error: calling index() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if ( L->cursor == NULL ){
        return -1;
    }else{
        return L->index;
    }
}
// Returns front element of L. Pre: length()>0
void* front(List L){
    if( L==NULL ){
        printf("List Error: calling front() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return(L->front->data);
} 
// Returns back element of L. Pre: length()>0
void* back(List L){
    if( L==NULL ){
        printf("List Error: calling back() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return(L->back->data);
}
// Returns cursor element of L. Pre: length()>0, index()>=0
void* get(List L){
    if( L==NULL ){
        printf("List Error: calling get()) on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return(L->cursor->data);
}
// Returns true iff Lists A and B are in same state, and returns false otherwise.
/*bool equals(List A, List B){
    if( A==NULL || B==NULL ){
        printf("List Error: calling equals() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    bool eq;
    Node N, M;

    eq = ( A->length == B->length );
    N = A->front;
    M = B->front;
    while( eq && N!=NULL ){
        eq = ( N->data==M->data );
        N = N->next;
        M = M->next;
    }
    return eq;
} 
*/

// Manipulation procedures ----------------------------------------------------
// Resets L to its original empty state.
void clear(List L){
    if(L!=NULL) { 
      while( L->length!=0 ) { 
         deleteFront(L); 
      }
    }
}
// Overwrites the cursor element’s data with x.
// Pre: length()>0, index()>=0
void set(List L, void* x){
    Node N = L->cursor;
	if (N != NULL) {
		if (length(L) > 0 && index(L) >= 0) {
            void* u = L->cursor->data;
			L->cursor->data = x;
            L->index = index(L);
            free(u);
		}
	}
} 
// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L){
    if(L->length > 0){
        L->index = 0;
        L->cursor = L->front;
    }
}
// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L){
    if(L->length > 0){
        L->index = L->length - 1;
        L->cursor = L->back;
    }
}
// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L){
    if(L->cursor != NULL){
        if(L->cursor != L->front){
            L->index -= 1;
            L->cursor = L->cursor->prev;
        }else if (L->cursor == L->front){
            L->cursor = NULL;
            L->index = -1;
        }
    }
}
// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L){
    if(L->cursor != NULL){
        if(L->cursor != L->back){
            L->index += 1;
            L->cursor = L->cursor->next;
        }else if (L->cursor == L->back){
            L->cursor = NULL;
            L->index = -1;
        }
    }
}
// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, void* x){
    Node n = newNode(x);
    if(L->length > 0){
        n->next = L->front;
        L->front->prev = n;
        L->front = n;
        if(L->index != -1){
            L->index += 1;
        }
    }else{
        L->front = L->back = n;
    }
    L->length += 1;
}
// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, void* x){
    Node n = newNode(x);
    if(L->length > 0){
        n->prev = L->back;
        L->back->next = n;
        L->back = n;
        
    }else{
        L->back = L->front = n;
    }
    
    L->length += 1;
}
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, void* x){
    if(length(L)>0 && index(L)>=0){
        if(L->cursor == L->front){
            prepend(L, x);
        }else{
            Node n = newNode(x);
            Node cursor_prev = L->cursor->prev;
            n->next = L->cursor;
            n->prev = cursor_prev;
            L->cursor->prev = n;
            cursor_prev->next = n;
            L->length += 1;
            L->index += 1;
        }
    }
} 
// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, void* x){
    if(length(L)>0 && index(L)>=0){
        if(L->cursor == L->back){
            append(L, x);
        }else{
            Node n = newNode(x);
            Node cursor_next = L->cursor->next;
            n->prev = L->cursor;
            n->next = cursor_next;
            L->cursor->next = n;
            cursor_next->prev = n;
            L->length += 1;
            //L->index += 1;
        }
    }
}
// Delete the front element. Pre: length()>0
void deleteFront(List L) { 
	Node N = L->front;
	if (N != NULL) {
		if (L->length == 1) {
			freeNode(&N);
			L->front = L->back = L->cursor = NULL;
            L->index = -1;
		}
		else {
			L->front = N->next;
			freeNode(&N);
            L->index -= 1;
		}
	}
	// free(N);
	L->length--;
	return;
}
// Delete the back element. Pre: length()>0
void deleteBack(List L){
    Node N = L->back;
	if (N != NULL) {
		if (L->length == 1) {
			freeNode(&N);
			L->back = L->front = L->cursor = NULL;
            L->index = -1;
		}
		else {
            if(L->cursor == L->back){
                L->index = -1;
            }
			L->back = N->prev;
			freeNode(&N);
            L->back->next = NULL;
		}
	}
	// free(N);
	L->length--;
	return;
}
// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L){
    //Node N = L->cursor;
	if (length(L) == 1) {
		freeNode(&L->cursor);
		L->front = NULL;
		L->back = NULL;
		L->length--;
        L->index = -1;
		return;
	}
	if (index(L) == 0) {
		L->front = L->cursor->next;
		freeNode(&L->cursor);
		L->length--;
        L->index = -1;
		return;
	}
	if (index(L) == (length(L)-1)) {
		L->back = L->cursor->prev;
		freeNode(&L->cursor);
        L->back->next = NULL;
		L->length--;
        L->index = -1;
		return;
	}

    

	// At this moement, there are at least 3 elements in the list and cursor
	// is not the first and not the last element.


	L->cursor->prev->next = L->cursor->next;
	L->cursor->next->prev = L->cursor->prev;
	freeNode(&L->cursor);
	L->length--;
    L->index = -1;
	return;
}

// Other operations -----------------------------------------------------------
// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
/*void printList(FILE* out, List L){
    Node N = NULL;

    if( L==NULL ){
        printf("List Error: calling printList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    for(N = L->front; N != NULL; N = N->next){
        if(N == L->front){
            fprintf(out, "%d", N->data);
        }else{
            fprintf(out, " %d", N->data);
        }
        
    }
}

// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L){
    Node origin = L->cursor;
    int ori_index = L->index;
    List L1 = newList();
    for(moveFront(L); index(L) >= 0; moveNext(L)){
        append(L1, get(L));
    }

    L->cursor = origin;
    L->index = ori_index;

    return L1;

}*/
 


