#pragma once

class Box;

class BoxChar : public Objects
{
private:
	D3DXVECTOR3 position;
	D3DXVECTOR3 dir;
	float		velocity;
	float		angle;

	std::vector<Box*> Bodies;
	std::vector<D3DXVECTOR3> BodyPivots;
	std::vector<float> AnimAngle;
public:
	BoxChar();
	~BoxChar();

	void Init();
	void Update(float delta);
	void Draw(float delta);

	inline D3DXVECTOR3 & GetPos() { return position; }

};

