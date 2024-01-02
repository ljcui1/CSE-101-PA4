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
#include "Matrix.h"

double difference = 0.0000001;

// private Node type
typedef struct MatrixObj* Matrix;
typedef struct EntryObj* Entry;

typedef struct EntryObj {
    int col;
    double val;
}EntryObj;

Entry newEntry(int c, double v) {
    Entry E = (Entry)calloc(1, sizeof(EntryObj));
	assert(E != NULL);
	E->col = c;
	E->val = v;
	return(E);
    
}

void freeEntry(Entry* pE){
   if( pE!=NULL && *pE!=NULL ){
      free(*pE);
      *pE = NULL;
   }
}

typedef struct MatrixObj {
    List* row;
    int size;
    int nnz;
}MatrixObj;

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n){
    Matrix M;
    M = (Matrix) calloc(1, sizeof(MatrixObj));
    assert(M != NULL);
    M->row = calloc (n + 1, sizeof(List));
    for(int i = 0; i <= n; i++){
        M->row[i] = newList();
    }
    M->size = n;
    M->nnz = 0;
    return(M);
}
// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){
    if(pM != NULL && *pM != NULL){
        for(int i = 0; i <= size(*pM); i++){
            for(moveFront((*pM)->row[i]); index((*pM)->row[i]) >= 0; moveNext((*pM)->row[i])){
                Entry E = get((*pM)->row[i]);
                freeEntry(&E);
            }
            freeList(&((*pM)->row[i]));
        }
        free((*pM)->row);
        free((*pM));
        *pM = NULL;
        pM = NULL;
    }
}
// Access functions
// size()
// Return the size of square Matrix M.
int size(Matrix M){
    return M->size;
}
// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M){
    return M->nnz;
}
// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){
    if(A->size != B->size || A->nnz != B->nnz){
        return 0;
    }
    for(int i = 1; i <= size(A); i++){
        if (length(A->row[i]) != length(B->row[i])) {
            return 0;
        }
        moveFront(B->row[i]);
        for(moveFront(A->row[i]); index(A->row[i]) >= 0; moveNext(A->row[i])){
            if(((Entry)get(A->row[i]))->col != ((Entry)get(B->row[i]))->col ){
                return 0;
            }
            if(((Entry)get(A->row[i]))->val != ((Entry)get(B->row[i]))->val ){
                return 0;
            }
            moveNext(B->row[i]);
        }
    }
    return 1;
}
// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M){
    for(int i = 0; i <= size(M); i++){
        while(length(M->row[i]) > 0){
            Entry E = front(M->row[i]);
            freeEntry(&E);
            deleteFront(M->row[i]);
        }
    }
    M->nnz = 0;
}
// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){
    // if(x == 0){
    //     return;
    // }
    List L = M->row[i];
    // if L is empty, append(L, newEntry(j, x))
    if ( length(L) == 0 ) {
        double d1 = x;
        if (d1 < 0) {
            d1 = -d1;
        }

        if (d1 > difference) {
            Entry e = newEntry(j, x);
            append(M->row[i], e); //  //First time append it
            M->nnz++;
        }

        return;

    } else {
        // if L is not empty
        for(moveFront(M->row[i]); index(M->row[i]) >= 0; moveNext(M->row[i])){
            Entry p = (Entry) get(L);
            if ( p->col == j) {
                //update L
                double d1 = x;
                if (d1 < 0) {
                    d1 = -d1;
                }

                if (d1 > difference) {
                    Entry e = newEntry(j, x);
                    set(M->row[i], e);
                } else { // We need to toss e.
                    Entry e = get(M->row[i]);
                    delete(M->row[i]);
                    freeEntry(&e);
                    M->nnz--;
                }

                return;

            } else if (p->col > j) {
                double d1 = x;
                if (d1 < 0) {
                    d1 = -d1;
                }

                if (d1 > difference) {
                    Entry e = newEntry(j, x);
                    insertBefore(M->row[i], e);
                    M->nnz++;
                }
                return;

            }
        }
    }
    double d = x;
    if (d < 0) {
        d = -d;
    }

    if (d > difference) {
        append(M->row[i], newEntry(j, x));
        M->nnz++;
    }

}
// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){
    Matrix B = newMatrix(A->size);
    B->nnz = NNZ(A);
    for(int i = 1; i <= size(A); i++){
        moveFront(B->row[i]);
        for(moveFront(A->row[i]); index(A->row[i]) >= 0; moveNext(A->row[i])){
            append(B->row[i], newEntry(((Entry)get(A->row[i]))->col, ((Entry)get(A->row[i]))->val));
        }
    }
    return B;
}
// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A){
    Matrix B = newMatrix(size(A));
    B->nnz = NNZ(A);
    for (int i = 1; i <= size(A); i++){
        for(moveFront(A->row[i]); index(A->row[i]) >= 0; moveNext(A->row[i])){
            Entry e = (Entry)get(A->row[i]);
            append(B->row[e->col], newEntry(i, e->val));
        }
    }
    return B;
}
// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){
    Matrix mult = newMatrix(size(A));
    if(x != 0){
         mult->nnz = NNZ(A);
    }else{
        mult->nnz = 0;
    }
   
    for (int i = 1; i <= size(A); i++){
        for(moveFront(A->row[i]); index(A->row[i]) >= 0; moveNext(A->row[i])){
            Entry e = (Entry)get(A->row[i]);
            append(mult->row[i], newEntry(e->col, (e->val)*x));
        }
    }
    return mult;
}
// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B){
    Matrix A2 = copy(A);
    Matrix B2 = copy(B);

    Matrix added = newMatrix(size(A));
    // added->nnz = NNZ(A);
    for (int i = 1; i <= size(A); i++){
        int moveA = 0;
        int moveB = 0;
        Entry e1 = NULL;
        Entry e2  = NULL;
        moveFront(A2->row[i]);
        moveFront(B2->row[i]);
        while((moveA < length(A2->row[i])) || (moveB < length(B2->row[i]))){
            if((moveA < length(A2->row[i])) && (moveB < length(B2->row[i]))){
                e1 = (Entry)get(A2->row[i]);
                e2 = (Entry)get(B2->row[i]);

                if(e1->col == e2->col){
                    double d = e1->val + e2->val;
                    if(d < 0){
                        d = -d;
                    }
                    if(d > difference){
                        append(added->row[i], newEntry(e1->col, (e1->val)+(e2->val)));
                        added->nnz++;
                    }
                    // else{
                    //     added->nnz--;
                    // }
                    moveA++;
                    moveNext(A2->row[i]);
                    moveB++;
                    moveNext(B2->row[i]);
                }else if(e1->col < e2->col){
                    append(added->row[i], newEntry(e1->col, e1->val));
                    moveA++;
                    moveNext(A2->row[i]);
                    added->nnz++;
                }else{
                    append(added->row[i], newEntry(e2->col, e2->val));
                    moveB++;
                    moveNext(B2->row[i]);
                    added->nnz++;
                }
            }else if((moveA < length(A2->row[i])) && (moveB == length(B2->row[i]))){
                e1 = (Entry)get(A2->row[i]);
                append(added->row[i], newEntry(e1->col, e1->val));
                moveA++;
                moveNext(A2->row[i]);
                added->nnz++;
            }else{
                e2 = (Entry)get(B2->row[i]);
                append(added->row[i], newEntry(e2->col, e2->val));
                moveB++;
                moveNext(B2->row[i]);
                added->nnz++;
            }
            
            
        }
    }
    freeMatrix(&A2);
    freeMatrix(&B2);

    return added;
}
// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
    Matrix A2 = copy(A);
    Matrix B2 = copy(B);

    Matrix subtracted = newMatrix(size(A));
    // subtracted->nnz = NNZ(A);
    for (int i = 1; i <= size(A); i++){
        int moveA = 0;
        int moveB = 0;
        Entry e1 = NULL;
        Entry e2  = NULL;
        moveFront(A2->row[i]);
        moveFront(B2->row[i]);
        while((moveA < length(A2->row[i])) || (moveB < length(B2->row[i]))){
            if((moveA < length(A2->row[i])) && (moveB < length(B2->row[i]))){
                e1 = (Entry)get(A2->row[i]);
                e2 = (Entry)get(B2->row[i]);

                if(e1->col == e2->col){
                    double d = e1->val - e2->val;
                    if(d < 0){
                        d = -d;
                    }
                    if(d > difference){
                        append(subtracted->row[i], newEntry(e1->col, (e1->val)-(e2->val)));
                        subtracted->nnz++;
                    }
                    // else{
                    //     subtracted->nnz--;
                    // }
                    moveA++;
                    moveNext(A2->row[i]);
                    moveB++;
                    moveNext(B2->row[i]);
                }else if(e1->col < e2->col){
                    append(subtracted->row[i], newEntry(e1->col, e1->val));
                    moveA++;
                    moveNext(A2->row[i]);
                    subtracted->nnz++;
                }else{
                    append(subtracted->row[i], newEntry(e2->col, -(e2->val)));
                    moveB++;
                    moveNext(B2->row[i]);
                    subtracted->nnz++;
                }
            }else if((moveA < length(A2->row[i])) && (moveB == length(B2->row[i]))){
                e1 = (Entry)get(A2->row[i]);
                append(subtracted->row[i], newEntry(e1->col, e1->val));
                moveA++;
                moveNext(A2->row[i]);
                subtracted->nnz++;
            }else{
                e2 = (Entry)get(B2->row[i]);
                append(subtracted->row[i], newEntry(e2->col, -(e2->val)));
                moveB++;
                moveNext(B2->row[i]);
                subtracted->nnz++;
            }
            
            
        }
    }
    freeMatrix(&A2);
    freeMatrix(&B2);

    return subtracted;
}

double vectorDot(List P, List Q) {
    int n1 = 0;
    int n2 = 0;

    Entry t = NULL;
    if(length(P) > 0){
        t = (Entry)back(P);
        n1 = t->col;
    }else{
        n1 = 0;
    }
    if(length(Q) > 0){
        t = (Entry)back(Q);
        n2 = t->col;
    }else{
        n2 = 0;
    }

    int max = n1 + 1;
    if(max < n2 + 1){
        max = n2 + 1;
    }

    n1 = length(P);
    n2 = length(Q);

    int Pove = 0;
    int Qove = 0;

    moveFront(P);
    moveFront(Q);

    double answer = 0;
    for(int i = 0; i < max; i++){
        if(Pove < n1 && Qove < n2){
            Entry p = (Entry)get(P);
            Entry q = (Entry)get(Q);
            if(p->col < q->col){
                Pove++;
                moveNext(P);
            }else if(p->col > q->col){
                Qove++;
                moveNext(Q);
            }else{
                answer = answer + (p->val * q->val);
                Pove++;
                moveNext(P);
                Qove++;
                moveNext(Q);
            }
        }
        
    }
    return answer;
}
// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B) {
    // let T be the transpose of B
    Matrix TB = transpose(B);
    Matrix ATimesB = newMatrix(size(A));
    // loop through each row r of A and row of s of T
    for(int i = 1; i <= size(A); i++){
        if(length(A->row[i]) == 0){
            continue;
        }
        for(int j = 1; j <= size(TB); j++){
            if(length(TB->row[j]) == 0){
                continue;
            }
            // dotproduct r and s, the result is a double 
            double answer = vectorDot(A->row[i], TB->row[j]);
            double d = answer;
            if(d < 0){
                d = -answer;
            }

            if(d > difference){
                append(ATimesB->row[i], newEntry(j, answer));
                ATimesB->nnz += 1;
            }
        }
    }
    freeMatrix(&TB);
    return ATimesB;
    
    
}

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){
    for(int i = 1; i <= size(M); i++){
        moveFront(M->row[i]);
        if(length(M->row[i]) == 0){
            continue;
        }
        fprintf(out, "%d:", i);
        while(index(M->row[i]) >= 0){
            Entry E = (Entry)get(M->row[i]);
            fprintf(out, " (%d, %.1f)", E->col, E->val);
            moveNext(M->row[i]);
        }
        if(length(M->row[i]) == 0){
            fprintf(out, " ");
        }
        fprintf(out, " \n");
    }
}