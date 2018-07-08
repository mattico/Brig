#include "stdafx.h"
#include "AppContainer.h"

using namespace System::Diagnostics;
using namespace System::IO;

AppContainer::AppContainer(String ^executablePath) :
    m_ExecutablePath(executablePath)
{
    auto executableInfo = FileVersionInfo::GetVersionInfo(executablePath);
    Name = String::Format(L"{}Container", Path::GetFileName(executablePath));
    DisplayName = String::Format(L"{} Container",
        String::IsNullOrWhiteSpace(executableInfo->FileName) ?
        Path::GetFileNameWithoutExtension(ExecutablePath) :
        executableInfo->FileName);
    Description = String::Format(L"Container for {}",
        String::IsNullOrWhiteSpace(executableInfo->FileDescription) ?
        Path::GetFileNameWithoutExtension(executablePath) :
        executableInfo->FileDescription);
}

void AppContainer::Run()
{
    auto nativeName = interop::marshal_as<std::wstring>(Name),
        nativeDisplayName = interop::marshal_as<std::wstring>(DisplayName),
        nativeDescription = interop::marshal_as<std::wstring>(Description);

    PSID sid = nullptr;
    ThrowHR(CreateAppContainerProfile(
        nativeName.c_str(),
        nativeDisplayName.c_str(),
        nativeDescription.c_str(),
        nullptr,
        0,
        &sid));

    LPWSTR sidStr = nullptr;
    if (!ConvertSidToStringSidW(sid, &sidStr))
        ThrowLastError();
    m_StringSid = gcnew String(sidStr);
    LocalFree(sidStr);
}
