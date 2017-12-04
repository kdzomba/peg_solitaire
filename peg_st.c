#include <stdio.h>
#include <string.h>
#include <time.h>
//#include "plus.h"
#include "solitaire.h"
//#include "pyramid.h"
#define N  9
#define YES 1
#define NO 0
#define OCCUPIED 1
#define FREE 0
#define MAX 35


double dsecnd (void) {
    return (double)( clock( ) ) / CLOCKS_PER_SEC;
}

typedef char bool;
int moves=0;
int pegs=0;

char bd[N][N];

int sp=0;
struct {
    char board[N][N];
    int vert;
    int hor;
    int dir;
} stack[MAX];

char dirname[4][10];

enum dir{WEST, SOUTH, EAST, NORTH};
int dx[]= {0, 1, 0, -1};
int dy[]= {-1, 0, 1, 0};

void print_board(char bd[N][N]) {
    int i, j;

    printf("--------------------------------------------------------------------\n");
    for(i=0; i<N; i++) {
        for(j=0; j<N; j++) {
        if(bd[i][j]==OCCUPIED)
            printf(" 1");
        else if(bd[i][j]==FREE)
            printf(" 0");
        else printf("  ");
        }
        printf("\n");
     }
}

void print_solution() {
    int i;
    strcpy(dirname[0], "lijevo");
    strcpy(dirname[1], "dolje");
    strcpy(dirname[2], "desno");
    strcpy(dirname[3], "gore");

    for(i=0; i<sp; i++) {
        print_board(stack[i].board);
        printf("pomakni cunjic sa polja (%d, %d)", stack[i].hor, stack[i].vert);
        printf(" u smjeru:  %s\n", dirname[stack[i].dir]);
    }
}

void push( char bd[N][N], int xm, int ym, enum dir d) {

    int k, l;

    for(k=0; k<N; k++)
        for(l=0; l<N; l++)
            stack[sp].board[k][l]= bd[k][l];
    stack[sp].hor= xm;
    stack[sp].vert= ym;
    stack[sp].dir= d;
    sp++;
    moves++;
    }

void pop() {
    sp--;
}


bool move(int pegs) {
    int i, j, in, jn, inn, jnn;
    enum dir d;

    if(pegs==1) {
        if( bd[4][4]== OCCUPIED)
            return YES;
        else return NO;
    }

    for(i=0; i<N; i++)
        for(j=0; j<N; j++) {
            if(bd[i][j]==OCCUPIED) {

                for(d=WEST; d<=NORTH; d++) {

                    in= i+ dx[d];
                    jn= j+ dy[d];

                    if(bd[in][jn]==OCCUPIED) {
                        inn= in + dx[d];
                        jnn= jn+ dy[d];

                        if(bd[inn][jnn]==FREE) {
                            bd[i][j]=FREE;
                            bd[in][jn]=FREE;
                            bd[inn][jnn]=OCCUPIED;
                            pegs--;
                            push(bd, i, j, d);
                            if(move(pegs))
                                return YES;
                            bd[i][j]=OCCUPIED;
                            bd[in][jn]=OCCUPIED;
                            bd[inn][jnn]=FREE;
                            pegs++;
                            pop();
                        }
                    }
                }
            }
        }
            return NO;
}



main() {
    int i, j;
    double t;

    for(i=0; i<N; i++)
        for(j=0;j<N;j++)
            bd[i][j]=b[i][j];

     for(i=0; i<N; i++)
        for(j=0; j<N; j++)
            if(bd[i][j]==OCCUPIED)
                pegs++;

    printf("(%3d pegs)\n", pegs);
    print_board(bd);
    printf("to je bila pocetna ploca\n");
   if(move(pegs))
    print_solution();
    else
        printf("nema rjesenja\n");
    printf("ukupan broj poteza: %d\n", moves);
    t=dsecnd();
    printf("vrijeme: %f\n", t);

}




