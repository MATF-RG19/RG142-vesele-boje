#ifndef _PREPREKE_H_
#define _PREPREKE_H_

#include <GL/glut.h>
#include <stdlib.h>

#define MAX_META 100

typedef struct lopta {
    float x;
    float z;
    float boja;
    int prosla;
    int sudar;
    float parametar;
} Lopta;


Lopta napravi_loptu();
void nacrtaj_loptu();
void inicijalizacija_meta();
void azuriraj_mete();
void nacrtaj_mete();

#endif
