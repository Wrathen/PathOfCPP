#include "Scene.h"
#include "Core/Game/Entity/Entity.h"
#include <Core/Miscellaneous/Random.h>
#include "Game/Component/Components.h"
#include "Managers/TextureManager.h"
#include "Managers/RenderManager.h"
#include "Managers/CameraManager.h"
#include "Miscellaneous/Utils.h"

#include "Game/System/S_RenderEntities.h"
#include "Game/System/S_UpdateAnimators.h"
#include "Game/System/S_HandleLocalPlayerInput.h"

// Constructors
Scene::Scene() : Scene("Zone_Empty.PZD") {}
Scene::Scene(const std::string& _zoneDataPath) : BaseScene(_zoneDataPath, "Unnamed Scene") {}
Scene::Scene(const std::string& _zoneDataPath, const std::string& _name) : BaseScene(_zoneDataPath, _name) {}

// Base Functions
void Scene::Start() {
	BaseScene::Start();

	// Add the visual background associated with this Zone.PSD.
	AddBackground();
	
	// Add all the necessary systems for a generic Client::Scene.
	AddSystem<S_RenderEntities>();
	AddSystem<S_UpdateAnimators>();
	AddSystem<S_HandleLocalPlayerInput>();
}

void Scene::Update() {
	BaseScene::Update();
}

void Scene::LateUpdate() {
	BaseScene::LateUpdate();
}

void Scene::Clear() {
	BaseScene::Clear();
}

void Scene::LoadZone() {
	BaseScene::LoadZone();
}

void Scene::AddBackground() {
	// Let's add a background.
	Core::Entity background = Core::Entity(this, SpawnEntity());

	// Parse the Zone.PSD to get the Background Texture Path.
	Core::Zone zone = Core::Zone::FromSaveFile("../Assets/Zones/" + zoneDataPath);
	
	// Load the texture from the Assets, we will use this to initialize C_Texture component.
	SDL_Texture* tex;
	TextureMgr.LoadTexture(zone.GetBackground().bgPath, &tex);

	// Add components to the background entity.
	auto& C_Transform = background.AddComponent<TransformComponent>();
	auto& C_Texture = background.AddComponent<TextureComponent>(tex);
	auto& C_SpriteRenderer = background.AddComponent<SpriteRendererComponent>(TextureMgr.GetDimensions(C_Texture.texture));
}
entt::entity Scene::SpawnPlayer(float posX, float posY) {
	Core::Entity player = Core::Entity(this, BaseScene::SpawnPlayer(posX, posY));
	
	// [todo] server needs to decide on this, not us.
	// If we are the first player, we can assign ourselves as the LocalPlayer.
	if (totalNumberOfSpawnedPlayers == 1)
		player.AddComponent<LocalPlayerComponent>();

	// Load the texture from the Assets, we will use this to initialize C_Texture component.
	SDL_Texture* tex;
	TextureMgr.LoadTexture("../Assets/Sprites/player.png", &tex);

	// Add additional Components to Player on Client-side.
	auto& C_Texture = player.AddComponent<TextureComponent>(tex);
	auto& C_SpriteRenderer = player.AddComponent<SpriteRendererComponent>(TextureMgr.GetDimensions(C_Texture.texture));
	auto& C_HealthBar = player.AddComponent<HealthBarComponent>();
	auto& C_Animator = player.AddComponent<AnimatorComponent>();

	// Add Animations
	C_Animator.map.emplace("Idle", AnimationComponent("Idle", 120, 64, 64, 0, 0, 9, 0, true));
	C_Animator.map.emplace("Move", AnimationComponent("Move", 30, 64, 64, 0, 1, 3, 1, true));
	C_Animator.map.emplace("Attack", AnimationComponent("Attack", 10, 64, 64, 0, 2, 3, 2, false));

	C_Animator.currentAnimation = &C_Animator.map["Idle"];

	return player.GetRaw();
}
entt::entity Scene::SpawnNPC(float posX, float posY, int type) {
	Core::Entity npc = Core::Entity(this, BaseScene::SpawnNPC(posX, posY, type));

	// Pick a texture path for the appropriate type ID. Merchant Gambler Blacksmith, 1,2,3
	const std::string texturePath = (type == 1) ? "../Assets/Sprites/Monsters/146.png" :
									(type == 2) ? "../Assets/Sprites/Monsters/111.png" :
												  "../Assets/Sprites/Monsters/115.png" ;

	// [To-do] This will change. Should ask database about this information. This is OK right now due to small amount of variety.
	const std::string npcName = (type == 1) ? "Merchant" : (type == 2) ? "Gambler" : "Blacksmith";

	// Load the texture from the Assets, we will use this to initialize C_Texture component.
	SDL_Texture* tex;
	TextureMgr.LoadTexture(texturePath, &tex);

	// Create In-Common Components.
	auto& C_Texture = npc.AddComponent<TextureComponent>(tex);
	auto& C_SpriteRenderer = npc.AddComponent<SpriteRendererComponent>(TextureMgr.GetDimensions(C_Texture.texture));

	// Set-up component variables.
	npc.GetComponent<EntityDetailsComponent>().name = npcName;
	//C_SpriteRenderer.localScale.x = 0.05f;
	//C_SpriteRenderer.localScale.y = 0.05f;

	return npc.GetRaw();
}
entt::entity Scene::SpawnMonster(float posX, float posY) {
	Core::Entity monster = Core::Entity(this, BaseScene::SpawnMonster(posX, posY));

	// Pick a random monster rarity
	auto& C_MonsterDetails = monster.GetComponent<MonsterDetailsComponent>();

	// [To-do] This will change. Should ask database about this information. This is OK right now due to small amount of variety.
	const std::string npcName = C_MonsterDetails.monsterID == 1 ? "Boar" : "Zombie";
	std::string texturePath = C_MonsterDetails.monsterID == 1 ? "../Assets/Sprites/Monsters/Boar/" : "../Assets/Sprites/Monsters/Zombie/";
	texturePath.append(C_MonsterDetails.rarity == (MonsterRarity)0 ? "common.png" : 
					   C_MonsterDetails.rarity == (MonsterRarity)1 ? "magic.png"  :
					   C_MonsterDetails.rarity == (MonsterRarity)2 ? "rare.png"   :
																	 "unique.png");

	// Load the texture from the Assets, we will use this to initialize C_Texture component.
	SDL_Texture* tex;
	TextureMgr.LoadTexture(texturePath, &tex);

	// Create In-Common Components.
	auto& C_Texture = monster.AddComponent<TextureComponent>(tex);
	monster.AddComponent<SpriteRendererComponent>(TextureMgr.GetDimensions(C_Texture.texture));
	monster.AddComponent<HealthBarComponent>();

	return monster.GetRaw();
}
entt::entity Scene::SpawnMonsterInZone(const Core::ZoneSpawnZoneData& zone) {
	return BaseScene::SpawnMonsterInZone(zone); // This redirects to Scene::SpawnMonster() back.
}