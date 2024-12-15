#ifndef __CONDITION_
#define __CONDITION_

#include <string>
#include <vector>
#include <memory>
#include<list>

//#include <i>

class C2DModel;

class CCondition
{
private:

	int m_WINWIDTH;// = 1000;
	int m_WINHEIGHT;// = 950;

	float m_TrX;
	float m_TrY;
	float m_TrZ;

	float m_RotX;
	float m_RotY;
	float m_RotZ;

	float m_Amgel;

	int m_CycleSegments;
	int m_ElipseSegments;
	int m_HelixSegments;

	float m_cX{ 15.00 };
	float m_cY;
	float m_cZ;

	bool m_IsGenerate;

public:
	CCondition();
	~CCondition();

	void SetWINWIDTH(int InWinWidth);
	int GetWINWIDTH() { return m_WINWIDTH; };

	void SetWINHEIGHT(int InWinHeight);
	int GetWINHEIGHT() { return m_WINHEIGHT; };

	std::vector<float> GetTranslateValues();
	std::vector<float> GetRotateValues();

	void SetTranslateValues(const float InTrX, const float InTrY, const float InTrZ);
	void ChangeTranslateValues(const float InTrX, const float InTrY, const float InTrZ);

	void SetRotateValues(const float InRotAngel, const float InRotX, const float InRotY, const float InRotZ);
	void ChangeRotateValues(const float InRotAngel, const float InRotX, const float InRotY, const float InRotZ);

	void SetCycleSegments(int InCycleSegments) { m_CycleSegments = InCycleSegments; };
	int GetCycleSegments() { return m_CycleSegments; };

	void SetElipseSegments(int InElipseSegments) { m_ElipseSegments = InElipseSegments; };
	int GetElipseSegments() { return m_ElipseSegments; };

	void SetHelixSegments(int InCHelixSegments) { m_HelixSegments = InCHelixSegments; };
	int GetHelixSegments() { return m_HelixSegments; };

	std::vector<float> GetCenterXYZ() { return std::initializer_list<float>{ m_cX, m_cY, m_cZ }; };

	bool GetIsGenerate() { return m_IsGenerate; };
	void SetIsGenerate(bool InGenerate) { m_IsGenerate = InGenerate; };
	
};

#endif //__CONDITION_