#pragma once
#include "../Utilities/ErrorLogger.h"


class AdapterData
{
public:
	AdapterData(IDXGIAdapter* pAdapter);
	IDXGIAdapter* pAdapter = nullptr;
	DXGI_ADAPTER_DESC adapterdescription;
};

class ReadAdapter
{
public:
	static std::vector<AdapterData> getAdapters();
private:
	static std::vector<AdapterData> adapters;
};

