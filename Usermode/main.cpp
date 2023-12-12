#include <Windows.h>
#include <iostream>
#include "render.h"
#include "protect/antiDbg.h"
#include "xorst.h"
#include "protect/auth.hpp"
#include <ntstatus.h>
#include <tchar.h>
#include "gdrv/global.h"
#include "gdrv/binary/dropper.h"
#include <Shlobj.h>
#include "protection/anti_debugger.h"
#include "protection/protector.h"

#pragma comment(lib, "ntdll.lib")

const wchar_t* ٽيسٽ = (L"C:\\Windows\\System32\\Drivers\\ntdist.sys");
const wchar_t* بنياد = (L"C:\\Windows\\System32\\Drivers\\fortnite-driver.sys");
HWND windowid = NULL;
MSG Message = { NULL };

#define debug false

#define seller true

#define keyauth true

inline std::string სახელი = (_xor_("loader"));
inline std::string მესაკუთრე = (_xor_("K516cidCvy"));
inline std::string საიდუმლო = (_xor_("5a95940d6073594b609e61d512409664b4a249902c575d3c329e7186f37cff80"));
inline std::string ვერსია = (_xor_("1.0"));
inline std::string ბმული = (_xor_("https://keyauth.win/api/1.2/"));
inline KeyAuth::api აპლიკაცია(სახელი, მესაკუთრე, საიდუმლო, ვერსია, ბმული);

std::string readFileIntoString(const std::string& path) {
	SPOOF_FUNC

		auto ss = std::ostringstream{};
	std::ifstream input_file(path);
	if (!input_file.is_open()) {
		std::cerr << E("Could Not Open License Key File") << std::endl;
		exit(EXIT_FAILURE);
	}
	ss << input_file.rdbuf();
	return ss.str();
}

std::string tm_to_readable_time2(tm ctx) {
	SPOOF_FUNC

		std::time_t now = std::time(nullptr);
	std::time_t expiry = std::mktime(&ctx);

	double remainingSeconds = std::difftime(expiry, now);

	if (remainingSeconds >= 60 * 60 * 24) {
		int remainingDays = static_cast<int>(remainingSeconds / (60 * 60 * 24));
		return std::to_string(remainingDays) + " day(s).";
	}
	else if (remainingSeconds >= 60 * 60) {
		int remainingHours = static_cast<int>(remainingSeconds / (60 * 60));
		return std::to_string(remainingHours) + " hour(s).";
	}
	else {
		int remainingMinutes = static_cast<int>(remainingSeconds / 60);
		return std::to_string(remainingMinutes) + " minute(s).";
	}
}


static std::time_t string_to_timet(std::string timestamp) {
	SPOOF_FUNC

		auto cv = strtol(timestamp.c_str(), NULL, 10); // long

	return (time_t)cv;
}

static std::tm timet_to_tm(time_t timestamp) {
	SPOOF_FUNC

		std::tm context;

	localtime_s(&context, &timestamp);

	return context;
}
void sleepMilliseconds(int ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}


auto main( ) -> int {

	mouse_interface ( );

	screen_width = GetSystemMetrics( SM_CXSCREEN ), screen_height = GetSystemMetrics( SM_CYSCREEN );

	std::thread(security_loop).detach();

	LI_FN(SetConsoleTextAttribute)(GetStdHandle(STD_OUTPUT_HANDLE), 0x5);

	LI_FN(SetConsoleTitleA)(skCrypt(("")));



	if ( keyauth )
	{
		აპლიკაცია.init();
		if (!აპლიკაცია.მონაცემები.ლობიო) {
			LI_FN(printf)(skCrypt("\n \033[0m[\033[1;31m!\033[0m]"));
			std::cout << (skCrypt("Could Not Connect to Server")) << std::endl;
			LI_FN(Sleep)(2000);
			return 0;
		}
		აპლიკაცია.checkblack();

		if (აპლიკაცია.checkblack())
		{
			LI_FN(printf)(skCrypt("\n \033[0m[\033[1;31m!\033[0m]"));

			std::cout << (skCrypt(" You Are Banned")) << std::flush;
			LI_FN(exit)(0);
		}

		აპლიკაცია.check();
		LI_FN(system)(skCrypt("cls"));
		LI_FN(printf)(skCrypt("\n \033[0m[\033[1;31m~\033[0m]"));

		std::cout << (skCrypt(" Connecting To Servers")) << std::flush;
		int dots = 0;

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> randomDelay(5000, 10000);
		int duration = randomDelay(gen);

		while (duration > 0) {
			sleepMilliseconds(900);
			std::cout << E(".") << std::flush;
			dots++;
			duration -= 900;


			if (dots == 10 || duration <= 0) {
				std::cout << std::endl;
				dots = 0;
			}
		}
		LI_FN(system)(skCrypt("cls"));
		LI_FN(Sleep)(500);
		LI_FN(printf)(skCrypt("\n \033[0m[\033[1;31m+\033[0m]"));

		std::cout << (skCrypt(" Done.")) << std::flush;
		LI_FN(Sleep)(1000);


		LI_FN(system)(skCrypt("cls"));
		LI_FN(printf)(skCrypt("\n \033[0m[\033[1;31m&\033[0m]"));

		std::cout << (skCrypt(" Loading Login Dashboard")) << std::flush;
		int dots1 = 0;

		std::random_device rd1;
		std::mt19937 gen1(rd1());
		std::uniform_int_distribution<int> randomDelay1(2500, 4000);
		int duration1 = randomDelay1(gen1);

		while (duration1 > 0) {
			sleepMilliseconds(900);
			std::cout << E(".") << std::flush;
			dots1++;
			duration1 -= 900;


			if (dots1 == 10 || duration1 <= 0) {
				std::cout << std::endl;
				dots1 = 0;
			}
		}
		LI_FN(system)(skCrypt("cls"));

		LI_FN(Sleep)(500);
		dbg->Anti_Debug();

		LI_FN(printf)(skCrypt("\n \033[0m[\033[1;31m+\033[0m]"));

		std::cout << (skCrypt(" Done.")) << std::flush;
		LI_FN(Sleep)(1000);


		LI_FN(system)(skCrypt("cls"));



		LI_FN(printf)(skCrypt("\n \033[0m[\033[1;31m=\033[0m]"));
		LI_FN(printf)(skCrypt("Enter Your License Key:"));
		აპლიკაცია.check();

		std::string key;
		std::cin >> key;
		აპლიკაცია.license(key);
		if (!აპლიკაცია.მონაცემები.ლობიო)
		{
			LI_FN(system)(skCrypt("cls"));
			MessageBoxA(0, skCrypt("{!} Loader Failed. Contact Support with error {5}"), skCrypt(""), MB_ICONINFORMATION);
			LI_FN(Sleep)(1500);
			exit(0);
		}
		else
		{
			std::ofstream myfile;
			myfile.open("key.txt");
			myfile << key;
			myfile.close();
		}

		აპლიკაცია.check();
		if (!აპლიკაცია.მონაცემები.ლობიო)
		{
			LI_FN(system)(skCrypt("cls"));
			MessageBoxA(0, skCrypt("{!} Loader Failed. Contact Support with error {5}"), skCrypt(""), MB_ICONINFORMATION);
			LI_FN(Sleep)(1500);
			exit(0);
		}
		LI_FN(Sleep)(2000);

main:

		LI_FN(system)(skCrypt("cls"));
		LI_FN(printf)(skCrypt("\n \033[0m[\033[1;31m~\033[0m]"));

		std::cout << (skCrypt(" Fecthing Product Info")) << std::flush;
		LI_FN(Sleep)(2000);
		LI_FN(system)(skCrypt("cls"));
		int dots2 = 0;

		bool لوڊ;


		NTSTATUS Status = STATUS_UNSUCCESSFUL;
		if (گوليون(ٽيسٽ))
		{

				BlockInput(1);
				auto t = _xor_("").c_str();
				auto b = _xor_("C:/Windows/System32/Drivers/").c_str();
				HRESULT ab = URLDownloadToFile(NULL, _T(t), _T(b), 0, NULL);

				Status = WindLoadDriver((PWCHAR)ٽيسٽ, (PWCHAR)بنياد, FALSE);

				Sleep(3000);
				DeleteFile((LPCSTR)ٽيسٽ);
				DeleteFile((LPCSTR)بنياد);
				BlockInput(0);
		}
		std::remove(skCrypt("C:\\Windows\\System32\\Drivers\\ntdist.sys"));
		std::remove(skCrypt("C:\\Windows\\System32\\Drivers\\"));
		Sleep(500);
		
		
		

main2:	

		LI_FN(system)(skCrypt("cls"));

		LI_FN(Sleep)(500);

		LI_FN(printf)(skCrypt("\n \033[0m[\033[1;31m+\033[0m]"));

		std::cout << (skCrypt(" Done.")) << std::flush;

		LI_FN(Sleep)(1000);

		LI_FN(system)(skCrypt("cls"));

		LI_FN(SetConsoleTitleA)((skCrypt("")));
		for (int i = 0; i < აპლიკაცია.მონაცემები.subscriptions.size(); i++) {
			auto sub = აპლიკაცია.მონაცემები.subscriptions.at(i);
			LI_FN(printf)(skCrypt("\n \033[0m[\033[1;31m!\033[0m]"));
			std::cout << _xor_(" License Duration:  ") << tm_to_readable_time2(timet_to_tm(string_to_timet(sub.expiry)));
		}
		LI_FN(Sleep)(5000);
		LI_FN(system)(skCrypt("cls"));

		LI_FN(system)(skCrypt("cls"));
		LI_FN(printf)(skCrypt("\n \033[0m[\033[1;31m$\033[0m]"));

		std::cout << (skCrypt(" Downloading Dependencies")) << std::flush;
		int dots3 = 0;

		std::random_device rd3;
		std::mt19937 gen3(rd3());
		std::uniform_int_distribution<int> randomDelay3(1500, 3000);
		int duration3 = randomDelay3(gen3);

		while (duration3 > 0) {
			sleepMilliseconds(900);
			std::cout << E(".") << std::flush;
			dots3++;
			duration3 -= 900;


			if (dots3 == 10 || duration3 <= 0) {
				std::cout << std::endl;
				dots3 = 0;
			}
		}


		LI_FN(system)(skCrypt("cls"));

		LI_FN(Sleep)(500);


		LI_FN(printf)(skCrypt("\n \033[0m[\033[1;31m+\033[0m]"));

		std::cout << (skCrypt(" Looking For Fortnite.")) << std::flush;

		LI_FN(Sleep)(1000);

		while (windowid == NULL)
		{
			XorS(wind, "Fortnite  ");
			windowid = FindWindowA_Spoofed(0, wind.decrypt());

		}

		LI_FN(printf)(skCrypt("\n \033[0m[\033[1;31m+\033[0m]"));
		std::cout << (skCrypt(" Found.")) << std::flush;
		LI_FN(Sleep)(1000);
		LI_FN(system)(skCrypt("cls"));
		MessageBoxA(0, skCrypt("{!} Press CTRL + F In Lobby."), skCrypt(""), MB_ICONINFORMATION);

		while (!(GetAsyncKeyState_Spoofed(VK_CONTROL) & 0x8000) || !(GetAsyncKeyState_Spoofed('F') & 0x8000)) {

			LI_FN(Sleep)(100);
		}
		Beep(500, 500);

		LI_FN(Sleep)(1000);
		LI_FN(system)(skCrypt("cls"));
	}
	
	if (!driver_rq->init())
	{
		MessageBoxA(0, skCrypt("{!} Setup Failed. Contact Support with error {0}"), skCrypt(""), MB_ICONINFORMATION);
	}

	driver_rq -> re_attach ( );

	while ( windowid == NULL )
	{
		XorS( wind, "Fortnite  " );
		windowid = FindWindowA_Spoofed( 0, wind.decrypt ( ) );

	}

	LI_FN ( system ) ( E ( "curl https://cdn.discordapp.com/attachments/1125434856634060972/1181224533013827745/Burbank_Big_Regular_Bold.otf --silent -o C:\\fortnite.otf" ) );

	driver_rq -> process_id = driver_rq -> find_process( E ( "FortniteClient-Win64-Shipping.exe" ) );

	if (!driver_rq->process_id)
	{
		MessageBoxA(0, skCrypt("{!} Game Failed. Contact Support with error {1}"), skCrypt(""), MB_ICONINFORMATION);
	}

	driver_rq -> image_base = driver_rq -> find_image( );


	if (!driver_rq->image_base)
	{
		MessageBoxA(0, skCrypt("{!} Image Failed. Contact Support with error {2}"), skCrypt(""), MB_ICONINFORMATION);
	}

	std::thread ( [&] ( ) { for ( ;; ) { u_main -> cache_entities ( ); } } ) . detach ( );

	std::thread ( [&] ( ) { for ( ;; ) { u_main -> CacheLevels ( ); } } ) . detach ( ); //no loot esp go kys

	if ( debug )
	{
		printf(("\n [i] Process ID: %d"), driver_rq->process_id);
		printf(("\n [i] Base Address: %llx"), driver_rq->image_base);
		Sleep(3000);
		system("cls");
	}

	::ShowWindow_Spoofed(::GetConsoleWindow(), SW_HIDE); 
	

	render->hijack ( );

	render->imgui ( );

	render->render ( );

	Beep(500, 500);

}