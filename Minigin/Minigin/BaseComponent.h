#pragma once

class Object;
class BaseComponent
{
public:
	BaseComponent(Object* object) { m_pObject = object; };
	virtual ~BaseComponent() = default;
	BaseComponent(const BaseComponent& other) = delete;
	BaseComponent(BaseComponent&& other) = delete;
	BaseComponent& operator=(const BaseComponent& other) = delete;
	BaseComponent& operator=(BaseComponent&& other) = delete;

	void RemoveObject() { m_pObject = nullptr; };

	virtual void Awake() = 0;
	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void LateUpdate(float deltaTime) = 0;
	virtual void Draw() = 0;

protected:

	Object* m_pObject;
};