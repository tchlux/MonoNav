#version 120

attribute vec3 vertex_3f;   // vertex position
attribute vec2 tex_coord_2f; // Texture coordinate

uniform mat4 model_view_projection_matrix4f;

varying vec2 texture; // The texture coordinate

void main() {
  texture = tex_coord_2f;
  gl_Position = model_view_projection_matrix4f * vec4(vertex_3f, 1);
}
