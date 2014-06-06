#include <stdio.h>
#include <assert.h>

#include "Util.h"
#include "Config.h"

#include "Block.h"

Block::Block() {

#ifdef PRINT
    puts("Block::Block()");
#endif

	// Default constructor creates a block of size 50
	// with a random location.
	size(Config::BLOCK_SIZE, Config::BLOCK_SIZE);
	randomLocation();

	// Calculate edges accordingly.
	setEdges();

}

Block::Block(int x, int y, int w, int h) {

    location(x, y);
    size(w, h);
}

Block::~Block() {

	deleteEdges();

#ifdef PRINT
    puts("Block::~Block()");
#endif
}

void Block::deleteEdges() {

	// Delete edges and free pointers.
    std::vector< Edge* >::iterator iEdge;
    for(iEdge = edges_.begin(); iEdge != edges_.end(); ++iEdge) {
        Edge* anEdge = *iEdge;
        delete anEdge;
    }

    edges_.clear();
}

void Block::setEdges() {

    // Edges must be empty to set edges.    
    assert( edges_.size() == 0 );

    // Set/Create edges.
    Vector2f A(x_, y_);
    Vector2f B(x_ + width_, y_);
    Vector2f C(x_ + width_, y_ + height_);
    Vector2f D(x_, y_ + height_);

    edges_.push_back( new Edge(A, B) );
    edges_.push_back( new Edge(B, C) );
    edges_.push_back( new Edge(C, D) );
    edges_.push_back( new Edge(D, A) );
}

void Block::location(int x, int y) {

	x_ = x;
	y_ = y;

#ifdef PRINT
    printf("Block::location(%d, %d)\n", x_, y_);
#endif
}

void Block::size(int width, int height) {

	width_ = width;
	height_ = height;

#ifdef PRINT
    printf("Block::size(%d, %d)\n", width_, height_);
#endif
}

void Block::randomLocation() {

	// Initialize with a random location within boundaries.
	int margin = 10;

	int x = Util::randomInRange(
		margin,
		Config::SCREEN_WIDTH - width_ - margin
	);

	int y = Util::randomInRange(
		margin,
		Config::SCREEN_HEIGHT - height_ - margin 
	);

    location(x, y);
}

std::vector< Edge* >& Block::getEdges() {

	return edges_;
}