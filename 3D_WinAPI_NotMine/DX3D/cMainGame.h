#pragma once
class cCubePC;
class cCamera;
class cGrid;
class cCubeMan;
class cLight;
class cGroup;
class cFrame;
class cMtlTex;
class cSkinnedMesh;
class cZealot;


class cMainGame
{
private:
	//vector<ST_PC_VERTEX> m_vecLineVertex;
	//vector<ST_PC_VERTEX > m_vecTriangleVertex;

	cCubePC*	m_pCubePC;
	cCamera*	m_pCamera;
	cGrid*		m_pGrid;

	cCubeMan* m_pCubeMan;

	cLight* m_pLight;

	// >> :
	/*
	LPDIRECT3DTEXTURE9 m_pTexture;	//텍스쳐를 관리할 텍스쳐 객체
	vector<ST_PT_VERTEX> m_vecVertex;
	*/
	// << :
	
	vector<cGroup*> m_vecGroup;
	iMap* m_pMap;

	cFrame* m_pRootFrame;

	LPD3DXMESH m_pMeshTeapot;
	LPD3DXMESH m_pMeshSphere;
	D3DMATERIAL9 m_stMtlTeapot;
	D3DMATERIAL9 m_stMtlSphere;

	LPD3DXMESH m_pObjMesh;
	vector<cMtlTex*> m_vecObjMtlTex;

	vector<ST_SPHERE> m_vecSphere;
	D3DMATERIAL9 m_stMtlNone;
	D3DMATERIAL9 m_stMtlPicked;
	D3DMATERIAL9 m_stMtlPlane;
	vector<ST_PN_VERTEX> m_vecPlaneVertex;
	D3DXVECTOR3 m_vPickedPosition;

	cSkinnedMesh* m_pSkinnedMesh;

	cZealot* m_pHoldZealot;
	cZealot* m_pMoveZealot;
public:
	cMainGame();
	~cMainGame();

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lparam);

	//void Draw_Texture();
	void Setup_Obj();
	void Obj_Render();

	void Load_Surface();

	void Setup_MeshObject();
	void Mesh_Render();

	void Setup_PickingObj();
	void PickingObj_Render();

	void SkinnedMesh_Render();


	void Setup_HeightMap();
	
	void Setup_OBB();
	void OBB_Render();
};

	