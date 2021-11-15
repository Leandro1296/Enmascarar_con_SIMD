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

El código principal comienza ejecutando la función main la cual recibe 5 parametros de entrada
1 - La ruta de la primer imagen
2 - La ruta de la segunda imagen
3 - La ruta de la mascara
4 - El ancho de las imagenes
5 - El alto de las imagenes

![image](https://user-images.githubusercontent.com/21018256/141840081-173b248a-904e-426d-ba75-cc8b5a519db0.png)

Estos datos se almacenan en un puntero de tipo char el cual distribuye sus valores en variables del mismo tipo

Luego declaramos e inicializamos variables que nos servirán para calcular el tiempo de ejecución y para calcular los bytes que debemos recorrer en cada imagen

![image](https://user-images.githubusercontent.com/21018256/141840378-d5b06eaf-693a-411b-990d-b7d364af2604.png)

Reservamos memoria con la función malloc(cantidad de bytes a reservar) para cada buffer que almacenará la información de cada imagen

![image](https://user-images.githubusercontent.com/21018256/141840464-bd9fd955-d72d-4860-9edf-28ab2271eeec.png)

Llamamos a la función "abrirImagen" que se encarga de abrir el archivo y cargar la información en el buffer pasado por parametro. Realizamos esta acción para las 3 imágenes

![image](https://user-images.githubusercontent.com/21018256/141840533-f879f877-4c04-4fd4-b0e7-0566247aa153.png)

![image](https://user-images.githubusercontent.com/21018256/141840711-24bca30b-2e72-43b5-9f5b-b0a93edee4be.png)

Duplicamos el buffer de la imagen A para que uno sea trabajado por C y otro por ASM con la funcion memcpy

![image](https://user-images.githubusercontent.com/21018256/141840669-75ab4025-f554-4705-a014-3520f36b688a.png)

Una vez que ya tenemos la información de las imagenes cargada en su buffer correspondiente, llamamos a la funcion de C "enmascarar_c" la cual se encarga de realizar la logica. Además, tomamos el tiempo que demora en ejecutar

![image](https://user-images.githubusercontent.com/21018256/141840917-5185e812-c066-401d-81c8-988dfdb5b310.png)

En la implementación de la función, recorremos los bytes del buffer donde tomamos de a 3 bytes (ya que un pixel se representa con 3 bytes donde cada uno contiene la información de R, G y B). Si los 3 valores son 0 es porque ese pixel es negro. En ese caso realizamos el reemplazo del byte de la imagen A por la informacion del pixel de la imagen B. De esta forma vamos realizando el enmascarado

![image](https://user-images.githubusercontent.com/21018256/141840934-29bf77d3-0bab-40bb-98ae-10a146a3d9e0.png)

Aplicamos la misma logica con ASM llamando a la función correspondiente

![image](https://user-images.githubusercontent.com/21018256/141841298-923403a8-57af-45f9-9543-ebc2097b6433.png)

Para ir finalizando, guardamos la información en un archivo bmp donde llamamos a la funcion "guardarImagen"

![image](https://user-images.githubusercontent.com/21018256/141841370-fd4e5993-7739-4280-a325-66bb35f36997.png)

![image](https://user-images.githubusercontent.com/21018256/141841399-93c977fb-18b2-45b1-9480-2947ed7aba14.png)

Luego liberamos la memoria que reservamos para el procesamiento

![image](https://user-images.githubusercontent.com/21018256/141841488-33d83f72-f253-4d0a-ba1f-0ee550393cbf.png)

Calculamos cuánto tardó en ejecutar cada función e informamos al usuario que la imagen ya se encuentra disponible.

![image](https://user-images.githubusercontent.com/21018256/141841587-f8a01ba3-1667-4fa7-ae10-e0905f04ccef.png)

#### Enmascarar en ASM 💻

> Para este punto se dasarrollo el que codigo que esta en el archivo enmascarar.asm.

Recibe 4 parametros
  * la imagen a
  * la imagen b
  * la mascara
  * cantidad

  El programa recorre los pixeles de las 3 imagenes y utlizando las funciones de mmx MOVQ, PAND y PANDN realiza la modificacion de los pixeles en a segun el color de la mascara.
  Intercambiando los que sean blancos con los datos de la imagen b. 
  
  Finalmente en la pila se va asignando la imagen los cambios que se le fueron haciendo durante el ciclo.

## Ejecucion de pruebas 🧪

  Para la ejecucion de la aplicacion se ceeo un archivo script bash **Script.sh** el cual compila las implementaciones de C y ASM.

  Para ejecutarlo, escribir en la linea de comandos:

  > ./Script.sh
 
 Para ejecutar el código, una vez parados dentro de la carpeta llamamos al ejecutable y le pasamos los parametros necesarios.
 A continuación un ejemplo...

 ![image](https://user-images.githubusercontent.com/21018256/141841936-c5a38931-7d6d-4ae8-94cb-3e2e01af4a79.png)
  
## Comparación de rendimiento 💹

 Luego de probar el codigo con imagenes de distintos tamaños, hemos llegado a tomar el tiempo (en milisegundos) de cuánto tarda en ejecutarse la logica en C y cuánto tarda en ASM.

 Estos son los resultados:

 ![image](https://user-images.githubusercontent.com/21018256/141842187-a5f3172f-732d-4994-985a-0c9d280121c1.png)

 De esta forma, observamos que la ejecución en ASM es mucho más rápida ya que se opera directamente en los registros evitando muchas etapas de compilación que se realizan en C. 

## Muchas Gracias!

## Autores ✒️
- Emiliano Saucedo
- Leandro Gonzalez


