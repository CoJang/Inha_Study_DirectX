#pragma once
class MyGrid
{
private:
	vector<MyVector3> vec_Vertex;
	
	MyMatrix ScaleMat;
	MyMatrix RotateMat;
	MyMatrix TransMat;
	MyMatrix WorldMat;

	float CellSize;
	float MaxSize;
public:
	MyGrid();
	~MyGrid();

	void InitGrid();
	void Update();
	void Render(HDC hdc, MyMatrix & viewport_mat);

	void DrawLine(HDC hdc, MyVector3 & v1, MyVector3 & v2);
};

