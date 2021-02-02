#include "stdafx.h"
#include "DrawVertex.h"

void DrawVertex::Initialize()
{
	//shader = new Shader(L"001_Vertex.fx");
	//shader = new Shader(L"002_Rect.fx");
	//shader = new Shader(L"003_World.fx");
	shader = new Shader(L"004_Quad.fx");

	{
		vertices[0].Position = Vector3(-0.5f, -0.0f, -0.5f);
		vertices[1].Position = Vector3(-0.5f,  0.0f,  0.5f);
		vertices[2].Position = Vector3( 0.5f, -0.0f, -0.5f);

		vertices[3].Position = Vector3(0.5f, -0.0f, -0.5f);
		vertices[4].Position = Vector3(-0.5f, 0.0f, 0.5f);
		vertices[5].Position = Vector3(0.5f,  0.0f, 0.5f);

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(Vertex) * 6;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = indices;

		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));
	}

	{
		vertices[0].Position = Vector3(-0.5f, -0.0f, -0.5f);
		vertices[1].Position = Vector3(-0.5f, 0.0f, 0.5f);
		vertices[2].Position = Vector3(0.5f, -0.0f, -0.5f);
		vertices[3].Position = Vector3(0.5f, -0.0f, -0.5f);
		
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(UINT) * 4;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = indices;

		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));
	}

	color = Color(1, 0, 1, 1);
}

void DrawVertex::Destroy()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);
	SafeRelease(indexBuffer);
}

void DrawVertex::Update()
{
	ImGui::ColorEdit3("Color", (float*)&color);
	shader->AsVector("Color")->SetFloatVector(color);
	
	Matrix world;
	D3DXMatrixIdentity(&world);
	static Vector3 position(0, 0, 0);
	
	//if (Keyboard::Get()->Press(VK_LEFT))
	//{
	//	position.x -= 1.0f * Time::Delta();
	//}
	//else if (Keyboard::Get()->Press(VK_RIGHT))
	//{
	//	position.x += 1.0f * Time::Delta();
	//}
	
	D3DXMatrixTranslation(&world, position.x, position.y, position.z);
	shader->AsMatrix("World")->SetMatrix(world);

	Matrix view = Context::Get()->View();
	shader->AsMatrix("View")->SetMatrix(view);

	Matrix projection = Context::Get()->Projection();
	shader->AsMatrix("Projection")->SetMatrix(projection);

	
}

void DrawVertex::Render()
{
	// АЃАн
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// 0202
	static bool b = false;
	ImGui::Checkbox("Wireframe", &b);
	shader->DrawIndexed(0, (b ? 0 : 1), 6);

	
	static Vector3 position(0, 0, 0);
	Matrix world;
	D3DXMatrixTranslation(&world, position.x, position.y, position.z);
	shader->AsVector("Color")->SetFloatVector(color);
	shader->AsMatrix("World")->SetMatrix(world);
	shader->Draw(0, 0, 6);
}
