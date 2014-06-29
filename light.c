#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>
#include "gllight.h"

static float modelAmb[4] = {0.2, 0.2, 0.2, 1.0}
      ,      matAmb[4] = {0.2, 0.2, 0.2, 1.0}
      ,      matDiff[4] = {0.8, 0.8, 0.8, 1.0}
      ,      matSpec[4] = {0.4, 0.4, 0.4, 1.0}
      ,      matEmission[4] = {0.0, 0.0, 0.0, 1.0};

static Light spots[] =
{
  /* LUZ BRANCA! */
  {
    {0.2, 0.2, 0.2, 1.0},  /* ambient */
    {0.8, 0.8, 0.8, 1.0},  /* diffuse */
    {0.4, 0.0, 0.0, 1.0},  /* specular */
    {0.0, 0.0, 0.0, 1.0},  /* position */
    {0.0, -1.0, 0.0},   /* direction */
    20.0,
    60.0,             /* exponent, cutoff */
    {1.0, 0.0, 0.0},    /* attenuation */
    {0.0, 1.25, 0.0},   /* translation */
    {0.0, 0.0, 0.0},    /* rotation */
    {20.0, 0.0, 40.0},  /* swing */
    {0.0, 0.0, 0.0},    /* arc */
    {TWO_PI / 70.0, 0.0, TWO_PI / 140.0}  /* arc increment */
  }
};

static void drawPlane(int w, int h)
{
  int i, j;
  float dw = 1.0 / w;
  float dh = 1.0 / h;

  glPushMatrix();
    glRotatef(-90.0, 1, 0, 0);
    glScalef(1.9, 1.9, 1.0);
    glTranslatef(-0.5, -0.5, 0.0);

    glNormal3f(0.0, 0.0, 1.0);
    for (j = 0; j < h; ++j) {
      glBegin(GL_TRIANGLE_STRIP);
      for (i = 0; i <= w; ++i) {
        glVertex2f(dw * i, dh * (j + 1));
        glVertex2f(dw * i, dh * j);
      }
      glEnd();
    }

  glPopMatrix();
}

static void aimLight(Light * light)
{
    light->rot[0] = 65;
    light->rot[1] = 0;
    light->rot[2] = 0;

    light->trans[0] = 0.;
    light->trans[1] = 0.5;
    light->trans[2] = 1.25;
}

void display(void)
{
  Light *light = &spots[0];
  glClear(GL_COLOR_BUFFER_BIT);

  glPushMatrix();
    aimLight(light);
    LIGHT_set(light, GL_LIGHT0);
    drawPlane(16, 16);
    LIGHT_draw(light);
  glPopMatrix();

  glutSwapBuffers();
}

void animate(void)
{
  glutPostRedisplay();
}

void visibilityFunc(int state)
{
  if (state == GLUT_VISIBLE)
    glutIdleFunc(animate);
  else
    glutIdleFunc(NULL);
}

int main(int argc, char **argv)
{
  Light *light = &spots[0];
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

  glutCreateWindow("GLUT spotlight swing");
  glutDisplayFunc(display);
  glutVisibilityFunc(visibilityFunc);

  glMatrixMode(GL_PROJECTION);
  glFrustum(-1, 1, -1, 1, 2, 6);

  glMatrixMode(GL_MODELVIEW);
  glTranslatef(0.0, 0.0, -3.0);
  glRotatef(45.0, 1, 0, 0);

  glEnable(GL_LIGHTING);
  glEnable(GL_NORMALIZE);

  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, modelAmb);
  glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
  glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

  glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiff);
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
  glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
  glMaterialf(GL_FRONT, GL_SHININESS, 10.0);


  LIGHT_init(light, GL_LIGHT0);

  glutMainLoop();

  return 0;
}
