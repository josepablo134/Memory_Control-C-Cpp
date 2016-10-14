//
//  main.c
//  MemoryControl
//
//  Created by Josepablo Cruz Baas on 13/10/16.
//  Copyright © 2016 Josepablo Cruz Baas. All rights reserved.
//
/*
 *PRUEBA DE USO
 *
 *DESCRIPCION:
 *  Se generaran poco mas de 2mb de datos de forma aleatoria,
 *  entre 1 apuntador tipo int y otro de tipo char, para luego
 *  Eliminar un dato al azar apuntado por buffer, cada paso sera
 *  señalado por una salida en consola.
 *
 * */
#include <stdio.h>
#include <stdlib.h>
#include "MemoryControl.h"

int main(int argc, const char * argv[]) {
    Memory *control = newMemoryControl();
    int* buffer=NULL;
        //Allocate
    printf("Allocating data . . .\n\n");
        for(int j=0;j<200;j++){
            for(int i=0; i<205 ; i++){
                int         *Numero = newInt(control);
                char        *Caracter = newChar(control);
                *Numero     =  i;
                *Caracter   =  i+'0';
                if(i==199 && j==153){
                    buffer = Numero;
                }
            }
        }
    printf("Allocated data length %ld\n\n",lenght(control));
    printf("Allocated data size in bytes %ld\n\n",size(control));
    
    printf("Deleting data int -> %d\n\n",*buffer);
    releaseIt(buffer,control);
    
    printf("Update of allocated data length %ld\n\n",lenght(control));
    printf("Update of allocated data size in bytes %ld\n\n",size(control));

    release(control);
    printf("Memory completely erased\n\n");
    return 0;
}
