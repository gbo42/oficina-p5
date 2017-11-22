//Guilherme Bastos de Oliveira - GRR20167818
#include "datatypes.h"
#include <stdio.h>
#include <stdlib.h>

//função que calcula quantidade total de vertices ou faces no objeto
int conta(FILE *arq, char letra);

//função que salva na mémoria os vertices e faces
void leObj(FILE *arq, vertice *vertices, face *faces, int nVert, int nFace);
