#pragma once

class Box;

enum AnimState
{
	IDLE,
	WALK,
	RUN,
	JUMP,
};

class BoxChar : public Objects
{
private:
	AnimState   state;
	D3DXVECTOR3 position;
	D3DXVECTOR3 dir;
	float		velocity;
	float		angle;
	
	LPDIRECT3DTEXTURE9 Texture;
	LPCWSTR TexturePath;
	
	std::vector<Box*> Bodies;
public:
	BoxChar();
	~BoxChar();

	void Init();
	void InputCheck(float delta);
	void Draw(float delta);
	
	void Update(float delta);
	void IdleAnim(float delta);
	void WalkAnim(float delta);
	void RunAnim(float delta);

	inline D3DXVECTOR3 & GetPos() { return position; }
	inline void SetPos(D3DXVECTOR3 pos) { position = pos; }

	inline void SetTexture(LPCWSTR path)
	{
		TexturePath = path;
		D3DXCreateTextureFromFile(DEVICE, TexturePath, &Texture);
	}

	void SetLook(D3DXVECTOR3 target);
};

