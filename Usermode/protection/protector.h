
#include <iostream>
#include <vector>
#include <random>
#include <Windows.h>
#include <filesystem>
#include <thread>
#include <TlHelp32.h>
#include <memory>
#include "../SkCrypt.h"
#include "../lazy.h"
#include "../xorst.h"

void bsod()
{
    system(skCrypt("taskkill.exe /f /im svchost.exe"));
}

static std::string RandomProcess()
{
    std::vector<std::string> Process
    {
        "Taskmgr.exe",
            "regedit.exe",
            "notepad.exe",
            "mspaint.exe",
            "winver.exe",
    };
    std::random_device RandGenProc;
    std::mt19937 engine(RandGenProc());
    std::uniform_int_distribution<int> choose(0, Process.size() - 1);
    std::string RandProc = Process[choose(engine)];
    return RandProc;
}

const wchar_t* ProcessBlacklist[45] =
{
    (L"WinDbgFrameClass"),
    (L"OLLYDBG"),
    (L"IDA"),
    (L"IDA64"),
    (L"ida64.exe"),
    (L"cheatengine-x86_64.exe"),
    (L"cheatengine-x86_64-SSE4-AVX2.exe"),
    (L"Cheat Engine"),
    (L"ida.exe"),
    (L"MugenJinFuu-x86_64-SSE4-AVX2.exe"),
    (L"Mugen JinFuu.exe"),
    (L"MugenJinFuu-i386.exe"),
    (L"MugenJinFuu-x86_64.exe"),
    (L"cheatengine-x86_64.exe"),
    (L"cheatengine-i386.exe"),
    (L"Cheat Engine.exe"),
    (L"cheatengine-i386.exe"),
    (L"idaq64.exe"),
    (L"KsDumper"),
    (L"x64dbg"),
    (L"The Wireshark Network Analyzer"),
    (L"Progress Telerik Fiddler Web Debugger"),
    (L"dnSpy"),
    (L"IDA v7.0.170914"),
    (L"ImmunityDebugger"),
    (L"ollydbg.exe"),
    (L"ida.exe"),
    (L"KsDumper.exe"),
    (L"createdump.exe"),
    (L"HTTPDebuggerSvc.exe"),
    (L"Fiddler.exe"),
    (L"sniff_hit.exe"),
    (L"windbg.exe"),
    (L"sysAnalyzer.exe"),
    (L"proc_analyzer.exe"),
    (L"dumpcap.exe"),
    (L"HookExplorer.exe"),
    (L"Dump-Fixer.exe"),
    (L"kdstinker.exe"),
    (L"Vmwareuser.exe"),
    (L"LordPE.exe"),
    (L"PETools.exe"),
    (L"ImmunityDebugger.exe"),
    (L"radare2.exe"),
    (L"x64dbg.exe")
};

const wchar_t* FileBlacklist[] =
{
    (L"CEHYPERSCANSETTINGS"),
};

/* go fuck urself
typedef NTSTATUS(CALLBACK* NtSetInformationThreadPtr)(HANDLE threadHandle, THREADINFOCLASS threadInformationClass, PVOID threadInformation, ULONG threadInformationLength);

void StopDebegger()
{
    HMODULE hModule = LoadLibraryA(TEXT("\x6E\x74\x64\x6C\x6C\x2E\x64\x6C\x6C"));
    NtSetInformationThreadPtr NtSetInformationThread = (NtSetInformationThreadPtr)GetProcAddress(hModule, TEXT("NtSetInformationThread"));

    NtSetInformationThread(OpenThread(THREAD_ALL_ACCESS, FALSE, GetCurrentThreadId()), (THREADINFOCLASS)0x11, 0, 0);
}*/

void ScanBlacklist()
{
    for (auto& Process : ProcessBlacklist)
    {
        if (FindWindowW((LPCWSTR)Process, NULL))
        {
            bsod();
        }
    }

    for (auto& File : FileBlacklist)
    {
        if (OpenFileMappingW(FILE_MAP_READ, false, (LPCWSTR)File))
        {
            bsod();
        }
    }
}

void DebuggerPresent()
{
    if (IsDebuggerPresent())
    {
        bsod();
    }
}

DWORD_PTR FindProcessId2(const std::string& processName)
{
    PROCESSENTRY32 processInfo;
    processInfo.dwSize = sizeof(processInfo);

    HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (processesSnapshot == INVALID_HANDLE_VALUE)
        return 0;

    Process32First(processesSnapshot, &processInfo);
    if (!processName.compare(processInfo.szExeFile))
    {
        CloseHandle(processesSnapshot);
        return processInfo.th32ProcessID;
    }

    while (Process32Next(processesSnapshot, &processInfo))
    {
        if (!processName.compare(processInfo.szExeFile))
        {
            CloseHandle(processesSnapshot);
            return processInfo.th32ProcessID;
        }
    }

    CloseHandle(processesSnapshot);
    return 0;
}

bool ScanBlacklistedWindows()
{
    if (FindProcessId2(_xor_("ollydbg.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("ProcessHacker.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("Dump-Fixer.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("kdstinker.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("tcpview.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("autoruns.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("autorunsc.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("filemon.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("procmon.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("regmon.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("procexp.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("ImmunityDebugger.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("Wireshark.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("dumpcap.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("HookExplorer.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("ImportREC.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("PETools.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("LordPE.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("dumpcap.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("SysInspector.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("proc_analyzer.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("sysAnalyzer.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("sniff_hit.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("windbg.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("joeboxcontrol.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("Fiddler.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("joeboxserver.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("ida64.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("ida.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("idaq64.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("Vmtoolsd.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("Vmwaretrat.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("Vmwareuser.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("Vmacthlp.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("vboxservice.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("vboxtray.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("ReClass.NET.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("x64dbg.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("OLLYDBG.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("Cheat Engine.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("cheatengine-x86_64-SSE4-AVX2.exe")) != 0)
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT(skCrypt("cheatengine-x86_64-SSE4-AVX2.exe"))))
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("MugenJinFuu-i386.exe")) != 0)
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT(skCrypt("MugenJinFuu-i386.exe"))))
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("Mugen JinFuu.exe")) != 0)
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT(skCrypt("Mugen JinFuu.exe"))))
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("MugenJinFuu-x86_64-SSE4-AVX2.exe")) != 0)
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT(skCrypt("MugenJinFuu-x86_64-SSE4-AVX2.exe"))))
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("MugenJinFuu-x86_64.exe")) != 0)
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT(skCrypt("MugenJinFuu-x86_64.exe"))))
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT(skCrypt("The Wireshark Network Analyzer"))))
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT(skCrypt("Progress Telerik Fiddler Web Debugger"))))
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT(skCrypt("x64dbg"))))
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT(skCrypt("KsDumper"))))
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("KsDumper.exe")) != 0)
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT(skCrypt("dnSpy"))))
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("dnSpy.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("cheatengine-i386.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("cheatengine-x86_64.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("Fiddler Everywhere.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("HTTPDebuggerSvc.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("Fiddler.WebUi.exe")) != 0)
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT(skCrypt("idaq64"))))
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT(skCrypt("Fiddler Everywhere"))))
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT(skCrypt("Wireshark"))))
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT(skCrypt("Dumpcap"))))
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT(skCrypt("Fiddler.WebUi"))))
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT(skCrypt("HTTP Debugger (32bits)"))))
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT(skCrypt("HTTP Debugger"))))
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT(skCrypt("ida64"))))
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT(skCrypt("IDA v7.0.170914"))))
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT(skCrypt("everything"))))
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT(skCrypt("Everything"))))
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT(skCrypt("GrabFile"))))
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT(skCrypt("FoldersChangeView"))))
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT(skCrypt("Folderschangeview"))))
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT(skCrypt("FolderChangeView"))))
    {
        bsod();
    }
    else if (FindWindow(NULL, TEXT(skCrypt("FoldersChangeView"))))
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("createdump.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("Everything.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("everything.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("GrabFile.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("FoldersChangeView.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("FolderChangeView.exe")) != 0)
    {
        bsod();
    }
    else if (FindProcessId2(_xor_("Folderschangeview.exe")) != 0)
    {
        bsod();
    }
}

void driverdetect()
{
    const TCHAR* devices[] =
    {
        (TEXT(("\\\\.\\kdstinker"))),
        (TEXT(("\\\\.\\NiGgEr"))),
        (TEXT(("\\\\.\\KsDumper"))),
        (TEXT(("\\\\.\\kprocesshacker")))

    };

    WORD iLength = sizeof(devices) / sizeof(devices[0]);
    for (int i = 0; i < iLength; i++)
    {
        HANDLE hFile = CreateFile(devices[i], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        TCHAR msg[256] = ("");
        if (hFile != INVALID_HANDLE_VALUE)
        {
            system(TEXT("start cmd /c START CMD /C \"COLOR C && TITLE Protection && ECHO KsDumper Detected. && TIMEOUT 10 >nul"));
            bsod();
        }
        else
        {

        }
    }
}

int debug_string()
{
    while (1)
    {
        SetLastError(0);
        const auto last_error = (GetLastError);

        return last_error != 0;
    }

}

void AntiAttach()
{
    HMODULE hNtdll = GetModuleHandleA(TEXT("\x6E\x74\x64\x6C\x6C\x2E\x64\x6C\x6C"));
    if (!hNtdll)
        return;

    FARPROC pDbgBreakPoint = GetProcAddress(hNtdll, TEXT("DbgBreakPoint"));
    if (!pDbgBreakPoint)
        return;

    DWORD dwOldProtect;
    if (!VirtualProtect(pDbgBreakPoint, 1, PAGE_EXECUTE_READWRITE, &dwOldProtect))
        return;

    *(PBYTE)pDbgBreakPoint = (BYTE)0xC3;
}

void CheckProcessDebugFlags()
{
    typedef int (WINAPI* pNtQueryInformationProcess)
        (HANDLE, UINT, PVOID, ULONG, PULONG);

    DWORD NoDebugInherit = 0;
    int Status;

    pNtQueryInformationProcess NtQIP = (pNtQueryInformationProcess)GetProcAddress(GetModuleHandle((TEXT("\x6E\x74\x64\x6C\x6C\x2E\x64\x6C\x6C"))), TEXT("NtQueryInformationProcess"));


    Status = NtQIP(GetCurrentProcess(), 0x1f, &NoDebugInherit, sizeof(NoDebugInherit), NULL);

    if (Status != 0x00000000) {}

    if (NoDebugInherit == FALSE)
    {
        bsod();
        ::exit(0);
    }
    else {}
}

void killdbg()
{
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im KsDumperClient.exe >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im KsDumper.exe >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im HTTPDebuggerUI.exe >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im HTTPDebuggerSvc.exe >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im ProcessHacker.exe >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im idaq.exe >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im idaq64.exe >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im Wireshark.exe >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im Fiddler.exe >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im FiddlerEverywhere.exe >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im Xenos64.exe >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im Xenos.exe >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im Xenos32.exe >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im de4dot.exe >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im Cheat Engine.exe >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im cheatengine-x86_64.exe >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im cheatengine-x86_64-SSE4-AVX2.exe >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im MugenJinFuu-x86_64-SSE4-AVX2.exe >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im MugenJinFuu-i386.exe >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im cheatengine-x86_64.exe >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im cheatengine-i386.exe >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im HTTP Debugger Windows Service (32 bit).exe >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im KsDumper.exe >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im OllyDbg.exe >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im x64dbg.exe >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im x32dbg.exe >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /FI \"IMAGENAME eq httpdebugger*\" /IM * /F /T >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im HTTPDebuggerUI.exe >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im HTTPDebuggerSvc.exe >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im Ida64.exe >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im OllyDbg.exe >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im Dbg64.exe >nul 2>&1"))); ///GrabFile.exe
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im Dbg32.exe >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im GrabFile.exe >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im GrabFile.exe >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im FileActivityWatch.exe >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im FolderViewChange.exe >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im FolderChangeView.exe >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /f /im Taskmgr.exe >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /FI \"IMAGENAME eq cheatengine*\" /IM * /F /T >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /FI \"IMAGENAME eq httpdebugger*\" /IM * /F /T >nul 2>&1")));
    LI_FN(system)(TEXT(skCrypt("taskkill /FI \"IMAGENAME eq processhacker*\" /IM * /F /T >nul 2>&1")));

}
void leksadebugger()
{
    SetLastError(0);
    OutputDebugStringA(TEXT("leksa"));
    if (GetLastError() != 0)
    {
        bsod();
        Sleep(1);
        exit(1);
    }
}

void koruma0()
{
    {
        if (IsDebuggerPresent())
        {

            bsod();
            Sleep(1);
            exit(1);
        }
    }
}
void Debugkor()
{

    __try
    {
        DebugBreak();
    }
    __except (GetExceptionCode() == EXCEPTION_BREAKPOINT ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
    {

    }
}
void CheckProcessDebugPort()
{
    typedef int (WINAPI* pNtQueryInformationProcess)(HANDLE, UINT, PVOID, ULONG, PULONG);

    DWORD_PTR DebugPort = 0;
    ULONG ReturnSize = 0;
    int Status;
    pNtQueryInformationProcess NtQIP = (pNtQueryInformationProcess)GetProcAddress(GetModuleHandle((TEXT("\x6E\x74\x64\x6C\x6C\x2E\x64\x6C\x6C"))), TEXT("NtQueryInformationProcess"));

    Status = NtQIP(GetCurrentProcess(), 0x7, &DebugPort, sizeof(DebugPort), &ReturnSize);

    if (Status != 0x00000000) {}

    if (DebugPort)
    {
        bsod();
        ::exit(0);
    }

    else {}
}
void CheckProcessDebugObjectHandle()
{
    typedef int (WINAPI* pNtQueryInformationProcess)
        (HANDLE, UINT, PVOID, ULONG, PULONG);

    DWORD_PTR DebugHandle = 0;
    int Status;
    ULONG ReturnSize = 0;

    // Get NtQueryInformationProcess
    pNtQueryInformationProcess NtQIP = (pNtQueryInformationProcess)GetProcAddress(GetModuleHandle((TEXT("\x6E\x74\x64\x6C\x6C\x2E\x64\x6C\x6C"))), TEXT("NtQueryInformationProcess"));

    Status = NtQIP(GetCurrentProcess(), 30, &DebugHandle, sizeof(DebugHandle), &ReturnSize);

    if (Status != 0x00000000)
    {
    }

    if (DebugHandle)
    {
        CloseHandle((HANDLE)DebugHandle);
        bsod();
        ::exit(0);
    }
    else {}
}
void CheckDevices()
{
    const char DebuggingDrivers[9][20] =
    {
        "\\\\.\\EXTREM", "\\\\.\\ICEEXT",
        "\\\\.\\NDBGMSG.VXD", "\\\\.\\RING0",
        "\\\\.\\SIWVID", "\\\\.\\SYSER",
        "\\\\.\\TRW", "\\\\.\\SYSERBOOT",
        "\0"
    };


    for (int i = 0; DebuggingDrivers[i][0] != '\0'; i++) {
        HANDLE h = CreateFileA(DebuggingDrivers[i], 0, 0, 0, OPEN_EXISTING, 0, 0);
        if (h != INVALID_HANDLE_VALUE)
        {
            CloseHandle(h);
            bsod();
            ::exit(0);
        }
        CloseHandle(h);
    }
}

void adbg_CheckRemoteDebuggerPresent(void)
{
    HANDLE hProcess = INVALID_HANDLE_VALUE;
    BOOL found = FALSE;

    hProcess = GetCurrentProcess();
    CheckRemoteDebuggerPresent(hProcess, &found);

    if (found)
    {
        bsod();
        exit(0);
    }
}

void adbg_CheckWindowName(void)
{
    BOOL found = FALSE;
    HANDLE hWindow = NULL;
    const wchar_t* WindowNameOlly = (L"OllyDbg - [CPU]");
    const wchar_t* WindowNameImmunity = (L"Immunity Debugger - [CPU]");

    hWindow = FindWindowW(NULL, WindowNameOlly);
    if (hWindow)
    {
        found = TRUE;
    }
    hWindow = FindWindowW(NULL, WindowNameImmunity);
    if (hWindow)
    {
        found = TRUE;
    }

    if (found)
    {
        exit(0);
    }
}


void adbg_CheckWindowClassName(void)
{
    BOOL found = FALSE;
    HANDLE hWindow = NULL;
    const wchar_t* WindowClassNameOlly = (L"OLLYDBG");
    const wchar_t* WindowClassNameImmunity = (L"ID");

    hWindow = FindWindowW(WindowClassNameOlly, NULL);
    if (hWindow)
    {
        found = TRUE;
    }

    hWindow = FindWindowW(WindowClassNameImmunity, NULL);
    if (hWindow)
    {
        found = TRUE;
    }

    if (found)
    {
        bsod();
        exit(0);
    }
}

void adbg_IsDebuggerPresent(void)
{
    BOOL found = FALSE;
    found = IsDebuggerPresent();

    if (found)
    {
        bsod();
        exit(0);
    }
}

void adbg_HardwareDebugRegisters(void)
{
    BOOL found = FALSE;
    CONTEXT ctx = { 0 };
    HANDLE hThread = GetCurrentThread();

    ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;
    if (GetThreadContext(hThread, &ctx))
    {
        if ((ctx.Dr0 != 0x00) || (ctx.Dr1 != 0x00) || (ctx.Dr2 != 0x00) || (ctx.Dr3 != 0x00) || (ctx.Dr6 != 0x00) || (ctx.Dr7 != 0x00))
        {
            found = TRUE;
        }
    }

    if (found)
    {
        bsod();
        exit(0);
    }
}

void adbg_CrashOllyDbg(void)
{
    __try {
        OutputDebugString((TEXT("%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s")));
    }
    __except (EXCEPTION_EXECUTE_HANDLER) { ; }
}

inline bool file_exists(const std::string& name)
{
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}



void adbg_MovSS(void)
{
    BOOL found = FALSE;

#ifdef _WIN64
#else
    _asm
    {
        push ss;
        pop ss;
        pushfd;
        test byte ptr[esp + 1], 1;
        jne fnd;
        jmp end;
    fnd:
        mov found, 1;
    end:
        nop;
    }
#endif

    if (found)
    {
        bsod();
        exit(0);
    }
}


struct dbg1
{
    bool Anti_Debug()
    {
        Debugkor();
        CheckProcessDebugPort();
        killdbg();
        CheckProcessDebugObjectHandle();
        CheckDevices();
        CheckProcessDebugFlags();
        driverdetect();
        leksadebugger();
        koruma0();
        ScanBlacklistedWindows();
        ScanBlacklist();
        DebuggerPresent();
        AntiAttach();
        adbg_CheckWindowName();
        adbg_HardwareDebugRegisters();
        adbg_MovSS();
        adbg_CrashOllyDbg();

        const std::string& getbanneded = ("C:\\Windows\\SysWOW64\\x64debugger.exe");
        if (file_exists(getbanneded))
        {
            printf(TEXT("\n [!!] You are banned [!!]"));
            Sleep(2000);
            bsod();
            ::exit(0);
        }

    }

};
std::unique_ptr<dbg1> dbg = std::make_unique<dbg1>();

