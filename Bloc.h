#ifndef BLOC_H
#define BLOC_H


#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPolygonItem>
#include <Box2D.h>
#include "Utils.h"

class Bloc : public QGraphicsPolygonItem
{
public:
	explicit Bloc(b2World *w, QGraphicsItem *parent = 0);

	void setup();
	void adjust();
	void actualizeBody();

	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

protected:
	QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
	b2World *world;
	b2Body *body;

	bool active;
};

#endif // BLOC_H
