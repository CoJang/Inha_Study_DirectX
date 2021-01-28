#include "framework.h"
#include "VertexStruct.h"
#include "ObjLoader.h"

#include "Box.h"

cBox::cBox()
{
}

cBox::~cBox()
{
}

void cBox::Setup(const char* folder, const char* file)
{
	cObjObject::Setup(folder, file);
	SetPosition(D3DXVECTOR3(2, 0, 3));
}

void cBox::RenderShadow()
{
	D3DLIGHT9  light;
	g_pDevice->GetLight(0, &light);
	D3DXVECTOR4 vDir(light.Direction, 0);
	//vDir = -vDir;

	// 그림자 행렬 만들기.
	D3DXPLANE  plane(0, -1, 0, 0);
	D3DXMATRIX   mShadow;
	D3DXMatrixShadow(&mShadow, &vDir, &plane);


	//// 그림자 반투명처리.
	g_pDevice->SetTexture(0, NULL);
	g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_CONSTANT);
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_CONSTANT);
	g_pDevice->SetTextureStageState(0, D3DTSS_CONSTANT, D3DXCOLOR(0, 0, 0, 0.5f));

	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	////  스텐실 테스트 옵션 설정. : '0' 인곳에 그린후, 값을 증가 시켜, 중복렌더링을 방지.
	g_pDevice->SetRenderState(D3DRS_STENCILENABLE, true);
	g_pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	g_pDevice->SetRenderState(D3DRS_STENCILREF, 0x00);				//기본값은 0x00
	g_pDevice->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);		//기본값.
	g_pDevice->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);	//기본값.
	g_pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	g_pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	g_pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);   //성공시, 버퍼의 값을 증가 


	// 기타 옵션.
	g_pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	g_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	g_pDevice->SetRenderState(D3DRS_CULLMODE, false);


	// 그리기..
	D3DXMATRIX matId;
	D3DXMatrixIdentity(&matId);
	D3DXMATRIX _mTM = (D3DXMATRIX)m_matWorld * mShadow;
	//D3DXMATRIXA16 _mTM = matId * mShadow;
	//D3DXMATRIXA16 originWorld = m_matWorld;
	
	g_pDevice->SetTransform(D3DTS_WORLD, &_mTM);
	g_pDevice->SetFVF(PNT_VERTEX::FVF);
	for (cGroup* group : m_vecGroup)
	{
		g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
									group->GetVertices().size() / 3,
									&group->GetVertices()[0],
									sizeof(PNT_VERTEX));
	}
	//cObjObject::Render();
	
	// 옵션 복구.
	g_pDevice->SetRenderState(D3DRS_CULLMODE, true);
	g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	g_pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	g_pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

void cBox::Render()
{
	RenderShadow();
	cObjObject::Render();
}
