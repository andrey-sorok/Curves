#ifndef __BASECURVE_
#define __BASECURVE_

#include <Point3D.h>
#include <Color3D.h>

#include <vector>
#include <memory>

enum FType{fNone, fCycle, fElipse, fHelix};

class CBaseCurve
{

protected:

	FType m_fType;

	std::shared_ptr<CPoint3D> m_Center;

	std::shared_ptr<CColor3D> m_Color;

	int m_Rudius;

	int m_Segments{ 0 };
	
	std::vector<std::shared_ptr<CPoint3D>> m_VecPoints;


public:
	CBaseCurve();

	virtual ~CBaseCurve();

	std::shared_ptr<CPoint3D> GetCenter();
	void SetCenter(std::shared_ptr<CPoint3D> InCenter);

	std::shared_ptr<CColor3D> GetSeColor() { return m_Color; };
	void SetColor(std::shared_ptr<CColor3D> InColor) { m_Color = InColor; };

	int GetRadius() { return m_Rudius; };
	void SetRadius(int InRadius) { m_Rudius = InRadius; };

	int GetSegments() { return m_Segments; };
	void SetSegments(int InSegments) { m_Segments = InSegments; };

	FType GetType() {return m_fType; };

	std::vector<std::shared_ptr<CPoint3D>>& GetVecPoints() { return m_VecPoints; };

	std::shared_ptr<CPoint3D> GetPointOn—ueve(float t); // 0 <= t <= 1
	virtual std::shared_ptr<CPoint3D> GetDerivativeCurvePoint(float t); // 0 <= t <= 1);
};

#endif
