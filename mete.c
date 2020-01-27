#include <stdio.h>
#include "mete.h"
#include <math.h>
#include "image.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <string.h>
extern int loptica_u_redu[100];
extern float animation_parametar1;
const float korak_mete = 2;
float brzina_mete = 0.04;
Lopta lopte[MAX_META];
extern float slucajni1[MAX_META];
float rotacija=0;

GLuint wall_texture_name;

Lopta napravi_loptu() {
    	Lopta tmp_lopta;    	
		tmp_lopta.x = -4 +rand() % 7;
		tmp_lopta.x1=tmp_lopta.x;
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
				lopte[i].x=lopte[i].x1+sin(animation_parametar1);
				rotacija+=0.05;
      
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
            		glRotatef(rotacija,1,1,1);
            		if(slucajni1[i]<0.3)
            		glutSolidSphere(0.15, 25, 25);
            		else if (slucajni1[i]>=0.3 && slucajni1[i]<0.6)
            		glutSolidCube(0.3);
            		else{
						glRotatef(90,1,0,0);
						glutSolidCone(0.15, 0.15, 15, 1);
						glRotatef(-180,1,0,0);
						glutSolidCone(0.15, 0.15, 15, 1);
					}
       			glPopMatrix();
			}
			else if (lopte[i].sudar==1){
				glPushMatrix();
            		glTranslatef(lopte[i].x+ j*0.3, 0,lopte[i].z );
            		glRotatef(rotacija,1,1,1);
            		if(slucajni1[i]<0.3)
            		glutSolidSphere(lopte[i].parametar*0.15, 25, 25);
            		else if (slucajni1[i]>=0.3 && slucajni1[i]<0.6)
            		glutSolidCube(lopte[i].parametar*0.3);
            		else{
						glRotatef(90,1,0,0);
						glutSolidCone(0.15*lopte[i].parametar, 0.15*lopte[i].parametar, 15, 1);
						glRotatef(-180,1,0,0);
						glutSolidCone(0.15*lopte[i].parametar, 0.15*lopte[i].parametar, 15, 1);
					}
            	if(lopte[i].parametar>0){
					lopte[i].parametar-=0.025;
				}
				else{ 
					lopte[i].x=-10;
					lopte[i].parametar=0;
					}
				glPopMatrix();
       			}
    		}
	}
}

void initialize()
{
    /* Objekat koji predstavlja teskturu ucitanu iz fajla. */
    Image * image;

    /* Postavlja se boja pozadine. */
    glClearColor(0, 0, 0, 0);

    /* Ukljucuje se testiranje z-koordinate piksela. */
    glEnable(GL_DEPTH_TEST);

    /* Ukljucuju se teksture. */
    glEnable(GL_TEXTURE_2D);

    glTexEnvf(GL_TEXTURE_ENV,
              GL_TEXTURE_ENV_MODE,
              GL_REPLACE);

    /*
     * Inicijalizuje se objekat koji ce sadrzati teksture ucitane iz
     * fajla.
     */
    image = image_init(0, 0);

    /* Kreira se prva tekstura. */
    image_read(image, "stars.bmp");

    /* Generisu se identifikatori tekstura. */
    glGenTextures(1, &wall_texture_name);

    glBindTexture(GL_TEXTURE_2D, wall_texture_name);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    /* Iskljucujemo aktivnu teksturu */
    glBindTexture(GL_TEXTURE_2D, 0);

    /* Unistava se objekat za citanje tekstura iz fajla. */
    image_done(image);
}

void iscrtaj_pozadinu(){
	const static GLfloat material_emission[] = { 0.15, 0.15, 0.15, 1 };
    	
	GLfloat ambient_coeffs[] = { 0.05375, 0.05, 0.06625, 1 };
    	GLfloat diffuse_coeffs[] = { 0.6, 0.6, 0.6, 1 };
    	GLfloat specular_coeffs[] = {  0.332741, 0.528634, 0.346435, 1 };
	GLfloat shininess = 0.3*128;
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs);
    	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs);
    	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs);
    	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	
	glMaterialfv(GL_FRONT, GL_EMISSION, material_emission);


	glPushMatrix();
		glBegin(GL_QUADS);

		    glColor3f(1, 0, 0);
		    glNormal3f(0, 0, 1);

		    glTexCoord2f(0 ,1);
		    glVertex3f(-0.5, 0.5, 0);

		    glTexCoord2f(1 ,1);
			glVertex3f(0.5, 0.5, 0);

		    glTexCoord2f(1 ,0);
			glVertex3f(0.5, -0.5, 0);

		    glTexCoord2f(0 ,0);
			glVertex3f(-0.5, -0.5, 0);

		glEnd();
	glPopMatrix();
}


