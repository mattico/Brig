#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <UserEnv.h>
#include <sddl.h>
#include <msclr/marshal_cppstd.h>

#include <string>
#include <vector>

#using "System.dll"

using namespace System;
using namespace msclr;


inline void ThrowHR(HRESULT hr)
{
    if (FAILED(hr))
        System::Runtime::InteropServices::Marshal::ThrowExceptionForHR(hr);
}

inline void ThrowLastError()
{
    System::Runtime::InteropServices::Marshal::ThrowExceptionForHR(HRESULT_FROM_WIN32(GetLastError()));
}