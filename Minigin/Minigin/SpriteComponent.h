#pragma once
#include "BaseComponent.h"
#include "Transform.h"
#include "HitboxStruct.h"
#include <string>

namespace minigin
{
	class Texture2D;
	class SpriteComponent : public BaseComponent
    {
	public:
		//only supports horizontal sprites
		SpriteComponent(const std::shared_ptr<Object>& object, const std::string& filename, int nrOfFrames, float loopTime);
		virtual ~SpriteComponent() = default;
		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) = delete;

		virtual void Awake() override {};
		virtual void Update(float deltaTime) override;
		virtual void Render() override;

		const Transform& GetTransform() const;
		void SetTransform(const Transform & transform);

		int GetFrameHeight() const;
		int GetFrameWidth() const;
		float GetTextureHeight() const;

		void SetFrameHeight(int height);

		void SetVisible(bool isVisible);

	private:
		std::shared_ptr<Texture2D> m_pTexture{};
		Transform m_Transform;
		bool m_IsVisible;

		int m_TextureWidth;
		int m_TextureHeight;

		int m_FrameWidth;
		int m_FrameHeight;

		int m_NrOfFrames;
		int m_CurrentFrame;
		float m_SecPerFrame;
		float m_AccuSec;
	};

}