uniform sampler2D playerTexture;
uniform sampler2D levelTexture;

void main()
{
    // Sample the player texture and the level texture
    vec4 playerColor = texture2D(playerTexture, gl_TexCoord[0].xy);
    vec4 levelColor = texture2D(levelTexture, gl_TexCoord[0].xy);

    // Calculate the distance from the current pixel to the light position
    float distance = distance(gl_TexCoord[0].xy, lightPosition);

    // Calculate the amount of light based on the distance and radius
    float light = smoothstep(lightRadius, lightRadius - 0.02, distance);

    // Apply the light to the player texture by adding it to the color
    vec3 playerLightColor = playerColor.rgb + light;

    // Combine the player texture and the level texture
    vec3 finalColor = mix(playerLightColor, levelColor.rgb, levelColor.a);

    // Set the output color
    gl_FragColor = vec4(finalColor, max(playerColor.a, levelColor.a));
}