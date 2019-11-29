#pragma once
#include "SDK/PluginSDK.h"
#include "SDK/EventHandler.h"
#include "SDK/clipper.hpp"
#include "SDK/EventArgs.h"
#include "SDK/Geometry.h"
#include "SDK/PluginSDK_Enums.h"
#include "SDK/Vector.h"
namespace  MainSpace
{
	class Main
	{
	public:
		static void Load();
		static void UnLoad();
	};
	void OnUpdate();
	void DrawingOnDraw();
	void CreateMainMenu();
	void CreateEvents();
	void OnProcessSpellCast(IGameObject* sender, OnProcessSpellEventArgs* args);
	void OnWndProcEvent(OnWndProcEventArgs* args);
	void GameObjectOnCreate(IGameObject* sender);
	void OnBuffUpdate(IGameObject* sender, OnBuffEventArgs* args);
	void GameObjectOnDelete(IGameObject* sender);
	void OnPlayAnimationEvent(IGameObject* sender, OnPlayAnimationEventArgs* args);
	void OnDoCastEvent(IGameObject* sender, OnProcessSpellEventArgs* args);
	
}


