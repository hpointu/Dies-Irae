#ifndef DBLOC_H
#define DBLOC_H

#include <Box2D/Box2D.h>

#include "Bloc.h"

class DBloc : public Bloc
{
public:
	DBloc(b2World *w);
	void setup();

	virtual void onCollision(Entity *other);

	virtual void redraw();

	virtual void deleteMe();

private:
	float fragility;
};

#endif // DBLOC_H
