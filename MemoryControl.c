//
//  MemoryControl.c
//  MemoryControl
//
//  Created by Josepablo Cruz Baas on 13/10/16.
//  Copyright © 2016 Josepablo Cruz Baas. All rights reserved.
//
/*
 *
 *	FACULTAD DE MATEMATICAS
 *	UNIVERSIDAD AUTONOMA DE YUCATAN
 *
 *	ESTUDIANTE DE INGENIERIA EN COMPUTACION
 *
 *	LIBRERIA PARA USO DE MEMORIA DINAMICA
 *
 * 		AUTOR : Josepablo Cruz Baas
 * 		FECHA :	13 - Octubre - 2016
 *
 *	DESCRIPCION :
 *		El siguiente codigo presenta una serie de funciones y una estructura de datos
 *          con la cual se pretende facilitar el uso de memoria dinamica en cualquier programa
 *          escrito en C.
 *      La libreria funciona como una estructura de control llamada Memory. Dicha estructura
 *          almacena de forma ordenada apuntadores a las variables que se construyen de forma
 *          dinamica por medio de las funciones Allocators (newData).
 *
 *  OBJETIVO :
 *      El objetivo de este programa es construir un Garbage Collector para C que pueda
 *      funcionar tanto en programas para pc como en sistemas embebidos.
 *
 *	DESCRIPCION DE USO	:
 *      Se declara y construye la estructura de control utilizando newMemoryControl();
 *      Apartir de este momento, toda memoria dinamica necesaria para el programa
 *          debe ser generada por medio de las funciones Allocator.
 *      Para liberar memoria de una sola variable se puede utilizar releaseIt asegurandose
 *          de referenciar a la estructura de control que la almacena.
 *      Para liberar la totalidad de la memoria en la estructura de control, se utiliza
 *          la funcion release.
 *
 * */
#include "MemoryControl.h"
#include <stdlib.h>         //Libreria para el uso de malloc y free
#include <stdbool.h>        //Libreria para el uso de datos de tipo bool


/*
 *CONSTRUCTOR
 *
 *SALIDA:
 *  Memory*
 *
 *ENTRADAS:
 *  void
 *
 *DESCRIPCION:
 *  Genera memoria dinamica suficiente para la estructura de control
 * */
Memory* newMemoryControl(void){
    Memory* temp = (Memory*)malloc(sizeof(Memory));
    temp->data  = NULL;
    temp->next  = NULL;
    return temp;
}

/*
 *ALLOCATOR
 *  -Dato nuevo
 *SALIDA:
 *  void*           Puntero a la nueva memoria reservada
 *
 *ENTRADAS:
 *  Memory*         Puntero a la estructura de control
 *  long            Tamaño en bytes de la memoria a reservar
 *
 *
 *DESCRIPCION:
 *  Segun el tamaño especificado en la entrada, se reserva
 *  memoria dinamica y se guarda al final de la estructura de control.
 *  Se retorna el apuntador a esa nueva memoria.
 *
 * */
void*   newData(Memory* m,long size){
    Memory *tempM   = m;
    Memory *before = NULL;
    while(tempM){
        before = tempM;
        tempM = tempM->next;
    }
    tempM = newMemoryControl();
    tempM->data     = (void*)malloc(size);
    tempM->next     = NULL;
    before->next = tempM;
    return tempM->data;
}

/*
 *ALLOCATOR
 *  -Nuevo int
 *SALIDA:
 *  int*           Puntero a la nueva memoria reservada
 *
 *ENTRADAS:
 *  Memory*         Puntero a la estructura de control
 *
 *
 *DESCRIPCION:
 *  Se reserva memoria dinamica del tamaño de un entero
 *  y se guarda al final de la estructura de control.
 *  Se retorna el apuntador a esa nueva memoria.
 *
 * */
int*    newInt(Memory* m){
    return (int*)newData(m,sizeof(int));
}
/*
 *ALLOCATOR
 *  -Nuevo double
 *SALIDA:
 *  double*           Puntero a la nueva memoria reservada
 *
 *ENTRADAS:
 *  Memory*         Puntero a la estructura de control
 *
 *
 *DESCRIPCION:
 *  Se reserva memoria dinamica del tamaño de un double
 *  y se guarda al final de la estructura de control.
 *  Se retorna el apuntador a esa nueva memoria.
 *
 * */
double* newDouble(Memory* m){
    return (double*)newData(m,sizeof(double));
}
/*
 *ALLOCATOR
 *  -Nuevo long
 *SALIDA:
 *  long*           Puntero a la nueva memoria reservada
 *
 *ENTRADAS:
 *  Memory*         Puntero a la estructura de control
 *
 *
 *DESCRIPCION:
 *  Se reserva memoria dinamica del tamaño de un long
 *  y se guarda al final de la estructura de control.
 *  Se retorna el apuntador a esa nueva memoria.
 *
 * */
long*   newLong(Memory* m){
    return (long*)newData(m,sizeof(long));
}
/*
 *ALLOCATOR
 *  -Nuevo char
 *SALIDA:
 *  char*           Puntero a la nueva memoria reservada
 *
 *ENTRADAS:
 *  Memory*         Puntero a la estructura de control
 *
 *
 *DESCRIPCION:
 *  Se reserva memoria dinamica del tamaño de un char
 *  y se guarda al final de la estructura de control.
 *  Se retorna el apuntador a esa nueva memoria.
 *
 * */
char*   newChar(Memory* m){
    return (char*)newData(m,sizeof(char));
}


/*
 *RELEASERS
 *  -Liberar un solo dato
 *SALIDA:
 *  bool           false->problema detectado, memoria no liberada
 *
 *ENTRADAS:
 *  Memory*         Puntero a la estructura de control
 *
 *
 *DESCRIPCION:
 *  Se busca en la estructura de control el apuntador conrrespondiente,
 *  Si es encontrado, se libera la memoria y se retorna true.
 *      de lo contrario, se retorna false sin realizar ninguna liberacion.
 *
 * */
bool releaseIt(void* d,Memory* m){
    Memory *temp    = m;
    Memory *before  = NULL;
    while(temp){
        if(temp->data == d){
            free(d);
            before->next = temp->next;
            return true;
        }
        before = temp;
        temp = temp->next;
    }
    return false;
}

/*
 *RELEASERS
 *  -Liberar toda la estructura
 *SALIDA:
 *  void
 *
 *ENTRADAS:
 *  Memory*         Puntero a la estructura de control
 *
 *
 *DESCRIPCION:
 *  Se elimina uno a uno, los datos dentro de la estructura de control,
 *  comenzando por el primer dato almacenado hasta el ultimo.
 *  Para finalizar, se iguala a NULL el puntero de la estructura de datos.
 * */
void    release(Memory* m){
    Memory *temp    = m;
    Memory *before  = NULL;
    while(temp){
        //Eliminamos todos los elementos
        before = temp;
        temp = temp->next;
        free(before->data);
        free(before);
    }
    m=NULL;
}

/*
 *CONTROL Y DEBUG
 *  -Tamaño de la estructura
 *SALIDA:
 *  long            Numero de elementos que contiene la estructura de control.
 *
 *ENTRADAS:
 *  Memory*         Puntero a la estructura de control
 *
 *
 *DESCRIPCION:
 *  Se realiza un conteo de todos los elementos, uno a uno,
 *  almacenados en la estructura de control, eso incluye a
 *  la misma estructura.
 * */
long    lenght(Memory* m){
    long i=0;
    Memory *temp    = m;
    while(temp){
        i++;
        temp = temp->next;
    }
    return i;
}
/*
 *CONTROL Y DEBUG
 *  -Tamaño de la estructura en bytes
 *SALIDA:
 *  long            bytes almacenados en la estructura de control
 *
 *ENTRADAS:
 *  Memory*         Puntero a la estructura de control
 *
 *
 *DESCRIPCION:
 *  Se realiza una suma de memoria reservada de cada
 *  elemento de la estructura de control y se retorna el total.
 * */
long    size(Memory* m){
    long buffer=0;
    Memory *temp    = m;
    while(temp){
        buffer += sizeof(temp->data);
        temp = temp->next;
    }
    return buffer;
}
