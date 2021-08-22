#pragma once
#include "BaseComponent.h"
#include "Transform.h"
#include <string>

namespace minigin
{
	class Texture2D;
	class TextureComponent : public BaseComponent
	{
	public:
		TextureComponent(const std::shared_ptr<Object>& object, const std::string& filename, const std::string& componentName = "none");
		virtual ~TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		virtual void Awake() override {};
		virtual void Update([[maybe_unused]] float deltaTime) override {};
		virtual void Render() override;

		const Transform& GetTransform() const;
		void SetTransform(const Transform& transform);

		void SetVisible(bool isVisible);

	private:
		std::shared_ptr<Texture2D> m_pTexture{};
		Transform m_Transform;
		bool m_IsVisible;
	};
}
