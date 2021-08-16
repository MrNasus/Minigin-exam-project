#pragma once

namespace minigin
{
	struct Rotation2D
	{
		float z = 0.f;
	};

	struct Position2D
	{
		float x = 0.f;
		float y = 0.f;
	};

	struct Scale2D
	{
		float x = 1.f;
		float y = 1.f;
	};

	struct Transform2D
	{
		Position2D position;
		Rotation2D rotation;
		Scale2D scale;
	};
}