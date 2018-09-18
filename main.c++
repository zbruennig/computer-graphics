// main.c++

#include "GLFWController.h"
#include "ModelView.h"

#include <fstream>

void createScene(GLFWController& c, ShaderIF* sIF, std::string fileName) {
	std::ifstream in;
	in.open(fileName);
	if(!in) {
		std::cout << "Unable to open " << fileName << ".\n";
		exit(1);
	}
	int num;
	in >> num;
	int length;
	in >> length;
	float values[num][length];

	float x;

	for(int i=0; i<num; i++){
		for(int j=0; j<length; j++){
			in >> x;
			values[i][j] = x;
		}
	}

	for(int i=0; i<num; i++){
		c.addModel(new ModelView(sIF, values[i], length));
	}
}

int main(int argc, char* argv[]) {
	GLFWController c(argv[0]);
	c.reportVersions(std::cout);

	if(argc == 1){
		std::cout << "File name not provided.\n";
		return 0;
	}

	ShaderIF* sIF = new ShaderIF("shaders/project1.vsh", "shaders/project1.fsh");

	createScene(c, sIF, argv[1]);

	// initialize 2D viewing information:
	// Get the overall scene bounding box in Model Coordinates:
	double xyz[6]; // xyz limits, even though this is 2D
	c.getOverallMCBoundingBox(xyz);
	std::cout << "Bounding box: " << xyz[0] << " <= x <= " << xyz[1] << '\n';
	std::cout << "              " << xyz[2] << " <= y <= " << xyz[3] << '\n';
	std::cout << "              " << xyz[4] << " <= z <= " << xyz[5] << "\n\n";
	// Tell class ModelView we initially want to see the whole scene:
	ModelView::setMCRegionOfInterest(xyz);

	glClearColor(1,1,1,1);
	c.run();

	delete sIF;

	return 0;
}
