#include <GL/freeglut_std.h>
#include <GL/glut.h>
#include <time.h>

#include "gol_commonincl.h"

#if NCOLS > 200 || NROWS > 100
#define CELL_SIZE 5
#else
#define CELL_SIZE 10
#endif

#define WINDOW_WIDTH NCOLS*CELL_SIZE + 4*CELL_SIZE
#define WINDOW_HEIGHT NROWS*CELL_SIZE + 4*CELL_SIZE

const GLfloat black[3] = {0.0f, 0.0f, 0.0f};
const GLfloat white[3] = {0.9f, 0.9f, 0.9f};

#define BLACK black
#define WHITE white

Board* currentBoard = NULL;

static void drawBoard(Board* board) {

    glBegin(GL_QUADS);

    for (int i = 0; i < NROWS; i++) {
        for (int j = 0; j < NCOLS; j++) {

            if (board->boardMatrix[i][j] == 1) {
                glColor3fv(BLACK);
            } else {
                glColor3fv(WHITE);
            }

            GLfloat x1 = j * CELL_SIZE + 2 * CELL_SIZE;
            GLfloat y1 = i * CELL_SIZE + 2 * CELL_SIZE;

            GLfloat x2 = x1 + CELL_SIZE * .8;
            GLfloat y2 = y1;

            GLfloat x3 = x2;
            GLfloat y3 = y1 + CELL_SIZE * .8;

            GLfloat x4 = x1;
            GLfloat y4 = y3;

            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
            glVertex2f(x3, y3);
            glVertex2f(x4, y4);
        }
    }
    glEnd();
    glFlush();
}

static void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    void (*nextBoard)(Board*);

    if (NCOLS > 512 && NROWS <=512) {
        puts("using openmp.");
        nextBoard = generateNext_mp;
    } else if (NCOLS > 512 && NROWS > 512) {
        puts("using nested openmp.");
        nextBoard = generateNext_mp2;
    } else {
        nextBoard = generateNext;
    }

    nextBoard(currentBoard);
    drawBoard(currentBoard);
    glutSwapBuffers();
}

static void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(1000/30, timer, 0);
}

/* static void idle() {
    glutPostRedisplay();
} */

void render(int argc, char* argv[]) {
    currentBoard = makeRandomBoard(NROWS, NCOLS);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("OpenGL Grid Simulation");

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);

    // Initialize your 'board' array with initial state

    glutDisplayFunc(display);
    // glutIdleFunc(idle);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    freeBoard(currentBoard);
}
