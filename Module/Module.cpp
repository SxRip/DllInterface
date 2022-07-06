#include "Module.hpp"

void SafeFreeLibrary(HMODULE& hModule)
{
	if (hModule != nullptr)
	{
		FreeLibrary(hModule);

		hModule = nullptr;
	}
}

DLL::DLL() :
	_modules{}
{}

DLL::~DLL()
{
	clear();
}

void DLL::pop_front() noexcept
{
	SafeFreeLibrary(_modules.begin()->second);
	_modules.erase(_modules.begin()->first);
}

void DLL::pop_back() noexcept
{
	_modules.erase(--(_modules.end()));
}

inline void DLL::clear() noexcept
{
	for (auto& elem : _modules)
		SafeFreeLibrary(elem.second);
	_modules.clear();
}

const size_t DLL::size() const noexcept
{
	return _modules.size();
}

void DLL::push_back(const char* dllName, HMODULE& dllInfo) noexcept
{
	_modules.emplace(dllName, dllInfo);
}

bool DLL::push_back(const char* dllName) noexcept
{
	HMODULE hDLL = LoadLibrary(dllName);

	if (!hDLL)
		return false;

	_modules.emplace(dllName, hDLL);
	return true;
}

void DLL::push_back(HMODULE& dllInfo) noexcept
{
	char cdllPath[MAX_PATH]{};
	GetModuleFileName(dllInfo, cdllPath, sizeof(cdllPath));

	std::string dllPath = cdllPath;
	dllPath = dllPath.substr(dllPath.find_last_of("\\") + 1);

	_modules.emplace(dllPath.c_str(), dllInfo);
}