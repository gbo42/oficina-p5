//Guilherme Bastos de Oliveira - GRR20167818
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL.h>
#include <time.h>
#include "graphics.h"
#include "perspect.h"
#include "objread.h"

//define altura e largura da tela
#define H 600
#define W 800

#define LIMITE 4000000

int main(int argc, char const *argv[]) {
    //declaração de variáveis
    int fim = 0, nVert = 0, nFace = 0, mouse = 0, move = 0, tempo = 0;
    struct timespec anterior, atual;
    float xc = 0, yc = 0;
    coord *pontos = NULL;
    vertice *vertices;
    face *faces;
    FILE *arq;
    char ch;

    clock_gettime(CLOCK_MONOTONIC, &anterior);
    //se receber parâmetro abre arquivo, caso contrário usa a entrada padrão
    if(argc == 2){
        arq = fopen(argv[1], "r");
        if(!arq){
            perror("Não foi possível abrir o arquivo");
            exit(1);
        }
    } else {
        arq = fopen("._wireframe_temp", "w+");
        do{
            ch = fgetc(stdin);
            fputc(ch, arq);
        } while(ch != EOF);
        rewind(arq);
    }

    //calcula a quantidade de vertices e faces
    nVert = conta(arq, 'v');
    nFace = conta(arq, 'f');

    //aloca memória
    faces = (face *)malloc(sizeof(face) * nFace);
    pontos = (coord *)malloc(sizeof(coord) * nVert);
    vertices = (vertice *)malloc(sizeof(vertice) * nVert);

    //salva as informações na memória
    leObj(arq, vertices, faces, nVert, nFace);

    //inicialização da SDL
    SDL_Event event;
    SDL_Init( SDL_INIT_VIDEO );
    SDL_Surface* screen = SDL_SetVideoMode( W, H, 0, SDL_HWSURFACE | SDL_DOUBLEBUF );
    SDL_WM_SetCaption( "Wireframe", 0 );

    //loop principal
    while (!fim) {
        clock_gettime(CLOCK_MONOTONIC, &atual);

        printf("%ld\n", (atual.tv_nsec - anterior.tv_nsec));

        if((atual.tv_sec - anterior.tv_sec) == 0){
            if((atual.tv_nsec - anterior.tv_nsec) > LIMITE){
                tempo = 1;
                anterior.tv_nsec = atual.tv_nsec;
                anterior.tv_sec = atual.tv_sec;
            } else {
                tempo = 0;
            }
        } else {
            tempo = 1;
            anterior.tv_nsec = atual.tv_nsec;
            anterior.tv_sec = atual.tv_sec;
        }
        //faz os testes para as entradas de teclas e mouse
        if (SDL_PollEvent(&event)) {

            switch(event.type){
                case SDL_QUIT:
                    fim = 1;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    mouse = 1;
                    break;
                case SDL_MOUSEBUTTONUP:
                    mouse = 0;
                    move = 0;
                    break;
                case SDL_MOUSEMOTION:
                    if(mouse){
                        if (event.motion.xrel < 0)
                            xc += 3;
                        else if (event.motion.xrel > 0)
                            xc -= 3;
                        if (event.motion.yrel < 0)
                             yc += 3;
                        else if (event.motion.yrel > 0){
                             yc -= 3;
                        } else {
                            move = 0;
                        }
                    }
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_LEFT:
                        move = 1;
                        break;
                        case SDLK_RIGHT:
                        move = 2;
                        break;
                        case SDLK_UP:
                        move = 3;
                        break;
                        case SDLK_DOWN:
                        move = 4;
                        break;
                        case SDLK_ESCAPE:
                        fim = 1;
                        break;
                        default:
                            move = 0;
                        break;
                    }
                    break;
                case SDL_KEYUP:
                    move = 0;
                    break;
                default:
                    break;
            }
        }

        if(tempo){
            switch(move){
                case 1:
                    xc += 1;
                    break;
                case 2:
                    xc -= 1;
                    break;
                case 3:
                    yc -= 1;
                    break;
                case 4:
                    yc += 1;
                    break;
                default:
                break;
            }

            //preenche a tela de cinza
            SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 25, 25, 25));

            //calcula os pontos em relação a posição atual da câmera
            calculaPontos(vertices, faces, pontos, nVert, xc, yc);

            //impreme as linhas de acordo com as faces e os pontos calculados anteriormente
            printaObj(faces, pontos, nFace, screen);

            SDL_Flip(screen);
        }
    }

    //encerra SDL
    SDL_Quit();

    //libera memória
    free(arq);
    free(vertices);
    free(pontos);
    for(int k = 0; k < nFace; k++){
        free(faces[k].verts);
    }
    free(faces);

    //caso tenha recibo pela entrada padrão, deleta arquivo temporário
    if(argc != 2){
        remove("._wireframe_temp");
    }
    return 0;
}
