#include <math.h>
#include <time.h>
#include <stdio.h>
#define max(X,Y) ((X)>(Y) ? (X) : (Y))
#define min(X,Y) ((X)<(Y) ? (X) : (Y))
#define abs(X) ((X)>0 ? (X) : -(X))

#define N 1000
#define M 5

 time_t t1, t2;
time(&t1);

//void iloczynWektorow()

int main(){

    FILE  * fp, *pp;
    fp=fopen("dane_1.dat", "w");
    pp=fopen("dane_2.dat", "w");
    
    int i=0, j=0;
    double A[N][N];
    double b[N], r[N] ,x[N], y[N], temp[N], x1[N]; 
    double AlfaK=0.0, r2=0.0, r2A=0.0, x2=0.0;
    int licznik=0;
    //wypełnienie macierzy 
    for(i=0; i<N; ++i){
        for(j=0; j<N; ++j){
            if(abs(i-j)<=M)
                A[i][j] = (1./(1+abs(i-j)));
            else
                A[i][j] = 0;
        }
    }
    //wypełnienie wektora b, x,r, y, temp
    for(i=0; i<N; ++i){
        b[i]=i;
        x[i]=0.0;
        r[i]=0.0;
        y[i]=0.0;
        temp[i]=0.0;
        x1[i]=1.0;
    }
    //fprintf()

    //metoda największego spadku
    do{
        licznik++;
        r2=0.0; 
        r2A=0.0;
        for(i=0; i<N; ++i){
            y[i]=0.0;
            for(j=max(0, i-M); j<=min(N-1, i+M); ++j){
                y[i]+=A[i][j]*x[j];     //obliczanie iloczynu Ax
            }
        }

        for (i=0; i<N; ++i){
            r[i]=b[i] - y[i];           //wektor reszt
            r2+=r[i]*r[i];
        }

        for(i=0; i<N; i++){  
            temp[i]=0.0;           //
            for(j=max(0, i-M); j<=min(N-1, i+M); ++j){         //
                temp[i]+=A[i][j]*r[j];   //
            }                           //iloczyn wektora reszt i macierzy A
        }                               //
        
        
        
        
                                        //
        for (i=0; i<N; ++i){            //
            r2A+=temp[i]*r[i];          //
        }
         
        AlfaK=r2/r2A;
        
        for (i=0; i<N; ++i){            //
            x[i]= x[i]+AlfaK*r[i];    // 
        }
        x2=0.0;
        for(i=0; i<N; ++i){
            x2+=x[i]*x[i];
        }
        fprintf( fp," %d. %g %g %g \n", licznik, sqrt(r2), AlfaK, sqrt(x2));
    }while(sqrt(r2)>(1e-6));

   
    licznik=0;
    do{
        licznik++;
        r2=0.0; 
        r2A=0.0;
        for(i=0; i<N; ++i){
            y[i]=0.0;
            for(j=max(0, i-M); j<=min(N-1, i+M); ++j){
                y[i]+=A[i][j]*x1[j];     //obliczanie iloczynu Ax
            }
        }

        for (i=0; i<N; ++i){
            r[i]=b[i] - y[i];           //wektor reszt
            r2+=r[i]*r[i];
        }

        for(i=0; i<N; i++){  
            temp[i]=0.0;           //
            for(j=max(0, i-M); j<=min(N-1, i+M); ++j){         //
                temp[i]+=A[i][j]*r[j];   //
            }                           //iloczyn wektora reszt i macierzy A
        }                               //
                                        //
        for (i=0; i<N; ++i){            //
            r2A+=temp[i]*r[i];          //
        }
         
        AlfaK=r2/r2A;
        
        for (i=0; i<N; ++i){            //
            x1[i]= x1[i]+AlfaK*r[i];    // 
        }
        x2=0.0;
        for(i=0; i<N; ++i){
            x2+=x1[i]*x1[i];
        }
        fprintf( pp," %d. %g %g %g \n", licznik, sqrt(r2), AlfaK, sqrt(x2));
    }while(sqrt(r2)>(1e-6));
       
    printf("%d\n", clock());
    fclose(fp);
    fclose(pp);
return 0;
}