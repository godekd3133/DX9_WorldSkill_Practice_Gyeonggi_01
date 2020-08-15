#pragma once
class Sprite
{
public:
	Sprite();
	~Sprite();

public:
	LPDIRECT3DTEXTURE9 D3DTexture;
	Vector2 Size;

public:
	void SetTexture(LPDIRECT3DTEXTURE9 _D3DTexture, D3DXIMAGE_INFO _D3DIMAGEINFO);
};

