#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char estado[10];
    char simbolo;
    char destino[10];
} Transicion;

char estados[MAX][10];
char alfabeto[MAX];
char inicial[10];
char finales[MAX][10];
Transicion transiciones[MAX];
int num_estados, num_finales, num_transiciones;

// Lee el archivo Conf.txt y llena las estructuras del AFD
void leer_conf(char *archivo) {
    FILE *f = fopen(archivo, "r");
    if (!f) { printf("Error abriendo Conf.txt\n"); exit(1); }

    char linea[200];
    num_estados = num_finales = num_transiciones = 0;

    // leer estados
    while (fgets(linea, sizeof(linea), f)) {
        if (strncmp(linea, "Estados:", 8) == 0) {
            char *tok = strtok(linea + 8, ", \n");
            while (tok) { strcpy(estados[num_estados++], tok); tok = strtok(NULL, ", \n"); }
        }
        else if (strncmp(linea, "Alfabeto:", 9) == 0) {
            char *tok = strtok(linea + 9, ", \n");
            int i=0;
            while (tok) { alfabeto[i++] = tok[0]; tok = strtok(NULL, ", \n"); }
        }
        else if (strncmp(linea, "Inicial:", 8) == 0) {
            sscanf(linea+8, "%s", inicial);
        }
        else if (strncmp(linea, "Finales:", 8) == 0) {
            char *tok = strtok(linea + 8, ", \n");
            while (tok) { strcpy(finales[num_finales++], tok); tok = strtok(NULL, ", \n"); }
        }
        else if (strchr(linea, '=')) {
            char izq[20], der[20];
            sscanf(linea, "%[^=]=%s", izq, der);
            char *estado = strtok(izq, ",");
            char *simbolo = strtok(NULL, ",");
            strcpy(transiciones[num_transiciones].estado, estado);
            transiciones[num_transiciones].simbolo = simbolo[0];
            strcpy(transiciones[num_transiciones].destino, der);
            num_transiciones++;
        }
    }
    fclose(f);
}

// revuelve 1 si estado es un estado final, 0 si no
int es_final(char *estado) {
    for (int i = 0; i < num_finales; i++)
        if (strcmp(finales[i], estado) == 0) return 1;
    return 0;
}

// simula el AFD sobre una cadena de entrada
int procesar_cadena(char *cadena) {
    char actual[10];
    strcpy(actual, inicial);

    for (int i = 0; i < strlen(cadena); i++) {
        char simbolo = cadena[i];
        int encontrado = 0;
        for (int j = 0; j < num_transiciones; j++) {
            if (strcmp(transiciones[j].estado, actual) == 0 && transiciones[j].simbolo == simbolo) {
                strcpy(actual, transiciones[j].destino);
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) return 0;
    }
    return es_final(actual);
}

int main(int argc, char *argv[]) {

    // Leer archivo configuracion
    leer_conf(argv[1]);

    FILE *f = fopen(argv[2], "r");
    if (!f) { printf("Error abriendo Cadenas.txt\n"); return 1; }

    // procesar cada cadena del archivo    
    char cadena[200];
    while (fgets(cadena, sizeof(cadena), f)) {
        cadena[strcspn(cadena, "\n")] = 0; 
        if (procesar_cadena(cadena))
            printf("%s = acepta\n", cadena);
        else
            printf("%s = NO acepta\n", cadena);
    }
    fclose(f);
    return 0;
}