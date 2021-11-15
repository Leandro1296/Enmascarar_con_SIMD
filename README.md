# Enmascarar_con_SIMD 🤖 
Funciones para enmascarar imágenes usando SIMD.

### Detalle de la solucion 📜

Se implementó la función enmascarar_asm en lenguaje ensamblador de 32
bits usando instrucciones SIMD y respetando la convención de C de pasaje de parámetros. Al igual
que enmascarar_c en el lenguaje C. Ambas funciones pisan el contenido del buffer a, con el
resultado de combinar a y b usando la máscara mask.
Además se desarrolló un programa en C que reciba los parámetros mencionados por
línea de comandos y que llame a las dos funciones para generar dos archivos (salida_c.bmp y
salida_asm.bmp) que corresponden a las imágenes producidas por las dos llamadas.

```
A. Función enmascarar_c ( unsigned char *a, unsigned char *b, unsigned char *mask, int
cant );

B. Función enmascarar_asm ( unsigned char *a, unsigned char *b, unsigned char *mask,
int cant);
```

#### Enmascarar en C 💻

#### Enmascarar en ASM 💻

> Para este punto se dasarrollo el que codigo que esta en el archivo <nombre del archivo>.

Recibe 4 parametros
  * la imagen a
  * la imagen b
  * la mascara
  * cantidad

  El programa recorre los pixeles de las 3 imagenes y utlizando las funciones de mmx MOVQ, PAND y PANDN realiza la modificacion de los pixeles en a segun el color de la mascara.
  Intercambiando los que sean blancos con los datos de la imagen b. 
  
  Finalmente en la pila se va asignando la imagen los cambios que se le fueron haciendo durante el ciclo.

## Ejecucion de pruebas 🧪

  Para la ejecucion de la aplicacion se ceeo un archivo script bash **nombre del archivo** el cual compila y ejecuta las implementaciones de C y ASM.
  
  Para ejecutarlo, escribir en la linea de comandos:
  
  > ./nombre del archivo
  
## Comparación de rendimiento 💹

#### Comentarios 💬

## Autores ✒️
- Emiliano Saucedo
- Leandro Gonzalez


