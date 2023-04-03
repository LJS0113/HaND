#pragma once


enum class eSceneType
{
	Title,
	Loading,
	Play,
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
	Test,
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