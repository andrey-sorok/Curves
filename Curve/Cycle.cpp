#include "Cycle.h"



CCycle::CCycle(std::shared_ptr<CPoint3D> InCenter, std::shared_ptr<CColor3D> InColor, int InRudius)
{
	m_fType = fCycle;

	m_Center = InCenter;
	m_Color = InColor;
	m_Rudius = InRudius;

}


CCycle::~CCycle()
{
}

std::shared_ptr<CPoint3D> CCycle::GetDerivativeCurvePoint(float t)
{

	//auto point = GetPointOn—ueve(t);

	if (t < 0.001) 
		t = 0.00;
	if (t > 1.001)
		t = 0.99;

	float ed = 1.00 / (float)m_VecPoints.size();
	int idx = (int)(t / ed);
	
	float Segments = (float)m_VecPoints.size();

	float theta = 2.0f * 3.1415926f * float(idx) / float(Segments);//get the current angle 
	float x = static_cast<float>(m_Rudius * -sinf(theta));//calculate the x component 
	float y = static_cast<float>(m_Rudius * cosf(theta));//calculate the y component 
	float z = 0;

	auto rtnPoint = std::make_shared<CPoint3D>(x, y, z);


	return rtnPoint;
}