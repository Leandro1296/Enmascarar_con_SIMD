#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void enmascarar_c(unsigned char *a, unsigned char *b, unsigned char *mask, int cant);
void enmascarar_asm(unsigned char *a, unsigned char *b, unsigned char *mask, int cant);

void enmascarar_c(unsigned char *a, unsigned char *b, unsigned char *mask, int cant)
{
    for(int i=0;i<cant;i++){
        if(mask[i]!=0){ //Si es negro el valor es 0, si es blanco es 255
	        a[i] = b[i]; 
	    }
    }
}

void abrirImagen(char *nombreArchivo, int cantidad, unsigned char *buffer)
{
    FILE *fp;
    fp = fopen(nombreArchivo,"rb"); 
    if (fp == NULL){
        printf("Error al abrir el archivo\n");
    }else{
    	fread(buffer, cantidad, 1,fp); 
    }
    fclose(fp);
}

void guardarImagen(char *nombreArchivo, int cantidad, unsigned char *buffer)
{
    FILE *file;
    file = fopen(nombreArchivo,"wb"); 
    fwrite(buffer, 1, cantidad, file);
    fclose(file);
}

// Main
int main(int argc, char *argv[])
{

    clock_t tiempo_inicio, tiempo_final;
    double segundos = 0.0;

    tiempo_inicio = clock();

    if (argc != 6)
    {
        printf("Error al ingresar los parametros. Por favor ingresar 5 parametros.\n");
        return 1;
    }
    
    //Lectura de parametros
    char *imagenA = argv[1]; //imagenA
    char *imagenB = argv[2]; //imagenB
    char *mascaraArg = argv[3]; //mascara
    int ancho = atoi(argv[4]); //para pasar el argumento a int 
    int alto = atoi(argv[5]); //para pasar el argumento a int
    
    int cantidadxPixel = 3; //RGB 3 bytes por pixel
    int cant = ancho * alto * cantidadxPixel;
    
    //Reservar memoria dinámica
    unsigned char *a = malloc(cant);
    unsigned char *b = malloc(cant);
    unsigned char *mascara = malloc(cant);

    //Abrimos las imagenes
    abrirImagen(imagenA, cant, a);
    abrirImagen(imagenB, cant, b);
    abrirImagen(mascaraArg, cant, mascara);

    enmascarar_c(a, b, mascara, cant);    
    enmascarar_asm(a, b, mascara, cant);

    guardarImagen("salida_c.rgb", cant, a);
    guardarImagen("salida_asm.rgb", cant, a);
    
    //Liberar memoria
    free(a);
    free(b);
	free(mascara);

    tiempo_final = clock();

    segundos = (double)(tiempo_final - tiempo_inicio) / CLOCKS_PER_SEC;
    printf("%.16g milisegundos\n", segundos * 1000.0);

    return 0;
}