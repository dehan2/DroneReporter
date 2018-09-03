#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_DroneReporter.h"

class DroneReporter : public QMainWindow
{
	Q_OBJECT

public:
	DroneReporter(QWidget *parent = Q_NULLPTR);

private:
	Ui::DroneReporterClass ui;
};
