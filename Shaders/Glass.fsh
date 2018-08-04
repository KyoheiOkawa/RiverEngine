uniform lowp vec4 unif_color;
uniform mediump vec3 unif_lightDir;
uniform mediump vec4 unif_eyePos;
uniform mediump mat4 unif_lookat;
uniform mediump mat4 unif_projection;

varying mediump vec4 v_pos;
varying mediump vec3 v_normal;
varying mediump vec2 v_screen_pos;

uniform sampler2D unif_texture;

void main()
{
    mediump vec4 light;
    
    mediump vec4 eye = unif_projection * unif_lookat * unif_eyePos;
    mediump vec4 eyeDir = normalize(v_pos - unif_eyePos);
    mediump vec3 ref = refract(eyeDir.xyz,v_normal,0.8);
    
    mediump vec4 backTex = texture2D(unif_texture,v_screen_pos+ref.xy*0.05);

    light = backTex;
    
    mediump float d = dot(normalize(v_normal),-unif_lightDir);
    mediump vec4 dif = vec4(0.8,0.8,0.8,0.0) * clamp(d,0.0,1.0) + vec4(0.5,0.5,0.5,0.0);
    light.w = unif_color.w;
    light = light * 0.7 + dif * 0.3;
    
    gl_FragColor = light;
}
