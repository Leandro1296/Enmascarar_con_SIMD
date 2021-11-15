#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void enmascarar_c(unsigned char *a, unsigned char *b, unsigned char *mask, int cant);
void enmascarar_asm(unsigned char *a, unsigned char *b, unsigned char *mask, int cant);

void abrirImagen(char *nombreArchivo, int cantidad, unsigned char *buffer)
{
    FILE *fp; //Declaracion de variable tipo Archivo
    fp = fopen(nombreArchivo,"rb");  //Abrir el archivo para lectura en modo binario. Si no existe el archivo, devuelve NULL
    if (fp == NULL){
        printf("El archivo %s no existe. Chequear y volver a intentar\n", nombreArchivo);
    }
    else
    {
    	fread(buffer, cantidad, 1,fp); //Carga en buffer el archivo abierto
    }
    fclose(fp); //Cerrar el archivo
}

void enmascarar_c(unsigned char *a, unsigned char *b, unsigned char *mask, int cant)
{
    for(int i=0; i<cant; i=i+3) //Recorre los bytes de la mascara
    {
        if(mask[i]!=0 && mask[i+1]!=0 && mask[i+2]!=0){ //Si el valor es 0, es negro. Si el valor es 255, es blanco
	    a[i] = b[i]; //Al byte de la imagen A le damos el valor de la imagen B
            a[i+1] = b[i+1];
            a[i+2] = b[i+2];
	    }
    }
}

void guardarImagen(char *nombreArchivo, int cantidad, unsigned char *buffer)
{
    FILE *file; //Declara variable de tipo Archivo
    file = fopen(nombreArchivo,"wb"); //Crea el archivo para escribir en modo binario
    fwrite(buffer, 1, cantidad, file); //Escribe en el archivo la informacion que contiene el buffer
    fclose(file); //Cierra el archivo
}

// Main
int main(int argc, char *argv[])
{
    if (argc != 6)
    {
        printf("Error al ingresar los parametros. Por favor ingresar 5 parametros (Ruta de la primer imagen, ruta de la segunda, ruta de la mascara, ancho de las imagenes, alto de las imagenes).\n");
        return 1;
    }

    //Lectura de parametros
    char *imagen_A = argv[1]; //imagenA
    char *imagen_B = argv[2]; //imagenB
    char *mascara = argv[3]; //mascara
    int ancho = atoi(argv[4]); //para pasar el argumento a int 
    int alto = atoi(argv[5]); //para pasar el argumento a int

    clock_t tiempo_inicio, tiempo_final, tiempo_inicio_asm, tiempo_final_asm;
    double segundos_c = 0.0;
    double segundos_asm = 0.0;

    int bytes_x_Pixel = 3; //Declara y inicializa la cantidad de bytes por pixel
    int cant = ancho * alto * bytes_x_Pixel; //Declara e inicializa la cantidad de bytes por imagen

    //Reservar memoria dinámica a partir de la funcion malloc para las imágenes
    unsigned char *memoria_a = malloc(cant);
    unsigned char *memoria_b = malloc(cant);
    unsigned char *memoria_mascara = malloc(cant);
    unsigned char *a_asm = malloc(cant);

    //Abrimos las imagenes pasando como parametros la ruta de la imagen, la cantidad de bytes de la misma y el espacio en memoria reservado
    abrirImagen(imagen_A, cant, memoria_a);
    abrirImagen(imagen_B, cant, memoria_b);
    abrirImagen(mascara, cant, memoria_mascara);

    //Duplicamos el buffer de la imagen a para usarla en C y en ASM
    memcpy(a_asm, memoria_a, cant);

    //Realizamos el enmascarado pasando por parametro los espacios reservados de memoria de las 3 imagenes y la cantidad de bytes de cada una
    tiempo_inicio = clock();
    enmascarar_c(memoria_a, memoria_b, memoria_mascara, cant);
    tiempo_final = clock();

    tiempo_inicio_asm = clock();
    enmascarar_asm(a_asm, memoria_b, memoria_mascara, cant);
    tiempo_final_asm = clock();

    //Guardamos las imagenes pasando como parametros la ruta del archivo final, la cantidad de bytes de la imagen y el espacio de memoria reservado
    guardarImagen("/home/lapassesungs/Escritorio/TP2/salida_c.bmp", cant, memoria_a);
    guardarImagen("/home/lapassesungs/Escritorio/TP2/salida_asm.bmp", cant, memoria_a);
    
    //Liberamos la memoria reservada
    free(memoria_a);
    free(memoria_b);
    free(memoria_mascara);
    free(a_asm);

    printf("\nListo! Las imágenes ya están listas.\n\nEl proceso se ejecutó en el siguiente tiempo:\n\n");
    printf("%f\n", 0.0);
    printf("%f\n", 0.0);
    
    //Calculamos los segundos que tardó en ejecutar y lo informamos al usuario
    segundos_c = (double)(tiempo_final - tiempo_inicio) / CLOCKS_PER_SEC;
    segundos_asm = (double)(tiempo_final_asm - tiempo_inicio_asm) / CLOCKS_PER_SEC;

    printf("Función en C: %.16f milisegundos\n\n", segundos_c * 1000.0);
    printf("Función en ASM: %.16f milisegundos\n\n", segundos_asm * 1000.0);

    return 0;
}
