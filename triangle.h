/*The MIT License (MIT)
 *
 *Copyright (c) 2014 Michael O'Farrell, Bram Wasti
 *
 *Permission is hereby granted, free of charge, to any person obtaining a copy
 *of this software and associated documentation files (the "Software"), to deal
 *in the Software without restriction, including without limitation the rights
 *to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *copies of the Software, and to permit persons to whom the Software is
 *furnished to do so, subject to the following conditions:
 *
 *The above copyright notice and this permission notice shall be included in
 *all copies or substantial portions of the Software.
 *
 *THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *THE SOFTWARE.
 *
 */


#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <GL/gl.h>
#include <GL/glext.h>

#include "colorshader.h"

namespace _Triangle {
  static const GLfloat vertices[] = {
    -1.0f,-1.0f, 0.0f,
     1.0f,-1.0f, 0.0f,
     0.0f, 1.0f, 0.0f,
  };

  static const GLfloat colors[] = {
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
  };
}

class Triangle {
 public:
  GLuint vbo;
  GLuint cbo;
  GLuint vao;
  ColorShader *shader;
  glm::mat4 model;

  Triangle (ColorShader *shader) : shader(shader) {
    model = glm::mat4(1.0f);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);


    //////////////////////////////
    // Vertice coords
    //////////////////////////////
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vbo);

    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(_Triangle::vertices), _Triangle::vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
            );
    glEnableVertexAttribArray(0);
    //////////////////////////////
    // Color coords
    //////////////////////////////
    glGenBuffers(1, &cbo);

    glBindBuffer(GL_ARRAY_BUFFER, cbo);

    // Give our colors to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(_Triangle::colors), _Triangle::colors, GL_STATIC_DRAW);
    glVertexAttribPointer(
            1,                  // attribute 1. No particular reason for 1, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
            );
    glEnableVertexAttribArray(1);


    glBindVertexArray(0);
  }

  void draw(glm::mat4 view, glm::mat4 projection) {
    shader->vp = projection * view;
    shader->model = model;
    (*shader)();

    glBindVertexArray(vao);

    glDrawArrays(GL_TRIANGLES, 0, sizeof(_Triangle::vertices)/sizeof(GLfloat)/3); // Starting from vertex 0; vertices total -> 1 triangle

    glBindVertexArray(0);
  }

  ~Triangle () {
  }
};

#endif /* TRIANGLE_H */

