#pragma once

#include <array>
#include "constForDroneReporter.h"

using namespace std;

class DroneInfo
{
private:
	int m_ID;
	int m_port;
	int m_group;
	DRONE_STATUS m_status = DISCONNECT;
	array<float, 3> m_currCoord;
	array<float, 3> m_targetCoord;
	float m_batteryLevel;

public:
	DroneInfo();
	DroneInfo(const int& ID, const int& port, const int& group);
	DroneInfo(const DroneInfo& rhs) { copy(rhs); }
	~DroneInfo();

	DroneInfo& operator=(const DroneInfo& rhs);

	void copy(const DroneInfo& rhs);
			

	inline int get_ID() const { return m_ID; }
	inline int get_port() const { return m_port; }
	inline int get_group() const { return m_group; }
	inline DRONE_STATUS get_status() const { return m_status; }
	inline array<float, 3> get_curr_coord() const { return m_currCoord; }
	inline array<float, 3> get_target_coord() const { return m_targetCoord; }
	inline float get_battery_level() const { return m_batteryLevel; }

	inline void set_ID(const int& ID) { m_ID = ID; }
	inline void set_port(const int& port) { m_port = port; }
	inline void set_group(const int& group) { m_group = group; }
	inline void set_status(const DRONE_STATUS& status) { m_status = status; }
	inline void set_curr_coord(const array<float, 3>& coord) { m_currCoord = coord; }
	inline void set_target_coord(const array<float, 3>& coord) { m_targetCoord = coord; }
	inline void set_battery_level(const float& batteryLevel) { m_batteryLevel = batteryLevel; }
};

