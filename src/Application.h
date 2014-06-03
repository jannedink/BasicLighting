#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>

#include "EdgeShadow.h"
#include "Light.h"
#include "Block.h"

class Application {

public:
	Application();
	~Application();

	void render();
	void setUpObjects();
	void initialize();
	void cleanup();
	bool isCloseRequested();
	EdgeShadow* castEdgeShadow( Light* light );
	int randomInRange(int min, int max);

private:

	int width_;
	int height_;
	std::vector< Light* > lights_;
	std::vector< Block* > blocks_;
};

#endif