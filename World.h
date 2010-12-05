#ifndef WORLD_H
#define WORLD_H

#include <Box2D.h>
#include <QObject>
#include <QGraphicsScene>

#include "Bloc.h"

class World : public QGraphicsScene
{

public:
	explicit World(QObject *parent = 0);

	void addHorizontal();
	void addVertical();

protected:
	void timerEvent(QTimerEvent *event);



private:
	QList<Bloc*> *blocs;
	b2Body *ground;
	b2World *world;

	QPolygonF poly;

	Bloc* createBloc();

};

#endif // WORLD_H
