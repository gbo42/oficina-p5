//Guilherme Bastos de Oliveira - GRR20167818
#include "perspect.h"
#include <stdlib.h>
#include <stdio.h>

void calculaPontos(vertice *vertices, face *faces, coord *final, int nVert, float XC, float YC){
    int ZC = -100, W = 800, H = 600;
    coord *pontos = (coord *)malloc(sizeof(coord) * nVert);

    //faz a projeção dos vértices
    #pragma omp parallel for
    for(int k = 0; k < nVert; k++){
        pontos[k].x = XC + ZC * ((vertices[k].x-XC)/(vertices[k].z-ZC));
        pontos[k].y = YC + ZC * ((vertices[k].y-YC)/(vertices[k].z-ZC));
    }

    float xmin = pontos[0].x;
    float xmax = xmin, xtemp;
    float ymin = pontos[0].y;
    float ymax = ymin, ytemp;

    //encontra maior e menor x e y
    for(int k = 1; k < nVert; k++){
        xtemp = pontos[k].x;
        ytemp = pontos[k].y;
        if(xtemp < xmin){
            xmin = xtemp;
        } else if (xtemp > xmax){
            xmax = xtemp;
        }
        if(ytemp < ymin){
            ymin = ytemp;
        } else if (ytemp > ymax){
            ymax = ytemp;
        }
    }

    //faz calculo do centro, diferença e escala de x e y
    float xcen = (xmax+xmin)/2;
    float xdif = xmax-xmin;

    float ycen = (ymax+ymin)/2;
    float ydif = ymax-ymin;

    float escx = (W - 20)/xdif;
    float escy = (H - 20)/ydif;

    //descobre menor escala
    float escala = escx<escy?escx:escy;

    //calculo final para todos os pontos
    #pragma omp parallel for
    for(int k = 0; k < nVert; k++){
        final[k].x = ((pontos[k].x-xcen)*escala)+W/2.0;
        final[k].y = ((pontos[k].y-ycen)*escala)+H/2.0;
    }

    free(pontos);
}
