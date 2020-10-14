#include "stdafx.h"
#include "ObjectNode.h"


ObjectNode::ObjectNode()
{
	D3DXMatrixIdentity(&ScaleMat);
	D3DXMatrixIdentity(&RotateMat);
	D3DXMatrixIdentity(&TransMat);
	D3DXMatrixIdentity(&WorldMat);
}


ObjectNode::~ObjectNode()
{
}

void ObjectNode::AddChild(ObjectNode* pChild)
{
	
}

void ObjectNode::Destroy()
{
}

void ObjectNode::Init()
{
}

void ObjectNode::Update(float delta)
{
}

void ObjectNode::Draw(float delta)
{
}
