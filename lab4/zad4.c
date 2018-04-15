#include </usr/include/gsl/gsl_math.h>
#include </usr/include/gsl/gsl_linalg.h>
#include</usr/include/gsl/gsl_eigen.h>
#include <time.h>
#include <math.h>

double delta(int i, int j){
    if (i==j)
        return 1.;
    else 
        return 0.;  
}

double pX(double alfa, double x){ return (1.0 + 4.0 * alfa * x *x); }

int main(){
    FILE  * fp;
    FILE * pp;
    FILE *lp;

    fp=fopen("dane_do_zad3.dat", "w");
    pp=fopen("wektory_wlasne_alfa0.dat", "w");
    lp=fopen("wektory_wlasne_alfa100.dat", "w");

    int i=0, j=0, a=0, b=0, alfa = 0;
    int L= 10, n=200;
    double a_member, b_member, N=1.0;
    double deltaX = (1.0*L)/(n+1);
   

    gsl_matrix * A = gsl_matrix_calloc(n,n);
    gsl_matrix * B = gsl_matrix_calloc(n,n);
    gsl_matrix * evec = gsl_matrix_calloc(n,n);
    gsl_vector *eval = gsl_vector_calloc(n);
    gsl_eigen_gensymmv_workspace *w = gsl_eigen_gensymmv_alloc(n);
    gsl_vector *x = gsl_vector_calloc(n);

    for(i = 0; i < n; i++)
	{
		gsl_vector_set(x,i, -L/2 + deltaX * (i+1));
	}

    for(alfa=0; alfa<=100;  alfa+=2){
        for(i=0; i<n; i++){
           
            for(j=0; j<n; j++){
                a_member=((-1.0 * delta(i, j+1) +2 *delta(i,j)- delta(i, j-1)))/(deltaX*deltaX);
                gsl_matrix_set(A, i,j,a_member);

                
                b_member = ((1.0*delta(i,j))/N) * pX(alfa, gsl_vector_get(x, i));
                gsl_matrix_set(B, i,j,b_member);

            }
        }
        gsl_eigen_gensymmv(A, B,eval,evec, w);
        gsl_eigen_gensymmv_sort(eval,  evec,GSL_EIGEN_SORT_ABS_ASC);
        fprintf(fp,"%d ", alfa);
        for(i=0; i<6; ++i)
            fprintf(fp,"  %f  ", sqrt(gsl_vector_get(eval,i)) );
        fprintf(fp, "\n");

        if(alfa == 0 ){
            
            for(a=0; a<n; a++){
                fprintf(pp,"%d ", a);
                for(b=0; b<6; b++)
                    fprintf(pp, " %f " , gsl_matrix_get(evec, a,b)); 
		 fprintf(pp, "\n");
                }  
            }   
        
        if(alfa == 100){                       
            for(a=0; a<n; a++){
                fprintf(lp,"%d ",a);
                    for(b=0; b<6; b++)
                        fprintf(lp, " %f " , gsl_matrix_get(evec,a,b));        
                    fprintf(lp, "\n");
            }          
        }          
    }

    fclose(fp);
    fclose(pp);
    fclose(lp);
    return 0;
}