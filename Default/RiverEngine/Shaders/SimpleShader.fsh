uniform sampler2D unif_texture;
varying mediump vec2 vary_uv;
void main(){
    gl_FragColor = texture2D(unif_texture, vary_uv);
}
