#version 410 core

uniform int colorMode
out vec4 fragmentColor;

void main()
{
	switch(colorMode)
	{
		case 0:
			fragmentColor = vec4(0.1, 0.9, 0.8, 0); //10,90,80,0
			break;
		case 1:
			fragmentColor = vec4(0.8, 0.3, 0.0, 0.0); //80,30,0,0
			break;
		case 2:
			fragmentColor = vec4(0.7, 0.0, 0.8, 0.0); //70,0,80,0
			break;
		case 3:
		 	fragmentColor = vec4(0.4, 0.65, 0.0, 0.0); //40,65,0,0
			break;
		case 4:
			fragmentColor = vec4(0.0, 0.5, 1.0, 0.0); //0,50,100,0
			break;
		default:
			fragmentColor = vec4(0.1, 0.9, 0.8, 0); //10,90,80,0
	}
}
