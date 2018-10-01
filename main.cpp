#include <GL/gl.h>     // The GL Header File
#include <GL/freeglut.h>   // The GL Utility Toolkit (Glut) Header

#include <cmath>
#include <vector>

#include "globals.h"
#include "point2d.h"
#include "delaunay.h"

void mouse_points(int button, int state, int X, int Y) {
  // Respond to mouse button presses.
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    // Adding current mouse point to polygonal

    auto current_point = point<double>(X, Y).change_coordinates(width, height);

    switch (mode) {
      case Mode::marking_points:points.push_back(current_point);
        break;

      default:return;
    }

    glutPostRedisplay();
  }
}

void keyboard_cb(unsigned char key, int X, int Y) {
  switch (key) {
    case 27:             // ESCAPE key
      points = std::move(std::vector<point<double>>{}); // Cleaning points
      triangles = std::move(std::vector<triangle>{});
      mode = Mode::marking_points; // Reset mode
      glutPostRedisplay();
      break;

    case 't':
      if (mode != Mode::triangulate) {
        mode = Mode::triangulate;
        triangles = delaunay::triangulate(points);
      }
      glutPostRedisplay();
      break;
  }
}

void display_points() {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 1.0, 1.0);
  glPointSize(8.0);

  glLineWidth(4);

  switch (mode) {
    case Mode::marking_points:glBegin(GL_POINTS);
      glColor3f(1.0, 1.0, 1.0);
      for (const auto& point: points)
        glVertex2d(point.x, point.y); // Drawing points
      glEnd();
      break;

    case Mode::triangulate:glBegin(GL_LINE_STRIP);
      glColor3f(1.0, 1.0, 1.0);
      for (const auto& triangle: triangles) { // Drawing triangles edges
        glVertex2d(triangle.get_point1().x, triangle.get_point1().y);
        glVertex2d(triangle.get_point2().x, triangle.get_point2().y);
        glVertex2d(triangle.get_point3().x, triangle.get_point3().y);
      }
      glEnd();

      glBegin(GL_POINTS);
      glColor3f(1.0, 0.0, 0.0);
      for (const auto& point: points) { // Drawing triangles vertexes
        glVertex2d(point.x, point.y);
      }
      glEnd();
      break;
  }

  glutSwapBuffers();
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(width, height);
  glutCreateWindow("Delaunay Triangulation");
  glutKeyboardFunc(keyboard_cb);
  glutMouseFunc(mouse_points);

  glutDisplayFunc(display_points);
  glutMainLoop();

  return EXIT_SUCCESS;
}
