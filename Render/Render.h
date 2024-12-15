#ifndef __OPENGLRENDER_
#define __OPENGLRENDER_

#include <memory>

class CGenerator;

class Render
{
private:
	std::shared_ptr<CGenerator> m_pGenerator;

public:
	Render();
	~Render();

	std::shared_ptr<CGenerator> GetGenerator() { return m_pGenerator; };
	void SetGenerator(std::shared_ptr<CGenerator> InGenerator) { m_pGenerator.reset(InGenerator.get()); };

	void InitSceneColor(unsigned int inR, unsigned int inG, unsigned int inB);
	void InitWindowParams(const int window_width, const int window_height, const int WinPositionWidth, const int WinPositionHeight);

	void OutPointsAnDerivativesPI4();

	void InitGL();

	void Draw();
};


#endif
