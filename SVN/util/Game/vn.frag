#version 120

uniform vec4  ambient_color_4f; // material ambient reflectance color
uniform vec4  diffuse_color_4f; // meterial diffuse reflectance color
uniform vec4  specular_color_4f;// material specular reflectance color
uniform float specular_coefficient_1f; // specular coefficient
uniform vec3  light_position_3f; // Light position
uniform vec4  light_color_4f;    // color of light
uniform float attenuation_factor_1f; // distance attenuation scale factor

varying vec3 position; // vertex position, camera space
varying vec3 normal;   // vertex normal, camera space
varying vec3 light;    // light vector, camera space
varying vec3 view;     // view vector, camera space

void main(){
  float dist = length(light_position_3f - position);
  float attenuation = 1.0 / (1.0 + (attenuation_factor_1f * dist));
  vec3 reflection = normalize(reflect(light, normal));
  float VdotR = max(dot(-view, reflection), 0.0);
  vec4 specular_intensity = pow(VdotR, specular_coefficient_1f) * specular_color_4f;
  vec4 diffuse_intensity = max(dot(normal, light), 0.0) * diffuse_color_4f;
  vec4 intensity = ambient_color_4f + diffuse_intensity + specular_intensity;
  gl_FragColor = attenuation * light_color_4f * intensity;
}
