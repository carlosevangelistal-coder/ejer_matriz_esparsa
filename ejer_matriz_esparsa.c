#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct { //Paso 2 representa una sola casilla individual de la matriz
    int fila;
    int col;
    double valor;
} ElementoEsparso;

// PASO 1
void generar_matriz_txt(const char *nombre_txt, int filas, int cols) {
    FILE *f = fopen(nombre_txt, "w");
    if (f == NULL) {
        printf("Error al crear %s\n", nombre_txt);
        exit(1);
    }

    // Calculamos el 5% de elementos no nulos
    int num_elementos = (int)((filas * cols) * 0.05);

    // Primera línea: guardamos dimensiones y cantidad de datos
    fprintf(f, "%d %d %d\n", filas, cols, num_elementos);

    // Generamos posiciones (i, j) y valores aleatorios
    for (int k = 0; k < num_elementos; k++) {
        int i = rand() % filas;
        int j = rand() % cols;
        double valor = (rand() % 99 + 1) / 10.0; // Números entre 0.1 y 9.9
        fprintf(f, "%d %d %.2f\n", i, j, valor);
    }

    fclose(f);
}

// PASO 2
void convertir_txt_a_bin(const char *nombre_txt, const char *nombre_bin) {
    FILE *txt = fopen(nombre_txt, "r");
    FILE *bin = fopen(nombre_bin, "wb");
    if (txt == NULL || bin == NULL) {
        printf("Error al abrir archivos en el Paso 2.\n");
        exit(1);
    }

    int filas, cols, num_elementos;
    // Leemos la cabecera de la primera línea
    fscanf(txt, "%d %d %d", &filas, &cols, &num_elementos);

    ElementoEsparso elem;
    // Leemos cada línea del texto y la volcamos como bloque binario
    while (fscanf(txt, "%d %d %lf", &elem.fila, &elem.col, &elem.valor) == 3) {
        fwrite(&elem, sizeof(ElementoEsparso), 1, bin);
    }

    fclose(txt);
    fclose(bin);
}

