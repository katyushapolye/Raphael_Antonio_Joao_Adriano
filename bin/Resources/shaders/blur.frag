uniform sampler2D texture;
uniform float blurAmount;

void main()
{
    vec2 texCoords = gl_FragCoord.xy / textureSize(texture, 0);
    
    // Aplica um desfoque gaussiano horizontal e verticalmente
    vec4 color = vec4(0.0);
    color += texture2D(texture, texCoords + vec2(-blurAmount, 0.0)) * 0.05;
    color += texture2D(texture, texCoords + vec2(blurAmount, 0.0)) * 0.05;
    color += texture2D(texture, texCoords + vec2(0.0, -blurAmount)) * 0.05;
    color += texture2D(texture, texCoords + vec2(0.0, blurAmount)) * 0.05;
    color += texture2D(texture, texCoords) * 0.55;
    
    gl_FragColor = color;
}