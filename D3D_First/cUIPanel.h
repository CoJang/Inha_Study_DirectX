#pragma once
#include "MySprite.h"

class cUIButton : public MySprite
{
public:
	void OnMouseClick() override;
	void OnMouseHover() override;
	void OnMouseLeave() override;
	void OnMouseDrag() override;
};

class cUIPanel : public MySprite
{
public:
	cUIPanel();
	~cUIPanel();

	void SetUp(char* szFullPath, char* szUIName) override;
	void Update(D3DXMATRIXA16* pmatParent) override;

	void OnMouseClick() override;
	void OnMouseHover() override;
	void OnMouseLeave() override;
	void OnMouseDrag() override;
};

