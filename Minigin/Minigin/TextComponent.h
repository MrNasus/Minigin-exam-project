#pragma once
#include "BaseComponent.h"
#include "Transform.h"
#include <string>

namespace minigin
{
	class Font;
	class Texture2D;
	class TextComponent : public BaseComponent
	{
	public:
		TextComponent(const std::shared_ptr<Object>& object, const std::string& text, const std::string& filepath, int fontSize);
		TextComponent(const std::shared_ptr<Object>& object, const std::string& text, const std::string& filepath, int fontSize, int r, int g, int b);
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		virtual void Awake() override {};
		virtual void Update([[maybe_unused]] float deltaTime) override {};
		virtual void Render() override;

		const Transform& GetTransform() const;
		void SetTransform(const Transform & transform);

		void SetVisible(bool isVisible);

	private:
		std::shared_ptr<Texture2D> m_pTexture{};
		std::shared_ptr<Font> m_pFont;
		std::string m_Text;
		Transform m_Transform;
		bool m_IsVisible;
	};

}