//
//  MemoryControl.h
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

#ifndef MemoryControl_h
#define MemoryControl_h


#include <stdlib.h>         //Libreria para el uso de malloc y free
#include <stdbool.h>        //Libreria para el uso de datos de tipo bool

//- - - - - - - - - - - - - - - - - - - -DEFINICION DE LA ESTRUCTURA
struct Memory{
    void* data;
    struct Memory *next;
};
typedef struct Memory Memory;


//- - - - - - - - - - - - - - - - - - - -CONSTRUCTOR
/*
 *  CONSTRUCTOR
 *      Genera memoria dinamica nueva y suficiente para la estructura
 * */
Memory* newMemoryControl(void);

//- - - - - - - - - - - - - - - - - - - -ALLOCATORS
/*
 *  ALLOCATORS
 *      -Dato nuevo             void*       newData
 *      -Nuevo int              int*        newInt
 *      -Nuevo double           double*     newDouble
 *      -Nuevo long             long*       newLong
 *      -Nuevo char             char*       newChar
 * */
void*   newData(Memory*,long);
int*    newInt(Memory*);
double* newDouble(Memory*);
long*   newLong(Memory*);
char*   newChar(Memory*);

//- - - - - - - - - - - - - - - - - - - -RELEASERS
/*
 *  RELEASERS
 *      -Liberar un solo dato       bool        releaseIt
 *      -Liberar toda la estructura void        release
 * */
bool    releaseIt(void*,Memory*);
void    release(Memory*);

//- - - - - - - - - - - - - - - - - - - -FUNCIONES EXTRA DE CONTROL Y DEBUG
/*
 *  CONTROL Y DEBUG
 *      -Longitud de la estructura             long        lenght
 *      -Tamaño de la estructura en bytes      long        size
 * */
long    lenght(Memory*);
long    size(Memory*);


#endif /* MemoryControl_h */
