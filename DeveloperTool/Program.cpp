#include "SDK/PluginSDK.h"
#include "SDK/EventHandler.h"
#include "SDK/clipper.hpp"
#include "SDK/EventArgs.h"
#include "SDK/Geometry.h"
#include "SDK/PluginSDK_Enums.h"
#include "SDK/Vector.h"
#include "Main.h"

//Plugin Definitions
PLUGIN_API const char PLUGIN_PRINT_NAME[32] = "DeveloperTool";
PLUGIN_API const char PLUGIN_PRINT_AUTHOR[32] = "xDreamms";
PLUGIN_API ChampionId PLUGIN_TARGET_CHAMP = ChampionId::Unknown;

PLUGIN_API bool OnLoadSDK(IPluginsSDK* plugin_sdk)
{
	DECLARE_GLOBALS(plugin_sdk);
	MainSpace::Main::Load();
	return true;
}
PLUGIN_API void OnUnloadSDK()
{
	MainSpace::Main::UnLoad();
}
