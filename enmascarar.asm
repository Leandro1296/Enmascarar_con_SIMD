;%include "io.inc"

section .data
    cantidad dd 0
    
section .text
    global enmascarar_asm
   
enmascarar_asm:
    enter 0,0
    
    mov esi, 0 ;inicializo el contador
  
    mov edx,[ebp+20] ;apunta a cant
    mov [cantidad],edx
    
  ciclo:
    cmp esi, [cantidad]  
    je termino
    
    ;parametros
    mov eax,[ebp+8]  ; puntero a la imagen a
    MOVQ mm0,[eax+esi] 
   
    mov eax,[ebp+12]  ;puntero a la imagen b
    MOVQ mm1,[eax+esi]
    
    mov eax,[ebp+16] ;puntero a la mascara
    MOVQ mm2,[eax+esi]

   
    PAND mm1, mm2 ;mantiene la imagen b cuando el pixel es negro f [0f0f00ff] 
		  ;mm1 [0b0b00bb] de la mascara uso los pixel de b si es negro
    PANDN mm2, mm0 ;mantiene la imagen a cuando el pixel es distinto de FFFFFF [0f0f00ff] 
		   ;mm2 [afafaaff] de la mascara uso los pixel de a si es blanco 
    POR mm1, mm2 ;[ababaabb]
       
    ;debe devolver la combinacion de la imagen a y b 
    mov eax,[ebp+8]
    MOVQ [eax+esi], mm1 ;se guarda el cambio
 
    add esi, 8 ; manejamos registros de mmx , se desplaza de a 64 bits
    jmp ciclo
    
   termino:
    
    leave ;Se reinicia la pila
    
    ret
