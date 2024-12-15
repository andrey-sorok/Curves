#include "Helix.h"



CHelix::CHelix(std::shared_ptr<CPoint3D> InCenter, int InRadius, int InStep, int InLoop, std::shared_ptr<CColor3D> InColor)
{
	m_fType = fHelix;

	m_Center = InCenter;
	m_Color = InColor;
	m_Step = InStep;
	m_Loop = InLoop;
}


CHelix::~CHelix()
{

}

std::shared_ptr<CPoint3D> CHelix::GetDerivativeCurvePoint(const std::shared_ptr<CPoint3D> InPoint)
{

	return std::shared_ptr<CPoint3D>();
}

std::shared_ptr<CPoint3D> CHelix::GetDerivativeCurvePoint(float t)
{
	auto point = GetPointOn—ueve(t);

	float ed = 1.00 / (float)m_VecPoints.size();
	int idx = (int)(t / ed);

	float Segments = (float)m_VecPoints.size();

	float theta = 2.0f * 3.1415926f * float(idx) / float(Segments);//get the current angle 
	float x = static_cast<float>(m_Rudius * -sinf(theta));//calculate the x component 
	float z = static_cast<float>(m_Rudius * cosf(theta));//calculate the y component 				

	float y = 0.1;

	auto rtnPoint = std::make_shared<CPoint3D>(x, y, z);

	return rtnPoint;
}


//std::shared_ptr<CPoint3D> CHelix::GetPointOnT(float t)
//{
//	return std::shared_ptr<CPoint3D>();
//}
