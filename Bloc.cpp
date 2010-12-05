#include "Bloc.h"
#include <QGraphicsScene>
Bloc::Bloc(b2World *w, QGraphicsItem *parent) :
	QGraphicsPolygonItem(parent),
	world(w),
	body(0),
	active(true)
{
//	setFlag(QGraphicsItem::ItemIsMovable, true);
	setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

void Bloc::setup()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x(), -y());
	bodyDef.angle = -(Utils::deg2rad(rotation()));
	body = world->CreateBody(&bodyDef);

	b2PolygonShape shape;

	const QPolygonF &pg = polygon();
	int n = pg.size();
	b2Vec2 vertices[n];

	for(int i=0; i<n; i++)
	{
		const QPointF &p = pg.at(i);
		vertices[i].Set(p.x(), -p.y());
	}

	shape.Set(vertices, n);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.f;
	fixtureDef.friction = 0.5f;

	body->CreateFixture(&fixtureDef);
}

QVariant Bloc::itemChange(GraphicsItemChange change, const QVariant &value)
{
	if(change == QGraphicsItem::ItemPositionHasChanged)
	{
		if(!active)
			actualizeBody();
	}
	return value;
}

void Bloc::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	active = false;
	body->SetType(b2_kinematicBody);
}

void Bloc::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	setPos(mapToScene(event->pos()));
	event->accept();
//	QGraphicsItem::mouseMoveEvent(event);
}

void Bloc::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	active = true;
	body->SetAwake(true);
	body->SetType(b2_dynamicBody);
}

void Bloc::actualizeBody()
{
	if(body)
		body->SetTransform(b2Vec2(x(), -y()), -(Utils::deg2rad(rotation())));

}

void Bloc::adjust()
{
	if(active)
	{
		b2Vec2 position = body->GetPosition();
		float32 angle = body->GetAngle();
		setPos(position.x, -position.y);
		setRotation(-(Utils::rad2deg(angle)));
	}
}
