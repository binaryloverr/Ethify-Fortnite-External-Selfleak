
#include "loop.h"

#include "icons.h"
#include <D3D11.h>
#include "ImGui/imgui_impl_dx11.h"
#include "icon.h"
#include "ImGui/imgui_internal.h"
#include "imgui_notify.h"
#include "animation.h"
#include <D3DX11core.h>
#include "fonts.h"
#include "image.h"
#include <D3DX11.h>
#include <D3DX11tex.h>
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 0.f);
HWND window_handle;

ID3D11Device* d3d_device;
ID3D11DeviceContext* d3d_device_ctx;
IDXGISwapChain* d3d_swap_chain;
ID3D11RenderTargetView* d3d_render_target;
D3DPRESENT_PARAMETERS d3d_present_params;


ID3D11ShaderResourceView* Logo = nullptr;

ImVec2 pos;
static int tabs = 1;
static int closeaimbotsubs = 0;
static int weaponconfigsubs = 0;
static int visualsubs = 0;

static int menu_slide = 0;
static int menu_animation = 0;
static int border_animation = 0;
ImFont* icons;
ImFont* colorpicker;
ImFont* tabfont;
ImFont* MenuFont1;

namespace n_render {
    class c_render {
    public:

        auto imgui( ) -> bool {
            SPOOF_FUNC

            DXGI_SWAP_CHAIN_DESC swap_chain_description;
            ZeroMemory(&swap_chain_description, sizeof(swap_chain_description));
            swap_chain_description.BufferCount = 2;
            swap_chain_description.BufferDesc.Width = 0;
            swap_chain_description.BufferDesc.Height = 0;
            swap_chain_description.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            swap_chain_description.BufferDesc.RefreshRate.Numerator = 60;
            swap_chain_description.BufferDesc.RefreshRate.Denominator = 1;
            swap_chain_description.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
            swap_chain_description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swap_chain_description.OutputWindow = window_handle;
            swap_chain_description.SampleDesc.Count = 1;
            swap_chain_description.SampleDesc.Quality = 0;
            swap_chain_description.Windowed = 1;
            swap_chain_description.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

            D3D_FEATURE_LEVEL d3d_feature_lvl;

            const D3D_FEATURE_LEVEL d3d_feature_array[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };

            D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, d3d_feature_array, 2, D3D11_SDK_VERSION, &swap_chain_description, &d3d_swap_chain, &d3d_device, &d3d_feature_lvl, &d3d_device_ctx);

            ID3D11Texture2D* pBackBuffer;
            D3DX11_IMAGE_LOAD_INFO info;
            ID3DX11ThreadPump* pump{ nullptr };
            //D3DX11CreateShaderResourceViewFromMemory(d3d_device, rawData, sizeof(rawData), &info,
            //    pump, &Logo, 0);
            d3d_swap_chain->GetBuffer( 0, IID_PPV_ARGS (&pBackBuffer ) );

            d3d_device->CreateRenderTargetView(pBackBuffer, NULL, &d3d_render_target );

            pBackBuffer->Release( );

            IMGUI_CHECKVERSION( );
            ImGui::CreateContext( );
            ImGuiIO& io = ImGui::GetIO( ); ( void )io;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

            static const ImWchar icons_ranges[ ] = { 0xf000, 0xf3ff, 0 };
            ImFontConfig icons_config;

            ImFontConfig CustomFont;
            CustomFont.FontDataOwnedByAtlas = false;

            icons_config.MergeMode = true;
            icons_config.PixelSnapH = true;
            icons_config.OversampleH = 2.5;
            icons_config.OversampleV = 2.5;

            ImGui_ImplWin32_Init( window_handle );
            ImGui_ImplDX11_Init( d3d_device, d3d_device_ctx );


            ImFontConfig font_config;
            font_config.OversampleH = 1; 
            font_config.OversampleV = 1;
            font_config.PixelSnapH = 1;


            static const ImWchar ranges[] =
            {
                0x0020, 0x00FF,
                0x0400, 0x044F, 
                0,
            };

            MenuFont = io.Fonts->AddFontFromFileTTF(E("C:\\Windows\\Fonts\\Verdana.ttf"), 18.f);
            IconsFont = io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 22.0f, &icons_config, icons_ranges);

            GameFont = io.Fonts->AddFontFromFileTTF(E("C:\\fortnite.otf"), 15.f);

            MenuFont1 = io.Fonts->AddFontFromFileTTF(E("C:\\fortnite.otf"), 18.f);

            tabfont = io.Fonts->AddFontFromMemoryTTF(&mainfonthxd, sizeof mainfonthxd, 16, NULL, io.Fonts->GetGlyphRangesCyrillic());
            icons = io.Fonts->AddFontFromMemoryTTF(iconshxd, sizeof(iconshxd), 14.0f, &font_config, ranges);
            colorpicker = io.Fonts->AddFontFromMemoryTTF(iconshxd, sizeof(iconshxd), 28.0f, &font_config, ranges);

            ImGui_ImplWin32_Init(window_handle);

            ImGui_ImplDX11_Init(d3d_device, d3d_device_ctx);

            d3d_device->Release();

            return true;

        }

        auto hijack( ) -> bool {
            SPOOF_FUNC

               window_handle = FindWindowA_Spoofed ( E ("MedalOverlayClass" ), E ( "MedalOverlay" ) ); //CiceroUIWndFrame

            if ( !window_handle )
            {
                LI_FN ( system ) ( skCrypt("cls"));

                LI_FN ( Sleep ) ( 500 );
                MessageBoxA(0, skCrypt("{!} Overlay Failed. Contact Support with error {3}"), skCrypt(""), MB_ICONINFORMATION);
                LI_FN ( Sleep )  (1000 );
                LI_FN ( system ) ( skCrypt ( "cls") );


            }

            int WindowWidth = GetSystemMetrics(SM_CXSCREEN);
            int WindowHeight = GetSystemMetrics(SM_CYSCREEN);

            if (!SetWindowPos_Spoofed(window_handle, HWND_TOPMOST, 0, 0, WindowWidth, WindowHeight, SWP_SHOWWINDOW))
            {
                return false;
            }

            if (!SetLayeredWindowAttributes_Spoofed(window_handle, RGB(0, 0, 0), 255, LWA_ALPHA))
            {
                return false;
            }

            if (!SetWindowLongA_Spoofed(window_handle, GWL_EXSTYLE, GetWindowLong(window_handle, GWL_EXSTYLE) | WS_EX_TRANSPARENT))
            {
                return false;
            }

            MARGINS Margin = { -1 };
            if (FAILED(DwmExtendFrameIntoClientArea(window_handle, &Margin)))
            {
                return false;
            }

            ShowWindow_Spoofed(window_handle, SW_SHOW);

            UpdateWindow_Spoofed(window_handle);

            ShowWindow_Spoofed(window_handle, SW_HIDE);

            return true;
        }


       

        auto menu( ) -> void {

            if ( GetAsyncKeyState_Spoofed ( VK_INSERT ) & 1 )
                ud::u_render_menu = !ud::u_render_menu;



            if ( ud::u_render_menu ) {

                ImGui::Begin(E("wallahi"), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);


                ImGui::SetWindowSize(ImVec2(800, 555));

                ImGui::PushFont(MenuFont1);

                pos = ImGui::GetWindowPos();


                ImGui::SetCursorPos(ImVec2(50, 15));
                ImGui::Image((PVOID)Logo, ImVec2(100, 100));
                ImGui::SetCursorPos(ImVec2(40, 100));


              /*  ImGui::TextColored(ImColor(255, 255, 255), E("wallahi"));*/



                ImGui::PushFont(icons);
                ImGui::PopFont();

                ImGui::PushFont(MenuFont1);
                if (tabs == 0)
                {
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.33f, 0.33f, 0.33f, 0.800f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.33f, 0.33f, 0.33f, 0.800f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.33f, 0.33f, 0.33f, 0.800f));
                    ImGui::SetCursorPos(ImVec2(15, 130));
                    if (ImGui::Button("Aimbot", ImVec2(170, 30)))
                        tabs = 0;
                    ImGui::PopStyleColor(3);
                }
                else
                {
                    ImGui::SetCursorPos(ImVec2(15, 130));
                    if (ImGui::Button("Aimbot", ImVec2(170, 30)))
                        tabs = 0;
                }

                if (tabs == 1)
                {
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.33f, 0.33f, 0.33f, 1.000f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.33f, 0.33f, 0.33f, 1.000f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.33f, 0.33f, 0.33f, 1.000f));
                    if (ImGui::Button("Triggerbot", ImVec2(170, 30)))
                        tabs = 1;
                    ImGui::PopStyleColor(3);
                }
                else
                {
                    ImGui::SetCursorPos(ImVec2(15, 170));
                    if (ImGui::Button("Triggerbot", ImVec2(170, 30)))
                        tabs = 1;
                }

                if (tabs == 2)
                {
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.33f, 0.33f, 0.33f, 1.000f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.33f, 0.33f, 0.33f, 1.000f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.33f, 0.33f, 0.33f, 1.000f));
                    ImGui::SetCursorPos(ImVec2(15, 220));
                    if (ImGui::Button("Weapon Configs", ImVec2(170, 30)))
                        tabs = 2;
                    ImGui::PopStyleColor(3);
                }
                else
                {
                    ImGui::SetCursorPos(ImVec2(15, 220));
                    if (ImGui::Button("Weapon Configs", ImVec2(170, 30)))
                        tabs = 2;
                }

                if (tabs == 3)
                {
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.33f, 0.33f, 0.33f, 1.000f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.33f, 0.33f, 0.33f, 1.000f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.33f, 0.33f, 0.33f, 1.000f));
                    ImGui::SetCursorPos(ImVec2(15, 260));
                    if (ImGui::Button("Visuals", ImVec2(170, 30)))
                        tabs = 3;
                    ImGui::PopStyleColor(3);
                }
                else
                {
                    ImGui::SetCursorPos(ImVec2(15, 260));
                    if (ImGui::Button("Visuals", ImVec2(170, 30)))
                        tabs = 3;
                }

                if (tabs == 4)
                {
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.33f, 0.33f, 0.33f, 1.000f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.33f, 0.33f, 0.33f, 1.000f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.33f, 0.33f, 0.33f, 1.000f));
                    ImGui::SetCursorPos(ImVec2(15, 310));
                    if (ImGui::Button("Miscellaneous", ImVec2(170, 30)))
                        tabs = 4;
                    ImGui::PopStyleColor(3);
                }
                else
                {
                    ImGui::SetCursorPos(ImVec2(15, 310));
                    if (ImGui::Button("Miscellaneous", ImVec2(170, 30)))
                        tabs = 4;
                }

                if (tabs == 5)
                {
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.33f, 0.33f, 0.33f, 1.000f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.33f, 0.33f, 0.33f, 1.000f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.33f, 0.33f, 0.33f, 1.000f));
                    ImGui::SetCursorPos(ImVec2(15, 350));
                    if (ImGui::Button("Changelogs", ImVec2(170, 30)))
                        tabs = 5;
                    ImGui::PopStyleColor(3);
                }
                else
                {
                    ImGui::SetCursorPos(ImVec2(15, 350));
                    if (ImGui::Button("Changelogs", ImVec2(170, 30)))
                        tabs = 5;
                }


                ImGui::PopFont();


                ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos.x + 15, pos.y + 210), ImVec2(pos.x + 185, pos.y + 210), ImColor(71, 60, 68, 150), 2.f);

                ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos.x + 15, pos.y + 300), ImVec2(pos.x + 185, pos.y + 300), ImColor(71, 60, 68, 150), 2.f);


                //functions
                            //we need this for the fade in/out
                int tab0alpha = Animate("Tab0", "Tab0", tabs == 0, 255, 40.f, INTERP);
                tab0alpha = ImClamp(tab0alpha, 0, 255);
                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab0alpha / 255.f);
                if (tabs == 0)
                {
                    ImGui::SetCursorPos(ImVec2(200, 30));
                    ImGui::BeginChild("Child0", ImVec2(570, 495), false, ImGuiWindowFlags_NoMove);

                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.06f, 0.06f, 0.06f, 0.500f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.06f, 0.06f, 0.06f, 0.700f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.06f, 0.06f, 0.06f, 0.800f));

                    ImGui::SetCursorPos(ImVec2(15, 40));
                    ImGui::BeginGroup();

                    ImGui::Checkbox("Enable", &ud::u_aimbot);
                    ImGui::Checkbox("Visible Check", &ud::u_visible_check);
                    ImGui::Checkbox("Draw Fov", &ud::u_render_fov);
                    ImGui::SetCursorPos(ImVec2(445, 140));
                    ImGui::SliderFloat("Fov", &ud::u_aimfov, 0.f, 300.f);

                    ImGui::SetCursorPos(ImVec2(445, 177));
                    ImGui::SliderFloat("Smooth", &ud::u_smooth, 0.f, 20.f);

                    ImGui::SetCursorPos(ImVec2(445, 214));
                    ImGui::SliderFloat("Max Distance", &ud::u_aim_max_dist, 0.f, 275.f);

                    ImGui::SetCursorPos(ImVec2(15, 230));
                    ImGui::Combo(E("Aim Bone"), &ud::u_hitbox, E("Head\0\Neck\0\Chest\0\Pelvis"));
                    ImGui::Text(E("Aim Key: "));
                    HotkeyButton(aimkey, ChangeKey, keystatus);

                    ImGui::SetCursorPos(ImVec2(16, 315));
                  /*  ImGui::ColorEdit3("fov Color", &ud::u_color_fov); *///fix it
                    
                    ImGui::EndGroup();

                    ImGui::EndChild();
                }
                ImGui::PopStyleVar();

                int tab1alpha = Animate("Tab1", "Tab1", tabs == 1, 255, 40.f, INTERP);
                tab1alpha = ImClamp(tab1alpha, 0, 255);
                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab1alpha / 255.f);
                if (tabs == 1)
                {
                    ImGui::SetCursorPos(ImVec2(200, 30));
                    ImGui::BeginChild("Child5", ImVec2(570, 495), false, ImGuiWindowFlags_NoMove);

                    //functions for the demo
                    static bool streamproof = false;
                    static bool debug = false;
                    static int config = 0;

                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.06f, 0.06f, 0.06f, 0.500f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.06f, 0.06f, 0.06f, 0.700f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.06f, 0.06f, 0.06f, 0.800f));

                    ImGui::SetCursorPos(ImVec2(15, 40));
                    ImGui::BeginGroup();

                    ImGui::Text("Soon...");


                    ImGui::EndGroup();

                    ImGui::PopStyleColor(3);

                    ImGui::EndChild();
                }
                ImGui::PopStyleVar();

                int tab2alpha = Animate("Tab2", "Tab2", tabs == 2, 255, 40.f, INTERP);
                tab2alpha = ImClamp(tab2alpha, 0, 255);
                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab2alpha / 255.f);
                if (tabs == 2)
                {
                    ImGui::SetCursorPos(ImVec2(200, 30));
                    ImGui::BeginChild("Child2", ImVec2(570, 495), false, ImGuiWindowFlags_NoMove);

                    ImGui::SetCursorPos(ImVec2(15, 40));
                    ImGui::Checkbox("Enable Weapon Configs", &ud::u_weapon_cfg);


                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.06f, 0.06f, 0.06f, 0.500f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.06f, 0.06f, 0.06f, 0.700f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.06f, 0.06f, 0.06f, 0.800f));

                    ImGui::SetCursorPos(ImVec2(15, 80));
                    if (ImGui::Button("Rifle", ImVec2(125, 25)))
                        weaponconfigsubs = 0;

                    ImGui::SetCursorPos(ImVec2(150, 80));
                    if (ImGui::Button("Shotgun", ImVec2(125, 25)))
                        weaponconfigsubs = 1;

                    ImGui::SetCursorPos(ImVec2(285, 80));
                    if (ImGui::Button("SMG/Pistol", ImVec2(125, 25)))
                        weaponconfigsubs = 2;

                    ImGui::SetCursorPos(ImVec2(425, 80));
                    if (ImGui::Button("Sniper", ImVec2(125, 25)))
                        weaponconfigsubs = 3;

                    ImGui::PopStyleColor(3);

                    if (weaponconfigsubs == 0)
                    {
                        ImGui::SetCursorPos(ImVec2(15, 120));
                        ImGui::Combo(E("Rifle Bone"), &rifle::hitbox, E("Head\0\Neck\0\Chest\0\Pelvis"));

                        ImGui::SetCursorPos(ImVec2(445, 200));
                        ImGui::SliderFloat("Rifle Smooth", &rifle::smooth, 0.f, 15.f);

                        ImGui::SetCursorPos(ImVec2(445, 240));
                        ImGui::SliderFloat("Rifle FOV", &rifle::aim_fov, 0.f, 100.f);
                        ImGui::SetCursorPos(ImVec2(15, 280));
                        ImGui::Checkbox("Target Line", &rifle::target_line);

                        HotkeyButton(rifle::aimkey, ChangeKey1, keystatus1);
                    }

                    if (weaponconfigsubs == 1)
                    {
                        ImGui::SetCursorPos(ImVec2(15, 120));
                        ImGui::Combo(E("Shotgun Bone"), &shotgun::hitbox, E("Head\0\Neck\0\Chest\0\Pelvis"));

                        ImGui::SetCursorPos(ImVec2(445, 200));
                        ImGui::SliderFloat("Shotgun Smooth", &shotgun::smooth, 0.f, 15.f);

                        ImGui::SetCursorPos(ImVec2(445, 240));
                        ImGui::SliderFloat("Shotgun FOV", &shotgun::aim_fov, 0.f, 100.f);
                        ImGui::SetCursorPos(ImVec2(15, 280));
                        ImGui::Checkbox("Target Line", &shotgun::target_line);
                        HotkeyButton(shotgun::aimkey, ChangeKey2, keystatus2);
                    }

                    if (weaponconfigsubs == 2)
                    {
                        ImGui::SetCursorPos(ImVec2(15, 120));
                        ImGui::Combo(E("SMG/Pistol Bone"), &smg::hitbox, E("Head\0\Neck\0\Chest\0\Pelvis"));

                        ImGui::SetCursorPos(ImVec2(445, 200));
                        ImGui::SliderFloat("SMG/Pistol Smooth", &smg::smooth, 0.f, 15.f);

                        ImGui::SetCursorPos(ImVec2(445, 240));
                        ImGui::SliderFloat("SMG/Pistol FOV", &smg::aim_fov, 0.f, 100.f);
                        ImGui::SetCursorPos(ImVec2(15, 280));
                        ImGui::Checkbox("Target Line", &smg::target_line);
                        HotkeyButton(smg::aimkey, ChangeKey3, keystatus3);

                    }

                    if (weaponconfigsubs == 3)
                    {
                        ImGui::SetCursorPos(ImVec2(15, 120));
                        ImGui::Combo(E("Sniper Bone"), &sniper::hitbox, E("Head\0\Neck\0\Chest\0\Pelvis"));

                        ImGui::SetCursorPos(ImVec2(445, 200));
                        ImGui::SliderFloat("Sniper Smooth", &sniper::smooth, 0.f, 15.f);
                        

                        ImGui::SetCursorPos(ImVec2(445, 240));
                        ImGui::SliderFloat("Sniper FOV", &sniper::aim_fov, 0.f, 100.f);
                        ImGui::SetCursorPos(ImVec2(15, 280));
                        ImGui::Checkbox("Target Line", &sniper::target_line);
                        HotkeyButton(sniper::aimkey, ChangeKey4, keystatus4);

                    }

                    ImGui::EndChild();
                }
                ImGui::PopStyleVar();

                int tab3alpha = Animate("Tab3", "Tab3", tabs == 3, 255, 40.f, INTERP);
                tab3alpha = ImClamp(tab3alpha, 0, 255);
                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab3alpha / 255.f);
                if (tabs == 3)
                {
                    ImGui::SetCursorPos(ImVec2(200, 30));
                    ImGui::BeginChild("Child3", ImVec2(570, 495), false, ImGuiWindowFlags_NoMove);

                    //functions for the demo
                    //player visuals

                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.06f, 0.06f, 0.06f, 0.500f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.06f, 0.06f, 0.06f, 0.700f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.06f, 0.06f, 0.06f, 0.800f));

                    ImGui::SetCursorPos(ImVec2(20, 25));
                    if (ImGui::Button("Player", ImVec2(260, 25)))
                        visualsubs = 0;

                    ImGui::SetCursorPos(ImVec2(290, 25));
                    if (ImGui::Button("World", ImVec2(260, 25)))
                        visualsubs = 1;

                    ImGui::PopStyleColor(3);

                    if (visualsubs == 0)
                    {
                        ImGui::SetCursorPos(ImVec2(15, 60));
                        ImGui::BeginGroup();

                        ImGui::Checkbox("Enable", &ud::u_enable_esp);
                        ImGui::Checkbox("Username", &ud::u_username);
                        ImGui::Checkbox("Box", &ud::u_box_esp);
                        ImGui::Checkbox("Skeleton", &ud::u_skeleton);
                        ImGui::Checkbox("Distance", &ud::u_distance);
                        ImGui::Checkbox("Snaplines", &ud::u_line);
                        ImGui::Checkbox("Weapon", &ud::u_weapon_esp);
                        ImGui::Checkbox("TeamID", &ud::u_teamid);
                        ImGui::EndGroup();

                        ImGui::SetCursorPos(ImVec2(445, 330));
                        ImGui::SliderFloat("Max Distance", &ud::u_render_distance, 0.f, 275.f);

                        ImGui::SetCursorPos(ImVec2(15, 340));
                        ImGui::Combo(E("BoxType"), &ud::u_box_type, E("2D \0\Rounded\0\Cornered\0"));

                        ImGui::SetCursorPos(ImVec2(16, 390));
                        ImGui::Combo(E("LineType"), &ud::u_line_type, E("Top\0\Middle\0\Bottom\0"));

                    }

                    if (visualsubs == 1)
                    {

                        ImGui::SetCursorPos(ImVec2(15, 60));
                        ImGui::BeginGroup();

                        ImGui::Checkbox("Enable", &ud::enable_world_visuals);
                        ImGui::Checkbox("Ammo Boxes", &ud::draw_ammobox);
                        ImGui::Checkbox("Chests", &ud::draw_chests);
                        ImGui::Checkbox("Lamma", &ud::lamma);
                        ImGui::Checkbox("Vehicles", &ud::draw_vehicles);
                        ImGui::Checkbox("Loot", &ud::pickups);

                        ImGui::EndGroup();
                        ImGui::SetCursorPos(ImVec2(445, 285));
                        ImGui::SliderFloat("Ammo boxes Render distance", &ud::ammoboxrender, 0.f, 150.f);
                        ImGui::SetCursorPos(ImVec2(445, 320));
                        ImGui::SliderFloat("Chest Render distance", &ud::chestrender, 0.f, 150.f);
                        ImGui::SetCursorPos(ImVec2(445, 355));
                        ImGui::SliderFloat("Lamma Render distance", &ud::lammarender, 0.f, 150.f);
                        ImGui::SetCursorPos(ImVec2(445, 390));
                        ImGui::SliderFloat("Vehicles Render distance", &ud::vehiclesrender, 0.f, 150.f);
                        ImGui::SetCursorPos(ImVec2(445, 425));
                        ImGui::SliderFloat("Loot Render distance", &ud::pickupsrender, 0.f, 150.f);
                    }

                    ImGui::EndChild();
                }
                ImGui::PopStyleVar();

                int tab4alpha = Animate("Tab4", "Tab4", tabs == 4, 255, 40.f, INTERP);
                tab4alpha = ImClamp(tab4alpha, 0, 255);
                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab4alpha / 255.f);
                if (tabs == 4)
                {
                    ImGui::SetCursorPos(ImVec2(200, 30));
                    ImGui::BeginChild("Child4", ImVec2(570, 495), false, ImGuiWindowFlags_NoMove);

                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.06f, 0.06f, 0.06f, 0.500f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.06f, 0.06f, 0.06f, 0.700f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.06f, 0.06f, 0.06f, 0.800f));

                    ImGui::SetCursorPos(ImVec2(15, 40));
                    ImGui::BeginGroup();

                    ImGui::Checkbox("Ignore Dead", &ud::bIgnoreDead);
                    ImGui::Checkbox("Debug Info", &ud::u_debug);
                    ImGui::Checkbox("Weapon Rarity", &ud::u_weapon_rarity);
                    ImGui::Checkbox("Outlined Esp", &ud::u_outline);
                    ImGui::Checkbox("Head Circle", &ud::u_head);
                    ImGui::Checkbox("Loot Text Outlined", &ud::u_textoutline);
                    ImGui::SetCursorPos(ImVec2(445, 245));
                    ImGui::SliderInt(E("Skeleton Thickness"), &ud::u_skeleton_thick, 0.f, 5);
                    ImGui::SetCursorPos(ImVec2(445, 280));
                    ImGui::SliderInt(E("Box Thickness"), &ud::u_box_thick, 0.f, 5);
                    ImGui::SetCursorPos(ImVec2(445, 315));
                    ImGui::SliderInt(E("Line Thickness"), &ud::u_line_thick, 0.f, 5);
                    ImGui::SetCursorPos(ImVec2(445, 350));
                    ImGui::SliderInt(E("Head Circle Size"), &ud::u_head_size, 0.f, 50);
               
                    ImGui::EndGroup();

                    ImGui::PopStyleColor(3);

                    ImGui::EndChild();
                }
                ImGui::PopStyleVar();

               /* int tab5alpha = Animate("Tab0", "Tab0", tabs == 5, 255, 40.f, INTERP);
                tab5alpha = ImClamp(tab5alpha, 0, 255);
                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab5alpha / 255.f);
                if (tabs == 5)
                {
                    ImGui::SetCursorPos(ImVec2(200, 30));
                    ImGui::BeginChild("Child5", ImVec2(570, 495), false, ImGuiWindowFlags_NoMove);

                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.06f, 0.06f, 0.06f, 0.500f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.06f, 0.06f, 0.06f, 0.700f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.06f, 0.06f, 0.06f, 0.800f));
                    ImGui::SetCursorPos(ImVec2(15, 40));
                    ImGui::BeginGroup();
                    ImGui::Text("Cheat version -> 1.2.");
                    ImGui::Text("[+] Fixed Fov.");
                    ImGui::Text("[+] More secure loader and faster.");
                    ImGui::Text("[+] New mapping section in memory.");
                    ImGui::Text("[+] New driver.");
                    

                    ImGui::EndGroup();

                    ImGui::EndChild();
                }
                ImGui::PopStyleVar();*/
                int tab5alpha = Animate("Tab5", "Tab5", tabs == 5, 255, 40.f, INTERP);
                tab5alpha = ImClamp(tab5alpha, 0, 255);
                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab5alpha / 255.f);
                if (tabs == 5)
                {
                    ImGui::SetCursorPos(ImVec2(200, 30));
                    ImGui::BeginChild("Child5", ImVec2(570, 495), false, ImGuiWindowFlags_NoMove);

                    //functions for the demo
                    static bool streamproof = false;
                    static bool debug = false;
                    static int config = 0;

                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.06f, 0.06f, 0.06f, 0.500f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.06f, 0.06f, 0.06f, 0.700f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.06f, 0.06f, 0.06f, 0.800f));

                    ImGui::SetCursorPos(ImVec2(15, 40));
                    ImGui::BeginGroup();

                    ImGui::Text("Cheat version -> 1.2.");
                    ImGui::Text("[+] Fixed Fov.");
                    ImGui::Text("[+] More secure loader and faster.");
                    ImGui::Text("[+] New mapping section in memory.");
                    ImGui::Text("[+] New driver.");
                    ImGui::Text("[+] World esp disabled.");

                    ImGui::EndGroup();

                    ImGui::PopStyleColor(3);

                    ImGui::EndChild();
                }
                ImGui::PopStyleVar();

                ImGui::End();

            }
        }


        auto draw( ) -> void {

            ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 0.f);

            ImGui::StyleColorsDark();


            ImGui_ImplDX11_NewFrame( );
            ImGui_ImplWin32_NewFrame( );
            ImGui::NewFrame( );

            u_main -> actor_loop( );
            u_main -> LevelDrawing( );

            menu( );

            ImGui::Render( );
            const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
            d3d_device_ctx->OMSetRenderTargets(1, &d3d_render_target, nullptr);
            d3d_device_ctx->ClearRenderTargetView(d3d_render_target, clear_color_with_alpha);
            ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

            d3d_swap_chain->Present(1, 0);

        }

        auto render( ) -> bool {
            SPOOF_FUNC

            static RECT rect_og;
            MSG msg = { NULL };
            ZeroMemory(&msg, sizeof(MSG));

            while (msg.message != WM_QUIT)
            {

                UpdateWindow_Spoofed(window_handle);
                ShowWindow_Spoofed(window_handle, SW_SHOW);

                if (PeekMessageA_Spoofed(&msg, window_handle, 0, 0, PM_REMOVE))
                {
                    TranslateMessage_Spoofed(&msg);
                    DispatchMessage(&msg);
                }

                ImGuiIO& io = ImGui::GetIO();
                io.ImeWindowHandle = window_handle;
                io.DeltaTime = 1.0f / 60.0f;


                POINT p_cursor;
                GetCursorPos(&p_cursor);
                io.MousePos.x = p_cursor.x;
                io.MousePos.y = p_cursor.y;

                if (GetAsyncKeyState_Spoofed(VK_LBUTTON)) {
                    io.MouseDown[0] = true;
                    io.MouseClicked[0] = true;
                    io.MouseClickedPos[0].x = io.MousePos.x;
                    io.MouseClickedPos[0].x = io.MousePos.y;
                }
                else
                    io.MouseDown[0] = false;

                draw();

            }
            ImGui_ImplDX11_Shutdown( );
            ImGui_ImplWin32_Shutdown( );
            ImGui::DestroyContext( );

            DestroyWindow(window_handle);

            return true;

        }

    };
} static n_render::c_render* render = new n_render::c_render();