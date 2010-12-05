#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	qsrand(QDateTime::currentDateTime().toTime_t());

	world = new World();
	world->setItemIndexMethod(QGraphicsScene::NoIndex);
	world->setSceneRect(-110, -150, 220, 200);


	ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
	ui->graphicsView->setRenderHint(QPainter::Antialiasing);
//	ui->graphicsView->scale(2, 2);
	ui->graphicsView->setScene(world);


	world->startTimer(4);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionVertical_triggered()
{
	world->addVertical();
}

void MainWindow::on_actionHorizontal_triggered()
{
	world->addHorizontal();
}
