#pragma once
#include "ObjectSrc/Objects.h"

class ObjectNode : public Objects_PNT
{
protected:
	vector<ObjectNode*> childVector;
	
	D3DXMATRIXA16 ScaleMat;
	D3DXMATRIXA16 RotateMat;
	D3DXMATRIXA16 TransMat;
	
	Synthesize_pass_by_Ref(D3DXMATRIXA16, WorldMat, WorldMatrix);
	 
public:
	ObjectNode();
	virtual ~ObjectNode();

	virtual void AddChild(ObjectNode* pChild);
	virtual void Destroy();

	virtual	void Init();
	virtual void Update(float delta);
	virtual void Draw(float delta);
};

