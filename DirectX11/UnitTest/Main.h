#pragma once
#include "Framework.h"
#include "Systems/IExecute.h"

class Main : public IExecute
{
public:
	virtual void Initialize() override;;
	virtual void Ready() override;
	virtual void Destroy() override;
	virtual void PostRender() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
	virtual void Update() override;
private:
	void Push(IExecute* execute);
private:
	vector<IExecute*> executes;
};