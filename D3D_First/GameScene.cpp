#include "stdafx.h"
#include "ObjectSrc/MyGrid.h"
#include "ObjectSrc/PlayerSrc/BoxChar.h"
#include "MyCamera.h"

#include "ObjectFrame.h"
#include "ObjectSrc/Group.h"
#include "objUnit.h"
#include "ObjectSrc/OBJ_Loader.h"
#include "ASE_Loader.h"

#include "GameScene.h"

GameScene::GameScene()
	:Sun(0)
	,FlashLight(1)
	,Torch(2)
{
}


GameScene::~GameScene()
{
	SafeDelete(Camera);
	SafeDelete(Grid);
	SafeDelete(Line);
	SafeDelete(Zemmin2);
	SafeDelete(Bot_Zemmin2);
	SafeDelete(map_surface);
	DEVICEMANAGER->Destroy();
}


void GameScene::WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	static POINT MousePos;
	static POINT OldMousePos;
	
	switch (Msg)
	{
	case WM_LBUTTONDOWN:
		{
			MousePos.x = LOWORD(lParam);
			MousePos.y = HIWORD(lParam);

			Ray ray = CalcPickingRay(MousePos);

			if (IsRayHitInSphere(ray, *sphere))
			{
				sphere->SetMaterialColor(D3DXCOLOR(1, 1, 0, 1));
			}
		}
		break;
	case WM_RBUTTONDOWN:
		{
			MousePos.x = LOWORD(lParam);
			MousePos.y = HIWORD(lParam);
			
			Ray ray = CalcPickingRay(MousePos);
			GridRayHitProcess(ray);
		}
		break;
	case WM_MOUSEMOVE:
		switch(wParam)
		{
		case MK_LBUTTON:
			{
				MousePos.x = LOWORD(lParam);
				MousePos.y = HIWORD(lParam);

				D3DXMATRIXA16 tempX, tempY;
				D3DXVECTOR3 CameraPosition = CamPivot;
				D3DXMatrixRotationX(&tempY, (OldMousePos.y - MousePos.y) * 0.02f);
				D3DXMatrixRotationY(&tempX, (OldMousePos.x - MousePos.x) * -0.01f);
				
				D3DXVec3TransformCoord(&CamPivot, &CameraPosition, &(tempX * tempY));
				break;
			}
		case MK_RBUTTON:
			{
				MousePos.x = LOWORD(lParam);
				MousePos.y = HIWORD(lParam);
				Ray ray = CalcPickingRay(MousePos);
				GridRayHitProcess(ray);
			}
			break;
		default:
			break;
		}
		OldMousePos.x = LOWORD(lParam);
		OldMousePos.y = HIWORD(lParam);
		break;
	case WM_MOUSEWHEEL:
	{
		short Input = HIWORD(wParam);
		Input /= 120;
		//*CamFov += Input * 0.1f;
		CamPivot.y += Input;
		CamPivot.z += Input;
	}
	break;
	default:
		break;
	}
}

void GameScene::InitGameScene()
{
	SetLight();

	Grid = new MyGrid;
	Grid->Init(30, 0.5f);

	Line = new AxisLine;
	Line->Init();

	Zemmin2 = new BoxChar;
	Zemmin2->Init();
	OldCharPos = Zemmin2->GetPos();
	
	{
		bc = new BezierCurve;
		bc->Init();

		map_surface = new objUnit;
		map_surface->Init("Data", "map_surface.obj");
		map_surface->SetScale(0.05f, 0.05f, 0.05f);
		map_surface->SetAngleX(Deg2Rad(-90));
		map_surface->RePositionVertice();

		objMap = new objUnit;
		objMap->Init("Data", "map.obj");
		objMap->SetScale(0.05f, 0.05f, 0.05f);
		objMap->SetAngleX(Deg2Rad(-90));
		objMap->RePositionVertice();

		ASE_Loader loader;
		RootFrame = loader.Load("woman/woman_01_all.ASE");

		sphere = new MySphere;
	}

	Bot_Zemmin2 = new BoxCharBot;
	Bot_Zemmin2->Init();
	Bot_Zemmin2->SetPos(D3DXVECTOR3(5, 4.1f, 5));
	Bot_Zemmin2->SetTexture(TEXT("texture/78075e030cd39335.png"));
	//Bot_Zemmin2->SetDestList(bc->GetVertexList());
	Bot_Zemmin2->SetLook(D3DXVECTOR3(0, 0, 0));
	Bot_Zemmin2->AddDest(D3DXVECTOR3(0, 0, 0));
	Bot_Zemmin2->SetState(AnimState::WALK, 5.0f);

	Camera = new MyCamera;
	Camera->Init();

	CamPos = Camera->GetCamPos();
	CamTarget = Camera->GetCamTarget();
	CamFov = Camera->GetCamFov();
	CamPivot = D3DXVECTOR3(0, 15, -15);
	Camera->SetCamPos(Zemmin2->GetPos() + CamPivot);
}

void GameScene::SetLight()
{
	Sun.SetDiffuseColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	Sun.SetAmbientColor(D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f));
	Sun.SetSpecularColor(D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f));
	//Sun.SetLightState(false);

	FlashLight.SetDiffuseColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	FlashLight.SetAmbientColor(D3DXCOLOR(0.0f, 0.8f, 0.0f, 1.0f));
	FlashLight.SetSpecularColor(D3DXCOLOR(0.0f, 0.8f, 0.0f, 1.0f));
	FlashLight.SetDirection(D3DXVECTOR3(0, 1, 0));
	FlashLight.SetPosition(D3DXVECTOR3(0, 5, 0));
	FlashLight.SetRange(10.0f);
	//FlashLight.SetLightState(false);

	Torch.SetDiffuseColor(D3DXCOLOR(0.0f, 0.0f, 5.0f, 1.0f));
	Torch.SetAmbientColor(D3DXCOLOR(0.0f, 0.0f, 0.3f, 1.0f));
	Torch.SetSpecularColor(D3DXCOLOR(0.0f, 0.0f, 0.3f, 1.0f));
	Torch.SetPosition(D3DXVECTOR3(10, 3, 10));
	Torch.SetRange(5.0f);
	//Torch.SetLightState(false);
}

void GameScene::InputCheck(float delta)
{
	Zemmin2->InputCheck(delta);
	
	if (GetKeyState(VK_ADD) & 0x8000)
	{
		Torch.SetRange(Torch.GetRange() + delta);
	}

	if (GetKeyState(VK_SUBTRACT) & 0x8000)
	{
		Torch.SetRange(Torch.GetRange() - delta);
	}

	if (GetKeyState(VK_NUMPAD2) & 0x8000)
	{
		D3DXVECTOR3 pos = FlashLight.GetPosition();
		pos = D3DXVECTOR3(pos.x, pos.y, pos.z - delta);
		FlashLight.SetPosition(pos);
	}

	if (GetKeyState(VK_NUMPAD8) & 0x8000)
	{
		//D3DXVECTOR3 pos = FlashLight.GetPosition();
		D3DXVECTOR3 dir = FlashLight.GetDirection();
		D3DXMATRIXA16 RotMat;
		D3DXMatrixIdentity(&RotMat);
		D3DXMatrixRotationX(&RotMat, 1.0f);
		D3DXVec3TransformNormal(&dir, &dir, &RotMat);

		//dir = D3DXVECTOR3(dir.x, dir.y, dir.z + 1.0f);
		FlashLight.SetDirection(dir);
	}

	if (GetKeyState(VK_NUMPAD4) & 0x8000)
	{
		D3DXVECTOR3 pos = FlashLight.GetPosition();
		pos = D3DXVECTOR3(pos.x - delta, pos.y, pos.z);
		FlashLight.SetPosition(pos);
	}

	if (GetKeyState(VK_NUMPAD6) & 0x8000)
	{
		D3DXVECTOR3 pos = FlashLight.GetPosition();
		pos = D3DXVECTOR3(pos.x + delta, pos.y, pos.z);
		FlashLight.SetPosition(pos);
	}
}

void GameScene::Update(float delta)
{
	InputCheck(delta);
	
	Sun.LightUpdate(delta);
	FlashLight.LightUpdate(delta);
	Torch.LightUpdate(delta);
	
	Camera->Update(delta);
	Grid->Update(delta);
	Line->Update(delta);
	
	
	Zemmin2->Update(delta);

	Bot_Zemmin2->Update(delta);
	
	Camera->SetCamTarget(Zemmin2->GetPos());
	Camera->SetCamPos(Zemmin2->GetPos() + CamPivot);

	//map_surface->Update(delta);
	
	// When Player's Pos Changed
	if(OldCharPos != Zemmin2->GetPos())
	{
		if(!MapCheck(Zemmin2->GetPos(), map_surface->GetGroups()))
		{
			Zemmin2->SetPos(OldCharPos);
		}
		
		OldCharPos = Zemmin2->GetPos();
	}

	RootFrame->Update(RootFrame->GetKeyFrame(), nullptr);

	
	//static float SunTimer = 0;
	//static float moveDir = -1.0f;
	//SunTimer += delta;
	
	//if(SunTimer > 1.0f)
	{
		D3DXVECTOR3 dir = Sun.GetDirection();

		D3DXMATRIXA16 RotMat;
		D3DXMatrixIdentity(&RotMat);
		D3DXMatrixRotationZ(&RotMat, 1.0f * delta);
		D3DXVec3TransformNormal(&dir, &dir, &RotMat);
	
		Sun.SetDirection(dir);
		//SunTimer = 0;
	}
}

void GameScene::Render(float delta)
{
	if(DEVICE)
	{
		DEVICE->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		DEVICE->BeginScene();

		//map_surface->Render(delta);
		//objMap->Render(delta);
		
		Grid->Draw(delta);
		Line->Draw(delta);
		Zemmin2->Draw(delta);
		
		Bot_Zemmin2->Draw(delta);

		FlashLight.DrawGizmo(delta);
		Torch.DrawGizmo(delta);

		{
			RootFrame->Render();
			sphere->Render(delta);
			bc->Draw(delta);
		}
		

		DEVICE->EndScene();
		DEVICE->Present(NULL, NULL, NULL, NULL);
	}
}

float GameScene::MapCheck(D3DXVECTOR3& charpos, vector<Group*>& terrain)
{
	float U(0), V(0), Dist(0);
	bool IsHit = false;
	D3DXVECTOR3 Anchor(0, 4.1f, 0);

	D3DXVECTOR3 TempPos = charpos + D3DXVECTOR3(0, 5, 0);
	D3DXVECTOR3 TempDir = D3DXVECTOR3(0, -1, 0);
	
	for (int groupNum = 0; groupNum < terrain.size(); groupNum++)
	{
		for (int i = 0; i < terrain[groupNum]->GetVertex().size(); i += 3)
		{
			if(D3DXIntersectTri(&terrain[groupNum]->GetVertex()[i].p,
				&terrain[groupNum]->GetVertex()[i + 1].p,
				&terrain[groupNum]->GetVertex()[i + 2].p,
				&TempPos,
				&TempDir,
				&U, &V, &Dist))
			{
				if (Dist < 16.5f)
				{
					//cout << Dist << endl;
					D3DXVECTOR3 MovedPos = TempPos + (TempDir * Dist);
					Zemmin2->SetPos(MovedPos + Anchor);
					return true;
				}
			}
		}
	}

	return false;
}

Ray GameScene::CalcPickingRay(POINT MPos)
{
	float px = 0.0f; float py = 0.0f; Ray ray;

	D3DVIEWPORT9 vp;
	DEVICE->GetViewport(&vp);
	D3DXMATRIXA16 view, proj, worldmat, viewInverse;
	DEVICE->GetTransform(D3DTS_VIEW, &view);
	DEVICE->GetTransform(D3DTS_PROJECTION, &proj);
	DEVICE->GetTransform(D3DTS_WORLD, &worldmat);
	D3DXMatrixInverse(&viewInverse, 0, &view);

	D3DXVec3Unproject(&ray.Dir, &D3DXVECTOR3(MPos.x, MPos.y, 1.0f), &vp, &proj, &view, &worldmat);

	ray.Pos = D3DXVECTOR3(viewInverse._41, viewInverse._42, viewInverse._43);
	D3DXVec3Normalize(&ray.Dir, &ray.Dir);

	return ray;
}

bool GameScene::IsRayHitInSphere(Ray& ray, MySphere& sphere)
{
	D3DXVECTOR3 v = ray.Pos - sphere.GetPosition();

	float b = 2.0f * D3DXVec3Dot(&ray.Dir, &v);
	float c = D3DXVec3Dot(&v, &v) - sphere.GetRadius() * sphere.GetRadius();
	float discriminant = b * b - 4.0f * c;

	if (discriminant < 0.0f) return false;

	discriminant = sqrtf(discriminant);

	float s0 = (-b + discriminant) / 2.0f;
	float s1 = (-b - discriminant) / 2.0f;

	if (s0 >= 0.0f || s1 >= 0.0f)
		return true;

	return false;
}

void GameScene::GridRayHitProcess(Ray& ray)
{
	vector<PC_VERTEX> & GridVertices = Grid->Getvertices();
	D3DXVECTOR3 HitPos;
	for (int i = 0; i < GridVertices.size(); i += 3)
	{
		float U(0), V(0), Dist(0);

		if (D3DXIntersectTri(&GridVertices[i].p,
			&GridVertices[i + 1].p,
			&GridVertices[i + 2].p,
			&ray.Pos, &ray.Dir, &U, &V, &Dist))
		{
			HitPos = ray.Pos + (ray.Dir * Dist);
			Bot_Zemmin2->FirstPriorityMove(HitPos);
			GridVertices[i].c = D3DCOLOR_XRGB(0, 0, 0);
			GridVertices[i + 1].c = D3DCOLOR_XRGB(0, 0, 0);
			GridVertices[i + 2].c = D3DCOLOR_XRGB(0, 0, 0);
			break;
		}
	}
}

MySphere::MySphere()
	:Position(0, 10, 0),
	Radius(1.f)
{
	ZeroMemory(&Material, sizeof(D3DMATERIAL9));
	
	Material.Ambient = D3DXCOLOR(0.7f, 0.0f, 0.7f, 1.0f);
	Material.Diffuse = D3DXCOLOR(0.7f, 0.0f, 0.7f, 1.0f);
	Material.Specular = D3DXCOLOR(0.7f, 0.0f, 0.7f, 1.0f);
	Material.Power = 1.0f;
	//Material.Emissive = D3DXCOLOR(0.5f, -0.5f, -1.0f, 1.0f);

	D3DXCreateSphere(DEVICE, Radius, 10, 10, &Mesh, NULL);
}

MySphere::~MySphere()
{
	Mesh->Release();
}

void MySphere::Update(float delta)
{
	
}

void MySphere::Render(float delta)
{
	//DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	D3DXMATRIXA16 TransMat;
	D3DXMatrixTranslation(&TransMat, Position.x, Position.y, Position.z);
	DEVICE->SetTransform(D3DTS_WORLD, &TransMat);
	
	DEVICE->SetMaterial(&Material);
	Mesh->DrawSubset(0);
	//DEVICE->SetRenderState(D3DRS_LIGHTING, true);
}

void MySphere::SetMaterialColor(D3DXCOLOR color)
{
	Material.Ambient = color;
	Material.Diffuse = color;
	Material.Specular = color;
}



