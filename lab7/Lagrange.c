#include <stdio.h>
#include <math.h>

#define XMIN -5
#define XMAX 5
#define RANGE 10
#define N 20

double f_interpolowana(double x){
    return exp(-(pow(x,2)));
}

double M(double xj, double xi[N+1], double size, double IfJ){
    double temp=1.0;
    int j;

    for (j=0; j<size; j++){
        if(j!=IfJ)
        {
            temp*= (xj-xi[j]);
        }
    }
    return temp;
}


double L(double x, double xi[N+1], double size, double IfJ){
    double temp=1.0;
    int j;
    for (j=0; j<size; j++){
        if(j!=IfJ)
        {
            temp*= (x-xi[j]);
        }
    }
    return temp;
}

double wielomian(double x, double xi[N+1], double yi[N+1], double size){
    int j;
    double temp=0.0;
    for(j=0; j<size; j++){
        temp+=yi[j]*L(x,xi, size,j )/M(xi[j], xi, size,j);
    }
    return temp;
}

int main(){
    FILE * fp, *pp;
    fp=fopen("n_20.dat", "w");
    //pp=fopen("zj_10_10I.dat", "w");
    int  m=N+1;
    int i,j;

    double x_i[N+1]={};
    double f_x_i[N+1]={};
    double x, wynik=0;
    double steps=200;
    

    double L=1.0;

    x_i[0]=XMIN;
    f_x_i[0]=f_interpolowana(XMIN);
    printf("%f %f\n", x_i[0], f_x_i[0]);


    for (i=1; i<=N;i++){
        x_i[i]=x_i[i-1] + (RANGE/(N*1.0));
        f_x_i[i]=f_interpolowana(x_i[i]);
        printf("%f   %f\n", x_i[i], f_x_i[i]);
    }

    wynik=0.0;
    for (x=XMIN; x<XMAX; x=x+(RANGE/(steps*1.0))){
        wynik=wielomian(x,x_i, f_x_i, N+1);
        printf("%f\n", wynik);
        fprintf(fp," %f %f %f \n",x, f_interpolowana(x), wynik);

    }
    fclose(fp);
}
