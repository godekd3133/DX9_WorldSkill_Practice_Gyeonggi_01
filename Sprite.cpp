#include "DXUT.h"
#include "Sprite.h"

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
	SAFE_RELEASE(D3DTexture);
}

void Sprite::SetTexture(LPDIRECT3DTEXTURE9 _D3DTexture, D3DXIMAGE_INFO _D3DIMAGEINFO)
{
	this->D3DTexture = _D3DTexture;
	Size = Vector2(_D3DIMAGEINFO.Width, _D3DIMAGEINFO.Height);
}
