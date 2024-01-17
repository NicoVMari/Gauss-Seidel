#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include <libgen.h>

#define MAXDIM 30
#define MAX_ITER 100

float A[MAXDIM][MAXDIM],B[MAXDIM],X[MAXDIM],XT[MAXDIM];

void gauss_seidel(int, float, char *);

int main(int argc, char const *argv[]){
    FILE *fp;
    float tmp,acc;
    int dim = 0;
    
    if(argc != 2){
        printf("Errore: non inserimento del file\n");
		exit(1);
    }
   
    fp = fopen(argv[1],"r");

    if (fp==NULL){
		printf("ERRORE: nell'apertura del file\n");
		exit(2);
	}

    printf("Programma per la soluzione di sistemi di equazioni lineari\n");
    printf("con il metodo iterativo di Gauss-Seidel\n");

    fscanf(fp, "%d", &dim);
    printf("La dimensione del sistema e' %d \n", dim);

    printf("Sistema lineare rappresentato come A e B\n");
    for (int i = 0; i < dim; i++) { 
        printf("(");
        for (int j = 0; j < dim; j++) {
            fscanf(fp, "%f", &tmp);
            A[i][j] = tmp;
            printf("%f ",A[i][j]);
        }
        fscanf(fp, "%f", &tmp);
        B[i] = tmp;
        printf(")\t(%f) \n",B[i]);
    }

    fclose(fp);

    printf("Accuratezza: ");
    scanf("%f", &acc);

    char filepath[MAXDIM] = "gnuplot/";
    strcat(filepath, basename((char *)argv[1]));


    gauss_seidel(dim,acc,filepath);

    printf("\nRisultato del sistema lineare rappresentato come A * B = X\n");
    for (int i = 0; i < dim; i++) { 
        printf("( ");
        for (int j = 0; j < dim; j++) {
            printf("%f ",A[i][j]);
        }
        printf(")\t(%f)\t",B[i]);
        printf("(%f)\n", X[i]);
        
    }

    return 0;
}

void gauss_seidel(int dim, float acc, char *filepath){
    float errore = 0.0f, somma1, somma2;
    int itr = 0;

    //Elementi diagonali non nulli e un vettore di tentativi
    for (int i = 0; i < dim; i++){
        XT[i] = 0.0f;
        if(A[i][i] == 0){
            printf("ERRORE: gli elementi diagonali non devono essere nulli, provocato da A[%d][%d]", i,i);
            exit(3);
        }
    }

    FILE *output_file = fopen(filepath, "w");
    if (output_file == NULL){
		printf("ERRORE: nell'apertura del file\n");
		exit(4);
	}

    do
    {
        for (int i = 0; i < dim; i++){

            //prima sommatoria
            somma1 = 0.0f;
            if(i > 0){
                for (int j = 0; j < i; j++){
                   somma1 += A[i][j] * X[j];
                }
                
            }

            //seconda sommatoria
            somma2 = 0.0f;
            if(i < dim-1){
                for (int j = i + 1; j < dim; j++){
                    somma2 += A[i][j] * XT[j];
                }
                
            }

            //successione x
            X[i] = (B[i] - somma1 -somma2)/ A[i][i];
            errore = (float)fabs(X[i]-XT[i]);
        }

        for (int i = 0; i < dim; i++) XT[i] = X[i];

        printf("\nNumero iterazione: %d\n", itr);
        printf("Errore: %f\n", errore);
        printf("( ");
        for (int i = 0; i < dim; i++) printf("%f ", XT[i]);
        printf(")\n");

        fprintf(output_file, "%d %f\n", itr, errore);

        itr++;

        if (isnan(errore) || isinf(errore)){
            printf("ERRORE: numero diventato null o infinito\n");
            fclose(output_file);
            remove(filepath);
            exit(5);
        }
        
    } while (errore > acc && itr < MAX_ITER);

    if(itr == MAX_ITER){
        printf("ERRORE: raggiunto massimo numero di iterazioni (diminuire l'accuratezza)\n");
        fclose(output_file);
        remove(filepath);
        exit(6);
    }

    fclose(output_file);
    
    return;
}