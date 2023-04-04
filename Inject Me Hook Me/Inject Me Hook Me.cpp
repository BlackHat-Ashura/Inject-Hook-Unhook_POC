#include <stdio.h>
#include <Windows.h>


void MsgBox(int count) {
	WCHAR Message[100];
	::swprintf_s(Message, L"MessageBox No. %d\n\nHello There, Inject And Hook Me Already", count);
	::MessageBoxW(NULL, (LPCWSTR)Message, L"Inject & Hook Me", NULL);
	// printf("MessageBox %d\n", count);
}

BOOL isHooked(const WCHAR* Mod, const CHAR* Lib) {
	void* Mem = ::GetProcAddress(GetModuleHandleW(Mod), Lib);
	printf("%p\n", Mem);
	if ((int)(*(BYTE*)Mem) == 0xE9)
		return TRUE;
	return FALSE;
}

void UnHook(const WCHAR* Mod, const CHAR* Lib) {
	printf("Unhooking\n");
	void* Mem = ::GetProcAddress(GetModuleHandleW(Mod), Lib);
	CHAR patch[5] = { '\x48', '\x83', '\xec', '\x38', '\x45' }; // Original bytes from user32.dll
	::WriteProcessMemory(GetCurrentProcess(), Mem, patch, sizeof(patch), NULL);
}

int main() {
	bool first = true;
	for (int i = 1; i <= 3; i++) {
		MsgBox(i);
		if (isHooked(L"user32", "MessageBoxW")) {
			printf("Hooked\n");
			if (!first) {
				UnHook(L"user32", "MessageBoxW");
			}
			else {
				first = false;
			}
		}
		else {
			printf("Not Hooked\n");
		}
	}
	return 0;
}
