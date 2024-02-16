#include <mutex>
namespace ud
{


	inline inline bool u_aimbot = 1;

	inline inline bool bIgnoreDead = 0;

	inline inline bool u_enemies = 1;


	inline inline int radartype = 0;
	inline inline int radarsize = 150;

	inline inline bool u_debug = 0;

	inline inline bool u_debugd = 0;


	inline inline bool u_ignore_downed = 1;

	inline inline bool u_ignore_bots = 0;

	inline inline bool u_visible_check = 1;

	inline inline bool u_line = 0;

	inline int u_line_type = 0;

	inline inline bool lamma = 0;

	inline inline bool pickups = 0;

	inline inline bool u_textoutline = 0;

	inline inline bool uddev1 = 0;

	inline int u_lastlooptime = 150;

	inline int u_lastloopworldtime = 1;

	inline inline bool enable_world_visuals = 0;

	inline inline bool draw_chests = 0;

	inline inline bool draw_ammobox = 0;

	inline inline bool draw_loot = 0;

	inline inline bool draw_vehicles = 0;

	inline inline float lootdelay = 1;

	inline inline float loot_render_distance = 300;

	inline inline float chestrender = 100;

	inline inline float vehiclesrender = 100;

	inline inline float ammoboxrender = 100;

	inline inline float pickupsrender = 100;

	inline inline float lammarender = 100;

	inline inline bool UnCommon = 1;

	inline inline bool items = 1;

	inline inline bool rare = 1;

	inline inline bool purple = 1;

	inline inline bool gold = 1;

	inline inline bool mythic = 1;

	inline inline bool Common = 1;

	inline float u_aimfov = 100;

	inline int u_hitbox = 0;

	inline bool u_prediction = 0;


	inline inline bool u_target_line;

	inline inline bool u_skeleton = 0;

	inline bool u_box_esp = 1;
	inline bool u_enable_esp = 1;

	inline bool u_distance = 1;

	inline bool u_username = 0;

	inline bool u_head = 0;

	inline int u_head_size = 15;

	inline bool u_snapline = 0;

	inline bool u_weapon_cfg = 0;

	inline bool dev2 = 0;

	inline bool dev = 0;

	inline bool dev4 = 0;

	inline bool dev3 = 0;
	static float u_color_Visible[3] = { 87 / 255.0f, 173 / 255.0f, 17 / 255.0f };
	static float u_color_invisible[3] = { 173 / 255.0f, 17 / 255.0f, 17 / 255.0f };
	static float u_color[3] = { 1.00f, 1.00f, 1.00f };

	
	static int u_color_fov[3] = { 1.00f, 1.00f, 1.00f };

	float u_render_distance = 275;

	inline bool u_view_angle = 0;

	inline bool u_weapon_esp = 0;

	inline bool u_teamid = 0;

	inline int u_box_type = 0;

	inline bool u_outline = 1;

	inline int u_box_thick = 2;

	inline int u_line_thick = 2;


	inline int u_skeleton_thick = 1;

	inline float u_aim_max_dist = 275;

	inline float u_smooth = 6;

	inline bool u_render_fov = 1;

	inline bool u_weapon_rarity = 0;

	inline bool u_render_crosshair = 0;

	inline bool u_render_menu = 0;

	inline bool u_shotguns_only = 1;

	inline bool u_ignore_keybind = 0;

	inline int u_aim_key = VK_RBUTTON;

	inline bool in_lobby;

	inline bool u_triggerbot = 1;
	inline float u_maximum_distance = 50;
	inline float u_custom_delay = 1;

	inline bool u_streamproof;
}

namespace rifle
{

	inline bool aimbot = 1;
	inline bool ignore_downed = 1;
	inline bool ignore_bots = 0;
	inline bool visible_check = 1;
	inline bool target_line = 0;
	inline float aim_fov = 15;
	inline float smooth = 3;
	inline int hitbox = 0;
	inline int aimkey;
}

namespace shotgun
{

	inline bool aimbot = 1;
	inline bool ignore_downed = 1;
	inline bool ignore_bots = 0;
	inline bool visible_check = 1;
	inline bool target_line = 0;
	inline float aim_fov = 15;
	inline float smooth = 3;
	inline int hitbox = 0;
	inline int aimkey;



}

namespace smg
{

	inline bool aimbot = 1;
	inline bool ignore_downed = 1;
	inline bool ignore_bots = 0;
	inline bool visible_check = 1;
	inline bool target_line = 0;
	inline 	float aim_fov = 15;
	inline 	float smooth = 3;
	inline int hitbox = 0;
	inline int aimkey;


}

namespace sniper
{
	inline bool aimbot = 1;
	inline bool ignore_downed = 1;
	inline bool ignore_bots = 0;
	inline bool visible_check = 1;
	inline bool target_line = 0;
	inline	float aim_fov = 15;
	inline float smooth = 3;
	inline int hitbox = 0;
	inline int aimkey;
}
