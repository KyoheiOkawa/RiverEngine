attribute mediump vec4 attr_pos;
attribute mediump vec4 attr_normal;

uniform mediump mat4 unif_lookat;
uniform mediump mat4 unif_projection;
uniform mediump mat4 unif_world;

varying mediump vec3 v_normal;

void main()
{
    v_normal = mat3(unif_world) * attr_normal.xyz;
    
    gl_Position = unif_projection * unif_lookat * unif_world * attr_pos;
}
