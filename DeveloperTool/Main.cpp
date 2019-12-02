#include "Main.h"


namespace  MainSpace
{
	IMenu* MainMenu = nullptr;
	IMenuElement* ColorPicker = nullptr;
	IMenuElement* ObjectTeam = nullptr;
	IMenuElement* ObjectSearchRange = nullptr;
	IMenuElement* OnPLayAnimationTeam = nullptr;
	IMenuElement* OnPLayAnimationSearchRange = nullptr;
	IMenuElement* OnBuffUpdateSearchRange = nullptr;
	IMenuElement* EnabledAntiAFK = nullptr;
	
	void Main::Load()
	{
		CreateMainMenu();
		CreateEvents();
	}
	void DrawTextScr(Vector position, uint32_t color, std::string text, bool checkValue)
	{
		if (checkValue)
		{
			g_Drawing->AddTextOnScreen(Vector2(position.x,position.y), color, 20, text.c_str());
		}
	}
	void Main::UnLoad()
	{
		EventHandler<Events::GameUpdate>::RemoveEventHandler(OnUpdate);
		EventHandler<Events::OnHudDraw>::RemoveEventHandler(DrawingOnDraw);
		EventHandler<Events::OnProcessSpellCast>::RemoveEventHandler(OnProcessSpellCast);
		EventHandler<Events::OnWndProc>::RemoveEventHandler(OnWndProcEvent);
		EventHandler<Events::OnCreateObject>::RemoveEventHandler(GameObjectOnCreate);
		EventHandler<Events::OnBuff>::RemoveEventHandler(OnBuffUpdate);
		EventHandler<Events::OnDeleteObject>::RemoveEventHandler(GameObjectOnDelete);
		EventHandler<Events::OnPlayAnimation>::RemoveEventHandler(OnPlayAnimationEvent);
		EventHandler<Events::OnDoCast>::RemoveEventHandler(OnDoCastEvent);
		MainMenu->Remove();
		g_Log->Print("Developer Tool unloaded.");
	}
	std::string OnProcessSpellCastSpellName = "";
	std::string OnProcessSpellCastSpellRange = "";
	std::string OnProcessSpellCastSpellDelay = "";
	std::string OnProcessSpellCastSpellRadius = "";
	std::string OnProcessSpellCastSpellSpeed = "";
	std::string OnWndProcuMsg = "";
	std::string GameObjectOnCreateObjectName = "";
	std::string GameObjectOnCreateObjectType = "";
	std::string GameObjectOnCreateObjectPosition = "";

	std::string GameObjectOnDeleteObjectName = "";
	std::string GameObjectOnDeleteObjectType = "";
	std::string GameObjectOnDeleteObjectPosition = "";

	std::string OnBuffUpdateMyBuffNameBuffGain = "";
	std::string OnBuffUpdateMyBuffCountBuffGain = "";
	std::string OnBuffUpdateMyBuffMaxCountBuffGain = "";
	std::string OnBuffUpdateMyBuffTypeBuffGain = "";

	std::string OnBuffUpdateMyBuffNameBuffLose = "";
	std::string OnBuffUpdateMyBuffCountBuffLose = "";
	std::string OnBuffUpdateMyBuffMaxCountBuffLose = "";
	std::string OnBuffUpdateMyBuffTypeBuffLose = "";


	std::string OnBuffUpdateEnemyBuffNameBuffGain = "";
	std::string OnBuffUpdateEnemyBuffCountBuffGain = "";
	std::string OnBuffUpdateEnemyBuffMaxCountBuffGain = "";
	std::string OnBuffUpdateEnemyBuffTypeBuffGain = "";


	std::string OnBuffUpdateEnemyBuffNameBuffLose = "";
	std::string OnBuffUpdateEnemyBuffCountBuffLose = "";
	std::string OnBuffUpdateEnemyBuffMaxCountBuffLose = "";
	std::string OnBuffUpdateEnemyBuffTypeBuffLose = "";

	std::string OnPlayAnimationName = "";
	std::string OnPlayAnimationSenderName = "";

	std::string OnDoCastSpellName = "";
	std::string OnDoCastSpellSlot = "";
	std::string OnDoCastSpellRange = "";
	std::string OnDoCastSpellDelay = "";
	std::string OnDoCastSpellRadius = "";
	std::string OnDoCastSpellSpeed = "";

	

	void OnUpdate()
	{
		if (EnabledAntiAFK->GetBool() && !g_Orbwalker->IsModeActive(eOrbwalkingMode::kModeCombo)
			&& !g_Orbwalker->IsModeActive(eOrbwalkingMode::kModeHarass) 
			&& !g_Orbwalker->IsModeActive(eOrbwalkingMode::kModeLaneClear) 
			&& !g_Orbwalker->IsModeActive(eOrbwalkingMode::kModeFarm))
		   g_Orbwalker->MoveTo(g_LocalPlayer->Position());
	}

	void DrawingOnDraw()
	{
		auto pos = g_Renderer->WorldToScreen(g_LocalPlayer->Position() - 50);
		g_Drawing->AddTextOnScreen(pos, 4294901503, 20, EnabledAntiAFK->GetBool() ? "Anti AFK: Enabled" : "Anti AFK: Not Enabled");
		
		std::string cursorpos = "Cursor Position: X: " + std::to_string(g_Common->CursorPosition().x) + " Y: " + std::to_string(g_Common->CursorPosition().y) + " Z: "+
		std::to_string(g_Common->CursorPosition().z);
		DrawTextScr(Vector(100, 150), 4294901503, cursorpos, true);
		DrawTextScr(Vector(100, 170), 4294901503, "Color: " + std::to_string(ColorPicker->GetColor()), true);
		DrawTextScr(Vector(100, 190), 4294901503, OnWndProcuMsg, !OnWndProcuMsg.empty());

		DrawTextScr(Vector(100, 220), 3690987775, "OnProcessSpellCast: ", true);
		DrawTextScr(Vector(100, 240), 3690987775, "====================", true);
		DrawTextScr(Vector(100, 260), 4294901503, OnProcessSpellCastSpellName, !OnProcessSpellCastSpellName.empty());
		DrawTextScr(Vector(100, 280), 4294901503, OnProcessSpellCastSpellRange, !OnProcessSpellCastSpellRange.empty());
		DrawTextScr(Vector(100, 300), 4294901503, OnProcessSpellCastSpellDelay, !OnProcessSpellCastSpellDelay.empty());
		DrawTextScr(Vector(100, 320), 4294901503, OnProcessSpellCastSpellRadius, !OnProcessSpellCastSpellRadius.empty());
		DrawTextScr(Vector(100, 340), 4294901503, OnProcessSpellCastSpellSpeed, !OnProcessSpellCastSpellSpeed.empty());

		DrawTextScr(Vector(100, 370), 3690987775, "OnCreateObject: ", true);
		DrawTextScr(Vector(100, 390), 3690987775, "========================", true);
		DrawTextScr(Vector(100, 410), 4294901503, GameObjectOnCreateObjectName, !GameObjectOnCreateObjectName.empty());
		DrawTextScr(Vector(100, 430), 4294901503, GameObjectOnCreateObjectType, !GameObjectOnCreateObjectType.empty());
		DrawTextScr(Vector(100, 450), 4294901503, GameObjectOnCreateObjectPosition, !GameObjectOnCreateObjectPosition.empty());

		DrawTextScr(Vector(100, 480), 3690987775, "On My Buff Gain", true);
		DrawTextScr(Vector(100, 500), 3690987775, "=================", true);
		DrawTextScr(Vector(100, 520), 4294901503, OnBuffUpdateMyBuffNameBuffGain, !OnBuffUpdateMyBuffNameBuffGain.empty());
		DrawTextScr(Vector(100, 540), 4294901503, OnBuffUpdateMyBuffCountBuffGain, !OnBuffUpdateMyBuffCountBuffGain.empty());
		DrawTextScr(Vector(100, 560), 4294901503, OnBuffUpdateMyBuffMaxCountBuffGain, !OnBuffUpdateMyBuffMaxCountBuffGain.empty());
		DrawTextScr(Vector(100, 580), 4294901503, OnBuffUpdateMyBuffTypeBuffGain, !OnBuffUpdateMyBuffTypeBuffGain.empty());

		DrawTextScr(Vector(100, 610), 3690987775, "On My Buff Lose", true);
		DrawTextScr(Vector(100, 630), 3690987775, "================", true);
		DrawTextScr(Vector(100, 650), 4294901503, OnBuffUpdateMyBuffNameBuffLose, !OnBuffUpdateMyBuffNameBuffLose.empty());
		DrawTextScr(Vector(100, 670), 4294901503, OnBuffUpdateMyBuffCountBuffLose, !OnBuffUpdateMyBuffCountBuffLose.empty());
		DrawTextScr(Vector(100, 690), 4294901503, OnBuffUpdateMyBuffMaxCountBuffLose, !OnBuffUpdateMyBuffMaxCountBuffLose.empty());
		DrawTextScr(Vector(100, 710), 4294901503, OnBuffUpdateMyBuffTypeBuffLose, !OnBuffUpdateMyBuffTypeBuffLose.empty());

		DrawTextScr(Vector(100, 740), 3690987775, "On Enemy Buff Gain", true);
		DrawTextScr(Vector(100, 760), 3690987775, "=================", true);
		DrawTextScr(Vector(100, 780), 4294901503, OnBuffUpdateEnemyBuffNameBuffGain, !OnBuffUpdateEnemyBuffNameBuffGain.empty());
		DrawTextScr(Vector(100, 800), 4294901503, OnBuffUpdateEnemyBuffCountBuffGain, !OnBuffUpdateEnemyBuffCountBuffGain.empty());
		DrawTextScr(Vector(100, 820), 4294901503, OnBuffUpdateEnemyBuffMaxCountBuffGain, !OnBuffUpdateEnemyBuffMaxCountBuffGain.empty());
		DrawTextScr(Vector(100, 840), 4294901503, OnBuffUpdateEnemyBuffTypeBuffGain, !OnBuffUpdateEnemyBuffTypeBuffGain.empty());

		DrawTextScr(Vector(700, 200), 3690987775, "On Enemy Buff Lose", true);
		DrawTextScr(Vector(700, 220), 3690987775, "==================", true);
		DrawTextScr(Vector(700, 240), 4294901503, OnBuffUpdateEnemyBuffNameBuffLose, !OnBuffUpdateEnemyBuffNameBuffLose.empty());
		DrawTextScr(Vector(700, 260), 4294901503, OnBuffUpdateEnemyBuffCountBuffLose, !OnBuffUpdateEnemyBuffCountBuffLose.empty());
		DrawTextScr(Vector(700, 280), 4294901503, OnBuffUpdateEnemyBuffMaxCountBuffLose, !OnBuffUpdateEnemyBuffMaxCountBuffLose.empty());
		DrawTextScr(Vector(700, 300), 4294901503, OnBuffUpdateEnemyBuffTypeBuffLose, !OnBuffUpdateEnemyBuffTypeBuffLose.empty());


		DrawTextScr(Vector(700, 330), 3690987775, "On Object Delete", true);
		DrawTextScr(Vector(700, 350), 3690987775, "==================", true);
		DrawTextScr(Vector(700, 370), 4294901503, GameObjectOnDeleteObjectName, !GameObjectOnDeleteObjectName.empty());
		DrawTextScr(Vector(700, 390), 4294901503, GameObjectOnDeleteObjectType, !GameObjectOnDeleteObjectType.empty());
		DrawTextScr(Vector(700, 410), 4294901503, GameObjectOnDeleteObjectPosition, !GameObjectOnDeleteObjectPosition.empty());

		DrawTextScr(Vector(700, 440), 3690987775, "On Play Animation", true);
		DrawTextScr(Vector(700, 460), 3690987775, "==================", true);
		DrawTextScr(Vector(700, 480), 4294901503, OnPlayAnimationName, !OnPlayAnimationName.empty());
		DrawTextScr(Vector(700, 500), 4294901503, OnPlayAnimationSenderName, !OnPlayAnimationSenderName.empty());

	
		DrawTextScr(Vector(700, 530), 3690987775, "On Do Cast", true);
		DrawTextScr(Vector(700, 550), 3690987775, "==================", true);
		DrawTextScr(Vector(700, 570), 4294901503, OnDoCastSpellName, !OnDoCastSpellName.empty());
		DrawTextScr(Vector(700, 590), 4294901503, OnDoCastSpellSlot, !OnDoCastSpellSlot.empty());
		DrawTextScr(Vector(700, 610), 4294901503, OnDoCastSpellRange, !OnDoCastSpellRange.empty());
		DrawTextScr(Vector(700, 630), 4294901503, OnDoCastSpellDelay, !OnDoCastSpellDelay.empty());
		DrawTextScr(Vector(700, 650), 4294901503, OnDoCastSpellRadius, !OnDoCastSpellRadius.empty());
		DrawTextScr(Vector(700, 670), 4294901503, OnDoCastSpellSpeed, !OnDoCastSpellSpeed.empty());

		DrawTextScr(Vector(700, 700), 3690987775, "My Position", true);
		DrawTextScr(Vector(700, 720), 3690987775, "===========================", true);
		std::string myPos = "My Position: X: " + std::to_string(g_LocalPlayer->Position().x) + " Y: " + std::to_string(g_LocalPlayer->Position().y) + " Z: " +
			std::to_string(g_LocalPlayer->Position().z);
		DrawTextScr(Vector(700, 740), 4294901503, myPos, !myPos.empty());

		std::vector<IGameObject*> minions;
		for (auto minion : g_ObjectManager->GetByType(EntityType::AIMinionClient))
		{
			if(minion->Distance(g_LocalPlayer->Position()) < 1000)
			{
				minions.push_back(minion);
			}
		}

		std::sort(minions.begin(), minions.end(), [](IGameObject*& a, IGameObject*& b) ->bool {
			return a->Distance(g_LocalPlayer) < b->Distance(g_LocalPlayer);
			});

		if(!minions.empty())
		{
			DrawTextScr(Vector(700, 760), 4294901503, "Minion's name arround me: "+minions.front()->Name(), true);
		}
		DrawTextScr(Vector(700, 780), 4294901503, "My Champion name: " + g_LocalPlayer->ChampionName(), true);
		DrawTextScr(Vector(700, 800), 4294901503, "My Bonus ability power: " + std::to_string((g_LocalPlayer->TotalAbilityPower() - g_LocalPlayer->BaseAbilityDamage())), true);
		DrawTextScr(Vector(700, 820), 4294901503, "My Bonus attack damage: " + std::to_string((g_LocalPlayer->TotalAttackDamage() - g_LocalPlayer->BaseAttackDamage())) ,true);
	}
	
	void CreateMainMenu()
	{
		MainMenu = g_Menu->CreateMenu("Developer Tool by xDreamms", "DeveloperTool");

		//Settings Menu
		const auto SettingsMenu = MainMenu->AddSubMenu("Settings", "Settings");
		ColorPicker = SettingsMenu->AddColorPicker("Color picker: ", "ColorPicker", 255, 0, 0, 0);

		const auto GameObjectSettings = MainMenu->AddSubMenu("Game Object Settings", "GameObjectSettings");
		ObjectTeam = GameObjectSettings->AddComboBox("Game object team: ", "ObjectTeam", std::vector<std::string>{"Enemy", "Ally"}, 1);
		ObjectSearchRange = GameObjectSettings->AddSlider("Search range: ", "ObjectSearchRange", 1000, 0, 5000);

		const auto OnPLayAnimationMenu = MainMenu->AddSubMenu("On Play Animation Settings", "OnPLayAnimationMenu");
		OnPLayAnimationTeam = OnPLayAnimationMenu->AddComboBox("On Play Animation team: ", "OnPLayAnimationTeam", std::vector<std::string>{"Enemy", "Ally"}, 1);
		OnPLayAnimationSearchRange = OnPLayAnimationMenu->AddSlider("Search range: ", "OnPLayAnimationSearchRange", 1000, 0, 5000);

		const auto OnBuffUpdateMenu = MainMenu->AddSubMenu("On Buff Update Settings", "OnBuffUpdateMenu");
		OnBuffUpdateSearchRange = OnBuffUpdateMenu->AddSlider("Search range: ", "OnBuffUpdateSearchRange", 1000, 0, 5000);
		
		const auto AntiAFKMenu = MainMenu->AddSubMenu("Anti AFK", "AntiAFKMenu");
		EnabledAntiAFK = AntiAFKMenu->AddCheckBox("Enable Anti AFK (Change with middle mouse)", "EnabledAntiAFK", false);
	
	}

	void CreateEvents()
	{
		EventHandler<Events::GameUpdate>::AddEventHandler(OnUpdate);
		EventHandler<Events::OnHudDraw>::AddEventHandler(DrawingOnDraw);
		EventHandler<Events::OnProcessSpellCast>::AddEventHandler(OnProcessSpellCast);
		EventHandler<Events::OnWndProc>::AddEventHandler(OnWndProcEvent);
		EventHandler<Events::OnCreateObject>::AddEventHandler(GameObjectOnCreate);
		EventHandler<Events::OnBuff>::AddEventHandler(OnBuffUpdate);
		EventHandler<Events::OnDeleteObject>::AddEventHandler(GameObjectOnDelete);
		EventHandler<Events::OnPlayAnimation>::AddEventHandler(OnPlayAnimationEvent);
		EventHandler<Events::OnDoCast>::AddEventHandler(OnDoCastEvent);
	
	}
	
	void OnProcessSpellCast(IGameObject* sender, OnProcessSpellEventArgs* args)
	{
		if(!sender->IsMe())return;
		OnProcessSpellCastSpellName = "Name: " + args->SpellData->SpellName;
		OnProcessSpellCastSpellRange = "Range: " + std::to_string(args->SpellData->CastRange.at(0));
		OnProcessSpellCastSpellDelay = "Delay: " + std::to_string((args->SpellData->CastFrame / 30.f));
		OnProcessSpellCastSpellRadius = "Radius: " + std::to_string(args->SpellData->CastRadius.at(0));
		OnProcessSpellCastSpellSpeed = "Speed: " + std::to_string(args->SpellData->MissileSpeed);
	}
	void OnWndProcEvent(OnWndProcEventArgs* args)
	{
		OnWndProcuMsg = "OnWndPrc uMsg: " + std::to_string(args->uMsg);
		if(args->uMsg == 519)
		{
			EnabledAntiAFK->SetBool(!EnabledAntiAFK->GetBool());
		}
	}

	void GameObjectOnCreate(IGameObject* sender)
	{
		switch (ObjectTeam->GetInt())
		{
		case 0://Enemy
			if(sender->IsEnemy() && sender->Distance(g_LocalPlayer) < ObjectSearchRange->GetInt())
			{
				GameObjectOnCreateObjectName = "Enemy Object name: " + sender->Name();
				GameObjectOnCreateObjectPosition = "Enemy Object X: " + std::to_string(sender->Position().x) + "Y: "+ std::to_string(sender->Position().y) + "Z: "+ std::to_string(sender->Position().z);
				switch (sender->Type())
				{
				case EntityType::NeutralMinionCamp: GameObjectOnCreateObjectType = "Enemy Object Type: NeutralMinionCamp "; break;
				case EntityType::AIHeroClient: GameObjectOnCreateObjectType = "Enemy Object Type: AIHeroClient "; break;
				case EntityType::AIMarker: GameObjectOnCreateObjectType = "Enemy Object Type: AIMarker "; break;
				case EntityType::AIMinionClient: GameObjectOnCreateObjectType = "Enemy Object Type: AIMinionClient "; break;
				case EntityType::LevelPropAIClient:GameObjectOnCreateObjectType = "Enemy Object Type: LevelPropAIClient "; break;
				case EntityType::AITurretClient:GameObjectOnCreateObjectType = "Enemy Object Type: AITurretClient "; break;
				case EntityType::obj_GeneralParticleEmitter:GameObjectOnCreateObjectType = "Enemy Object Type: obj_GeneralParticleEmitter "; break;
				case EntityType::MissileClient:GameObjectOnCreateObjectType = "Enemy Object Type: MissileClient "; break;
				case EntityType::DrawFX:GameObjectOnCreateObjectType = "Enemy Object Type: DrawFX "; break;
				case EntityType::BarracksDampener:GameObjectOnCreateObjectType = "Enemy Object Type: BarracksDampener "; break;
				case EntityType::Barracks:GameObjectOnCreateObjectType = "Enemy Object Type: Barracks "; break;
				case EntityType::obj_SpawnPoint:GameObjectOnCreateObjectType = "Enemy Object Type: obj_SpawnPoint "; break;
				case EntityType::GrassObject: GameObjectOnCreateObjectType = "Enemy Object Type: GrassObject "; break;
				case EntityType::HQ:GameObjectOnCreateObjectType = "Enemy Object Type: HQ "; break;
				case EntityType::obj_InfoPoint:GameObjectOnCreateObjectType = "Enemy Object Type: obj_InfoPoint "; break;
				case EntityType::LevelPropGameObject: GameObjectOnCreateObjectType = "Enemy Object Type: LevelPropGameObject "; break;
				case EntityType::LevelPropSpawnerPoint: GameObjectOnCreateObjectType = "Enemy Object Type: LevelPropSpawnerPoint "; break;
				case EntityType::Shop:GameObjectOnCreateObjectType = "Enemy Object Type: Shop "; break;
				case EntityType::obj_Turret: GameObjectOnCreateObjectType = "Enemy Object Type: obj_Turret "; break;
				case EntityType::AIBase:GameObjectOnCreateObjectType = "Enemy Object Type: AIBase "; break;
				case EntityType::Any:GameObjectOnCreateObjectType = "Enemy Object Type: Any "; break;
				default: ;
				}
			}
			break;
		case 1://Ally
			if (sender->IsAlly() && sender->Distance(g_LocalPlayer) < ObjectSearchRange->GetInt())
			{
				GameObjectOnCreateObjectName = "Ally Object name: " + sender->Name();
				GameObjectOnCreateObjectPosition = "Ally Object X: " + std::to_string(sender->Position().x) + "Y: " + std::to_string(sender->Position().y) + "Z: " + std::to_string(sender->Position().z);
				switch (sender->Type())
				{
				case EntityType::NeutralMinionCamp: GameObjectOnCreateObjectType = "Ally Object Type: NeutralMinionCamp "; break;
				case EntityType::AIHeroClient: GameObjectOnCreateObjectType = "Ally Object Type: AIHeroClient "; break;
				case EntityType::AIMarker: GameObjectOnCreateObjectType = "Ally Object Type: AIMarker "; break;
				case EntityType::AIMinionClient: GameObjectOnCreateObjectType = "Ally Object Type: AIMinionClient "; break;
				case EntityType::LevelPropAIClient:GameObjectOnCreateObjectType = "Ally Object Type: LevelPropAIClient "; break;
				case EntityType::AITurretClient:GameObjectOnCreateObjectType = "Ally Object Type: AITurretClient "; break;
				case EntityType::obj_GeneralParticleEmitter:GameObjectOnCreateObjectType = "Ally Object Type: obj_GeneralParticleEmitter "; break;
				case EntityType::MissileClient:GameObjectOnCreateObjectType = "Ally Object Type: MissileClient "; break;
				case EntityType::DrawFX:GameObjectOnCreateObjectType = "Ally Object Type: DrawFX "; break;
				case EntityType::BarracksDampener:GameObjectOnCreateObjectType = "Ally Object Type: BarracksDampener "; break;
				case EntityType::Barracks:GameObjectOnCreateObjectType = "Ally Object Type: Barracks "; break;
				case EntityType::obj_SpawnPoint:GameObjectOnCreateObjectType = "Ally Object Type: obj_SpawnPoint "; break;
				case EntityType::GrassObject: GameObjectOnCreateObjectType = "Ally Object Type: GrassObject "; break;
				case EntityType::HQ:GameObjectOnCreateObjectType = "Ally Object Type: HQ "; break;
				case EntityType::obj_InfoPoint:GameObjectOnCreateObjectType = "Ally Object Type: obj_InfoPoint "; break;
				case EntityType::LevelPropGameObject: GameObjectOnCreateObjectType = "Ally Object Type: LevelPropGameObject "; break;
				case EntityType::LevelPropSpawnerPoint: GameObjectOnCreateObjectType = "Ally Object Type: LevelPropSpawnerPoint "; break;
				case EntityType::Shop:GameObjectOnCreateObjectType = "Ally Object Type: Shop "; break;
				case EntityType::obj_Turret: GameObjectOnCreateObjectType = "Ally Object Type: obj_Turret "; break;
				case EntityType::AIBase:GameObjectOnCreateObjectType = "Ally Object Type: AIBase "; break;
				case EntityType::Any:GameObjectOnCreateObjectType = "Ally Object Type: Any "; break;
				default:;
				}
			}
			break;
		}
	}

	
	void OnBuffUpdate(IGameObject* sender, OnBuffEventArgs* args)
	{
		if(args->IsBuffGain)
		{
			if(args->Buff.Owner->IsMe())
			{
				OnBuffUpdateMyBuffNameBuffGain = "My buff name: " + args->Buff.Name;
				OnBuffUpdateMyBuffCountBuffGain = "My Buff Count: " + std::to_string(args->Buff.Count);
				OnBuffUpdateMyBuffMaxCountBuffGain = "My Buff MaxCount: " + std::to_string(args->Buff.MaxCount);
				switch (args->Buff.Type)
				{
				case BuffType::Aura: OnBuffUpdateMyBuffTypeBuffGain = "My Buff Type: Aura"; break;
				case BuffType::Blind:OnBuffUpdateMyBuffTypeBuffGain = "My Buff Type: Blind"; break;
				case BuffType::Charm:OnBuffUpdateMyBuffTypeBuffGain = "My Buff Type: Charm"; break;
				case BuffType::CombatDehancer:OnBuffUpdateMyBuffTypeBuffGain = "My Buff Type: CombatDehancer"; break;
				case BuffType::CombatEnchancer:OnBuffUpdateMyBuffTypeBuffGain = "My Buff Type: CombatEnchancer"; break;
				case BuffType::Counter:OnBuffUpdateMyBuffTypeBuffGain = "My Buff Type: Counter"; break;
				case BuffType::Damage:OnBuffUpdateMyBuffTypeBuffGain = "My Buff Type: Damage"; break;
				case BuffType::Disarm:OnBuffUpdateMyBuffTypeBuffGain = "My Buff Type: Disarm"; break;
				case BuffType::Fear:OnBuffUpdateMyBuffTypeBuffGain = "My Buff Type: Fear"; break;
				case BuffType::Flee:OnBuffUpdateMyBuffTypeBuffGain = "My Buff Type: Flee"; break;
				case BuffType::Frenzy:OnBuffUpdateMyBuffTypeBuffGain = "My Buff Type: Frenzy"; break;
				case BuffType::Haste:OnBuffUpdateMyBuffTypeBuffGain = "My Buff Type: Haste"; break;
				case BuffType::Heal:OnBuffUpdateMyBuffTypeBuffGain = "My Buff Type: Heal"; break;
				case BuffType::Internal:OnBuffUpdateMyBuffTypeBuffGain = "My Buff Type: Internal"; break;
				case BuffType::Invisibility: OnBuffUpdateMyBuffTypeBuffGain = "My Buff Type: Invisibility"; break;
				case BuffType::Invulnerability:OnBuffUpdateMyBuffTypeBuffGain = "My Buff Type: Invulnerability"; break;
				case BuffType::Knockback:OnBuffUpdateMyBuffTypeBuffGain = "My Buff Type: Knockback"; break;
				case BuffType::Knockup:OnBuffUpdateMyBuffTypeBuffGain = "My Buff Type: Knockup"; break;
				case BuffType::NearSight:OnBuffUpdateMyBuffTypeBuffGain = "My Buff Type: NearSight"; break;
				case BuffType::PhysicalImmunity:OnBuffUpdateMyBuffTypeBuffGain = "My Buff Type: PhysicalImmunity"; break;
				case BuffType::Poison:OnBuffUpdateMyBuffTypeBuffGain = "My Buff Type: Poison"; break;
				case BuffType::Polymorph: OnBuffUpdateMyBuffTypeBuffGain = "My Buff Type: Polymorph"; break;
				case BuffType::Shred:OnBuffUpdateMyBuffTypeBuffGain = "My Buff Type: Shred"; break;
				case BuffType::Silence:OnBuffUpdateMyBuffTypeBuffGain = "My Buff Type: Silence"; break;
				case BuffType::Sleep:OnBuffUpdateMyBuffTypeBuffGain = "My Buff Type: Sleep"; break;
				case BuffType::Slow:OnBuffUpdateMyBuffTypeBuffGain = "My Buff Type: Slow"; break;
				case BuffType::Snare:OnBuffUpdateMyBuffTypeBuffGain = "My Buff Type: Snare"; break;
				case BuffType::SpellImmunity:OnBuffUpdateMyBuffTypeBuffGain = "My Buff Type: SpellImmunity"; break;
				case BuffType::SpellShield: OnBuffUpdateMyBuffTypeBuffGain = "My Buff Type: SpellShield"; break;
				case BuffType::Stun:OnBuffUpdateMyBuffTypeBuffGain = "My Buff Type: Stun"; break;
				case BuffType::Suppression: OnBuffUpdateMyBuffTypeBuffGain = "My Buff Type: Suppression"; break;
				case BuffType::Taunt:OnBuffUpdateMyBuffTypeBuffGain = "My Buff Type: Taunt"; break;
				default: ;
				}
				
			}
			if(args->Buff.Owner->IsEnemy())
			{
				OnBuffUpdateEnemyBuffNameBuffGain = "Enemy buff name: " + args->Buff.Name;
				OnBuffUpdateEnemyBuffCountBuffGain = "Enemy Buff Count: " + std::to_string(args->Buff.Count);
				OnBuffUpdateEnemyBuffMaxCountBuffGain = "Enemy Buff MaxCount: " + std::to_string(args->Buff.MaxCount);
				switch (args->Buff.Type)
				{
				case BuffType::Aura: OnBuffUpdateEnemyBuffTypeBuffGain = "Enemy Buff Type: Aura"; break;
				case BuffType::Blind:OnBuffUpdateEnemyBuffTypeBuffGain = "Enemy Buff Type: Blind"; break;
				case BuffType::Charm:OnBuffUpdateEnemyBuffTypeBuffGain = "Enemy Buff Type: Charm"; break;
				case BuffType::CombatDehancer:OnBuffUpdateEnemyBuffTypeBuffGain = "Enemy Buff Type: CombatDehancer"; break;
				case BuffType::CombatEnchancer:OnBuffUpdateEnemyBuffTypeBuffGain = "Enemy Buff Type: CombatEnchancer"; break;
				case BuffType::Counter:OnBuffUpdateEnemyBuffTypeBuffGain = "Enemy Buff Type: Counter"; break;
				case BuffType::Damage:OnBuffUpdateEnemyBuffTypeBuffGain = "Enemy Buff Type: Damage"; break;
				case BuffType::Disarm:OnBuffUpdateEnemyBuffTypeBuffGain = "Enemy Buff Type: Disarm"; break;
				case BuffType::Fear:OnBuffUpdateEnemyBuffTypeBuffGain = "Enemy Buff Type: Fear"; break;
				case BuffType::Flee:OnBuffUpdateEnemyBuffTypeBuffGain = "Enemy Buff Type: Flee"; break;
				case BuffType::Frenzy:OnBuffUpdateEnemyBuffTypeBuffGain = "Enemy Buff Type: Frenzy"; break;
				case BuffType::Haste:OnBuffUpdateEnemyBuffTypeBuffGain = "Enemy Buff Type: Haste"; break;
				case BuffType::Heal:OnBuffUpdateEnemyBuffTypeBuffGain = "Enemy Buff Type: Heal"; break;
				case BuffType::Internal:OnBuffUpdateEnemyBuffTypeBuffGain = "Enemy Buff Type: Internal"; break;
				case BuffType::Invisibility: OnBuffUpdateEnemyBuffTypeBuffGain = "Enemy Buff Type: Invisibility"; break;
				case BuffType::Invulnerability:OnBuffUpdateEnemyBuffTypeBuffGain = "Enemy Buff Type: Invulnerability"; break;
				case BuffType::Knockback:OnBuffUpdateEnemyBuffTypeBuffGain = "Enemy Buff Type: Knockback"; break;
				case BuffType::Knockup:OnBuffUpdateEnemyBuffTypeBuffGain = "Enemy Buff Type: Knockup"; break;
				case BuffType::NearSight:OnBuffUpdateEnemyBuffTypeBuffGain = "Enemy Buff Type: NearSight"; break;
				case BuffType::PhysicalImmunity:OnBuffUpdateEnemyBuffTypeBuffGain = "Enemy Buff Type: PhysicalImmunity"; break;
				case BuffType::Poison:OnBuffUpdateEnemyBuffTypeBuffGain = "Enemy Buff Type: Poison"; break;
				case BuffType::Polymorph: OnBuffUpdateEnemyBuffTypeBuffGain = "Enemy Buff Type: Polymorph"; break;
				case BuffType::Shred:OnBuffUpdateEnemyBuffTypeBuffGain = "Enemy Buff Type: Shred"; break;
				case BuffType::Silence:OnBuffUpdateEnemyBuffTypeBuffGain = "Enemy Buff Type: Silence"; break;
				case BuffType::Sleep:OnBuffUpdateEnemyBuffTypeBuffGain = "Enemy Buff Type: Sleep"; break;
				case BuffType::Slow:OnBuffUpdateEnemyBuffTypeBuffGain = "Enemy Buff Type: Slow"; break;
				case BuffType::Snare:OnBuffUpdateEnemyBuffTypeBuffGain = "Enemy Buff Type: Snare"; break;
				case BuffType::SpellImmunity:OnBuffUpdateEnemyBuffTypeBuffGain = "Enemy Buff Type: SpellImmunity"; break;
				case BuffType::SpellShield: OnBuffUpdateEnemyBuffTypeBuffGain = "Enemy Buff Type: SpellShield"; break;
				case BuffType::Stun:OnBuffUpdateEnemyBuffTypeBuffGain = "Enemy Buff Type: Stun"; break;
				case BuffType::Suppression: OnBuffUpdateEnemyBuffTypeBuffGain = "Enemy Buff Type: Suppression"; break;
				case BuffType::Taunt:OnBuffUpdateEnemyBuffTypeBuffGain = "Enemy Buff Type: Taunt"; break;
				default:;
				}
			}
		}
		else if(!args->IsBuffGain)
		{
			if (args->Buff.Owner->IsMe())
			{
				OnBuffUpdateMyBuffNameBuffLose = "My buff name: " + args->Buff.Name;
				OnBuffUpdateMyBuffCountBuffLose = "My Buff Count: " + std::to_string(args->Buff.Count);
				OnBuffUpdateMyBuffMaxCountBuffLose = "My Buff MaxCount: " + std::to_string(args->Buff.MaxCount);
				switch (args->Buff.Type)
				{
				case BuffType::Aura: OnBuffUpdateMyBuffTypeBuffLose = "My Buff Type: Aura"; break;
				case BuffType::Blind:OnBuffUpdateMyBuffTypeBuffLose = "My Buff Type: Blind"; break;
				case BuffType::Charm:OnBuffUpdateMyBuffTypeBuffLose = "My Buff Type: Charm"; break;
				case BuffType::CombatDehancer:OnBuffUpdateMyBuffTypeBuffLose = "My Buff Type: CombatDehancer"; break;
				case BuffType::CombatEnchancer:OnBuffUpdateMyBuffTypeBuffLose = "My Buff Type: CombatEnchancer"; break;
				case BuffType::Counter:OnBuffUpdateMyBuffTypeBuffLose = "My Buff Type: Counter"; break;
				case BuffType::Damage:OnBuffUpdateMyBuffTypeBuffLose = "My Buff Type: Damage"; break;
				case BuffType::Disarm:OnBuffUpdateMyBuffTypeBuffLose = "My Buff Type: Disarm"; break;
				case BuffType::Fear:OnBuffUpdateMyBuffTypeBuffLose = "My Buff Type: Fear"; break;
				case BuffType::Flee:OnBuffUpdateMyBuffTypeBuffLose = "My Buff Type: Flee"; break;
				case BuffType::Frenzy:OnBuffUpdateMyBuffTypeBuffLose = "My Buff Type: Frenzy"; break;
				case BuffType::Haste:OnBuffUpdateMyBuffTypeBuffLose = "My Buff Type: Haste"; break;
				case BuffType::Heal:OnBuffUpdateMyBuffTypeBuffLose = "My Buff Type: Heal"; break;
				case BuffType::Internal:OnBuffUpdateMyBuffTypeBuffLose = "My Buff Type: Internal"; break;
				case BuffType::Invisibility: OnBuffUpdateMyBuffTypeBuffLose = "My Buff Type: Invisibility"; break;
				case BuffType::Invulnerability:OnBuffUpdateMyBuffTypeBuffLose = "My Buff Type: Invulnerability"; break;
				case BuffType::Knockback:OnBuffUpdateMyBuffTypeBuffLose = "My Buff Type: Knockback"; break;
				case BuffType::Knockup:OnBuffUpdateMyBuffTypeBuffLose = "My Buff Type: Knockup"; break;
				case BuffType::NearSight:OnBuffUpdateMyBuffTypeBuffLose = "My Buff Type: NearSight"; break;
				case BuffType::PhysicalImmunity:OnBuffUpdateMyBuffTypeBuffLose = "My Buff Type: PhysicalImmunity"; break;
				case BuffType::Poison:OnBuffUpdateMyBuffTypeBuffLose = "My Buff Type: Poison"; break;
				case BuffType::Polymorph: OnBuffUpdateMyBuffTypeBuffLose = "My Buff Type: Polymorph"; break;
				case BuffType::Shred:OnBuffUpdateMyBuffTypeBuffLose = "My Buff Type: Shred"; break;
				case BuffType::Silence:OnBuffUpdateMyBuffTypeBuffLose = "My Buff Type: Silence"; break;
				case BuffType::Sleep:OnBuffUpdateMyBuffTypeBuffLose = "My Buff Type: Sleep"; break;
				case BuffType::Slow:OnBuffUpdateMyBuffTypeBuffLose = "My Buff Type: Slow"; break;
				case BuffType::Snare:OnBuffUpdateMyBuffTypeBuffLose = "My Buff Type: Snare"; break;
				case BuffType::SpellImmunity:OnBuffUpdateMyBuffTypeBuffLose = "My Buff Type: SpellImmunity"; break;
				case BuffType::SpellShield: OnBuffUpdateMyBuffTypeBuffLose = "My Buff Type: SpellShield"; break;
				case BuffType::Stun:OnBuffUpdateMyBuffTypeBuffLose = "My Buff Type: Stun"; break;
				case BuffType::Suppression: OnBuffUpdateMyBuffTypeBuffLose = "My Buff Type: Suppression"; break;
				case BuffType::Taunt:OnBuffUpdateMyBuffTypeBuffLose = "My Buff Type: Taunt"; break;
				default:;
				}
			}
			if (args->Buff.Owner->IsEnemy())
			{
				OnBuffUpdateEnemyBuffNameBuffLose = "Enemy buff name: " + args->Buff.Name;
				OnBuffUpdateEnemyBuffCountBuffLose = "Enemy Buff Count: " + std::to_string(args->Buff.Count);
				OnBuffUpdateEnemyBuffMaxCountBuffLose = "Enemy Buff MaxCount: " + std::to_string(args->Buff.MaxCount);
				switch (args->Buff.Type)
				{
				case BuffType::Aura: OnBuffUpdateEnemyBuffTypeBuffLose = "Enemy Buff Type: Aura"; break;
				case BuffType::Blind:OnBuffUpdateEnemyBuffTypeBuffLose = "Enemy Buff Type: Blind"; break;
				case BuffType::Charm:OnBuffUpdateEnemyBuffTypeBuffLose = "Enemy Buff Type: Charm"; break;
				case BuffType::CombatDehancer:OnBuffUpdateEnemyBuffTypeBuffLose = "Enemy Buff Type: CombatDehancer"; break;
				case BuffType::CombatEnchancer:OnBuffUpdateEnemyBuffTypeBuffLose = "Enemy Buff Type: CombatEnchancer"; break;
				case BuffType::Counter:OnBuffUpdateEnemyBuffTypeBuffLose = "Enemy Buff Type: Counter"; break;
				case BuffType::Damage:OnBuffUpdateEnemyBuffTypeBuffLose = "Enemy Buff Type: Damage"; break;
				case BuffType::Disarm:OnBuffUpdateEnemyBuffTypeBuffLose = "Enemy Buff Type: Disarm"; break;
				case BuffType::Fear:OnBuffUpdateEnemyBuffTypeBuffLose = "Enemy Buff Type: Fear"; break;
				case BuffType::Flee:OnBuffUpdateEnemyBuffTypeBuffLose = "Enemy Buff Type: Flee"; break;
				case BuffType::Frenzy:OnBuffUpdateEnemyBuffTypeBuffLose = "Enemy Buff Type: Frenzy"; break;
				case BuffType::Haste:OnBuffUpdateEnemyBuffTypeBuffLose = "Enemy Buff Type: Haste"; break;
				case BuffType::Heal:OnBuffUpdateEnemyBuffTypeBuffLose = "Enemy Buff Type: Heal"; break;
				case BuffType::Internal:OnBuffUpdateEnemyBuffTypeBuffLose = "Enemy Buff Type: Internal"; break;
				case BuffType::Invisibility: OnBuffUpdateEnemyBuffTypeBuffLose = "Enemy Buff Type: Invisibility"; break;
				case BuffType::Invulnerability:OnBuffUpdateEnemyBuffTypeBuffLose = "Enemy Buff Type: Invulnerability"; break;
				case BuffType::Knockback:OnBuffUpdateEnemyBuffTypeBuffLose = "Enemy Buff Type: Knockback"; break;
				case BuffType::Knockup:OnBuffUpdateEnemyBuffTypeBuffLose = "Enemy Buff Type: Knockup"; break;
				case BuffType::NearSight:OnBuffUpdateEnemyBuffTypeBuffLose = "Enemy Buff Type: NearSight"; break;
				case BuffType::PhysicalImmunity:OnBuffUpdateEnemyBuffTypeBuffLose = "Enemy Buff Type: PhysicalImmunity"; break;
				case BuffType::Poison:OnBuffUpdateEnemyBuffTypeBuffLose = "Enemy Buff Type: Poison"; break;
				case BuffType::Polymorph: OnBuffUpdateEnemyBuffTypeBuffLose = "Enemy Buff Type: Polymorph"; break;
				case BuffType::Shred:OnBuffUpdateEnemyBuffTypeBuffLose = "Enemy Buff Type: Shred"; break;
				case BuffType::Silence:OnBuffUpdateEnemyBuffTypeBuffLose = "Enemy Buff Type: Silence"; break;
				case BuffType::Sleep:OnBuffUpdateEnemyBuffTypeBuffLose = "Enemy Buff Type: Sleep"; break;
				case BuffType::Slow:OnBuffUpdateEnemyBuffTypeBuffLose = "Enemy Buff Type: Slow"; break;
				case BuffType::Snare:OnBuffUpdateEnemyBuffTypeBuffLose = "Enemy Buff Type: Snare"; break;
				case BuffType::SpellImmunity:OnBuffUpdateEnemyBuffTypeBuffLose = "Enemy Buff Type: SpellImmunity"; break;
				case BuffType::SpellShield: OnBuffUpdateEnemyBuffTypeBuffLose = "Enemy Buff Type: SpellShield"; break;
				case BuffType::Stun:OnBuffUpdateEnemyBuffTypeBuffLose = "Enemy Buff Type: Stun"; break;
				case BuffType::Suppression: OnBuffUpdateEnemyBuffTypeBuffLose = "Enemy Buff Type: Suppression"; break;
				case BuffType::Taunt:OnBuffUpdateEnemyBuffTypeBuffLose = "Enemy Buff Type: Taunt"; break;
				default:;
				}
			}
		}

	}
	void GameObjectOnDelete(IGameObject* sender)
	{
		switch (ObjectTeam->GetInt())
		{
		case 0://Enemy
			if (sender->IsEnemy() && sender->Distance(g_LocalPlayer) < ObjectSearchRange->GetInt())
			{
				GameObjectOnDeleteObjectName = "Enemy Object name: " + sender->Name();
				GameObjectOnDeleteObjectPosition = "Enemy Object X: " + std::to_string(sender->Position().x) + "Y: " + std::to_string(sender->Position().y) + "Z: " + std::to_string(sender->Position().z);
				switch (sender->Type())
				{
				case EntityType::NeutralMinionCamp: GameObjectOnDeleteObjectType = "Enemy Object Type: NeutralMinionCamp "; break;
				case EntityType::AIHeroClient: GameObjectOnDeleteObjectType = "Enemy Object Type: AIHeroClient "; break;
				case EntityType::AIMarker: GameObjectOnDeleteObjectType = "Enemy Object Type: AIMarker "; break;
				case EntityType::AIMinionClient: GameObjectOnDeleteObjectType = "Enemy Object Type: AIMinionClient "; break;
				case EntityType::LevelPropAIClient:GameObjectOnDeleteObjectType = "Enemy Object Type: LevelPropAIClient "; break;
				case EntityType::AITurretClient:GameObjectOnDeleteObjectType = "Enemy Object Type: AITurretClient "; break;
				case EntityType::obj_GeneralParticleEmitter:GameObjectOnDeleteObjectType = "Enemy Object Type: obj_GeneralParticleEmitter "; break;
				case EntityType::MissileClient:GameObjectOnDeleteObjectType = "Enemy Object Type: MissileClient "; break;
				case EntityType::DrawFX:GameObjectOnDeleteObjectType = "Enemy Object Type: DrawFX "; break;
				case EntityType::BarracksDampener:GameObjectOnDeleteObjectType = "Enemy Object Type: BarracksDampener "; break;
				case EntityType::Barracks:GameObjectOnDeleteObjectType = "Enemy Object Type: Barracks "; break;
				case EntityType::obj_SpawnPoint:GameObjectOnDeleteObjectType = "Enemy Object Type: obj_SpawnPoint "; break;
				case EntityType::GrassObject: GameObjectOnDeleteObjectType = "Enemy Object Type: GrassObject "; break;
				case EntityType::HQ:GameObjectOnDeleteObjectType = "Enemy Object Type: HQ "; break;
				case EntityType::obj_InfoPoint:GameObjectOnDeleteObjectType = "Enemy Object Type: obj_InfoPoint "; break;
				case EntityType::LevelPropGameObject: GameObjectOnDeleteObjectType = "Enemy Object Type: LevelPropGameObject "; break;
				case EntityType::LevelPropSpawnerPoint: GameObjectOnDeleteObjectType = "Enemy Object Type: LevelPropSpawnerPoint "; break;
				case EntityType::Shop:GameObjectOnDeleteObjectType = "Enemy Object Type: Shop "; break;
				case EntityType::obj_Turret: GameObjectOnDeleteObjectType = "Enemy Object Type: obj_Turret "; break;
				case EntityType::AIBase:GameObjectOnDeleteObjectType = "Enemy Object Type: AIBase "; break;
				case EntityType::Any:GameObjectOnDeleteObjectType = "Enemy Object Type: Any "; break;
				default:;
				}
			}
			break;
		case 1://Ally
			if (sender->IsAlly() && sender->Distance(g_LocalPlayer) < ObjectSearchRange->GetInt())
			{
				GameObjectOnDeleteObjectName = "Ally Object name: " + sender->Name();
				GameObjectOnDeleteObjectPosition = "Ally Object X: " + std::to_string(sender->Position().x) + "Y: " + std::to_string(sender->Position().y) + "Z: " + std::to_string(sender->Position().z);
				switch (sender->Type())
				{
				case EntityType::NeutralMinionCamp: GameObjectOnDeleteObjectType = "Ally Object Type: NeutralMinionCamp "; break;
				case EntityType::AIHeroClient: GameObjectOnDeleteObjectType = "Ally Object Type: AIHeroClient "; break;
				case EntityType::AIMarker: GameObjectOnDeleteObjectType = "Ally Object Type: AIMarker "; break;
				case EntityType::AIMinionClient: GameObjectOnDeleteObjectType = "Ally Object Type: AIMinionClient "; break;
				case EntityType::LevelPropAIClient:GameObjectOnDeleteObjectType = "Ally Object Type: LevelPropAIClient "; break;
				case EntityType::AITurretClient:GameObjectOnDeleteObjectType = "Ally Object Type: AITurretClient "; break;
				case EntityType::obj_GeneralParticleEmitter:GameObjectOnDeleteObjectType = "Ally Object Type: obj_GeneralParticleEmitter "; break;
				case EntityType::MissileClient:GameObjectOnDeleteObjectType = "Ally Object Type: MissileClient "; break;
				case EntityType::DrawFX:GameObjectOnDeleteObjectType = "Ally Object Type: DrawFX "; break;
				case EntityType::BarracksDampener:GameObjectOnDeleteObjectType = "Ally Object Type: BarracksDampener "; break;
				case EntityType::Barracks:GameObjectOnDeleteObjectType = "Ally Object Type: Barracks "; break;
				case EntityType::obj_SpawnPoint:GameObjectOnDeleteObjectType = "Ally Object Type: obj_SpawnPoint "; break;
				case EntityType::GrassObject: GameObjectOnDeleteObjectType = "Ally Object Type: GrassObject "; break;
				case EntityType::HQ:GameObjectOnDeleteObjectType = "Ally Object Type: HQ "; break;
				case EntityType::obj_InfoPoint:GameObjectOnDeleteObjectType = "Ally Object Type: obj_InfoPoint "; break;
				case EntityType::LevelPropGameObject: GameObjectOnDeleteObjectType = "Ally Object Type: LevelPropGameObject "; break;
				case EntityType::LevelPropSpawnerPoint: GameObjectOnDeleteObjectType = "Ally Object Type: LevelPropSpawnerPoint "; break;
				case EntityType::Shop:GameObjectOnDeleteObjectType = "Ally Object Type: Shop "; break;
				case EntityType::obj_Turret: GameObjectOnDeleteObjectType = "Ally Object Type: obj_Turret "; break;
				case EntityType::AIBase:GameObjectOnDeleteObjectType = "Ally Object Type: AIBase "; break;
				case EntityType::Any:GameObjectOnDeleteObjectType = "Ally Object Type: Any "; break;
				default:;
				}
			}
			break;
		}
	}

	void OnPlayAnimationEvent(IGameObject* sender, OnPlayAnimationEventArgs* args)
	{
		if(sender->Distance(g_LocalPlayer) < OnPLayAnimationSearchRange->GetFloat())
		{
				OnPlayAnimationName = "Animation Name: "+ args->AnimationName;
				OnPlayAnimationSenderName = "Sender name:" + sender->Name();
		}
	}
	
	void OnDoCastEvent(IGameObject* sender, OnProcessSpellEventArgs* args)
	{
		if(!sender->IsMe())return;
		OnDoCastSpellName = "Spell Name: "+ args->SpellData->SpellName;
		OnDoCastSpellRange = "Spell Range: " + std::to_string(args->SpellData->CastRange.at(0));
		OnDoCastSpellDelay = "Spell Delay: " + std::to_string((args->SpellData->CastFrame / 30.f));
		OnDoCastSpellRadius = "Spell Radius: " + std::to_string(args->SpellData->CastRadius.at(0));
		OnDoCastSpellSpeed = "Spell Speed: " + std::to_string(args->SpellData->MissileSpeed);
		switch (args->SpellSlot)
		{
		case SpellSlot::Invalid: OnDoCastSpellSlot = "Spell Slot: Invalid"; break;
		case SpellSlot::Q: OnDoCastSpellSlot = "Spell Slot: Q"; break;
		case SpellSlot::W: OnDoCastSpellSlot = "Spell Slot: W"; break;
		case SpellSlot::E: OnDoCastSpellSlot = "Spell Slot: E"; break;
		case SpellSlot::R: OnDoCastSpellSlot = "Spell Slot: R"; break;
		case SpellSlot::Summoner1: OnDoCastSpellSlot = "Spell Slot: Summoner1"; break;
		case SpellSlot::Summoner2:  OnDoCastSpellSlot = "Spell Slot: Summoner2"; break;
		case SpellSlot::Item_1: OnDoCastSpellSlot = "Spell Slot: Item_1"; break;
		case SpellSlot::Item_2: OnDoCastSpellSlot = "Spell Slot: Item_2"; break;
		case SpellSlot::Item_3: OnDoCastSpellSlot = "Spell Slot: Item_3"; break;
		case SpellSlot::Item_4: OnDoCastSpellSlot = "Spell Slot: Item_4"; break;
		case SpellSlot::Item_5: OnDoCastSpellSlot = "Spell Slot: Item_5"; break;
		case SpellSlot::Item_6: OnDoCastSpellSlot = "Spell Slot: Item_6"; break;
		case SpellSlot::Trinket:  OnDoCastSpellSlot = "Spell Slot: Trinket"; break;
		case SpellSlot::Recall: OnDoCastSpellSlot = "Spell Slot: Recall"; break;
		default: ;
		}
	}
}
