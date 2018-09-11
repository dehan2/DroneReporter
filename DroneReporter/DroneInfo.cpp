#include "DroneInfo.h"



DroneInfo::DroneInfo()
{
}


DroneInfo::DroneInfo(const int& ID, const int& port, const int& group)
{
	m_ID = ID;
	m_port = port;
	m_group = group;
}



DroneInfo::~DroneInfo()
{
}



DroneInfo& DroneInfo::operator=(const DroneInfo& rhs)
{
	if (this == &rhs)
		return *this;

	copy(rhs);
	return *this;
}



void DroneInfo::copy(const DroneInfo& rhs)
{
	m_ID = rhs.m_ID;
	m_port = rhs.m_port;
	m_group = rhs.m_group;
	m_status = rhs.m_status;
	m_currCoord = rhs.m_currCoord;
	m_targetCoord = rhs.m_targetCoord;
	m_batteryLevel = rhs.m_batteryLevel;
}