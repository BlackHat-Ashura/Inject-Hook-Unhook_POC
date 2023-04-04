# Inject-Hook-Unhook_POC
## POC demonstrating DLL Injection, API Hooking and API Unhooking.

## How to use
### 1. Compile code in all the folders, i.e., "Use Simple DLL", "Simple DLL", "Inject Me Hook Me" </br>
### 2. First run "Inject Me Hook Me.exe" and wait for first message box </br>
### 3. Next run "Use Simple DLL.exe" with arguments as path to "Simple DLL.dll" and the PID of "Inject Me Hook Me.exe" </br> </br>

## What's happening here?
### The DLL is injected into the mentioned process and the MessageBoxW API is hooked. The process then unhooks the hooked API on the second attempt of running the hooked function.
