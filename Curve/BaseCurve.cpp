#include "BaseCurve.h"

#include <algorithm>


CBaseCurve::CBaseCurve()
{
	m_fType = fNone;
	
	m_Center = std::make_shared<CPoint3D>(0., 0., 0.);

	m_Color = std::make_shared<CColor3D>(0., 0., 0.);

	int m_Rudius = 0;

}

CBaseCurve::~CBaseCurve()
{
}

std::shared_ptr<CPoint3D> CBaseCurve::GetCenter()
{
	return m_Center;
}

void CBaseCurve::SetCenter(std::shared_ptr<CPoint3D> InCenter)
{
	m_Center = InCenter;
}

std::shared_ptr<CPoint3D> CBaseCurve::GetPointOnÑueve(float t)
{
	float threshold = 0.001;
	auto rtnPoint = std::make_shared<CPoint3D>(0.0, 0.0, 0.0);

	if ((t < threshold) && (t > 1))
		return rtnPoint;

	float ed = 1.00 / (float)m_VecPoints.size();
	int idx = (int)(t / ed);
	rtnPoint = m_VecPoints[idx];

	return rtnPoint;
}

std::shared_ptr<CPoint3D> CBaseCurve::GetDerivativeCurvePoint(float t)
{
	return std::shared_ptr<CPoint3D>();
}
