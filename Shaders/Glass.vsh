attribute mediump vec4 attr_pos;
attribute mediump vec4 attr_normal;
attribute mediump vec2 attr_uv;

uniform mediump mat4 unif_lookat;
uniform mediump mat4 unif_projection;
uniform mediump mat4 unif_world;

varying mediump vec4 v_pos;
varying mediump vec3 v_normal;
varying mediump vec2 v_screen_pos;

void main()
{
    mediump vec4 pos;
    pos = unif_world * vec4(attr_pos.xyz,1.0);

    mediump vec4 v4Position = vec4(pos.xyz,1.0);
    mediump vec4 viewPosition = unif_lookat * v4Position;
    mediump vec4 projPosition = unif_projection * viewPosition;

    projPosition /= projPosition.w;

    mediump vec2 screenPoint;
    screenPoint.x = (1.0 + projPosition.x) / 2.0;
    screenPoint.y = (1.0 + projPosition.y) / 2.0;
    v_screen_pos = screenPoint;
    
    v_normal = mat3(unif_world) * attr_normal.xyz;
    v_pos = unif_projection * unif_lookat * unif_world * attr_pos;
    
    gl_Position = unif_projection * unif_lookat * unif_world * attr_pos;
}
