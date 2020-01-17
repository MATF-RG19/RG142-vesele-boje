#include <stdio.h>
#include "mete.h"
extern int loptica_u_redu[100];
const float korak_mete = 2;
float brzina_mete = 0.04;
Lopta lopte[MAX_META];

Lopta napravi_loptu() {
    	Lopta tmp_lopta;    	
		tmp_lopta.x = -4 +rand() % 7;
    	tmp_lopta.z = 10;
    	tmp_lopta.boja= rand()/(float)RAND_MAX;
		tmp_lopta.prosla=0;
		tmp_lopta.sudar=0;
		tmp_lopta.parametar=1;

    	return tmp_lopta;
	}



void inicijalizacija_meta() {
    	for(int i = 0; i < MAX_META; i++) {
            	lopte[i] = napravi_loptu();
            	lopte[i].z = lopte[i].z +korak_mete * i ;
		
    	}
}

void azuriraj_mete() {
    	int i;
    	for (i = 0; i < MAX_META; i++) {
				if (lopte[i].sudar==0){
					lopte[i].z -= brzina_mete;
				}
      
    	}
}



void nacrtaj_mete() {
	GLfloat ambient_coeffs[] = { 0.05375, 0.05, 0.06625, 1 };
    	GLfloat diffuse_coeffs[] = { 1.0, 0.37, 0.22525, 1 };
    	GLfloat specular_coeffs[] = {  0.332741, 0.528634, 0.346435, 1 };


    	GLfloat ambient_coeffs1[] = { 0.05375, 0.05, 0.06625, 1 };
    	GLfloat diffuse_coeffs1[] = { 0.0, 1.0, 0.22525, 1 };
    	GLfloat specular_coeffs1[] = {  0.332741, 0.528634, 0.346435, 1 };


    	GLfloat ambient_coeffs2[] = { 0.05375, 0.05, 0.06625, 1 };
    	GLfloat diffuse_coeffs2[] = { 0.0, 1.0, 1.0, 1 };
    	GLfloat specular_coeffs2[] = {  0.332741, 0.528634, 0.346435, 1 };

    	GLfloat shininess = 0.3*128;

    	for (int i = 0; i < MAX_META; i++) {
		for(int j=0;j<loptica_u_redu[i];j++) {
			//Proveravamo koja je boja
			if(lopte[i].boja<0.3){

    				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs);
    				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs);
    				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs);
    				glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
			}
			else if(lopte[i].boja>=0.3 && lopte[i].boja<0.6)  { 
    				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs1);
    				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs1);
    				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs1);
    				glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
			}
			else {
    				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs2);
    				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs2);
    				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs2);
    				glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
			}
			//crtamo lopte
				if (lopte[i].sudar==0){
       			glPushMatrix();
            		glTranslatef(lopte[i].x+ j*0.3, 0,lopte[i].z );
            		glutSolidSphere(0.15, 25, 25);
       			glPopMatrix();
			}
			else if (lopte[i].sudar==1){
				glPushMatrix();
            		glTranslatef(lopte[i].x+ j*0.3, 0,lopte[i].z );
            		glutSolidSphere(lopte[i].parametar*0.15, 25, 25);
            	if(lopte[i].parametar>0){
					lopte[i].parametar-=0.025;
				}
       			glPopMatrix();
       			}
    		}
	}
}
