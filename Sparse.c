//-----------------------------------------------------------------------------
// Name: Lia Cui
// CRUZID: ljcui
// Assignment Name: PA4
//
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"List.h"
#include"Matrix.h"

int main(int argc, char * argv[]){

   
   FILE *in, *out;

   //open files for reading and writing 
   //check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }
   in = fopen(argv[1], "r");
 //  in = fopen("in1.txt", "r");
      if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }

   out = fopen(argv[2], "w");
//   out = fopen("out.txt", "w");
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   //read 1st part

    int nSize = 0;
    int nnzA = 0;
    int nnzB = 0;
    fscanf(in, "%d %d %d\n\n", &nSize, &nnzA, &nnzB);

    Matrix A = newMatrix(nSize);
    Matrix B = newMatrix(nSize);


    for(int i = 0; i < nnzA; i++){
        int rowA = 0;
        int colA = 0;
        double valA = 0;
        fscanf(in, "%d %d %lf\n", &rowA, &colA, &valA);
        changeEntry(A, rowA, colA, valA);
    }

    for(int i = 0; i < nnzB; i++){
        int rowB = 0;
        int colB = 0;
        double valB = 0;
        fscanf(in, "%d %d %lf\n", &rowB, &colB, &valB);
        changeEntry(B, rowB, colB, valB);
    }
    fflush(out);

    fprintf(out, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(out, A);
    fprintf(out, "\n");
    fprintf(out, "B has %d non-zero entries:\n", NNZ(B));
    printMatrix(out, B);
    fprintf(out, "\n");

    fprintf(out, "(1.5)*A =\n");
    Matrix mult = scalarMult(1.5, A);
    printMatrix(out, mult);
    fprintf(out, "\n");

    fprintf(out, "A+B =\n");
    Matrix add = sum(A, B);
    printMatrix(out, add);
    fprintf(out, "\n");
    
    fprintf(out, "A+A =\n");
    Matrix add2 = sum(A, A);
    printMatrix(out, add2);
    fprintf(out, "\n");

    fprintf(out, "B-A =\n");
    Matrix sub = diff(B, A);
    printMatrix(out, sub);
    fprintf(out, "\n");

    fprintf(out, "A-A =\n");
    Matrix sub2 = diff(A, A);
    printMatrix(out, sub2);
    fprintf(out, "\n");

    fprintf(out, "Transpose(A) =\n");
    Matrix aT = transpose(A);
    printMatrix(out, aT);
    fprintf(out, "\n");

    fprintf(out, "A*B =\n");
    Matrix prod = product(A, B);
    printMatrix(out, prod);
    fprintf(out, "\n");

    fprintf(out, "B*B =\n");
    Matrix prod2 = product(B, B);
    printMatrix(out, prod2);
    fprintf(out, "\n");

    //printMatrix(out, g);
    
    

   //close files 
   fclose(in);
   fclose(out);
   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&mult);
   freeMatrix(&add);
   freeMatrix(&add2);
   freeMatrix(&sub);
   freeMatrix(&sub2);
   freeMatrix(&aT);
   freeMatrix(&prod);
   freeMatrix(&prod2);

   return(0);
}