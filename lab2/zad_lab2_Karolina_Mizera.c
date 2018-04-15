#include </usr/include/gsl/gsl_math.h>
#include </usr/include/gsl/gsl_linalg.h>
#include <time.h>
void show(gsl_matrix * matrix, int size){
    int i, j;
    printf("\n");
    for(i=0; i<size ; ++i){
        for(j=0; j<size; ++j){

            printf(" %g",gsl_matrix_get(matrix, i,j));

        }
        printf("\n");
    }
    printf("\n");
}

int main(){

clock_t t1, t2;
    t1=clock();
    int i, j,k, signum;
    int size=1000;

    double det=1.0;

    gsl_matrix * A = gsl_matrix_calloc(size,size);
    gsl_matrix * B = gsl_matrix_calloc(size,size);
    gsl_matrix * C = gsl_matrix_calloc(size,size);
    gsl_matrix * D= gsl_matrix_calloc(size,size);
	
    gsl_permutation * perm = gsl_permutation_calloc(size);
    gsl_vector *diagonal = gsl_vector_calloc(size);

    gsl_vector *b1 = gsl_vector_calloc(size);
    gsl_vector *b2 = gsl_vector_calloc(size);  
    gsl_vector *b3 = gsl_vector_calloc(size);  
    gsl_vector *b4 = gsl_vector_calloc(size); 

    gsl_vector *x1 = gsl_vector_calloc(size);
    

    //-------------------------------------------------------
    //tworzenie macierzy
    for(i=0; i<size ; ++i){
        for(j=0; j<size; ++j){

            gsl_matrix_set(A, i,j,1./(i+j+2));
            gsl_matrix_set(B,i,j,1./(i+j+2));
        }
    }
    //show(A, size);
    //rozkład LU
    gsl_linalg_LU_decomp(A,perm,&signum);
   // show(A, size);
    //diagonala U i obliczanie wyznacznika

    for(i=0; i<size ; ++i){
        for(j=0; j<size; ++j){
            if(i==j){
            gsl_vector_set(diagonal,i ,gsl_matrix_get(A, i,j));
            det*=gsl_matrix_get(A, i,j);
            }
        }
       // printf("%f\n", gsl_vector_get(diagonal, i));
    }

    //printf("%5.10f\n", det);


    gsl_vector_set(b1,0,1);
    gsl_vector_set(b2,1,1);
    gsl_vector_set(b3,2,1);
    gsl_vector_set(b4,3,1);

   // for(i=0; i<size; ++i){
     //   printf ("%f %f %f %f\n", gsl_vector_get(b1,i),gsl_vector_get(b2,i),gsl_vector_get(b3,i),  gsl_vector_get(b4,i));
    //}

    //wpisywanie do pliku
    /*FILE  * fp;
    fp=fopen("dane.dat", "w");
    fprintf(fp, "elementy diagonali U\n");
    for (i=0; i<size; i++)  
        fprintf(fp,"%f ", gsl_vector_get(diagonal, i));
    fprintf(fp, "\n\nWyznacznik macierzy A - %0.10f", det );

    fprintf(fp, "\nMacierz odwrotna macierzy A\n");
*/

     gsl_linalg_LU_solve(A, perm, b1, x1);
    
    for(j=0; j<size; j++){
            gsl_matrix_set(C, j, 0, gsl_vector_get(x1,j));
    }
    
    gsl_linalg_LU_solve(A, perm, b2, x1);
    
    for(j=0; j<size; j++){
            gsl_matrix_set(C, j, 1, gsl_vector_get(x1,j));
    }
    
     gsl_linalg_LU_solve(A, perm, b3, x1);
    for(j=0; j<size; j++){
            gsl_matrix_set(C, j,2, gsl_vector_get(x1,j));
        }
    
     gsl_linalg_LU_solve(A, perm, b4, x1);
    for(j=0; j<size; j++){
            gsl_matrix_set(C, j,3, gsl_vector_get(x1,j));
        }
    
    //show(C, size);

    //wpisywanie macierzy odwrotnej do A do pliku

   /* for(i=0; i<size; ++i){
        for(j=0; j<size; ++j ){
            fprintf(fp,"%f ", gsl_matrix_get(C, i, j));        
        }
        fprintf(fp, "\n");
    }*/

double temp=0.0;
    /*for(i=0; i<size; ++i){
        for(j=0; j<size; ++j ){
            temp=0.0;
            for(k=0;k<size; ++k){
                temp=temp+ gsl_matrix_get(C, i, k)*gsl_matrix_get(B, k, j);
               
            }
            gsl_matrix_set(D, i, j,temp);
        }
    }*/
    //show(D, size);

   /* fprintf(fp, "\nIloczyn macierzy odwrotnej do A i macierzy A\n");
    for(i=0; i<size; ++i){
        for(j=0; j<size; ++j ){
            fprintf(fp,"%g ", gsl_matrix_get(D, i, j));        
        }
        fprintf(fp, "\n");
    }*/
	t2= clock();
	printf("%f\n", ((float) t2)/CLOCKS_PER_SEC);

    //fclose(fp);
    
    
}