#version 410 core

uniform int colorMode;
out vec4 fragmentColor;

void main()
{
	switch(colorMode)
	{
		case 0:
			fragmentColor = vec4((228/255.0),(26/255.0),(28/255.0),0); //red
			break;
		case 1:
			fragmentColor = vec4((55/255.0),(126/255.0),(184/255.0),0); //blue
			break;
		case 2:
			fragmentColor = vec4((77/255.0), (175/255.0), (74/255.0), 0); //green
			break;
		case 3:
		 	fragmentColor = vec4((152/255.0), (78/255.0), (163/255.0), 0.0); //purple
			break;
		case 4:
			fragmentColor = vec4(1, (127/255.0), 0, 0); //orange
			break;
		default:
			fragmentColor = vec4(0.1, 0.9, 0.8, 0); //cyan
	}
}
