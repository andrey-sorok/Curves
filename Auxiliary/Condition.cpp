#include "Condition.h"

CCondition::CCondition()
{
	m_WINWIDTH = 0;
	m_WINHEIGHT = 0;

	m_TrX = 10.0f;
	m_TrY = 0.0f;
	m_TrZ = -60.0f;

	m_RotX = 0.0;
	m_RotY = 0.0;
	m_RotZ = 0.0;

	m_Amgel = 0.0;

	m_CycleSegments = 50;
	m_ElipseSegments = 50;
	m_HelixSegments = 100;
	
	m_cX = 15.00;
	m_cY = 5.00;
	m_cZ = -40.00;

	m_IsGenerate = false;

}

CCondition::~CCondition()
{

}

void CCondition::SetWINWIDTH(int InWinWidth)
{
	m_WINWIDTH = InWinWidth;
}

void CCondition::SetWINHEIGHT(int InWinHeight)
{
	m_WINHEIGHT = InWinHeight;
}

std::vector<float> CCondition::GetTranslateValues()
{
	std::vector<float> rtn{ m_TrX, m_TrY, m_TrZ };
	
	return rtn;
}

std::vector<float> CCondition::GetRotateValues()
{
	std::vector<float> rtn{m_Amgel, m_RotX, m_RotY, m_RotZ };

	return rtn;
}

void CCondition::SetTranslateValues(const float InTrX, const float InTrY, const float InTrZ)
{
	m_TrX = InTrX;
	m_TrY = InTrY;
	m_TrZ = InTrZ;
}

void CCondition::ChangeTranslateValues(const float InTrX, const float InTrY, const float InTrZ)
{
	m_TrX += InTrX;
	m_TrY += InTrY;
	m_TrZ += InTrZ;

}

void CCondition::SetRotateValues(const float InRotAngel, const float InRotX, const float InRotY, const float InRotZ)
{
	m_Amgel = InRotAngel;

	m_RotX = InRotX;
	m_RotY = InRotY;
	m_RotZ = InRotZ;
}

void CCondition::ChangeRotateValues(const float InRotAngel, const float InRotX, const float InRotY, const float InRotZ)
{
	m_Amgel += InRotAngel;

	m_RotX = InRotX;
	m_RotY = InRotY;
	m_RotZ = InRotZ;
}