uniform lowp vec4 unif_color;
uniform mediump vec3 unif_lightDir;

varying mediump vec3 v_normal;

void main()
{
    mediump vec4 light;
    mediump float d = dot(normalize(v_normal),-unif_lightDir);
    light = vec4(0.8,0.8,0.8,0.0) * clamp(d,0.0,1.0) + vec4(0.2,0.2,0.2,0.0);
    light.w = unif_color.w;
    
    gl_FragColor = light;
}
