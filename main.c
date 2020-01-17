#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "mete.h"
#define EPSILON 0.05
extern Lopta lopte[MAX_META];

const float DEGTORAD = 3.1415769/180.0f;

 
void on_keyboard(unsigned char key, int x, int y);
void on_display(void);
void on_reshape(int width, int height);
void on_timer(int value);
void on_timer1(int value);
static void on_mouse(int button, int state, int x, int y);
static void on_motion(int x, int y);


void draw_ball(float radius);
void draw_cannon(float radius,float height);
void draw_circle(float r);
void set_normal_and_vertex_tire(float u, float v, float r);
void draw_tire(float r, float h);


void ispisi_tekst(char * tekst, int x, int y, float r, float g, float b, int sirina_ekrana, int duzina_ekrana);

float cannon_movement_x;
float cannon_movement_y;
int animation_ongoing;
int animation_ongoing1;
float cannon_ball_x;
float cannon_ball_y;
float cannon_ball_z;


int ispaljena;
float brzina;
float brzinaY;
float brzinaZ;
float brzinaX;
float slucajni[MAX_META];

float brzina;

int loptica_u_redu[MAX_META];

int poeni=0;
int i;
int ostalo_zivota=10;

int windowWidth;
int windowHeight;

int k=0;
int p=0;
int pause=0;
extern float brzina_mete;

extern Lopta lopte[MAX_META];
int main(int argc, char **argv){

    	// Inicijalizacija gluta
    	glutInit(&argc, argv);
    	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
       
    	glutInitWindowSize(600, 600);
    	glutInitWindowPosition(100, 100);
    	glutCreateWindow("Vesele boje");
    	glutFullScreen();
	

    	glutKeyboardFunc(on_keyboard);
    	glutReshapeFunc(on_reshape);
    	glutDisplayFunc(on_display);
    	glutPassiveMotionFunc(on_motion);
    	glutMouseFunc(on_mouse);

    	//incijalizacija promenljivih
    	glClearColor(0.7, 0.7, 1, 0);
    	glEnable(GL_DEPTH_TEST);
    	cannon_movement_x=0;
    	cannon_movement_y=0;
    	cannon_ball_x = 0;
    	cannon_ball_y = 0;
    	cannon_ball_z = 0;

    	brzinaZ = 0.0f;
    	brzinaY = 0.0f;
    	brzinaX = 0.0f;

    	ispaljena=0;
    	animation_ongoing=0;
    	animation_ongoing1=0;



    	windowWidth=1366;
    	windowHeight=768;
    	//Dodeljujemo random boje
    	for(i=0;i<MAX_META;i++) {
		double random_broj = rand()/(float)RAND_MAX;
		slucajni[i]=random_broj;
		}
	for(i=0;i<MAX_META;i++)
		loptica_u_redu[i]= rand() % 6 +1;
    	i=0;
    	inicijalizacija_meta();

    	glutMainLoop();
		

    	return 0;
	}
void on_keyboard(unsigned char key, int x, int y)
{
    	switch (key) {
    		case 27:
        		exit(0);
        		break;
		case 'r':
		case 'R':
		//Resetovanje loptice
			ispaljena=0;
        		animation_ongoing = 0;
        		cannon_ball_z = 0;
        		cannon_ball_y = 0;
        		cannon_ball_x = 0;

        		brzinaZ = 0;
        		brzinaY = 0;
        		brzinaX = 0;
			i++;
			break;
    	case 'g':
		case 'G': 
			k=1;
			if (p==0) {
			if (animation_ongoing1==0 ){
				animation_ongoing1 = 1;
				pause=0;
				glutTimerFunc(17, on_timer1, 0);
				glutPostRedisplay();
			}
			}
        	break;
        case 'p':
        case 'P':
			if(animation_ongoing1==1){
				animation_ongoing1=0;
				pause=1;
			}
			break;

	}

}
void on_reshape(int width, int height)
{
    	glViewport(0, 0, width, height);
    
    	glMatrixMode(GL_PROJECTION);
    	glLoadIdentity();
    	gluPerspective(60, (float)width/height, 1, 1500);
}
void on_display(void)
{
    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    	glMatrixMode(GL_MODELVIEW);
    	glLoadIdentity();
    	gluLookAt(0,2, -1, 0, 1.1, 0, 0, 1, 0);

    	glEnable(GL_LIGHTING);
    	glEnable(GL_LIGHT0);

    	glEnable(GL_DEPTH_TEST);
    	draw_cannon(0.2,0.5);
	draw_ball(0.19);
	nacrtaj_mete();
	
    	glDisable(GL_LIGHTING);
    	glDisable(GL_LIGHT0);
	if(k==0) {
		char str2[255];
		char str3[255];
		ispisi_tekst("Da pokrenete igricu stisnite G ",windowWidth/2  - strlen(str2) - 120,
					 windowHeight/2+40,1,0,0,windowWidth,windowHeight);
		ispisi_tekst("Da promenite boju loptice stisnite R",windowWidth/2 - strlen(str3) - 120,
					 windowHeight/2-10,1,0,0,windowWidth,windowHeight);
	
		}
	char str[255];
   	sprintf(str, "Broj loptica: %d / 255", i);
	ispisi_tekst(str,2,2,1,0,0,windowWidth,windowHeight);
	char str1[255];
   	sprintf(str1, "Broj poena: %d", poeni);
	ispisi_tekst(str1,windowWidth - strlen(str1) - 210,2,1,0,0,windowWidth,windowHeight);
	char str6[255];
   	sprintf(str1, "Ostalo zivota: %d", ostalo_zivota);
	ispisi_tekst(str1,windowWidth/2  - strlen(str6) - 120,2,1,0,0,windowWidth,windowHeight);
	if(p==1) {
		char str4[255];
		char str5[255];
		sprintf(str4, "Izgubili ste broj ostavarenih poena %d", poeni);
		ispisi_tekst(str4,windowWidth/2  - strlen(str4) - 120,
					 windowHeight/2+40,1,0,0,windowWidth,windowHeight);
		ispisi_tekst("Da napustice igricu stisnite ESC",windowWidth/2 - strlen(str5) - 120,
					 windowHeight/2-10,1,0,0,windowWidth,windowHeight);
	}
	if(pause==1){
				ispisi_tekst("Pauzirali ste igricu",windowWidth/2 - strlen(str6) - 120,
				 windowHeight/2-10,1,0,0,windowWidth,windowHeight);
			 }
		


    	glutSwapBuffers();
}
void draw_ball(float radius) {
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
	if(slucajni[i]<0.3){

    		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs);
    		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs);
    		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs);
    		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
		}
	else if(slucajni[i]>=0.3 && slucajni[i]<0.6)  { 
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
	if(ispaljena==0) {
		glPushMatrix();
		glTranslatef(0,0,0);
        	glRotatef(cannon_movement_x, 1, 0, 0);
        	glRotatef(cannon_movement_y, 0, 1, 0);
		glTranslatef(0,0,0.5);
		glutSolidSphere(radius,25,25);
		glPopMatrix();
		}
	else if (ispaljena==1) {
		glPushMatrix();
        	glTranslatef(cannon_ball_x, cannon_ball_y, cannon_ball_z+0.5);
        	glutSolidSphere(0.1, 100, 100);
    		glPopMatrix();
		}
	}
void draw_cannon(float radius, float height){
    	GLfloat ambient_coeffs[] = { 0.05375, 0.05, 0.06625, 1 };
    	GLfloat diffuse_coeffs[] = { 0.28275, 0.37, 0.22525, 1 };
    	GLfloat specular_coeffs[] = {  0.332741, 0.528634, 0.346435, 1 };

    	GLfloat shininess = 0.3*128;
    	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs);
    	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs);
    	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs);
    	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);


    	float x = 0.0;  //x i y polarne koordinate
    	float y = 0.0;
    	float angle = 0.0; //ugao
    	float angle_step = 0.005; //pomeraj ugla





		//Rotacija za pomeranje topa
    	glPushMatrix();
        glRotatef(cannon_movement_x, 1, 0, 0);
        glRotatef(cannon_movement_y, 0, 1, 0);
        //Crtanje topa
        glBegin(GL_QUAD_STRIP);
        while(angle < 2*M_PI){
       		x = radius*cos(angle);
                y = radius*sin(angle);
                glNormal3f(x / radius, y / radius, 0.0); 
                glVertex3f(x, y, height);
                glVertex3f(x, y, 0.0); 
                angle += angle_step; 
            }
       	glVertex3f(radius, 0.0, height);
        glVertex3f(radius, 0.0, 0.0);
    	glEnd();

    	glutSolidSphere(radius, 100, 100);

	glTranslatef(radius,0,0);
    	draw_tire(0.1,0.05);
	glTranslatef(-2*radius,0,0);
    	draw_tire(0.1,0.05);

    	glPopMatrix();
	}
void set_normal_and_vertex_tire(float u, float v, float r){
    	glNormal3f(0, r*cos(v), r*sin(v));
    	glVertex3f(u, r*cos(v), r*sin(v));
	}

 /* crtanje kruga */
void draw_circle(float r){
    	float v;
    
    	glBegin(GL_TRIANGLE_FAN);
    	glVertex3f(0, 0, 0);
    	for (v = 0; v <= 2*M_PI+EPSILON; v += M_PI/1000) {
        	glNormal3f(1, 0, 0);
        	glVertex3f(0, r*cos(v), r*sin(v));
    		}
    	glEnd();
	}
    
/* crtanje tocka */
void draw_tire(float r, float h)
{
    	float u, v;
    
    	for (u = -h/2; u < h/2; u += 0.01) {
        	glBegin(GL_TRIANGLE_STRIP);
        	glColor3f(0.1, 0.1, 0.1);
        for (v = 0; v <= 2*M_PI+EPSILON; v += M_PI/20) {
            	set_normal_and_vertex_tire(u, v, r);
            	set_normal_and_vertex_tire(u + 0.01, v, r);
        	}
        	glEnd();
    	}
    
    	glPushMatrix();
        glTranslatef(h/2, 0, 0);
        glColor3f(0.1, 0.1, 0.1);
        draw_circle(r);
    	glPopMatrix();
    
    	glPushMatrix();
        glTranslatef(-h/2, 0, 0);
        glColor3f(0.1, 0.1, 0.1);
        draw_circle(r);
    	glPopMatrix();
}
void on_motion(int x, int y){

      double posY = y - windowHeight/2; // scaling [-height/2, height/2] -> [-45, 45]
      double posX = x - windowWidth/2; // scaling [-width/2, width/2] -> [30, -30]
      //using formula for scaling x from range [a, b] to range [c, d]
      // f(x) = (x-a) * ((d-c) / (b-a)) + c , where f(a) = c, f(b) = d;

      cannon_movement_x = (posY+(windowHeight*1.0)/2)*(180/(1.0*windowHeight)) - 90;
     

      cannon_movement_y = (posX+(windowWidth*1.0)/2)*(-120/(windowWidth*1.0)) + 60;

      glutPostRedisplay();

}
static void on_mouse(int button, int state, int x, int y) {
	if(button == GLUT_LEFT_BUTTON && !animation_ongoing && state == GLUT_DOWN) {
		// ispaljivanje loptice
		if( k==1){
			animation_ongoing=1;
			ispaljena=1;
          	brzina = 0.05;
          	brzinaZ = brzina * cos(cannon_movement_x * DEGTORAD) * cos(cannon_movement_y * DEGTORAD);
          	brzinaY = -brzina* sin(cannon_movement_x * DEGTORAD);
          	brzinaX = brzina * cos(cannon_movement_x * DEGTORAD) * sin(cannon_movement_y * DEGTORAD);

          	glutTimerFunc(15, on_timer, 0);
          	glutPostRedisplay();
		}
	}
	
}


void on_timer(int value){
   	if(value != 0)
        	return ;

    	if( cannon_ball_z <12){	
		//ispaljivanje loptice
        	cannon_ball_z += brzinaZ;
        	cannon_ball_y += brzinaY;
        	cannon_ball_x += brzinaX;
		for(int j = 0; j < MAX_META; j++){
			//proveramo sudar
				if(lopte[j].sudar==0){
            		if(cannon_ball_z  <= lopte[j].z + 0.2
                		&& cannon_ball_z >= lopte[j].z - 0.2

                		&& cannon_ball_y <= 0 + 0.2
                		&& cannon_ball_y >= 0 - 0.2

		                && cannon_ball_x >= lopte[j].x - 2*0.2
                		&& cannon_ball_x <= lopte[j].x + (loptica_u_redu[j]+1)*0.2){
							ispaljena=0;
							animation_ongoing = 0;
							cannon_ball_z = 0;
							cannon_ball_y = 0;
							cannon_ball_x = 0;
		
							brzinaZ = 0;
							brzinaY = 0;
							brzinaX = 0;
			if((lopte[j].boja<0.3 && slucajni[i]<0.3) || 
			(lopte[j].boja>=0.3 && slucajni[i]>=0.3 && lopte[j].boja<0.6 && slucajni[i]<0.6) ||
			(lopte[j].boja>=0.6 && slucajni[i]>=0.6)){
				//proveramo da li je ista boja
				lopte[j].sudar=1;
				poeni+=loptica_u_redu[i]*100;
			}
			else  poeni-=50;
				i++;				
				}
			}
	}
		}
    	else {	
	//vracanje loptice u top
		ispaljena=0;
        	animation_ongoing = 0;
        	cannon_ball_z = 0;
        	cannon_ball_y = 0;
        	cannon_ball_x = 0;

        	brzinaZ = 0;
        	brzinaY = 0;
        	brzinaX = 0;
		//povecanje brojaca da bi se manjala boja loptice
		i++;
		poeni-=50;
		}
	if(poeni>1000 && poeni< 2000)
		//ubrzavamo mete
		brzina_mete=0.06;
	if(poeni>2000)
		//ubrzavamo mete
		brzina_mete=0.07;

    	glutPostRedisplay();

    if(animation_ongoing) {
       	glutTimerFunc(15, on_timer, 0);
   	}
}

void on_timer1(int value){
    	if(value != 0)
        	return ;
    	azuriraj_mete();
    	glutTimerFunc(15, on_timer, 0);
	for(int j=0;j<MAX_META;j++) {
		if(lopte[j].z<0  && lopte[j].prosla==0){
			//Kada loptica prodje pored topa gubimo 1 zivot
			lopte[j].prosla=1;
			ostalo_zivota-=1;
			}
		if(ostalo_zivota==0){
			//Ako smo izgubili sve zivote zavrsava se igrica
			p=1;
			animation_ongoing1=0;
		}
	}
	if(animation_ongoing1)
		glutTimerFunc(15, on_timer1, 0);
	}
void ispisi_tekst(char * tekst, int x, int y, float r, float g, float b, int sirina_ekrana, int duzina_ekrana)
{
	glDisable(GL_LIGHTING);

        glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
        glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glColor4f(r, g, b, 1.0 );
	glOrtho(0, sirina_ekrana, 0, duzina_ekrana, -1, 1);
	
	glRasterPos2f(x, y);

	int len= strlen(tekst);
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, tekst[i]);
		}

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}
