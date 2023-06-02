#include <GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include<string>
#include <ctime>
#define ROWS 40.0
#define COLUMNS 60.0
#define MAX 60
#define UP 1
#define RIGHT 2
#define DOWN -1
#define LEFT -2
#define fps 30

using namespace std;
bool game_over=false;
bool game_cube = false;
int score=0;
void unit(int,int);
void random(int &,int &);
void output(int , int , char *);
void drawstring(int , int , char *,void* );
void timer_callback(int);
bool food=true;
int gridy=40,gridx=40;
int sDirection = RIGHT;
int foodx,foody;
int posx[MAX+1]={20,20,20,20,20};
int posy[MAX+1]={20,19,18,17,16};
int length=5,df=0;

GLfloat angle = 0.0f; // Nesnenin döndürme açısı
GLfloat xTranslate = 0.0f; // Nesnenin x ekseninde öteleme değeri
GLfloat yTranslate = 0.0f; // Nesnenin y ekseninde öteleme değeri

GLfloat red = 1.0f; // Kırmızı renk bileşeni
GLfloat green = 0.0f; // Yeşil renk bileşeni
GLfloat blue = 0.0f; // Mavi renk bileşeni

int lastMouseX = 0; // Son fare konumu x
int lastMouseY = 0; // Son fare konumu y


void keyboard(unsigned char key,int x,int y)
{
   if((df==0 )&& key=='1'){df=1;
    game_cube = false;
    }else if(df==0 && key=='2'){
        df=2;
   game_cube = true;
    }

   else if(df==0 && key=='3')
   df=3;
   else if(key==27)
   df=0;
  glutPostRedisplay ();

  if (key == 'q' || key == 'Q' || key == 27) {
        exit(0);
    }    else if (key == 'r' || key == 'R') {
        // Kırmızı rengi arttır veya sıfırla
        if (red < 1.0f)
            red += 0.1f;
        else
            red = 0.0f;
    }
    else if (key == 'g' || key == 'G') {
        // Yeşil rengi arttır veya sıfırla
        if (green < 1.0f)
            green += 0.1f;
        else
            green = 0.0f;
    }
    else if (key == 'b' || key == 'B') {
        // Mavi rengi arttır veya sıfırla
        if (blue < 1.0f)
            blue += 0.1f;
        else
            blue = 0.0f;
    }

    if (key == 'a' || key == 'A') {
        glutTimerFunc(0, timer_callback, 0); // Animasyonu başlat
    }

    glutPostRedisplay();

}

void startscreen()
{
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1.0,1.0,1.0);
output(2,38," CAN KURTTEKIN - 170401015 ");
output(2,36," KADIRHAN CEKMEZ - 170401037 ");
output(4,30,"1. OYUN");
output(4,28,"2. 3D OBJE");
output(4,26,"3. CIKIS");
glFlush();
}
/*
void instructions()
{
  glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.058,0.219,0.058);
    output(1,38,"3D OBJE:");
	glBegin(GL_LINES);
	glVertex2f(0,37);
	glVertex2f(60,37);
	glEnd();
	glColor3f(0,1,0);
  output(8,30,"* CAN KURTTEKIN - 170401015 ");
  output(8,28,"* KADIRHAN CEKMEZ - ");
  output(8,26,"* ");
  output(8,24,"* MENUYE DONMEK ICIN ESC'YE BAS");
   glFlush();
}*/

void output(int x, int y, char *string)
{
      int len, i;
           glRasterPos2f(x,y);
           len=(int) strlen(string);
           for (i = 0; i < len; i++)
			{
             glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
			}
}

void drawstring(int x, int y, char *string,void *font)
{
      int len, i;

           glRasterPos2f(x,y);
           len=(int) strlen(string);
           for (i = 0; i < len; i++)
			{
             glutBitmapCharacter(font,string[i]);
			}
}


void drawCube() {
	glColor3f(red, green, blue); // Renk bileşenlerini kullanarak renk ayarla
    glPushMatrix();
    glTranslatef(xTranslate, yTranslate, -5.0f);
    glRotatef(angle, 1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);
    // Ön yüz
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);

    // Sol yüz
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);

    // Arka yüz
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);

    // Sağ yüz
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);

    // Üst yüz
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);

    // Alt yüz
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    glEnd();

    glPopMatrix();
}

void draw_grid()
{
    //left line
    glBegin(GL_QUADS);//begin drawing mode
        glColor3d(1.0, 1.0, 1.0);
        glVertex2d(0,0);
        glColor3d(1.0, 1.0, 1.0);
        glVertex2d(1,0);
        glColor3d(1.0, 1.0, 1.0);
        glVertex2d(1,40);
        glColor3d(1.0, 1.0, 1.0);
        glVertex2d(0,40);
    glEnd();// ending drawing
   //right line
    glBegin(GL_QUADS);//begin drawing mode
        glColor3d(1.0, 1.0, 1.0);
        glVertex2d(39,0);
        glColor3d(1.0, 1.0, 1.0);
        glVertex2d(40,0);
        glColor3d(1.0, 1.0, 1.0);
        glVertex2d(40,40);
        glColor3d(1.0, 1.0, 1.0);
        glVertex2d(39,40);
    glEnd();// ending drawing
   //top line
    glBegin(GL_QUADS);//begin drawing mode
        glColor3d(1.0, 1.0, 1.0);
        glVertex2d(0,39);
        glColor3d(1.0, 1.0, 1.0);
        glVertex2d(40,39);
        glColor3d(1.0, 1.0, 1.0);
        glVertex2d(40,40);
        glColor3d(1.0, 1.0, 1.0);
        glVertex2d(0,40);
    glEnd();// ending drawing

    glBegin(GL_QUADS);//begin drawing mode
        glColor3d(1.0, 1.0, 1.0);
        glVertex2d(0,0);
        glColor3d(1.0, 1.0, 1.0);
        glVertex2d(40,0);
        glColor3d(1.0, 1.0, 1.0);
        glVertex2d(40,1);
        glColor3d(1.0, 1.0, 1.0);
        glVertex2d(0,1);
    glEnd();// ending drawing

}

void draw_snake()
{
    for(int i =length-1;i>0;i--)
    {
        posx[i]=posx[i-1];
        posy[i]=posy[i-1];
    }

            switch(sDirection)
            {
            case UP:
                posy[0]++;
                break;
            case DOWN:
                posy[0]--;
                break;
            case RIGHT:
                posx[0]++;
                break;
            case LEFT:
                posx[0]--;
                break;
            }
            for(int i=0;i<length;i++)
            {
                if(i==0)
                {
                    glColor3f(0.058,0.219,0.058);
                }
                else
                {
                    glColor3f(0.607,0.737,0.058);
                 }
                     glBegin(GL_QUADS);
                         glVertex2d(posx[i],posy[i]);
                         glVertex2d(posx[i]+1,posy[i]);
                         glVertex2d(posx[i]+1,posy[i]+1);
                         glVertex2d(posx[i],posy[i]+1);
                      glEnd();

            }
            if(posx[0]==0||posx[0]==gridx-1||posy[0]==0||posy[0]==gridy-1) //snake touches red boundary
                game_over=true;
            else if(posx[0]==foodx && posy[0]==foody)
            {    length++;
                food=true;
                score++;
                if(length>MAX)
                   length=MAX;

            }
            for(int j=1;j<length;j++)
            {
                if(posx[j]==posx[0] && posy[j]==posy[0])
                    game_over=true;
            }

}

void draw_food()
{
    if(food)
      random(foodx,foody);
     food=false;
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS);
        glVertex2d(foodx,foody);
        glVertex2d(foodx+1,foody);
        glVertex2d(foodx+1,foody+1);
        glVertex2d(foodx,foody+1);
    glEnd();
}

void random(int &_min,int &_max)
{
    srand(time(NULL));
    int a=0,b=0;
    a=gridx-2;
    b=gridy-2;
    int m=1;

    _min=m+rand()%(a-m);
    _max=m+rand()%(b-m);

}

void init()
{
    glClearColor(0.792,0.976,0.054,0.1); 	// #9bbc0f	(155,188,15)
    glClearColor(0.0,0.0,0.0,1.0); 	// #9bbc0f	(155,188,15)
}

//Callbacks
void display_callback()
{
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(df==0){
      startscreen();
    }else if(df==1)
     {
    draw_grid();
    draw_snake();
    draw_food();
    if(game_over)
    {
        string fscore;
        string tmp=to_string(score);
        string text = "Skorunuz : "+tmp;
        int n = text.length();
        char char_array[n + 1];
        strcpy(char_array, text.c_str());
        MessageBox(NULL,char_array,"Oyun Bitti",MB_OK);
        exit(0);
    }
    }
    else if(df==2){
        glClear(GL_COLOR_BUFFER_BIT);
        gluLookAt(0.0f, 0.0f, 5.0f,  // Kamera pozisyonu
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);

        drawCube();
    }else if(df==3)
     {
      exit(0);
     }
    glFlush();
glutSwapBuffers();
}

void reshape_callback(int w, int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(game_cube){
        gluPerspective(45.0f, (GLsizei)w / (GLsizei)h, 0.1f, 100.0f);
    }else if(game_cube == false){
        gluOrtho2D(0,COLUMNS,0,ROWS);
    }



    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void timer_callback(int)
{


    if(game_cube == true){
        angle += 1.0f; // Dönüş hızı
        if (angle > 360)
            angle -= 360;

        glutPostRedisplay();
        glutTimerFunc(16, timer_callback, 0); // Her 16ms'de bir güncelleme yap
    }else if(game_cube== false){
        glutPostRedisplay();
        glutTimerFunc(1000/fps,timer_callback,0);
    }

}

void keyboard_callback(int key,int x,int y)
{
    switch(key){
        case GLUT_KEY_UP:
            yTranslate += 0.1f;
            if(sDirection!=DOWN)
                sDirection=UP;
        break;
    case GLUT_KEY_DOWN:
        yTranslate -= 0.1f;
        if(sDirection!=UP)
            sDirection=DOWN;
        break;
    case GLUT_KEY_RIGHT:
        xTranslate -= 0.1f;
        if(sDirection!=LEFT)
            sDirection=RIGHT;
        break;
    case GLUT_KEY_LEFT:
        xTranslate += 0.1f;
        if(sDirection!=RIGHT)
            sDirection=LEFT;
        break;
    }
}

void motion(int x, int y) {
    int deltaX = x - lastMouseX;
    int deltaY = y - lastMouseY;

    angle += deltaX * 0.2f;
    yTranslate += deltaY * 0.01f;

    lastMouseX = x;
    lastMouseY = y;

    glutPostRedisplay();
}

void entry(int state) {
    if (state == GLUT_LEFT) {
        glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
    }
    else if (state == GLUT_ENTERED) {
        glutSetCursor(GLUT_CURSOR_NONE);
    }
}
void mouse(int button, int state, int x, int y) {
    // Fare tıklamasıyla ilgili herhangi bir işlem yapmıyoruz
}
int main(int argc,char**argv)
{
    glutInit(&argc,argv);//Initializing GLUT
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);//Initializing Display Mode
    glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH)/1.4,glutGet(GLUT_SCREEN_HEIGHT)/1.4);// opens window at max w,h

    glutCreateWindow("Can Kurttekin & Kadirhan Cekmez");//Name of window

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display_callback);//sets display callback for current window
    glutReshapeFunc(reshape_callback);//mainly used for setting view port and projection in reshape_callback
    glutSpecialFunc(keyboard_callback);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutEntryFunc(entry);
    glutTimerFunc(0,timer_callback,0);
    init();//initialization function
    glutMainLoop(); //all the processing will start by calling this line,it holds window on screen
    return 0;
}
