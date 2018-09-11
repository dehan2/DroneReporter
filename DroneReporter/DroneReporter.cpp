#include "DroneReporter.h"
#include <QFileDialog>
#include <fstream>
#include <sstream>
#include <QTimer>

DroneReporter::DroneReporter(QWidget *parent)
	: QMainWindow(parent), m_droneInfoModel(0, 14, this)
{
	ui.setupUi(this);

	add_drone_info_table_headers();
	ui.tableView_main->setModel(&m_droneInfoModel);

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(read_drone_info_file()));
	timer->stop();

	showMaximized();
}



void DroneReporter::add_drone_info_table_headers()
{
	int columnIndex = 0;
	m_droneInfoModel.setColumnCount(15);
	m_droneInfoModel.setHeaderData(columnIndex++, Qt::Horizontal, QObject::tr("ID"));
	m_droneInfoModel.setHeaderData(columnIndex++, Qt::Horizontal, QObject::tr("Port"));
	m_droneInfoModel.setHeaderData(columnIndex++, Qt::Horizontal, QObject::tr("Status"));
	m_droneInfoModel.setHeaderData(columnIndex++, Qt::Horizontal, QObject::tr("Group"));
	m_droneInfoModel.setHeaderData(columnIndex++, Qt::Horizontal, QObject::tr("Battery"));
	m_droneInfoModel.setHeaderData(columnIndex++, Qt::Horizontal, QObject::tr("X_curr"));
	m_droneInfoModel.setHeaderData(columnIndex++, Qt::Horizontal, QObject::tr("Y_curr"));
	m_droneInfoModel.setHeaderData(columnIndex++, Qt::Horizontal, QObject::tr("Z_curr"));
	m_droneInfoModel.setHeaderData(columnIndex++, Qt::Horizontal, QObject::tr("Deviation"));
	m_droneInfoModel.setHeaderData(columnIndex++, Qt::Horizontal, QObject::tr("X_target"));
	m_droneInfoModel.setHeaderData(columnIndex++, Qt::Horizontal, QObject::tr("Y_target"));
	m_droneInfoModel.setHeaderData(columnIndex++, Qt::Horizontal, QObject::tr("Z_target"));
	m_droneInfoModel.setHeaderData(columnIndex++, Qt::Horizontal, QObject::tr("X_diff"));
	m_droneInfoModel.setHeaderData(columnIndex++, Qt::Horizontal, QObject::tr("Y_diff"));
	m_droneInfoModel.setHeaderData(columnIndex++, Qt::Horizontal, QObject::tr("Z_diff"));
}



void DroneReporter::update_drone_info_table()
{
	m_droneInfoModel.clear();
	add_drone_info_table_headers();

	for (auto& drone : m_drones)
	{
		int row = drone.get_ID();
		int col = 0;
		QStandardItem* currItem = new QStandardItem(1, 15);
		m_droneInfoModel.insertRow(row, currItem);

		QModelIndex IDIndex = m_droneInfoModel.index(row, col++);
		QModelIndex portIndex = m_droneInfoModel.index(row, col++);
		QModelIndex statusIndex = m_droneInfoModel.index(row, col++);
		QModelIndex groupIndex = m_droneInfoModel.index(row, col++);
		QModelIndex batteryIndex = m_droneInfoModel.index(row, col++);
		QModelIndex X_currIndex = m_droneInfoModel.index(row, col++);
		QModelIndex Y_currIndex = m_droneInfoModel.index(row, col++);
		QModelIndex Z_currIndex = m_droneInfoModel.index(row, col++);
		QModelIndex deviationIndex = m_droneInfoModel.index(row, col++);
		QModelIndex X_targetIndex = m_droneInfoModel.index(row, col++);
		QModelIndex Y_targetIndex = m_droneInfoModel.index(row, col++);
		QModelIndex Z_targetIndex = m_droneInfoModel.index(row, col++);
		QModelIndex X_diffIndex = m_droneInfoModel.index(row, col++);
		QModelIndex Y_diffIndex = m_droneInfoModel.index(row, col++);
		QModelIndex Z_diffIndex = m_droneInfoModel.index(row, col++);

		m_droneInfoModel.setData(IDIndex, drone.get_ID());
		m_droneInfoModel.setData(portIndex, drone.get_port());
		m_droneInfoModel.setData(groupIndex, drone.get_group());

		string statusStr;
		switch (drone.get_status())
		{
		case DISCONNECT:
		default:
			statusStr = "Disconnect";
			break;
		case IDLE:
			statusStr = "Idle";
			break;
		case MOVING:
			statusStr = "Moving";
			break;
		case GUIDED:
			statusStr = "Guided";
			break;
		case LAND:
			statusStr = "Land";
			break;
		case RTL:
			statusStr = "RTL";
			break;
		}

		m_droneInfoModel.setData(statusIndex, QString::fromStdString(statusStr));

		if (drone.get_status() != DISCONNECT)
		{
			m_droneInfoModel.setData(batteryIndex, drone.get_battery_level());

			const array<float, 3>& currCoord = drone.get_curr_coord();
			m_droneInfoModel.setData(X_currIndex, currCoord.at(0));
			m_droneInfoModel.setData(Y_currIndex, currCoord.at(1));
			m_droneInfoModel.setData(Z_currIndex, currCoord.at(2));

/*
			const array<float, 3>& targetCoord = drone.get_target_coord();
			m_droneInfoModel.setData(X_targetIndex, targetCoord.at(0));
			m_droneInfoModel.setData(Y_targetIndex, targetCoord.at(1));
			m_droneInfoModel.setData(Z_targetIndex, targetCoord.at(2));

			m_droneInfoModel.setData(X_diffIndex, targetCoord.at(0)- currCoord.at(0));
			m_droneInfoModel.setData(Y_diffIndex, targetCoord.at(1) - currCoord.at(1));
			m_droneInfoModel.setData(Z_diffIndex, targetCoord.at(2) - currCoord.at(2));

			float deviation = sqrt(pow(targetCoord.at(0) - currCoord.at(0), 2) 
				+ pow(targetCoord.at(1) - currCoord.at(1), 2) + pow(targetCoord.at(2) - currCoord.at(2), 2));

			m_droneInfoModel.setData(deviationIndex, deviation);*/
		}
	}
	update();
}



string DroneReporter::translate_to_window_path(const QString& QfilePath) const
{
	string filePath = QfilePath.toLocal8Bit();

	size_t i = filePath.find('/');
	while (i != string::npos)
	{
		string part1 = filePath.substr(0, i);
		string part2 = filePath.substr(i + 1);
		filePath = part1 + R"(\)" + part2; // Use "\\\\" instead of R"(\\)" if your compiler doesn't support C++11's raw string literals
		i = filePath.find('/', i + 1);
	}
	return filePath;
}



array<float, 2> DroneReporter::translate_coord_to_gps(const float& x, const float& y) const
{
	float latitude = m_homeLat + (y / meter_per_latitude());
	float longitude = m_homeLon + (x / meter_per_longitude());
	return { latitude, longitude };
}

array<float, 2> DroneReporter::translate_gps_to_coord(const float& latitude, const float& longitude) const
{
	float x = (longitude - m_homeLon)*meter_per_longitude();
	float y = (latitude - m_homeLat)*meter_per_latitude();
	return { x, y };
}

void DroneReporter::load_port_file()
{
	QString QfilePath = QFileDialog::getOpenFileName(this, tr("Open Port File"), NULL, tr("Text file(*.txt)"));
	QFileInfo fileInfo(QfilePath);

	string filePath = translate_to_window_path(QfilePath);
	ifstream portFile(filePath.data());
	if (portFile.is_open()) {
		m_portInfo.clear();
		string line;
		while (getline(portFile, line)) 
		{
			istringstream iss(line);
			string portStr, groupStr;
			iss >> portStr;
			iss >> groupStr;
			int ID = m_drones.size();
			int port = stoi(portStr);
			int group = stoi(groupStr);
			m_drones.push_back(DroneInfo(ID, port, group));
			m_mapFromPortToID[port] = ID;
		}
		cout << "Port read finish" << endl;
		portFile.close();
		update_drone_info_table();
	}
	else
		cout << "Fail to read port file" << endl;
}



void DroneReporter::read_drone_info_file()
{
	if (!ifstream("lock.txt"))
	{
		ofstream lockFile("lock.txt");
		ifstream statusFile("status.txt");
		if (statusFile.is_open())
		{
			string line;
			while (getline(statusFile, line))
			{
				istringstream iss(line);
				string portStr, modeStr, batteryStr, latStr, lonStr, altStr;

				iss >> portStr;
				iss >> modeStr;
				iss >> batteryStr;
				iss >> latStr;
				iss >> lonStr;
				iss >> altStr;

				int port = stoi(portStr);
				if (m_mapFromPortToID.count(port) > 0)
				{
					DroneInfo& drone = m_drones.at(m_mapFromPortToID.at(port));

					if (modeStr.compare("MISSION") == 0)
						drone.set_status(MOVING);
					else if (modeStr.compare("LAND") == 0)
						drone.set_status(LAND);
					else if (modeStr.compare("LOITER") == 0)
						drone.set_status(IDLE);
					else if (modeStr.compare("GUIDED") == 0)
						drone.set_status(GUIDED);
					else if (modeStr.compare("RTL") == 0)
						drone.set_status(RTL);
					else
						drone.set_status(DISCONNECT);

					drone.set_battery_level(stoi(batteryStr));

					float lat = stof(latStr);
					float lon = stof(lonStr);
					float alt = stof(altStr);

					auto& coord = translate_gps_to_coord(lat, lon);
					drone.set_curr_coord({ coord.at(0), coord.at(1), alt });
				}
			}
			statusFile.close();
			update_drone_info_table();
		}
		else
			cout << "Status file not exist" << endl;

		lockFile.close();
		remove("lock.txt");
	}
	else
	{
		cout << "File locked" << endl;
	}
}

void DroneReporter::start_read_status()
{
	if (timer->isActive())
		timer->stop();
	else
		timer->start(1000);
}
