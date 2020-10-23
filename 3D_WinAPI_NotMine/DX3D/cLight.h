#pragma once
class cCubePC;


class cLight
{
protected:
	D3DXVECTOR3 directionalLight;
	D3DXVECTOR3 vecDir;
	float pointLightRange;


	D3DLIGHT9 stLight;
	D3DLIGHT9 dirLight;
	D3DLIGHT9 spotLight;
	D3DLIGHT9 pointLight;

	/*
	std::vector<ST_PC_VERTEX>	m_vecVertex;
	D3DXVECTOR3					m_Direction;
	D3DXVECTOR3					m_vPosition;
	D3DXMATRIXA16				m_matWorld;
	*/


public:
	cLight();
	~cLight();

	void Setup();
	void Update();
	void Render();

	void DirectionalLight();
	void SpotLight();
	void PointLight();

	void LightCube(float x, float y, float z);

};

