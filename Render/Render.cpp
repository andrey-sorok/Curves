#include "Render.h"

#include <gl\freeglut.h>

#include <vector>

#include "Generator.h"
#include "Condition.h"

#include "BaseCurve.h"
#include "Cycle.h"
#include "Elips.h"
#include "Helix.h"

#include <iostream>

Render::Render()
{
}


Render::~Render()
{
}


void Render::InitSceneColor(unsigned int inR, unsigned int inG, unsigned int inB)
{
	float fR = inR / 255.0F;
	float fG = inG / 255.0F;
	float fB = inB / 255.0F;

	glClearColor(fR, fG, fB, 0.0);
}

void Render::InitWindowParams(const int window_width, const int window_height, const int WinPositionWidth, const int WinPositionHeight)
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);//glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(WinPositionWidth, WinPositionHeight);
	glutInitWindowSize(window_width, window_height);
}

void Render::OutPointsAnDerivativesPI4()
{
	auto pCurves = m_pGenerator->GetVecCurves();
	for (int i = 0; i < pCurves.size(); ++i)
	{
		auto pType = pCurves[i]->GetType();
		switch (pType)
		{
			case fNone:
			{

			}
				break;
			case fCycle:
			{
				//auto pCycle = dynamic_cast<CCycle*>(pCurves[i].get());
				auto pPoints = pCurves[i]->GetVecPoints();// pCycle->GetVecPoints();

				for (int i = 0; i < pPoints.size() / 4; ++i)
				{
					auto point = pPoints[i];
					std::cout << "Point:" << point.get()->x << ", " << point.get()->y << ", " << point.get()->z << ", " << std::endl;
				}
			
				float ed = 1.00 / (float)pPoints.size();
				float cur = 0.0;
				for (int j = 0; j < pPoints.size()/4; ++j)
				{
					auto dPoint = dynamic_cast<CCycle*>(pCurves[i].get())->GetDerivativeCurvePoint(cur);
					cur += ed;
					
					std::cout << "Derivative:" << abs(dPoint.get()->x) << ", " << abs(dPoint.get()->y) << ", " << abs(dPoint.get()->z) << std::endl;
				}

			}
			break;
			case fElipse:
			{
				auto pPoints = pCurves[i]->GetVecPoints();// pCycle->GetVecPoints();

				for (int i = 0; i < pPoints.size() / 4; ++i)
				{
					auto point = pPoints[i];
					std::cout << "Point:" << point.get()->x << ", " << point.get()->y << ", " << point.get()->z << ", " << std::endl;
				}

				float ed = 1.00 / (float)pPoints.size();
				float cur = 0.0;
				for (int j = 0; j < pPoints.size()/ 4; ++j)
				{
					auto dPoint = dynamic_cast<CElips*>(pCurves[i].get())->GetDerivativeCurvePoint(cur);
					cur += ed;

					std::cout << "Derivative:" << abs(dPoint.get()->x) << ", " << abs(dPoint.get()->y) << ", " << abs(dPoint.get()->z) << std::endl;
				}

			}
				break;
			case fHelix:
			{
				auto pPoints = pCurves[i]->GetVecPoints();// pCycle->GetVecPoints();
				auto pLoops =  dynamic_cast<CHelix*>(pCurves[i].get())->GetLoop();
				for (int i = 0; i < ((pPoints.size() / pLoops)/ 4); ++i)
				{
					auto point = pPoints[i];
					std::cout << "Point:" << point.get()->x << ", " << point.get()->y << ", " << point.get()->z << ", " << std::endl;
				}
				
				float ed = 1.00 / (float)pPoints.size();
				float cur = 0.0;
				for (int j = 0; j < ((pPoints.size() / pLoops) / 4); ++j)
				{
					auto dPoint = dynamic_cast<CHelix*>(pCurves[i].get())->GetDerivativeCurvePoint(cur);
					cur += ed;

					std::cout << "Derivative:" << abs(dPoint.get()->x) << ", " << abs(dPoint.get()->y) << ", " << abs(dPoint.get()->z) << std::endl;
				}

			}
				break;
			default:
			{

			}
				break;
		}
	}

}

void Render::InitGL()
{
	
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque

	glClearColor(static_cast<GLclampf>(0.0), static_cast<GLclampf>(0.2), static_cast<GLclampf>(0.5), static_cast<GLclampf>(0.00));
	glClearDepth(1.0f);                   // Set background depth to farthest
	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
	glShadeModel(GL_SMOOTH);   // Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

void Render::Draw()
{
	auto pCondition = m_pGenerator->GetConditions();
	if (!pCondition->GetIsGenerate())
	{
		m_pGenerator->GenFigure();
		pCondition->SetIsGenerate(true);

		m_pGenerator->SetCyclesToVector();

		OutPointsAnDerivativesPI4();
	}

	auto VecCurves = m_pGenerator->GetVecCurves();

	for (auto& iCurve : VecCurves)
	{
		auto cType = iCurve->GetType();
		switch (cType)
		{
			case fCycle:
			{
				auto cemter = iCurve->GetCenter();
				auto radius = iCurve->GetRadius();
				auto color = iCurve->GetSeColor();

				auto cXYZ = pCondition->GetCenterXYZ();

				auto vecPoints = dynamic_cast<CCycle*>(iCurve.get())->GetVecPoints();
				//auto color = iCurve->GetSeColor();
				glColor3f(color->R / 255, color->G / 255, color->B / 255);
				//glColor3f(0.9, 0.00, 0.00);

				glBegin(GL_LINES);
				{
					for (int iPoint = 0; iPoint < vecPoints.size()-1; ++iPoint)
					{
						glVertex3f(vecPoints[iPoint]->x, vecPoints[iPoint]->y, vecPoints[iPoint]->z);//first vertex 
						glVertex3f(vecPoints[iPoint+1]->x, vecPoints[iPoint+1]->y, vecPoints[iPoint+1]->z);//first vertex 
					}

					glVertex3f(vecPoints[vecPoints.size()-1]->x, vecPoints[vecPoints.size()-1]->y, vecPoints[vecPoints.size()-1]->z);//first vertex 
					glVertex3f(vecPoints[0]->x, vecPoints[0]->y, vecPoints[0]->z);//first vertex 
				}
				glEnd();

				break;
			}

			case fElipse:
			{
				auto cemter = iCurve->GetCenter();
				auto radius = iCurve->GetRadius();
				auto color = iCurve->GetSeColor();

				auto cXYZ = pCondition->GetCenterXYZ();

				auto vecPoints = dynamic_cast<CElips*>(iCurve.get())->GetVecPoints();

				float R = static_cast<float>(color->R / 255.00);
				float G = static_cast<float>(color->G / 255.00);
				float B = static_cast<float>(color->B / 255.00);
				glColor3f(R, G, B);
				//glColor3f(0.9, 0.00, 0.00);

				glBegin(GL_LINES);
				{

					for (int iPoint = 0; iPoint < vecPoints.size() - 1; ++iPoint)
					{
						glVertex3f(vecPoints[iPoint]->x, vecPoints[iPoint]->y, vecPoints[iPoint]->z);//first vertex 
						glVertex3f(vecPoints[iPoint + 1]->x, vecPoints[iPoint + 1]->y, vecPoints[iPoint + 1]->z);//first vertex 
					}

					glVertex3f(vecPoints[vecPoints.size() - 1]->x, vecPoints[vecPoints.size() - 1]->y, vecPoints[vecPoints.size() - 1]->z);//first vertex 
					glVertex3f(vecPoints[0]->x, vecPoints[0]->y, vecPoints[0]->z);//first vertex 
					//for (auto iPoint : vecPoints)
					//{
					//	glVertex3f(iPoint->x, iPoint->y, iPoint->z);//first vertex 

					//}
				}

				glEnd();
				break;
			}

			case fHelix:
			{
				auto cemter = iCurve->GetCenter();
				auto radius = iCurve->GetRadius();
				auto color = iCurve->GetSeColor();

				auto cXYZ = pCondition->GetCenterXYZ();

				auto vecPoints = dynamic_cast<CHelix*>(iCurve.get())->GetVecPoints();

				float R = static_cast<float>(color->R / 255.00);
				float G = static_cast<float>(color->G / 255.00);
				float B = static_cast<float>(color->B / 255.00);
				glColor3f(R, G, B);
				//glColor3f(0.9, 0.00, 0.00);

				glBegin(GL_LINES);
				{
					for (int iPoint = 0; iPoint < vecPoints.size() - 1; ++iPoint)
					{
						glVertex3f(vecPoints[iPoint]->x, vecPoints[iPoint]->y, vecPoints[iPoint]->z);//first vertex 
						glVertex3f(vecPoints[iPoint + 1]->x, vecPoints[iPoint + 1]->y, vecPoints[iPoint + 1]->z);//first vertex 
					}

				}

				glEnd();
				break;

				break;
			}
			default:
				break;
		}

		
	}
}
