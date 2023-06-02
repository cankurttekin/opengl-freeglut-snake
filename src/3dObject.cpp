

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <GL/glut.h>
#include <cstring>
#include <cstdio>

float rotate_x = 0.0;
float rotate_y = 0.0;
int rotate_flag = 0;
float sphere_position[3] = {0.0, 0.0, 0.0};
float player1_position[3] = {0.0,0.362 ,0.0};  // Sol yarý sahanýn tam ortasýna yerleþtirildi
float player2_position[3] = {0.0,-0.362 ,0.0};  // Sað yarý sahanýn tam ortasýna yerleþtirildi
float sphere_speed = 0.01;  // This is the speed of the sphere
float sphere_direction[3] = {1.0, 1.0, 1.0};  // This is the direction of the sphere
float player_rotate = 0.0; // Player rotation
float player_speed = 0.01;
float player_direction[2] = {1.0, -1.0};
int score_top = 0;
int score_bottom = 0;
int player_turn = 1;
char score_display_top[50];
char score_display_bottom[50];
char turn_info[50] = "";

void renderString(float x, float y, void *font, const char* string) {
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(x, y);
    int len = (int) strlen(string);
    for (int i = 0; i < len; i++) {
        glutBitmapCharacter(font, string[i]);
    }
}

void drawCourt() {
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.724, -0.849);
    glVertex2f(0.724, -0.849);
    glVertex2f(0.724, 0.849);
    glVertex2f(-0.724, 0.849);
    glEnd();
    glPopMatrix();

    // Sahayý ikiye ayýran çizgi
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(-0.724, 0.0);
    glVertex2f(0.724, 0.0);
    glEnd();


}

void drawHoop(float y_position) {
    glColor3f(1.0, 1.0, 0.0);
    glPushMatrix();
    glTranslatef(0.0, y_position, 0.0);
    glutWireTorus(0.05, 0.4, 20, 20);
    glPopMatrix();
}

void drawPlayer(float player_position[3]) {
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslatef(player_position[0], player_position[1], player_position[2]);
    glRotatef(player_rotate, 0.0, 1.0, 0.0); // Rotate the player
    glScalef(1.0, 2.0, 1.0); // Make the cube a rectangular prism
    glutWireCube(0.1);
    glPopMatrix();
}

void drawSphere() {
    glColor3f(1.0, 0.5, 0.0);
    glPushMatrix();
    glTranslatef(sphere_position[0], sphere_position[1], sphere_position[2]);
    if (rotate_flag == 1) {
        rotate_x += 2.0;  // rotate_x'i yalnýzca 'a' tuþuna basýldýðýnda arttýrýrýz.
        glRotatef(rotate_x, 1.0, 0.0, 0.0);
    }
    glutWireSphere(0.15, 20, 20);
    glPopMatrix();
}



void checkCollision() {
    float sphere_radius = 0.15;  // Sphere'nin yarýçapý
    float player_half_width = 0.05;  // Oyuncunun yarý geniþliði

    if(abs(sphere_position[0] - player1_position[0]) < sphere_radius + player_half_width &&
       abs(sphere_position[1] - player1_position[1]) < sphere_radius + player_half_width) {
        sphere_position[0] = 0.0;
        sphere_position[1] = 0.0;
        score_top -= 1;
        player_turn = 2;
    }
    else if(abs(sphere_position[0] - player2_position[0]) < sphere_radius + player_half_width &&
            abs(sphere_position[1] - player2_position[1]) < sphere_radius + player_half_width) {
        sphere_position[0] = 0.0;
        sphere_position[1] = 0.0;
        score_bottom -= 1;
        player_turn = 1;
    }
}


void movePlayers() {
    player1_position[0] += player_speed * player_direction[0];
    player2_position[0] += player_speed * player_direction[1];

    if(player1_position[0] > 0.724 || player1_position[0] < -0.724) {
        player_direction[0] = -player_direction[0];
    }
    if(player2_position[0] > 0.724 || player2_position[0] < -0.724) {
        player_direction[1] = -player_direction[1];
    }

    player_rotate += 0.5; // Increment rotation
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    drawCourt();
    drawHoop(1.0);
    drawHoop(-1.0);

    drawSphere();
    drawPlayer(player1_position);
    drawPlayer(player2_position);


    checkCollision();

    sprintf(score_display_top, "Score: %d", score_top);
    sprintf(score_display_bottom, "Score: %d", score_bottom);

    renderString(-0.9, 0.9, GLUT_BITMAP_HELVETICA_18, score_display_top);
    renderString(-0.9, -0.9, GLUT_BITMAP_HELVETICA_18, score_display_bottom);

    if (strcmp(turn_info, "") != 0) {
        renderString(-0.1, 0, GLUT_BITMAP_HELVETICA_18, turn_info);
        sprintf(turn_info, "%s", "");
    }

    glutSwapBuffers();

    if (score_top == 3 || score_bottom == 3) {
        sprintf(turn_info, "Player %d Wins!", (score_top == 3) ? 1 : 2);
        renderString(-0.1, 0, GLUT_BITMAP_HELVETICA_18, turn_info);
        glutSwapBuffers();
        exit(0);
    }
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glOrtho(-0.75, 0.75, -0.90, 0.90, -1.0, 1.0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'a':
        rotate_flag = 1;
        break;
    case 'd':
        rotate_flag = 0;
        break;
    }
}

void special(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        sphere_position[1] += 0.1;
        if(sphere_position[1] > 0.849) {
            score_top += 1;
            sphere_position[1] = 0.0;
            player_turn = 2;
            sprintf(turn_info, "%s", "2nd player turn");
        }
        break;
    case GLUT_KEY_DOWN:
        sphere_position[1] -= 0.1;
        if(sphere_position[1] < -0.849) {
            score_bottom += 1;
            sphere_position[1] = 0.0;
            player_turn = 1;
            sprintf(turn_info, "%s", "1st player turn");
        }
        break;
    case GLUT_KEY_RIGHT:
        sphere_position[0] += 0.1;
        break;
    case GLUT_KEY_LEFT:
        sphere_position[0] -= 0.1;
        break;
    }
}

void timer(int) {
    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, 0);
    if(rotate_flag == 1)
        rotate_x += 2;
    else
        rotate_y += 2;

    movePlayers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("3D Basketball Game");

    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutTimerFunc(0, timer, 0);

    init();

    glutMainLoop();
    return 0;
}

