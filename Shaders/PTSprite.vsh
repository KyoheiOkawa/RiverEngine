uniform mediump mat4 unif_matrix;
attribute mediump vec4 attr_pos;
attribute mediump vec2 attr_uv;
varying mediump vec2 vary_uv;

void main(){
    gl_Position = unif_matrix * attr_pos;
    vary_uv = attr_uv;
}
