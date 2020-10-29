#pragma once

class cFont
{
private:
	string m_sText;
	LPD3DXFONT m_pFont;
	
	RECT m_rRect;
	D3DCOLOR m_dColor;
	DWORD m_dFormat;
public:
	cFont();
	~cFont();

	void Setup(string text, FontType type);
	void Update();
	void Render();

	void ChangeFont(FontType type);
	void SetFormat(DWORD format) { m_dFormat = format; }

	virtual void SetText(string text) { m_sText = text; }
	virtual void SetText(char* text) { m_sText = text; }

	virtual RECT GetDrawArea() { return m_rRect; }
	virtual void SetColor(D3DCOLOR color) { m_dColor = color; }
	virtual void SetDrawArea(RECT rc) { m_rRect = rc; }
	virtual void SetDrawArea(int left, int top, int right, int bottom)
	{
		SetRect(&m_rRect, left, top, right, bottom);
	}
};

