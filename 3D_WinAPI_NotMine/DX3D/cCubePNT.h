#pragma once
class cCubePNT
{
protected:
	std::vector<ST_PNT_VERTEX> m_vecVertex;

public:
	cCubePNT();
	virtual ~cCubePNT(void);
	virtual void Setup();
	virtual void Update();
	virtual void Render();


};

