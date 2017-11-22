//Guilherme Bastos de Oliveira - GRR20167818
#include "graphics.h"

void printaObj(face *faces, coord *pontos, int nFace, SDL_Surface *screen){
    //para todos as faces imprime linhas entre os vertices que a compõe
    #pragma omp parallel for
    for(int k = 0; k < nFace; k++){
        int l;
        for(l = 1; l < faces[k].qnt; l++){
            lineRGBA(screen, pontos[-1+faces[k].verts[l-1]].x, pontos[-1+faces[k].verts[l-1]].y, pontos[-1+faces[k].verts[l]].x, pontos[-1+faces[k].verts[l]].y, 100, 255, 100, 25);
        }
        lineRGBA(screen, pontos[-1+faces[k].verts[l-1]].x, pontos[-1+faces[k].verts[l-1]].y, pontos[-1+faces[k].verts[0]].x, pontos[-1+faces[k].verts[0]].y, 100, 255, 100, 25);
    }
}
