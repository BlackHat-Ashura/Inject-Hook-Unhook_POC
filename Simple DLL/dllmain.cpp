#include "pch.h"
#include "Windows.h"
#include <stdio.h>


void HookFunc() {
    printf("Hooked!!\n");
}

void InjectAndHook() {
    printf("Injected!!\n");

    LPVOID pMsgBox = ::GetProcAddress(::GetModuleHandleW(L"User32"), "MessageBoxW");
    void * pHookFunc = &HookFunc;

    DWORD src = (DWORD)pMsgBox + 5;
    DWORD dst = (DWORD)pHookFunc;
    DWORD * rOffset = (DWORD *)(dst - src);

    char patch[5] = { 0 };
    ::memcpy_s(patch, 1, "\xE9", 1); // E9 -> JMP
    ::memcpy_s(patch + 1, 4, &rOffset, 4);
    ::WriteProcessMemory(GetCurrentProcess(), (LPVOID)pMsgBox, patch, sizeof(patch), NULL);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        InjectAndHook();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

