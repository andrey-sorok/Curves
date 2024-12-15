#ifndef __GENERATOR_
#define __GENERATOR_

#include <memory>
#include <vector>

class CCondition;
class CBaseCurve;

class CGenerator
{
private:
	std::shared_ptr<CCondition> m_pCondition;

	std::vector <std::shared_ptr<CBaseCurve>> m_VecCurves;

	std::vector <std::shared_ptr<CBaseCurve>> m_VecCycles;

	int m_TotalSumOfCycles;

	void FigureDataGen(std::shared_ptr<CBaseCurve> InFigure);

	void CycleGen(std::shared_ptr<CBaseCurve> InFigure);
	void ElipseGen(std::shared_ptr<CBaseCurve> InFigure);
	void HelixGen(std::shared_ptr<CBaseCurve> InFigure);

	int GenerateRandomValueInRange(int InMin, int InMax);

public:
	CGenerator();
	~CGenerator();

	void GenFigure();

	std::shared_ptr<CCondition> GetConditions() { return m_pCondition; };
	void SetConditions(std::shared_ptr<CCondition> InConditions) { m_pCondition.reset(InConditions.get()); };

	std::vector <std::shared_ptr<CBaseCurve>> GetVecCurves() { return m_VecCurves; };

	void SetCyclesToVector();

};

#endif
