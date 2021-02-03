#pragma once
#include "Systems/IExecute.h"

class Camera : public IExecute
{
public:
	virtual void Initialize() override;
	virtual void Ready() override {};
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void PreRender() override {};
	virtual void Render() override;
	virtual void PostRender() override {};
	virtual void ResizeScreen() override {};

	Camera();
	~Camera();
	
	void Position(Vector3 & vec);
	void Position(float x, float y, float z);
	void Position(OUT Vector3 * vec);
	void GetMatrix(OUT Matrix* matrix);
	void Move();
	void View();
private:
	D3DXVECTOR3 right;
	D3DXVECTOR3 forward;
	D3DXVECTOR3 up;
	D3DXVECTOR3 position;

	D3DXMATRIXA16 matView;
};

