// ModelView.c++ - a basic combined Model and View for OpenGL

#include <iostream>

//Used for generating points on the Andrews curve
#include <math.h>

#include "ModelView.h"
#include "Controller.h"
#include "ShaderIF.h"

double ModelView::mcRegionOfInterest[6] = { -1.0, 1.0, -1.0, 1.0, -1.0, 1.0 };
bool ModelView::aspectRatioPreservationEnabled = true;

ModelView::ModelView(ShaderIF* sIF, float params[], int length, int color) : shaderIF(sIF), color(color)
{
	defineCurve(params, length);
}

ModelView::~ModelView()
{
	if (vao[0] > 0) // hasn't already been deleted
	{
		glDeleteBuffers(1, vbo);
		glDeleteVertexArrays(1, vao);
		vao[0] = vbo[0] = 0;
	}
}

void ModelView::compute2DScaleTrans(float* scaleTransF) // CLASS METHOD
{
	double xmin = mcRegionOfInterest[0];
	double xmax = mcRegionOfInterest[1];
	double ymin = mcRegionOfInterest[2];
	double ymax = mcRegionOfInterest[3];

	if (aspectRatioPreservationEnabled)
	{
		// preserve aspect ratio. Make "region of interest" wider or taller to
		// match the Controller's viewport aspect ratio.
		double vAR = Controller::getCurrentController()->getViewportAspectRatio();
		matchAspectRatio(xmin, xmax, ymin, ymax, vAR);
	}

    // We are only concerned with the xy extents for now, hence we will
    // ignore mcRegionOfInterest[4] and mcRegionOfInterest[5].
    // Map the overall limits to the -1..+1 range expected by the OpenGL engine:
	double scaleTrans[4];
	linearMap(xmin, xmax, -1.0, 1.0, scaleTrans[0], scaleTrans[1]);
	linearMap(ymin, ymax, -1.0, 1.0, scaleTrans[2], scaleTrans[3]);
	for (int i=0 ; i<4 ; i++)
		scaleTransF[i] = static_cast<float>(scaleTrans[i]);
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void ModelView::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = -3.14159;	xyzLimits[1] = 3.14159;
	xyzLimits[2] = ymin;				xyzLimits[3] = ymax;
	xyzLimits[4] = -1;				xyzLimits[5] = 1;
}

bool ModelView::handleCommand(unsigned char anASCIIChar, double ldsX, double ldsY)
{
	return true;
}

// linearMap determines the scale and translate parameters needed in
// order to map a value, f (fromMin <= f <= fromMax) to its corresponding
// value, t (toMin <= t <= toMax). Specifically: t = scale*f + trans.
void ModelView::linearMap(double fromMin, double fromMax, double toMin, double toMax,
					  double& scale, double& trans) // CLASS METHOD
{
	scale = (toMax - toMin) / (fromMax - fromMin);
	trans = toMin - scale*fromMin;
}

void ModelView::matchAspectRatio(double& xmin, double& xmax,
        double& ymin, double& ymax, double vAR)
{
	double wHeight = ymax - ymin;
	double wWidth = xmax - xmin;
	double wAR = wHeight / wWidth;
	if (wAR > vAR)
	{
		// make window wider
		wWidth = wHeight / vAR;
		double xmid = 0.5 * (xmin + xmax);
		xmin = xmid - 0.5*wWidth;
		xmax = xmid + 0.5*wWidth;
	}
	else
	{
		// make window taller
		wHeight = wWidth * vAR;
		double ymid = 0.5 * (ymin + ymax);
		ymin = ymid - 0.5*wHeight;
		ymax = ymid + 0.5*wHeight;
	}
}

void ModelView::render() const
{
	// save the current GLSL program in use
	GLint pgm;
	glGetIntegerv(GL_CURRENT_PROGRAM, &pgm);

	// draw the triangles using our vertex and fragment shaders
	glUseProgram(shaderIF->getShaderPgmID());

	if(shaderIF->ppuExists("scaleTrans") != -1){
		float scaleTrans[4];
		compute2DScaleTrans(scaleTrans);
		glUniform4fv(shaderIF->ppuLoc("scaleTrans"), 1, scaleTrans);
	}

	// Establish the color mode
	if(shaderIF->ppuExists("colorMode") != -1){
		glUniform1i(shaderIF->ppuLoc("colorMode"), color);
	}


	// TODO: make require primitive call(s)
	glBindVertexArray(vao[0]);

	// TODO: Draw the curve?
	glDrawArrays(GL_LINE_STRIP, 0, NUM_POINTS_ON_CURVE);

	// restore the previous program
	glUseProgram(pgm);
}

void ModelView::setMCRegionOfInterest(double xyz[6])
{
	for (int i=0 ; i<6 ; i++)
		mcRegionOfInterest[i] = xyz[i];
}

float ModelView::generateYValue(float t, float params[], int length) {
	float answer = 0;
	if (length >= 1) {
		answer += params[0] / sqrt(2);
	}
	for(int i=1; i<length; i++){
		int n = (i+1)/2;
		if (i%2==0) {
			// if even
			answer += params[i] * cos(n*t);
		}
		else{
			// if odd
			answer += params[i] * sin(n*t);
		}
	}
	return answer;
}

void ModelView::defineCurve(float params[], int length) {

	//Create all pairs of points based on the Andrews curves function
	vec2* vertices = new vec2[NUM_POINTS_ON_CURVE];
	for (int i = 0; i < NUM_POINTS_ON_CURVE; i++) {
		vertices[i][0] = -3.14159 + i*(3.14159/(NUM_POINTS_ON_CURVE/2));
		vertices[i][1] = generateYValue(vertices[i][0], params, length);
		if (i==0) {
			ymin = ymax = vertices[i][1];
		}
		else {
			ymax = vertices[i][1] > ymax ? vertices[i][1] : ymax;
			ymin = vertices[i][1] < ymin ? vertices[i][1] : ymin;
		}
	}

	// Create the VAO and VBO names
	glGenVertexArrays(1, vao);
	glGenBuffers(1, vbo);

	// Initialize them
	glBindVertexArray(vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	// Allocate space for AND send data to GPU
	int numBytesInBuffer = NUM_POINTS_ON_CURVE * sizeof(vec2);
	glBufferData(GL_ARRAY_BUFFER, numBytesInBuffer, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(shaderIF->pvaLoc("mcPosition"), 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shaderIF->pvaLoc("mcPosition"));
}
