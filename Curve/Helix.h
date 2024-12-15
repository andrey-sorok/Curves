#ifndef __HELIX_
#define __HELIX_

#include "BaseCurve.h"

class CHelix : public CBaseCurve
{
private:
	int m_Step;
	int m_Loop;

public:
	CHelix(std::shared_ptr<CPoint3D> InCenter, int InRadius, int InStep, int InLoop, std::shared_ptr<CColor3D> InColor);
	~CHelix();

	int GetStep() { return m_Step; };
	void SetStep(int InStep) { m_Step = InStep; };
	
	int GetLoop() { return m_Loop; };
	void SetLoop(int InLoop) { m_Loop = m_Loop; };

	std::shared_ptr<CPoint3D> GetDerivativeCurvePoint(const std::shared_ptr<CPoint3D> InPoint);

	std::shared_ptr<CPoint3D> GetDerivativeCurvePoint(float t)override;
};

#endif
