#pragma once


enum class eSceneType
{
	Title,
	Loading,
	Play,
	Hung,
	Brad,
	BradV2,
	Waldo,
	Ending,

	Tool,
	End,
};

enum class eLayerType
{
	BG,
	Tile,
	Monster,
	Player,
	Bullet,
	Ground,
	Effect,

	UI,
	End = 16,
};

enum class eComponentType
{
	Transform,
	SpriteRenderer,
	Animator,
	Collider,
	Rigidbody,
	Audio,
	End,
};