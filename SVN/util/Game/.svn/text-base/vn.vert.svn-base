#version 120

attribute vec3 vertex_3f;   // vertex position
attribute vec3 normal_3f;   // vertex normal

uniform mat4 model_view_projection_matrix4f;
uniform mat4 model_view_matrix4f;
uniform mat4 normal_matrix4f;
uniform vec3 light_position_3f; // location of light

varying vec3 position; // vertex position, camera space
varying vec3 normal;   // vertex normal, camera space
varying vec3 light;    // light vector, camera space
varying vec3 view;     // view vector, camera space

void main() {
  gl_Position = model_view_projection_matrix4f * vec4(vertex_3f, 1);
  position = (model_view_matrix4f * vec4(vertex_3f, 1)).xyz;
  normal = normalize((normal_matrix4f * vec4(normal_3f, 0)).xyz);
  light = normalize(light_position_3f - position);
  view = normalize(vec3(0,0,0) - position);
  //normalize tunrs a vector to unit length (length 1)
}
