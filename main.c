#include <stdio.h>
#include <stdlib.h>
double beta;
double infectados;

double pasos_estacionario;
double umbral_estacionario;

double step_mu;

double prob;
double infectados_pasado;
double valor;

FILE* fichero;
FILE* fichero2;

char nombre[30];

int i;

int main()
{
    beta = 0.6;
    pasos_estacionario = 100;
    umbral_estacionario = 0.0000001;
    step_mu = 0.01;

    fichero2 = fopen("diagrama_epidemico.txt", "wt");
    for (double mu = step_mu; mu < 1; mu += step_mu){

        // fichero para guardar evolución cambiando mu
        snprintf(nombre, sizeof(nombre), "infectados_%.2f.txt", mu);
        fichero = fopen(nombre, "wt");

        // primer paso METER FUNCIÓN!!!!!!!!!!!!!
        infectados = 0.01;
        prob = 1 - (1- beta*infectados);
        infectados_pasado = infectados;
        infectados = (1-mu)*infectados + prob*(1-infectados);
        valor = fabs(infectados - infectados_pasado);
        fprintf(fichero, "%d %f \n", 0, infectados);

        printf("mu = %f\n", mu);

        i = 1;
        while (valor > umbral_estacionario) {

            // evolucion
            prob = 1 - (1- beta*infectados);
            infectados_pasado = infectados;
            infectados = (1-mu)*infectados + prob*(1-infectados);

            // guardamos dato
            fprintf(fichero, "%d %f \n", i, infectados);

            // comprobamos si llega al estacionario y sumamos un paso más
            valor = fabs(infectados - infectados_pasado);
            i++;
        }
        fclose(fichero);

        // guardamos el valor de mu y el número de infectados termalizado en el documento de diagrama_epidemico (mu)
        fprintf(fichero2, "%f %f \n", mu, infectados);

    }
    fclose(fichero2);

    return 0;
}
