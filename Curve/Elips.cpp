#include "Elips.h"


CElips::CElips(std::shared_ptr<CPoint3D> InCenter, int InA, int InB, std::shared_ptr<CColor3D> InColor)
{
	m_fType = fElipse;

	m_Center = InCenter;
	m_Color = InColor;
	m_A = InA;
	m_B = InB;

}


CElips::~CElips()
{
}

std::shared_ptr<CPoint3D> CElips::GetDerivativeCurvePoint(float t)
{
	//auto point = GetPointOn—ueve(t);

	float ed = 1.00 / (float)m_VecPoints.size();
	int idx = (int)(t / ed);

	float Segments = (float)m_VecPoints.size();
	std::vector<int> AB = GetAB();

	float theta = 2.0f * 3.1415926f * float(idx) / float(Segments);//get the current angle 
	float x = static_cast<float>(AB[0] * -sinf(theta));//calculate the x component 
	float y = static_cast<float>(AB[1] * cosf(theta));//calculate the y component 
	float z = 0;

	auto rtnPoint = std::make_shared<CPoint3D>(x, y, z);


	return rtnPoint;
}