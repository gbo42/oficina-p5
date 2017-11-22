//Guilherme Bastos de Oliveira - GRR20167818
#ifndef DATATYPES
#define DATATYPES

//estrutura de vertice
typedef struct{
    float x, y, z;
} vertice;

//estrutura de face
typedef struct{
    int qnt, *verts;
} face;

//estrutura de coordena
typedef struct{
    float x, y;
} coord;

#endif
