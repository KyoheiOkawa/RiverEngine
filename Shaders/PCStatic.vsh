attribute mediump vec4 attr_pos;
attribute mediump vec4 attr_color;

uniform mediump mat4 unif_lookat;
uniform mediump mat4 unif_projection;
uniform mediump mat4 unif_world;

varying mediump vec4 v_color;

void main()
{
    v_color = attr_color;
    gl_Position = unif_projection * unif_lookat * unif_world * attr_pos;
}
