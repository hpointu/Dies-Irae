#include "World.h"

World::World(QObject *parent) :
	QGraphicsScene(parent)
{
	blocs = new QList<Bloc*>();

	world = new b2World(b2Vec2(0.0f, -9.81f), true);

	b2BodyDef bodyDef;
	b2PolygonShape shape;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;

	QGraphicsRectItem *groundItem = this->addRect(-100, -10, 200, 20);
	groundItem->setBrush(QColor(178, 192, 160));
	groundItem->setPos(0, 10);
	groundItem->setPen(Qt::NoPen);

	bodyDef.position.Set(groundItem->pos().x(), -groundItem->pos().y());

	shape.SetAsBox(groundItem->rect().width()/2, groundItem->rect().height()/2);
	ground = world->CreateBody(&bodyDef);

	ground->CreateFixture(&fixtureDef);

	poly << QPointF(-8,2) << QPointF(8,2) << QPointF(8,-2) << QPointF(-8,-2);

	for(int i=0; i<10; i++)
	{
		Bloc *bloc = new Bloc(world);
		blocs->append(bloc);
		bloc->setPos(-20 + qrand() % 40, -75 - qrand() % 150);
		bloc->setRotation(qrand()%360);
		bloc->setPolygon(poly);
		bloc->setBrush(Qt::blue);
		bloc->setup();
		this->addItem(bloc);
	}



}

void World::timerEvent(QTimerEvent *event)
{
	float32 tstep = 1.0f/25.0f;
	world->Step(tstep, 2, 2);
	for(int i=0; i<blocs->size(); i++)
		blocs->at(i)->adjust();
	QObject::timerEvent(event);
}

void World::addHorizontal()
{
	Bloc *bloc = createBloc();
	bloc->setup();
	this->addItem(bloc);
}

void World::addVertical()
{
	Bloc *bloc = createBloc();
	bloc->setRotation(90);
	bloc->setup();
	this->addItem(bloc);
}

Bloc* World::createBloc()
{
	Bloc *bloc = new Bloc(world);
	blocs->append(bloc);
	bloc->setPos(-20 + qrand() % 40, -75 - qrand() % 150);
	bloc->setPolygon(poly);
	bloc->setBrush(Qt::blue);

	return bloc;
}

