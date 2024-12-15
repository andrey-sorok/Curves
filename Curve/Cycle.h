#ifndef __CYCLE_
#define __CYCLE_

#include "BaseCurve.h"
class CCycle : public CBaseCurve
{
private:

public:
	CCycle(std::shared_ptr<CPoint3D> InCenter, std::shared_ptr<CColor3D> InColor, int InRudius);
	~CCycle();

	std::shared_ptr<CPoint3D> GetDerivativeCurvePoint(float t) override;  // 0 <= t <= 1);

};

#endif
