#include <stdio.h>
#include <math.h>


#define max(X,Y) ((X)>(Y) ? (X) : (Y))
#define min(X,Y) ((X)<(Y) ? (X) : (Y))
#define abs(X) ((X)>0 ? (X) : -(X))


//void copy()

void show(double m[7][7], int size){
    int i,j;
    printf("\n");
    for(i=0; i<size ; ++i){
        for(j=0; j<size; ++j){
            printf(" %g",m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void mat_vec(int size,double m[7][7], double vec_b[7], double  vec_o [7]){
   int i, j;
   
   for(i=0; i<size; i++){
       vec_b[i]=0.0;
    for(j=0; j<size; j++){
       vec_b[i]+= m[i][j]*vec_o[j];
        }
    }
}

double vec_vec(int size,double vec_b[7], double vec_o[7] ){
    int i;
    double lambda = 0.0;
    for(i=0; i<size; i++)
        lambda+= vec_b[i]*vec_o[i];    
        
    return lambda;
}

void mod_vec(int size,double m[7][7], double vec_o[7] , double lambda){
    int i, j;
    for(i=0; i<size; i++){
        
     for(j=0; j<size; j++){
        m[i][j]-= lambda*( vec_o[i]*vec_o[j]);
         }
     }
}

void mnozenie_macierzy(int size, double A[7][7], double X[7][7], double D[7][7]){
    double Z[7][7];
    double transX[7][7];
    double temp=0.0;
    int i,j,k;

    for(i=0; i<size; ++i){
        for(j=0; j<size; ++j ){
            transX[i][j]=X[j][i];
        }
    }

    for(i=0; i<size; ++i){
        for(j=0; j<size; ++j ){
            temp=0.0;
            for(k=0;k<size; ++k){
                temp=temp+ A[i][k]*X[k][j];
                }   
            Z[i][j]=temp;
        }
    }


    for(i=0; i<size; ++i){
        for(j=0; j<size; ++j ){
            temp=0.0;
            for(k=0;k<size; ++k){
                temp=temp+ transX[i][k]*Z[k][j];
                }   
            D[i][j]=temp;
        }
    }
}



int main(){



    FILE * fp, *pp;
    fp=fopen("lambda.dat", "w");
    pp=fopen("macierzD.dat", "w");
    int i,j, k, l;
    int size = 7;
    double A[size][size];
    double W[size][size];
    double x_ix[size];
    double x_i[size];
    int IT_MAX=12;
    int Kval= size;
    double lambda;
    double X[size][size];
    double D[size][size];

    for(i=0; i<size; i++){
         for(j=0; j<size; j++){
            A[i][j]=1.0/(sqrt(2+abs(i-j)));
            W[i][j]=1.0/sqrt(2+abs(i-j)); //inicjalizacja macierzy 
         }
    }
    //show(A, 7)

    
    for(k=0; k<Kval; ++k){

        for(i=0; i<size; i++){
            x_i[i]=1.0;
        }

        for(i=1; i<=30; ++i){
            mat_vec(7, W, x_ix, x_i);
            lambda=(vec_vec(7, x_ix, x_i)/vec_vec(7, x_i, x_i));
            printf(" %i  %i  %g  \n ", k, i, lambda);
            for(j=0; j<size;j++)
                x_i[j]= x_ix[j]/ sqrt(vec_vec(7, x_ix, x_ix));
		fprintf(fp,"%i %g  \n",i,lambda );

        }

        mod_vec(7, W, x_i, lambda); 

        for(i=0; i<size; ++i){
            X[i][k]=x_i[i];
        }
        
    }

    mnozenie_macierzy(7, A,X,D);
    show(D,7);

    for(i=0; i<size ; ++i){
        for(j=0; j<size; ++j){
            fprintf(pp," %0.15f",D[i][j]);
        }
        fprintf(pp,"\n");
    }

    fclose(fp);
    fclose(pp);
    return 0;
}
