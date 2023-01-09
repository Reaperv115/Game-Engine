#pragma once
#include "../Utilities/ErrorLogger.h"


class VertexShader
{
public:
	bool Initialize(Microsoft::WRL::ComPtr<ID3D11Device>& device, std::wstring shaderpath, D3D11_INPUT_ELEMENT_DESC* layoutdesc, UINT numElements);
	ID3D11VertexShader* getShader();
	ID3D10Blob* getBuffer();
	ID3D11InputLayout* getLayout();
private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> shader = nullptr;
	Microsoft::WRL::ComPtr<ID3D10Blob> shaderBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
};

class PixelShader
{
public:
	bool Initialize(Microsoft::WRL::ComPtr<ID3D11Device>& device, std::wstring shaderpath);
	ID3D11PixelShader* getShader();
	ID3D10Blob* getBuffer();
private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> shader = nullptr;
	Microsoft::WRL::ComPtr<ID3D10Blob> shaderBuffer = nullptr;
};

