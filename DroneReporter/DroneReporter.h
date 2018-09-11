#pragma once

#include <QtWidgets/QMainWindow>
#include <QStandardItemModel>
#include "ui_DroneReporter.h"
#include <string>
#include <iostream>
#include <vector>
#include "DroneInfo.h"
#include <functional>
#include <future>
#include <iostream>
#include <memory>


using namespace std;

class DroneReporter : public QMainWindow
{
	Q_OBJECT

private:
	QTimer * timer;
	QStandardItemModel m_droneInfoModel;
	vector<pair<int, int>> m_portInfo;
	vector<DroneInfo> m_drones;
	map<int, DroneInfo*> m_mapFromportToDroneInfo;
	float m_homeLat = 37.555418;
	float m_homeLon = 127.047692;

public:
	DroneReporter(QWidget *parent = Q_NULLPTR);

	void add_drone_info_table_headers();
	void update_drone_info_table();
	

	string translate_to_window_path(const QString& QfilePath) const;

	array<float, 2> translate_coord_to_gps(const float& x, const float& y) const;
	array<float, 2> translate_gps_to_coord(const float& latitude, const float& longitude) const;

	//the formulation belows are based on WGS84 and refered from https://en.wikipedia.org/wiki/Geographic_coordinate_system
	inline double meter_per_latitude() const { return 111132.92 - 559.82*cos(2 * m_homeLat) + 1.175*cos(4 * m_homeLat) - 0.0023*cos(6 * m_homeLat); }
	inline double meter_per_longitude() const { return 111412.84*cos(m_homeLat) - 93.5*cos(3 * m_homeLat) + 0.118*cos(5 * m_homeLat); }

private:
	Ui::DroneReporterClass ui;

public slots:
	void load_port_file();
	void read_drone_info_file();
	void start_read_status();
};
