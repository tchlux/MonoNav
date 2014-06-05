#version 120

attribute vec3 vertex_3f;   // vertex position
uniform mat4 model_view_projection_matrix4f;

void main() {
  gl_Position = model_view_projection_matrix4f * vec4(vertex_3f, 1);
}
