#include "Generator.h"

#include "Condition.h"

#include "BaseCurve.h"
#include "Cycle.h"
#include "Elips.h"
#include "Helix.h"

#include <algorithm>
#include <iostream>


CGenerator::CGenerator()
{
	m_TotalSumOfCycles = 0;
}


CGenerator::~CGenerator()
{
}

int CGenerator::GenerateRandomValueInRange(int InMin, int InMax)
{

	// ѕолучить случайное число - формула
	int num = rand() % (InMax - InMin) + InMin;

	return num;
}

void CGenerator::GenFigure()
{
	int allCurves = GenerateRandomValueInRange(8, 15);
	for (int i = 0; i < allCurves; ++i)
	{
		int curCurves = GenerateRandomValueInRange(0, 4);
		if (curCurves == 0)
			curCurves = 1;
		if (curCurves == 4)
			curCurves = 3;

		switch (curCurves)
		{
			case(1):
			{

				//for (int iCycle = 0; iCycle < NumCycles; iCycle++)
				{
					float x = GenerateRandomValueInRange(-50, 50);
					float y = GenerateRandomValueInRange(-50, 50);

					std::shared_ptr<CPoint3D> InCenter = std::make_shared<CPoint3D>(x, y, static_cast<float>(m_pCondition->GetCenterXYZ()[2]));

					auto R = GenerateRandomValueInRange(1, 254);
					auto G = GenerateRandomValueInRange(1, 10);
					auto B = GenerateRandomValueInRange(1, 254);
					auto InColor = std::make_shared<CColor3D>(R, G, B);

					int InRudius = GenerateRandomValueInRange(1, 10);

					auto pCycle = std::make_shared<CCycle>(InCenter, InColor, InRudius);

					FigureDataGen(pCycle);
				}
				break;
			}
			case(2):
			{
				//for (int iElips = 0; iElips < NumElips; iElips++)
				{

					float x = GenerateRandomValueInRange(-50, 50);
					float y = GenerateRandomValueInRange(-50, 50);

					std::shared_ptr<CPoint3D> InCenter = std::make_shared<CPoint3D>(x, y, static_cast<float>(m_pCondition->GetCenterXYZ()[2]));

					auto R = GenerateRandomValueInRange(100, 254);
					auto G = GenerateRandomValueInRange(1, 10);
					auto B = GenerateRandomValueInRange(100, 254);
					auto InColor = std::make_shared<CColor3D>(R, G, B);


					int prA = GenerateRandomValueInRange(3, 5);
					int prB = GenerateRandomValueInRange(1, 3);

					auto pElips = std::make_shared<CElips>(InCenter, prA, prB, InColor);


					FigureDataGen(pElips);

				}
			}
			break;
		
			case(3):
			{
				//for (int iHelix = 0; iHelix < NumHelix; iHelix++)
				{
					float x = GenerateRandomValueInRange(-50, 50);
					float z = GenerateRandomValueInRange(-50, 50);
					float y = GenerateRandomValueInRange(-50, 50);

					auto InLoop = GenerateRandomValueInRange(1, 4);
					float InStep = static_cast<float>(GenerateRandomValueInRange(1, 4) / 10.00);

					std::shared_ptr<CPoint3D> InCenter = std::make_shared<CPoint3D>(x, y, z);

					auto R = GenerateRandomValueInRange(220, 255);
					auto G = GenerateRandomValueInRange(220, 255);
					auto B = GenerateRandomValueInRange(220, 255);
					auto InColor = std::make_shared<CColor3D>(R, G, B);

					int InRadius = GenerateRandomValueInRange(1, 10);

					auto pHelix = std::make_shared<CHelix>(InCenter, InRadius, InStep, InLoop, InColor);
					pHelix->SetRadius(InRadius);

					FigureDataGen(pHelix);

				}
			}
		}
	}

}

void CGenerator::SetCyclesToVector()
{
	if (m_VecCurves.size() > 0)
	{
		for (auto & it : m_VecCurves)
		{
			if (it->GetType() == fCycle)
			{
				m_VecCycles.emplace_back(it);
			}
		}
	}

	std::sort(m_VecCycles.begin(), m_VecCycles.end(), [&](const auto& lhs, const auto& rhs)
	{
		m_TotalSumOfCycles += lhs->GetRadius();
		m_TotalSumOfCycles += rhs->GetRadius();
		return lhs->GetRadius() < rhs->GetRadius(); // по возрастаию
	});

	std::cout << "All sum Radius:" <<m_TotalSumOfCycles << std::endl;
}

void CGenerator::FigureDataGen(std::shared_ptr<CBaseCurve> InFigure)
{
	auto FigType = InFigure->GetType();
	switch (FigType)
	{
		case fNone:
			break;
		case fCycle:
		{
			CycleGen(InFigure);

			break;
		}

		case fElipse:
		{
			ElipseGen(InFigure);
			break;
		}

		case fHelix:
		{
			HelixGen(InFigure);

			break;
		}

		default:
			break;
	}

}

void CGenerator::CycleGen(std::shared_ptr<CBaseCurve> InFigure)
{
	float Radius =  (InFigure.get())->GetRadius();
	
	float Segments = m_pCondition->GetCycleSegments();
	//std::vector<float> vecCenter = m_pCondition->GetCenterXYZ();
	auto center = (InFigure.get())->GetCenter();
	int ii = 0;

	auto& vecPoints = (InFigure.get())->GetVecPoints();
	while (ii < Segments)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(Segments);//get the current angle 
		float x = static_cast<float>(Radius * cosf(theta));//calculate the x component 
		float y = static_cast<float>(Radius * sinf(theta));//calculate the y component 
		vecPoints.emplace_back(std::make_shared<CPoint3D>(x + center->x, y + center->y, center->z));
		
		ii++;

	}
	
	m_VecCurves.emplace_back(InFigure);
}

void CGenerator::ElipseGen(std::shared_ptr<CBaseCurve> InFigure)
{
	std::vector<int> AB = dynamic_cast<CElips*>(InFigure.get())->GetAB();

	float Segments = m_pCondition->GetElipseSegments();

	auto center = (InFigure.get())->GetCenter();
	int ii = 0;
	while (ii < Segments)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(Segments);//get the current angle 
		float x = static_cast<float>(AB[0] * cosf(theta));//calculate the x component 
		float y = static_cast<float>(AB[1] * sinf(theta));//calculate the y component 
		(InFigure.get())->GetVecPoints().emplace_back(std::make_shared<CPoint3D>(x + center->x, y + center->y, center->z));

		ii++;

	}

	m_VecCurves.emplace_back(InFigure);
}

void CGenerator::HelixGen(std::shared_ptr<CBaseCurve> InFigure)
{
	float Radius = dynamic_cast<CHelix*>(InFigure.get())->GetRadius();
	float Segments = m_pCondition->GetHelixSegments();

	auto center = (InFigure.get())->GetCenter();
	int ii = 0;
	int Loop = dynamic_cast<CHelix*>(InFigure.get())->GetLoop();
	
	float cY = 0.00;// vecCenter[1];

	for (int i = 0; i < Loop; ++i)
	{

		while (ii < Segments)
		{
			float theta = 2.0f * 3.1415926f * float(ii) / float(Segments);//get the current angle 
			float x = static_cast<float>(Radius * cosf(theta));//calculate the x component 
			float z = static_cast<float>(Radius * sinf(theta));//calculate the y component 				
			(InFigure.get())->GetVecPoints().emplace_back(std::make_shared<CPoint3D>(x + center->x, cY, z + center->z));
				
			cY += 0.1;

			ii++;
		}
		ii = 0;
	}

	m_VecCurves.emplace_back(InFigure);
}
