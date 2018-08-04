uniform lowp vec4 unif_color;
uniform mediump vec3 unif_lightDir;

varying mediump vec3 v_normal;
varying mediump vec2 v_uv;

uniform sampler2D unif_texture;

void main()
{
    mediump vec4 texColor = texture2D(unif_texture,v_uv);
    
    mediump vec4 light;
    mediump float d = dot(normalize(v_normal),-unif_lightDir);
    light = texColor * clamp(d,0.0,1.0) + texColor * vec4(0.4,0.4,0.4,0.0);
    light.w = unif_color.w;
    
    gl_FragColor = light;
}

