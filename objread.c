//Guilherme Bastos de Oliveira - GRR20167818
#include "objread.h"
#include <ctype.h>

int conta(FILE *arq, char letra){
    rewind(arq);
    char ch;
    int nVert = 0;

    //lê linha por linha se o primeiro caracter for o escolhido e o segundo ' ' incrementa o número de vertices
    do{
        ch = fgetc(arq);
        if(ch == letra){
            ch = fgetc(arq);
            if(ch == ' '){
                nVert++;
            }
        }
        while(ch != '\n' && ch != EOF) ch = fgetc(arq);
    } while (ch != EOF);

    rewind(arq);
    return nVert;
}


void leObj(FILE *arq, vertice *vertices, face *faces, int nVert, int nFace){
    int i = 0;
    int ch;


    rewind(arq);
    //para todas as linhas vê se é um vertice, se for salva a informação
    //no local correspondente ao número do vertice
    do{
        ch = fgetc(arq);
        if(ch == 'v'){
            ch = fgetc(arq);
            if(ch == ' '){
                fscanf(arq, "%f %f %f", &vertices[i].x, &vertices[i].y, &vertices[i].z);
                i++;
            }
        }
        while(ch != '\n' && ch != EOF) ch = fgetc(arq);
    } while (ch != EOF);

    rewind(arq);

    i = 0;
    ch = fgetc(arq);

    //para todas as linhas vê se é uma face, se for salva a informação
    //no local correspondente ao número da face
    while(ch != EOF){
        int v = 0, chars = 0;
        if(ch == 'f'){
            while(ch != EOF && ch != '\n'){
                if(ch == ' '){
                    ch = fgetc(arq);
                    chars++;
                    if(!isspace(ch)){
                        v++;
                    }
                } else {
                    ch = fgetc(arq);
                    chars++;
                }
            }
            if(v){
                fseek(arq, -chars, SEEK_CUR);
                faces[i].qnt = v;
                faces[i].verts = (int *)malloc(sizeof(int) * v);
                fscanf(arq, "%d", &faces[i].verts[0]);
                for(int k = 1; k < v; k++){
                    while(fgetc(arq) != ' ');
                    fscanf(arq, " %d", &faces[i].verts[k]);
                }
                i++;
            }
        } else {
            while(ch != '\n' && ch != EOF){
                ch = fgetc(arq);
            }
        }
        ch = fgetc(arq);
    }

    rewind(arq);
}
