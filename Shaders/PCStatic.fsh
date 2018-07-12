uniform mediump vec4 unif_color;

varying mediump vec4 v_color;

void main()
{
    mediump vec4 color = v_color / 255.0;
    gl_FragColor = unif_color * color;
}
