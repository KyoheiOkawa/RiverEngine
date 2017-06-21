uniform mediump mat4 unif_matrix;
attribute mediump vec4 attr_pos;

void main(){
    gl_Position = unif_matrix * attr_pos;
}
