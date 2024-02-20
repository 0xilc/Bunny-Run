#version 330 core

out vec4 fragColor;

uniform float offset;
uniform float scale;
uniform float shiftAmount;
in vec4 pos;

void main(void)
{
    // Convert position to a checkerboard pattern
    bool x = int((pos.x + offset ) * scale) % 2 != 0;
    bool y = int((pos.y + offset ) * scale) % 2 != 0;
    bool z = int((pos.z + offset - shiftAmount) * scale) % 2 != 0;
    
    bool xorXY = x != y;
    
    if (xorXY != z)
        fragColor = vec4(0.5, 0.6, 0.9, 1); // Black
    else
        fragColor = vec4(0.13, 0.11, 0.17, 1); // White
}
