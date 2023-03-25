uniform sampler2D levelTexture;
uniform vec2 lightPosition; //modify so it can store multiple lights
uniform float lightRadius;
// Add a new uniform variable for sprite positions
uniform vec2 spritePosition;
// Add a new uniform variable for default light value
uniform float defaultLight;

void main() {
    // Get the color of the current pixel
    vec4 color = texture2D(levelTexture, gl_TexCoord[0].xy);

    // Calculate the distance from the current pixel to the center of the light
    float distance = length(gl_TexCoord[0].xy - lightPosition);

    // Calculate the distance from the current sprite to the center of the light
    float spriteDistance = length(spritePosition - lightPosition);

    // Calculate the amount of light based on the distance and radius
    
    float control = distance/lightRadius;

    //avoids the value hitting smaller than 1 value and messing up the light calculation
    if(control < 1.0f){
        control = 1.0f;
    }
    float light = 1.0 - clamp(control, 0.0, 1.0);

    // If the current pixel belongs to the sprite, apply a stronger light effect
    if (spriteDistance < 100.0) {
        light = 1.0 - clamp(spriteDistance / lightRadius, 0.0, 1.0);
    }

    // Adjust the default light value by adding it to the light amount
    light += defaultLight;
    
    if(light > 1.0f){
        light = 1.0f;
    }
    
    // Multiply the texture color by the light amount and add it to the final color
    float lightBlue = light;

    if(lightBlue + 0.2 > 1.0){
        lightBlue = 0.8;
    }

    gl_FragColor = vec4(color.r * light,color.g*light,color.b*(lightBlue+0.2), color.a);

    
}






