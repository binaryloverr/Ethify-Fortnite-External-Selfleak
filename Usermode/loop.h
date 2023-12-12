#include <list>
#include <string>
#include "offsets.h"
#include "ue.h"
#include <string.h>
#include "xorst.h"
#include "fname.h"
#include <iostream>

#define debug_cache  false
#define debug_loot false
#define debug_calls false
#define debug_weapons  false

inline bool u_has_clicked;
std::chrono::steady_clock::time_point u_tb_begin;
std::chrono::steady_clock::time_point u_tb_end;
inline 	int u_tb_time_since;

int HeldWeaponType;

HWND window;
;

enum EFortWeaponType : int
{
	Rifle = 0,
	Shotgun = 1,
	Smg = 2,
	Sniper = 3
};

uintptr_t RootComponent ( uintptr_t actor )
{
	SPOOF_FUNC;
	return driver_rq->read <uintptr_t> ( actor + offset::root_component );
}
fvector GetLocation ( uintptr_t actor )
{
	SPOOF_FUNC;
	return driver_rq->read <fvector> ( RootComponent ( actor ) + offset::relative_location );
}

char* wchar_to_char(const wchar_t* pwchar)
{
	int currentCharIndex = 0;
	char currentChar = pwchar[currentCharIndex];

	while (currentChar != '\0')
	{
		currentCharIndex++;
		currentChar = pwchar[currentCharIndex];
	}

	const int charCount = currentCharIndex + 1;

	char* filePathC = (char*)malloc(sizeof(char) * charCount);

	for (int i = 0; i < charCount; i++)
	{
		char character = pwchar[i];

		*filePathC = character;

		filePathC += sizeof(char);

	}
	filePathC += '\0';

	filePathC -= (sizeof(char) * charCount);

	return filePathC;
}

namespace u_loop {
	class u_fn	 {
	public:

		auto get_player_name ( uintptr_t player_state ) -> std::string
		{
			SPOOF_FUNC
			if ( debug_calls )
			{
				std::cout << E ( "Name Esp" ) << std::endl;
			}
			int pNameLength; 
			_WORD* pNameBufferPointer;
			int i;     
			char v25; 
			int v26;  
			int v29; 

			char16_t* pNameBuffer;

				uintptr_t pNameStructure = driver_rq->read <uintptr_t> ( player_state + 0xAE8 ); //pNameStructure
				if ( is_valid ( pNameStructure ) ) {
					pNameLength = driver_rq->read <int> ( pNameStructure + 0x10 );
					if ( pNameLength <= 0)
						return "BOT";

					pNameBuffer = new char16_t[ pNameLength ];
					uintptr_t pNameEncryptedBuffer = driver_rq->read <uintptr_t> ( pNameStructure + 0x8 );
					if ( is_valid ( pNameEncryptedBuffer ) ) {
						driver_rq->read_array ( pNameEncryptedBuffer, pNameBuffer, pNameLength );

						v25 = pNameLength - 1;
						v26 = 0;
						pNameBufferPointer = ( _WORD* ) pNameBuffer;

						for ( i = ( v25 ) & 3;; *pNameBufferPointer++ += i & 7 ) {
							v29 = pNameLength - 1;
							if ( ! ( _DWORD ) pNameLength )
								v29 = 0;

							if ( v26 >= v29 )
								break;

							i += 3;
							++v26;
						}

						std::u16string temp_wstring ( pNameBuffer );
						delete[] pNameBuffer;
						return std::string ( temp_wstring.begin( ), temp_wstring.end( ) );
					}
				}
		}

		  //no loot esp for pasters

		camera_position_s get_camera( )
		{
			SPOOF_FUNC

			camera_position_s camera;

			auto location_pointer = driver_rq->read <uintptr_t> ( ud_cache->uworld + 0x110 );
			auto rotation_pointer = driver_rq->read <uintptr_t> ( ud_cache->uworld + 0x120 );

			struct FNRot
			{
				double a; //0x0000
				char pad_0008[24]; //0x0008
				double b; //0x0020
				char pad_0028[424]; //0x0028
				double c; //0x01D0
			} fnRot;

			fnRot.a = driver_rq->read <double> ( rotation_pointer );
			fnRot.b = driver_rq->read <double> ( rotation_pointer + 0x20 );
			fnRot.c = driver_rq->read <double> ( rotation_pointer + 0x1d0 ) ;

			camera.location = driver_rq->read <fvector> ( location_pointer );
			camera.rotation.x = asin ( fnRot.c ) * ( 180.0 / M_PI );
			camera.rotation.y = ( ( atan2 (fnRot.a * -1, fnRot.b ) * ( 180.0 / M_PI ) ) * -1 ) * -1;
			camera.fov = driver_rq->read <float> ( ( uintptr_t ) ud_cache->player_controller + 0x394 ) * 90.f;

			return camera;
		}

		inline fvector2d w2s( fvector WorldLocation )
		{
			SPOOF_FUNC
				if ( debug_calls )
				{
					std::cout << E ( "Calling W2S" ) << std::endl;
				}

			camera_postion = get_camera( );

			if ( WorldLocation.x == 0 )
				return fvector2d ( 0, 0 );

			_MATRIX tempMatrix = Matrix ( camera_postion.rotation );

			fvector vAxisX = fvector ( tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2] );
			fvector vAxisY = fvector ( tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2] );
			fvector vAxisZ = fvector ( tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2] );

			fvector vDelta = WorldLocation - camera_postion.location;
			fvector vTransformed = fvector ( vDelta.dot ( vAxisY ), vDelta.dot ( vAxisZ ), vDelta.dot ( vAxisX ) );

			if ( vTransformed.z < 1.f )
				vTransformed.z = 1.f;

			return fvector2d ( ( screen_width / 2.0f ) + vTransformed.x * ( ( ( screen_width / 2.0f ) / tanf ( camera_postion.fov * ( float)M_PI / 360.f ) ) ) / vTransformed.z, ( screen_height / 2.0f ) - vTransformed.y * ( ( ( screen_width / 2.0f ) / tanf ( camera_postion.fov * ( float ) M_PI / 360.f ) ) ) / vTransformed.z );
		}

		static auto is_visible( uintptr_t skeletal_mesh ) -> bool {
			SPOOF_FUNC
			if ( debug_calls )
			{
				std::cout << E ( "Calling Visible Check" ) << std::endl;
			}
			auto last_submit = driver_rq->read <float> ( skeletal_mesh + 0x358 ); //lastsumbittime
			auto last_render = driver_rq->read <float> ( skeletal_mesh + 0x360 ); //lastrendertimeonscreen
			return ( bool ) ( last_render + 0.06f >= last_submit );

		}

		auto in_screen( fvector2d screen_location ) -> bool {

			if ( screen_location.x > 0 && screen_location.x < screen_width && screen_location.y > 0 && screen_location.y < screen_height ) return true;
			else return false;

		}

		fvector get_bone_3d(uintptr_t skeletal_mesh, int index) const {

			SPOOF_FUNC

			if ( debug_calls )
			{
				std::cout << E ( "Calling Get Bone" ) << std::endl;
			}
			if ( ! ( uintptr_t ) this) return {};

			int is_cached = driver_rq->read <int> ( skeletal_mesh + 0x650); //bone cache
			auto bone_transform = driver_rq->read <FTransform> (driver_rq->read <u> ( skeletal_mesh + 0x10 * is_cached + 0x608) + 0x60 * index ); //bone array

			FTransform ComponentToWorld = driver_rq->read <FTransform> ( skeletal_mesh + 0x230 );

			D3DMATRIX Matrix =  { };
			Matrix = MatrixMultiplication( bone_transform.ToMatrixWithScale( ), ComponentToWorld.ToMatrixWithScale( ) );

			return fvector( Matrix._41, Matrix._42, Matrix._43 );
		}

		//no loot esp go kys

		fvector2d head;
		fvector2d root;
		fvector2d pelvis;
		fvector2d left_shoulder;
		fvector2d left_elbow;
		fvector2d left_hand;
		fvector2d right_shoulder;
		fvector2d neck;

		fvector2d right_elbow;
		fvector2d right_hand;
		fvector2d left_knee;
		fvector2d left_foot;
		fvector2d right_knee;
		fvector2d right_foot;

		
		auto cache_entities( ) -> void {

			temporary_entity_list.clear ( );

			ud_cache -> uworld = driver_rq->read <uintptr_t> ( driver_rq->image_base + offset::uworld );
			ud_cache -> game_instance = driver_rq->read <uintptr_t> ( ud_cache -> uworld + offset::game_instance );
			ud_cache -> local_player = driver_rq->read <uintptr_t> (driver_rq->read <uintptr_t>( ud_cache -> game_instance + offset::local_player ) );
			ud_cache -> player_controller = driver_rq->read <uintptr_t> ( ud_cache -> local_player + offset::player_controller );
			ud_cache -> acknowledged_pawn = driver_rq->read <uintptr_t> ( ud_cache -> player_controller + offset::acknowledged_pawn );
			ud_cache -> skeletal_mesh = driver_rq->read <uintptr_t> ( ud_cache -> acknowledged_pawn + offset::skeletal_mesh );
			ud_cache -> player_state = driver_rq->read <uintptr_t> ( ud_cache -> acknowledged_pawn + offset::player_state );
			ud_cache -> root_component = driver_rq->read <uintptr_t> ( ud_cache -> acknowledged_pawn + offset::root_component );
			ud_cache -> relative_location = driver_rq->read <fvector> ( ud_cache -> root_component + offset::relative_location );
			ud_cache -> team_index = driver_rq->read <int> ( ud_cache -> player_state + offset::team_index );

			if ( debug_cache )
			{
				std::cout << E ( " uworld -> " ) << ud_cache -> uworld << std::endl;
				std::cout << E ( " game_instance -> " ) << ud_cache -> game_instance << std::endl;
				std::cout << E ( " local_player -> " ) << ud_cache -> local_player << std::endl;
				std::cout << E ( " player_controller -> " ) << ud_cache -> player_controller << std::endl;
				std::cout << E ( " acknowledged_pawn -> " ) << ud_cache -> acknowledged_pawn << std::endl;
				std::cout << E ( " skeletal_mesh -> " ) << ud_cache -> skeletal_mesh << std::endl;
				std::cout << E ( " player_state -> " ) << ud_cache -> player_state << std::endl;
				std::cout << E ( " root_component -> " ) << ud_cache -> root_component << std::endl;
				std::cout << E ( " relative_location.X -> " ) << ud_cache -> relative_location.x << std::endl;
				std::cout << E ( " relative_location.Y -> " ) << ud_cache -> relative_location.y << std::endl;
				std::cout << E ( " relative_location.Z -> " ) << ud_cache -> relative_location.z << std::endl;
				std::cout << E ( " team_index -> " ) << ud_cache -> team_index << std::endl;
			}

			if ( !ud_cache->acknowledged_pawn )
			{
				ud::in_lobby = true;
			}
			else
			{
				ud::in_lobby = false;
			}
	
			if ( ud_cache->acknowledged_pawn ) {

				if  ( ud::u_weapon_cfg )
				{		
					uint64_t player_weapon = driver_rq->read <uint64_t> ( ud_cache -> acknowledged_pawn + 0xA20); // 	struct AFortWeapon* CurrentWeapon;

					if ( is_valid ( player_weapon ) ) {
					
						uint64_t weapon_data = driver_rq->read <uint64_t> ( player_weapon + 0x4a8);	//struct UFortWeaponItemDefinition* WeaponData;

						if ( is_valid( weapon_data ) ) {

							uint64_t ftext_ptr = driver_rq->read <uint64_t> ( weapon_data + 0x90 );

							if (is_valid ( ftext_ptr ) ) {
								uint64_t ftext_data = driver_rq->read <uint64_t> ( ftext_ptr + 0x28 );
								int ftext_length = driver_rq->read <int> ( ftext_ptr + 0x30 );
								if ( ftext_length > 0 && ftext_length < 50 ) {
									wchar_t* ftext_buf = new wchar_t[ ftext_length ];
									driver_rq->read1 ( ftext_data, ftext_buf, ftext_length * sizeof ( wchar_t ) );

									wchar_t* WeaponName = ftext_buf;

									delete[] ftext_buf;

									if ( wcsstr(WeaponName, E ( L"Assault Rifle")) || wcsstr ( WeaponName, E ( L"Havoc Suppressed Assault Rifle" ) ) || wcsstr ( WeaponName, E ( L"Red-Eye Assault Rifle" ) )
										|| wcsstr(WeaponName, E ( L"Suppressed Assault Rifle" ) ) || wcsstr ( WeaponName, E ( L"Striker Burst Rifle" ) ) || wcsstr ( WeaponName, E ( L"Burst Assault Rifle" ) )
										|| wcsstr(WeaponName, E ( L"Ranger Assault Rifle" ) ) || wcsstr ( WeaponName, E ( L"Flapjack Rifle" ) ) || wcsstr ( WeaponName, E ( L"Heavy Assault Rifle"))
										|| wcsstr(WeaponName, E ( L"MK-Seven Assault Rifle" ) ) || wcsstr ( WeaponName, E ( L"MK-Alpha Assault Rifle" ) ) || wcsstr ( WeaponName, E ( L"Combat Assault Rifle" ) )
										|| wcsstr(WeaponName, E(L"Nemesis AR")) || wcsstr(WeaponName, E(L"Ambush Striker AR")) || wcsstr(WeaponName, E(L"Striker AR"))
										|| wcsstr(WeaponName, E ( L"Tactical Assault Rifle" ) ) || wcsstr ( WeaponName, E ( L"Hammer Assault Rifle" ) ) || wcsstr ( WeaponName, E ( L"Sideways Rifle")) || wcsstr ( WeaponName, E ( L"Makeshift Rifle" ) ) || wcsstr(WeaponName, E(L"Drum Gun"))) {
										HeldWeaponType = EFortWeaponType::Rifle;
										ud::u_aimbot = rifle::aimbot;
										ud::u_visible_check = rifle::visible_check;
										ud::u_ignore_downed = rifle::ignore_downed;
										ud::u_ignore_bots = rifle::ignore_bots;
										ud::u_target_line = rifle::target_line;
										ud::u_aimfov = rifle::aim_fov;
										ud::u_smooth = rifle::smooth;
										ud::u_hitbox = rifle::hitbox;
										aimkey = rifle::aimkey;
										if ( debug_weapons )
										{
											std::cout << E ( "RIFLE HELD" ) << std::endl;
										}
									}
									if ( wcsstr ( WeaponName, E ( L"Shotgun" ) ) || wcsstr(WeaponName, E(L"Frenzy Auto Shotgun")) || wcsstr(WeaponName, E(L"Iron Warrior Hammer Pump Shogtun")) ) {
										HeldWeaponType = EFortWeaponType::Shotgun;
										ud::u_aimbot = shotgun::aimbot;
										ud::u_visible_check = shotgun::visible_check;
										ud::u_ignore_downed = shotgun::ignore_downed;
										ud::u_ignore_bots = shotgun::ignore_bots;
										ud::u_target_line = shotgun::target_line;
										ud::u_aimfov = shotgun::aim_fov;
										ud::u_smooth = shotgun::smooth;
										ud::u_hitbox = shotgun::hitbox;
										aimkey = shotgun::aimkey;
										if ( debug_weapons )
										{
											std::cout << E ( "SHOTGUN HELD" ) << std::endl;
										}
									}
									if ( wcsstr ( WeaponName, E ( L"Smg" ) ) || wcsstr(WeaponName, E(L"Ambush Hyper SMG")) || wcsstr ( WeaponName, E ( L"Submachine Gun" ) ) || wcsstr ( WeaponName, E ( L"Combat Smg" ) ) || wcsstr(WeaponName, E ( L"Pistol" ) ) || wcsstr(WeaponName, E( L"Machine Smg") )
										|| wcsstr ( WeaponName, E ( L"Scoped Burst SMG" ) ) || wcsstr(WeaponName, E(L"Hyper SMG")) || wcsstr(WeaponName, E(L"Thunger Burst SMG")) ) {
										HeldWeaponType = EFortWeaponType::Smg;
										ud::u_aimbot = smg::aimbot;
										ud::u_visible_check = smg::visible_check;
										ud::u_ignore_downed = smg::ignore_downed;
										ud::u_ignore_bots = smg::ignore_bots;
										ud::u_target_line = smg::target_line;
										ud::u_aimfov = smg::aim_fov;
										ud::u_smooth = smg::smooth;
										ud::u_hitbox = smg::hitbox;
										aimkey = smg::aimkey;
										if ( debug_weapons )
										{
											std::cout << E ( "SMG HELD" ) << std::endl;
										}
									}
									if ( wcsstr ( WeaponName, E ( L"Hunting Rifle" ) ) || wcsstr (WeaponName, E (L"Heavy Sniper Rifle" ) ) || wcsstr( WeaponName, E ( L"Suppressed Sniper Rifle" ) )
										|| wcsstr ( WeaponName, E ( L"Storm Scout" ) ) || wcsstr ( WeaponName, E ( L"Bolt-Action Sniper Rifle") ) || wcsstr( WeaponName, E ( L"Automatic Sniper Rifle" ) )
										|| wcsstr ( WeaponName, E ( L"DMR" ) ) || wcsstr ( WeaponName, E ( L"Thermal DMR" ) ) || wcsstr ( WeaponName, E ( L"Hunter Bolt-Action Sniper" ) )
										|| wcsstr(WeaponName, E(L"Reaper Sniper Rifle")) || wcsstr(WeaponName, E(L"Semi-Auto Sniper Rifle"))
										|| wcsstr ( WeaponName, E ( L"Crossbow" ) ) || wcsstr ( WeaponName, E ( L"Mechanical Bow" ) ) || wcsstr ( WeaponName, E ( L"Hand Cannon" ) ) ) {
										HeldWeaponType = EFortWeaponType::Sniper;
										ud::u_aimbot = sniper::aimbot;
										ud::u_visible_check = sniper::visible_check;
										ud::u_ignore_downed = sniper::ignore_downed;
										ud::u_ignore_bots = sniper::ignore_bots;
										ud::u_target_line = sniper::target_line;
										ud::u_aimfov = sniper::aim_fov;
										ud::u_smooth = sniper::smooth;
										ud::u_hitbox = sniper::hitbox;
										aimkey = sniper::aimkey;
										if ( debug_weapons )
										{
											std::cout << E( "SNIPER HELD" ) << std::endl;
										}
									}
								}
							}
						}
					}
				}
			}

			ud_cache -> game_state = driver_rq->read <uintptr_t> ( ud_cache -> uworld + offset::game_state );
			ud_cache -> player_array = driver_rq->read <uintptr_t> ( ud_cache -> game_state + offset::player_array );
			ud_cache -> player_array_size = driver_rq->read <int> ( ud_cache -> game_state + ( offset::player_array + sizeof ( uintptr_t ) ) );

			for ( int i = 0; i < ud_cache -> player_array_size; ++i ) {
				auto player_state = driver_rq->read <uintptr_t> ( ud_cache -> player_array + (i * sizeof ( uintptr_t ) ) );
				auto current_actor = driver_rq->read <uintptr_t> ( player_state + offset::pawn_private );

				auto root_component = driver_rq->read <uintptr_t> ( current_actor + offset::root_component );

				auto relative_location = driver_rq->read <fvector> ( root_component + offset::relative_location) ;

				auto pawn_private = driver_rq->read <uintptr_t>(player_state + 0x308);

				fvector2d screen_location;
				screen_location = w2s ( relative_location );
				if ( !in_screen ( screen_location ) ) continue;


				auto skeletalmesh = driver_rq->read <uintptr_t> ( current_actor + offset::skeletal_mesh );

				auto is_despawning = ( driver_rq->read <char> ( current_actor + 0x93a) >> 3 );

			

				auto team_index = driver_rq->read <int> ( player_state + offset::team_index );
				if ( ud_cache -> team_index == team_index && ud_cache -> acknowledged_pawn ) continue;

				if (ud::bIgnoreDead) {
					bool bIsDyingasd = ( driver_rq->read <BYTE> ( pawn_private + 0x758) & 0x10 );
					bool isDBNO = ( driver_rq->read <BYTE> ( pawn_private + 0x93a) >> 4) & 1; // 
					if (isDBNO || bIsDyingasd)
						continue;
				}

				entity cached_actors{ };
				cached_actors.entity = current_actor;
				cached_actors.skeletal_mesh = skeletalmesh;
				cached_actors.root_component = root_component;
				cached_actors.relative_location = relative_location;
				cached_actors.player_state = player_state;
				cached_actors.team_index = team_index;

				temporary_entity_list.push_back( cached_actors );
			}

			entity_list.clear( );
			entity_list = temporary_entity_list;
			std::this_thread::sleep_for ( std::chrono::milliseconds ( ud::u_lastlooptime) );

		}

		fvector2d head_box;
		fvector2d root_box;
		fvector2d root_box1;

		auto actor_loop( ) -> void {
			ImGui::PushFont( GameFont );

			ImDrawList* draw_list = ImGui::GetBackgroundDrawList( );
			float target_dist = FLT_MAX;
			uintptr_t target_entity = 0;

			char fpsinfo [ 256 ];
			sprintf_s ( fpsinfo, ( E ( "ethify -> beta" ) ) );
			draw_list->AddText ( ImVec2(15, 15), ImColor( 255, 255, 255, 255 ), fpsinfo );

			const float centerWidth = screen_width / 2;
			const float centerHeight = screen_height / 2;

			for ( auto& cached : entity_list ) {
				auto root_bone = get_bone_3d ( cached.skeletal_mesh, EBoneIndex::Root );
				root = w2s ( root_bone );

				root_box = w2s ( fvector ( root_bone.x, root_bone.y, root_bone.z + 30 ) );

				root_box1 = w2s ( fvector( root_bone.x, root_bone.y, root_bone.z - 15 ) );

				auto head_bone = get_bone_3d ( cached.skeletal_mesh, EBoneIndex::Head );
				head = w2s ( head_bone );
				head_box = w2s ( fvector ( head_bone.x, head_bone.y, head_bone.z + 15 ) );



				float box_height = abs ( head.y - root_box1.y );
				float box_width = box_height * 0.35f;
				float distance = ud_cache->relative_location.distance ( root_bone ) / 100;
	
				if ( distance > ud::u_render_distance && ud_cache->acknowledged_pawn ) continue;
				
				if ( ud::u_aimbot ) {

					auto dx = head.x - ( screen_width / 2 );
					auto dy = head.y - ( screen_height / 2 );
					auto dist = sqrtf ( dx * dx + dy * dy );

					if ( ud::u_visible_check ) {
						if ( is_visible ( cached.skeletal_mesh ) ) {
							if ( dist < ud::u_aimfov && dist * 10 < target_dist ) {
							
								target_dist = dist;
								target_entity = cached.entity;
							}
						}
					}
					else {
						if ( dist < ud::u_aimfov && dist * 10 < target_dist ) {
				
							target_dist = dist;
							target_entity = cached.entity;
						}
					}
				}

				if (ud::u_render_fov) {

					ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(screen_width / 2, screen_height / 2), ud::u_aimfov, ImColor(0, 0, 0), 64, 3);
					ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(screen_width / 2, screen_height / 2), ud::u_aimfov, ImColor(255, 255, 255), 64, 1);
				}
				

				ImColor vis;
				ImColor invis;
				ImColor normal;

				vis = ImVec4 ( ud::u_color_Visible[0], ud::u_color_Visible[1], ud::u_color_Visible[2], 1.0f );
				invis = ImVec4 ( ud::u_color_invisible[0], ud::u_color_invisible[1], ud::u_color_invisible[2], 1.0f );
				normal = ImVec4 ( ud::u_color[0], ud::u_color[1], ud::u_color[2], 1.0f );

				ImColor visibleColor;
				if ( ud::u_visible_check )
				{
					 visibleColor = is_visible ( cached.skeletal_mesh ) ? ImColor( vis ) : ImColor( invis );
				}
				else
				{
					visibleColor =  ImColor ( normal );
				}

				if ( ud::u_line )
				{
					if ( ud::u_line_type == 0 ) {
						draw_list -> AddLine ( ImVec2 ( screen_width / 2, 0 ), ImVec2( head_box.x, head_box.y ), visibleColor, ud::u_line_thick );
					}

					if ( ud::u_line_type == 1 ) {
						draw_list -> AddLine ( ImVec2 ( screen_width /2 , screen_height / 2 ), ImVec2 ( head_box.x, head_box.y ), visibleColor, ud::u_line_thick );
					}

					if ( ud::u_line_type == 2 ) {
						draw_list -> AddLine ( ImVec2 ( screen_width / 2, screen_height - 5 ), ImVec2 ( head_box.x, head_box.y ), visibleColor, ud::u_line_thick );
					}
				}
			
				if ( ud::u_box_esp && ud::u_enable_esp ) {

					if ( ud::u_box_type == 0 )
					{					
						if ( ud::u_outline )
						{
							draw_list -> AddLine ( ImVec2 ( head_box.x - ( box_width / 2 ), head_box.y ), ImVec2 ( root.x + ( box_width / 2 ), head_box.y ), ImColor ( 0, 0, 0 ), ud::u_box_thick + 2 ); 
							draw_list -> AddLine ( ImVec2 ( head_box.x - ( box_width / 2 ), head_box.y ), ImVec2 ( head_box.x - ( box_width / 2 ), root.y ), ImColor ( 0,0,0 ), ud::u_box_thick + 2 );
							draw_list -> AddLine ( ImVec2 ( head_box.x - ( box_width / 2 ), root.y ), ImVec2 ( root.x + ( box_width / 2 ), root.y ), ImColor ( 0, 0, 0 ), ud::u_box_thick + 2 ); 
							draw_list -> AddLine ( ImVec2 ( root.x + ( box_width / 2 ), head_box.y ), ImVec2 ( root.x + ( box_width / 2 ), root.y ), ImColor ( 0, 0, 0 ), ud::u_box_thick + 2 );
						}

						draw_list -> AddLine ( ImVec2 ( head_box.x - ( box_width / 2 ), head_box.y ), ImVec2 ( root.x + ( box_width / 2), head_box.y ), visibleColor, ud::u_box_thick ); 
						draw_list -> AddLine ( ImVec2 ( head_box.x - ( box_width / 2 ), head_box.y ), ImVec2 ( head_box.x - ( box_width / 2), root.y ), visibleColor, ud::u_box_thick ); 
						draw_list -> AddLine ( ImVec2 ( head_box.x -  ( box_width / 2 ), root.y ), ImVec2 ( root.x + ( box_width / 2), root.y ), visibleColor, ud::u_box_thick ); 
						draw_list -> AddLine ( ImVec2 ( root.x +  ( box_width / 2 ), head_box.y ), ImVec2 ( root.x + ( box_width / 2), root.y ), visibleColor, ud::u_box_thick ); 
					}
					else if ( ud::u_box_type == 1 ) {
						if  ( ud::u_outline )
						{
							draw_list -> AddRect ( ImVec2 ( head_box.x - box_width / 2, head_box.y ), ImVec2 ( ( head_box.x - box_width / 2 ) + box_width, head_box.y + box_height ), ImColor ( 0, 0, 0 ) , 10, ImDrawCornerFlags_All, ud::u_box_thick + 2.0 );
						}

						draw_list -> AddRect ( ImVec2 ( head_box.x - box_width / 2, head_box.y ), ImVec2 ( ( head_box.x - box_width / 2 ) + box_width, head_box.y + box_height ), visibleColor, 10, ImDrawCornerFlags_All, ud::u_box_thick );				
					}
					else if ( ud::u_box_type == 2 )
					{
						if ( ud::u_outline )
						{
							DrawCorneredBox ( root.x - ( box_width / 2 ), head_box.y, box_width, box_height, ImColor ( 0, 0, 0 ), ud::u_box_thick + 2.0, 0, 0 );
						}

						DrawCorneredBox ( root.x - ( box_width / 2 ), head_box.y, box_width, box_height, visibleColor,ud::u_box_thick, 0, 0 );
					}
				}
					if ( ud::u_weapon_esp && ud::u_enable_esp )
					{
						if ( ud_cache->acknowledged_pawn )
						{

						WeaponInformation held_weapon{ };

						uint64_t player_weapon = driver_rq->read<uint64_t>( cached.entity + 0xa20);

						if ( is_valid ( player_weapon ) ) {
							held_weapon.ammo_count = driver_rq->read <int32_t> ( player_weapon + 0xdcc);

							uint64_t weapon_data = driver_rq->read <uint64_t> ( player_weapon + 0x4a8);

							if ( is_valid ( weapon_data ) ) {
								held_weapon.tier = driver_rq->read <BYTE> ( weapon_data + 0x73 );

								uint64_t ftext_ptr = driver_rq->read <uint64_t> ( weapon_data + 0x90 );

								if ( is_valid ( ftext_ptr ) ) {
									uint64_t ftext_data = driver_rq->read <uint64_t> ( ftext_ptr + 0x28 );
									int ftext_length = driver_rq->read <int> ( ftext_ptr + 0x30 );
									if ( ftext_length > 0 && ftext_length < 50  ) {
										wchar_t* ftext_buf = new wchar_t[ ftext_length ];

										driver_rq->read1 ( ftext_data, ftext_buf, ftext_length * sizeof ( wchar_t ) );
										std::wstring wstr_buf ( ftext_buf );
										held_weapon.weapon_name = std::string( wstr_buf.begin( ), wstr_buf.end( ) );
										delete[] ftext_buf;
									}
								}

							}

							WeaponInfo = held_weapon;

							std::string final = ( "") + WeaponInfo.weapon_name + ("" );

							ImVec2 TextSize = ImGui::CalcTextSize ( final.c_str ( ) );

							ImVec2 text_size = ImGui::CalcTextSize ( final.c_str ( ) );
							int add;
							if ( ud::u_distance )
							{
								add = 25;
							}
							else
							{
								add = 5;
							}

							if ( ud::u_weapon_rarity )
							{
								if ( WeaponInfo.tier == 0 )
								{
									if ( strstr( WeaponInfo.weapon_name.c_str ( ), E ( "Pickaxe" ) ) != nullptr )
									{
										DrawString ( 16, ( root.x ) - (TextSize.x / 2), ( root.y + add ), ImColor ( 255, 255, 255 ), false, true, final.c_str ( ) );
									}
									else
									{
										std::string fina1l = ( "Building Plan" );
										ImVec2 TextSiz1e = ImGui::CalcTextSize ( fina1l.c_str ( ) );
										DrawString ( 16, ( root.x) - (TextSiz1e.x / 2 ), ( root.y + add ), ImColor ( 255, 255, 255 ), false, true, fina1l.c_str ( ) );
									}

								}
								if (WeaponInfo.tier == 1)
								{
									DrawString(18, (root.x) - (TextSize.x / 2), (root.y + add), ImColor(170, 165, 169), false, true, final.c_str());

								}
								if (WeaponInfo.tier == 2)
								{
									DrawString(18, (root.x) - (TextSize.x / 2), (root.y + add), ImColor(30, 255, 0), false, true, final.c_str());

								}
								if (WeaponInfo.tier == 3)
								{
									DrawString(18, (root.x) - (TextSize.x / 2), (root.y + add), ImColor(0, 112, 221), false, true, final.c_str());

								}
								if (WeaponInfo.tier == 4)
								{
									DrawString(18, (root.x) - (TextSize.x / 2), (root.y + add), ImColor(163, 53, 238), false, true, final.c_str());

								}
								if (WeaponInfo.tier == 5)
								{
									DrawString(18, (root.x) - (TextSize.x / 2), (root.y + add), ImColor(255, 128, 0), false, true, final.c_str());

								}
								if (WeaponInfo.tier == 6)
								{
									DrawString(18, (root.x) - (TextSize.x / 2), (root.y + add), ImColor(255, 255, 0), false, true, final.c_str());

								}
							}
							else
							{
								if (WeaponInfo.tier == 0)
								{
									if (strstr(WeaponInfo.weapon_name.c_str(), E("Pickaxe")) != nullptr)
									{
										DrawString(16, (root.x) - (TextSize.x / 2), (root.y + add), visibleColor, false, true, final.c_str());
									}
									else
									{
										std::string fina1l = ("Building Plan");
										ImVec2 TextSiz1e = ImGui::CalcTextSize(fina1l.c_str());
										DrawString(16, (root.x) - (TextSiz1e.x / 2), (root.y + add), visibleColor, false, true, fina1l.c_str());
									}
								}
								else
								{
									DrawString(16, root.x - (text_size.x / 2), root.y + 20, visibleColor, false, true, final.c_str());
								}
							}
						}

						}
					}

					if (ud::u_debug)
					{

					}


					if (ud::u_username && ud::u_enable_esp) {

						if (ud_cache->acknowledged_pawn)
						{
							std::string username_str = get_player_name(cached.player_state);
							ImVec2 text_size = ImGui::CalcTextSize(username_str.c_str());
							DrawString(16, head_box.x - (text_size.x / 2), head_box.y - 20, visibleColor, false, true, username_str.c_str());
						}
					}

					if (ud::u_teamid && ud::u_enable_esp) {

						if (ud_cache->acknowledged_pawn)
						{
							auto team_number = driver_rq->read<char>(cached.player_state + offset::team_index);

							DWORD_PTR test_platform = driver_rq->read<DWORD_PTR>(ud_cache->player_state + 0x438); 
							wchar_t platform[64];
							driver_rq->read1((uint64_t)test_platform, reinterpret_cast<PVOID>(platform), sizeof(platform));
							std::wstring balls_sus(platform);
							std::string str_platform(balls_sus.begin(), balls_sus.end());
							ImVec2 DistanceTextSize2 = ImGui::CalcTextSize(str_platform.c_str());
							ImVec2 text_size = ImGui::CalcTextSize(str_platform.c_str());
							int offset;
							if (ud::u_weapon_esp)
								offset = 30;
							else
								offset = 15;

							if (str_platform.find(("XBL")) != std::string::npos || str_platform.find(("XSX")) != std::string::npos) {
								DrawString(16, head_box.x - (text_size.x / 2), head_box.y, ImColor(128, 224, 0, 200), false, true, skCrypt("XBox"));
							}
							else if (str_platform.find(("XSX")) != std::string::npos) {
								DrawString(16, head_box.x - (text_size.x / 2), head_box.y, ImColor(128, 224, 0, 200), false, true, skCrypt("Xbox Series S/X"));						
							}
							else if (str_platform.find(("PSN")) != std::string::npos)
							{
								DrawString(16, head_box.x - (text_size.x / 2), head_box.y, ImColor(0, 96, 192, 255), false, true, skCrypt("PS4"));
							}
							else if (str_platform.find(("PS5")) != std::string::npos) {
								DrawString(16, head_box.x - (text_size.x / 2), head_box.y, ImColor(0, 96, 192, 255), false, true, skCrypt("PS5"));			
							}
							else if (str_platform.find(("WIN")) != std::string::npos) {
								DrawString(16, head_box.x - (text_size.x / 2), head_box.y, ImColor(255, 255, 255), false, true, skCrypt("Windows"));
							}
							else if (str_platform.find(("SWT")) != std::string::npos) {
								DrawString(16, head_box.x - (text_size.x / 2), head_box.y, ImColor(255, 0, 0), false, true, skCrypt("NintendoSwitch"));
							}
							else if (str_platform.find(("AND")) != std::string::npos) {
								DrawString(16, head_box.x - (text_size.x / 2), head_box.y, ImColor(255, 0, 0), false, true, skCrypt("Android"));
							}
							else if (str_platform.find(("MAC")) != std::string::npos) {
								DrawString(16, head_box.x - (text_size.x / 2), head_box.y, ImColor(255, 0, 0), false, true, skCrypt("MacOS"));
							}
							else if (str_platform.find(("LNX")) != std::string::npos) {
								DrawString(16, head_box.x - (text_size.x / 2), head_box.y, ImColor(255, 0, 0), false, true, skCrypt("Linux"));
							}
							else if (str_platform.find(("IOS")) != std::string::npos) {
								DrawString(16, head_box.x - (text_size.x / 2), head_box.y, ImColor(255, 0, 0), false, true, skCrypt("IOS"));
							}
							else {
								 DrawString(16, head_box.x - (text_size.x / 2), head_box.y, ImColor(255, 255, 255), false, true, ("IOS"));
							}
							offset -= 15;

						}
					}


					if (ud::u_head) {


					if (!ud_cache->acknowledged_pawn)
					{
							fvector2d head_2d = w2s(fvector(head_bone.x, head_bone.y, head_bone.z + 20));

							fvector delta = head_bone - camera_postion.location;
							float distance = delta.length();

							const float constant_circle_size = ud::u_head_size;

							float circle_radius = constant_circle_size * (screen_height / (2.0f * distance * tanf(camera_postion.fov * (float)M_PI / 360.f)));

							float y_offset = +70.0f;
							head_2d.y += y_offset;

							int segments = 50;
							float thickness = 2.0f;

							if (ud::u_outline)
							{
								ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(head_2d.x, head_2d.y), circle_radius, ImColor(0, 0, 0, 255), segments, ud::u_skeleton_thick + 2);
							}
							ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(head_2d.x, head_2d.y), circle_radius, visibleColor, segments, ud::u_skeleton_thick);

						}
						else
						{
							fvector2d head_2d = w2s(fvector(head_bone.x, head_bone.y, head_bone.z));

							fvector delta = head_bone - camera_postion.location;
							float distance = delta.length();

							const float constant_circle_size = ud::u_head_size;

							float circle_radius = constant_circle_size * (screen_height / (2.0f * distance * tanf(camera_postion.fov * (float)M_PI / 360.f)));

							float y_offset = +12.0f;

							int segments = 50;
							float thickness = 2.0f;
						
								if (ud::u_outline)
								{
									ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(head_2d.x, head_2d.y), circle_radius, ImColor(0, 0, 0, 255), segments, ud::u_skeleton_thick + 2);
								}
								ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(head_2d.x, head_2d.y), circle_radius, visibleColor, segments, ud::u_skeleton_thick);				
						}

					}

					if (ud::u_distance && ud::u_enable_esp) {
						std::string distance_str = (std::string)("") + std::to_string((int)distance) + (std::string)("m");
						ImVec2 text_size = ImGui::CalcTextSize(distance_str.c_str());

						DrawString(16, root.x - (text_size.x / 2), root.y + 5, visibleColor, false, true, distance_str.c_str());
					}
				

					if (ud::u_skeleton && ud::u_enable_esp) {

						pelvis = w2s(get_bone_3d(cached.skeletal_mesh, EBoneIndex::Pelvis));
						left_shoulder = w2s(get_bone_3d(cached.skeletal_mesh, EBoneIndex::LShoulder));
						left_elbow = w2s(get_bone_3d(cached.skeletal_mesh, EBoneIndex::LElbow));
						left_hand = w2s(get_bone_3d(cached.skeletal_mesh, EBoneIndex::LHand));
						right_shoulder = w2s(get_bone_3d(cached.skeletal_mesh, EBoneIndex::RShoulder));
						neck = w2s(get_bone_3d(cached.skeletal_mesh, EBoneIndex::Neck));
			
						right_elbow = w2s(get_bone_3d(cached.skeletal_mesh, EBoneIndex::RElbow));
						right_hand = w2s(get_bone_3d(cached.skeletal_mesh, EBoneIndex::RHand));
						left_knee = w2s(get_bone_3d(cached.skeletal_mesh, EBoneIndex::LKnee));
						left_foot = w2s(get_bone_3d(cached.skeletal_mesh, EBoneIndex::LFoot));
						right_knee = w2s(get_bone_3d(cached.skeletal_mesh, EBoneIndex::RKnee));
						right_foot = w2s(get_bone_3d(cached.skeletal_mesh, EBoneIndex::RFoot));
				
						if (ud::u_outline)
						{
							draw_list->AddLine(ImVec2(neck.x, neck.y), ImVec2(pelvis.x, pelvis.y), ImColor(0, 0, 0),  ud::u_skeleton_thick + 2.5);
							draw_list->AddLine(ImVec2(neck.x, neck.y), ImVec2(neck.x, neck.y), ImColor(0, 0, 0),  ud::u_skeleton_thick + 2.5);
							draw_list->AddLine(ImVec2(neck.x, neck.y), ImVec2(left_elbow.x, left_elbow.y), ImColor(0, 0, 0),  ud::u_skeleton_thick + 2.5);
							draw_list->AddLine(ImVec2(left_elbow.x, left_elbow.y), ImVec2(left_hand.x, left_hand.y), ImColor(0, 0, 0),  ud::u_skeleton_thick + 2.5);
							draw_list->AddLine(ImVec2(neck.x, neck.y), ImVec2(right_elbow.x, right_elbow.y), ImColor(0, 0, 0),  ud::u_skeleton_thick + 2.5);
							draw_list->AddLine(ImVec2(right_elbow.x, right_elbow.y), ImVec2(right_hand.x, right_hand.y), ImColor(0, 0, 0),  ud::u_skeleton_thick + 2.5);
							draw_list->AddLine(ImVec2(pelvis.x, pelvis.y), ImVec2(left_knee.x, left_knee.y), ImColor(0, 0, 0),  ud::u_skeleton_thick + 2.5);
							draw_list->AddLine(ImVec2(left_knee.x, left_knee.y), ImVec2(left_foot.x, left_foot.y), ImColor(0, 0, 0),  ud::u_skeleton_thick + 2.5);
							draw_list->AddLine(ImVec2(pelvis.x, pelvis.y), ImVec2(right_knee.x, right_knee.y), ImColor(0, 0, 0),  ud::u_skeleton_thick + 2.5);
							draw_list->AddLine(ImVec2(right_knee.x, right_knee.y), ImVec2(right_foot.x, right_foot.y), ImColor(0, 0, 0),  ud::u_skeleton_thick + 2.5);
						}

						draw_list->AddLine(ImVec2(neck.x, neck.y), ImVec2(pelvis.x, pelvis.y), visibleColor, ud::u_skeleton_thick);
						draw_list->AddLine(ImVec2(neck.x, neck.y), ImVec2(neck.x, neck.y), visibleColor, ud::u_skeleton_thick);
						draw_list->AddLine(ImVec2(neck.x, neck.y), ImVec2(left_elbow.x, left_elbow.y), visibleColor, ud::u_skeleton_thick);
						draw_list->AddLine(ImVec2(left_elbow.x, left_elbow.y), ImVec2(left_hand.x, left_hand.y), visibleColor, ud::u_skeleton_thick);
						draw_list->AddLine(ImVec2(neck.x, neck.y), ImVec2(right_elbow.x, right_elbow.y), visibleColor, ud::u_skeleton_thick);
						draw_list->AddLine(ImVec2(right_elbow.x, right_elbow.y), ImVec2(right_hand.x, right_hand.y), visibleColor, ud::u_skeleton_thick);
						draw_list->AddLine(ImVec2(pelvis.x, pelvis.y), ImVec2(left_knee.x, left_knee.y), visibleColor, ud::u_skeleton_thick);
						draw_list->AddLine(ImVec2(left_knee.x, left_knee.y), ImVec2(left_foot.x, left_foot.y), visibleColor, ud::u_skeleton_thick);
						draw_list->AddLine(ImVec2(pelvis.x, pelvis.y), ImVec2(right_knee.x, right_knee.y), visibleColor, ud::u_skeleton_thick);
						draw_list->AddLine(ImVec2(right_knee.x, right_knee.y), ImVec2(right_foot.x, right_foot.y), visibleColor, ud::u_skeleton_thick);

					}
				}
	

			if (target_entity && ud::u_aimbot) {

				auto closest_mesh = driver_rq->read<std::uint64_t>(target_entity + offset::skeletal_mesh);

				fvector hitbox;
				fvector2d hitbox_screen;

				switch (ud::u_hitbox) {
				case 0:
					hitbox_screen =	w2s(get_bone_3d(closest_mesh, EBoneIndex::Head));
					hitbox = get_bone_3d(closest_mesh, EBoneIndex::Head);;
					break;
				case 1:
					hitbox_screen =	w2s(get_bone_3d(closest_mesh, EBoneIndex::Neck));
					hitbox = get_bone_3d(closest_mesh, EBoneIndex::Neck);;
					break;
				case 2:
					hitbox_screen =	w2s(get_bone_3d(closest_mesh, EBoneIndex::Chest));
					hitbox = get_bone_3d(closest_mesh, EBoneIndex::Chest);;
					break;
				case 3:
					hitbox_screen = w2s(get_bone_3d(closest_mesh, EBoneIndex::Pelvis));
					hitbox = get_bone_3d(closest_mesh, EBoneIndex::Pelvis);;
					break;
				}

			

				if (hitbox.x != 0 || hitbox.y != 0 && (get_cross_distance(hitbox.x, hitbox.y, screen_width / 2, screen_height / 2) <= ud::u_aimfov))
				{
					if (ud::u_target_line)
						draw_list->AddLine(ImVec2(centerWidth, centerHeight), ImVec2(hitbox_screen.x, hitbox_screen.y), ImColor(255, 0, 0), 2);
	
						if (GetAsyncKeyState_Spoofed(aimkey))
							move_mouse(hitbox_screen);
		
				}

			}
			else {
				target_dist = FLT_MAX;
				target_entity = NULL;
			}
			ImGui::PopFont();
		}

	};
} static u_loop::u_fn* u_main = new u_loop::u_fn();
