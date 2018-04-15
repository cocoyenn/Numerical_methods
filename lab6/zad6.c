#include <complex.h>
#include <stdio.h>

#define INT_MAX 20

double complex obliczRj(int n, double complex a[5], double complex b[5], double complex zj, int l)
{
    int i;
    b[l]=0;
    for (i=l-1; i>=0; i--){
        b[i]=a[i+1]+zj*b[i+1];
    }
    return a[0]+ zj*b[0];

}


int main(){
    FILE * fp, *pp;
    //fp=fopen("zj_0_0I.dat", "w");
    pp=fopen("zj_10_10I.dat", "w");
    
    double complex a[5] ={ 16.0 + 8.I, -20.0 + 14.I ,  4.0 - 8.I , -4.0 + 1.I , 1.0 + 0.I};
    double complex b[5] = {0. + 0.I, 0. + 0.I, 0. + 0.I, 0. + 0.I, 0. + 0.I };
    double complex c[5] = {0. + 0.I, 0. + 0.I, 0. + 0.I, 0. + 0.I, 0. + 0.I };
    
    const double complex zo = -10 -10.I;
    double complex Rj, Rjprim, zj;
    
    int n = 4,i, j, l;

    for(l=n; l>=1; l--)//l - aktualny sposób wielomianu
    {
        zj=zo;
        for(j=1; j<=INT_MAX; j++)
        {
            Rj = obliczRj(n,a,b,zj,l);
            Rjprim = obliczRj(n, b,c, zj, l-1);
            zj = zj - (Rj/Rjprim);
            fprintf(pp,"%d %d %f %f\n",l,j, creal(zj), cimag(zj));
            
        }
        printf("%f %f\n", creal(zj), cimag(zj));
        for(i=0; i<5; i++)
            a[i]=b[i];  
        printf("\n\n\n"));        

    }
    //fclose(fp);
    fclose(pp);
    return 0;

}