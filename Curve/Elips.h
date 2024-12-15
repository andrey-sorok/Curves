#ifndef __ELIPS_
#define __ELIPS_

#include "BaseCurve.h"
class CElips : 	public CBaseCurve
{
private:
	int m_A;
	int m_B;

public:
	
	CElips(std::shared_ptr<CPoint3D> InCenter, int InA, int InB, std::shared_ptr<CColor3D> InColor);
	~CElips();

	std::vector<int> GetAB() {	return std::initializer_list<int>{m_A, m_B}; };

	std::shared_ptr<CPoint3D> GetDerivativeCurvePoint(float t) override;
	
};

#endif
