#pragma once

#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "Nalmak_Include.h"
#include "LineManager.h"
#include "ResourceManager.h"
#include "DeviceManager.h"
#include "DebugManager.h"
#include "ICycle.h"
#include "TimeManager.h"
#include "GameObject.h"
BEGIN(Nalmak) 
class Transform;

class NALMAK_DLL Component : public ICycle
{
	friend class GameObject;
protected:
	explicit Component();
	virtual ~Component();

protected:
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	virtual void Initialize()override = 0;
	virtual void Update()override = 0;
	virtual void LateUpdate()override;
	virtual void Release()override;
	virtual void PreRender()override;
	virtual void PostRender()override;
	virtual void OnTriggerEnter(Collisions& _collision)override;
	virtual void OnTriggerStay(Collisions& _collision)override;
	virtual void OnTriggerExit(Collisions& _collision)override;

private:
	template <typename T>
	static Component* Create(typename T::Desc* _desc)
	{
		Component* instance = new T(_desc);
		instance->m_name = typeid(T).name();

		assert("Fail to Create Component" &&instance);
		return instance;
	}
public:
	template <typename T>
	T* GetComponent()
	{
		return m_gameObject->GetComponent<T>();
	}
	template <typename T>
	void DeleteComponent()
	{
		m_gameObject->DeleteComponent<T>();
	}
	template <typename T>
	GameObject* AddComponent(typename T::Desc* _desc)
	{
		return m_gameObject->AddComponent<T>(_desc);
	}
	template <typename T>
	GameObject* AddComponent()
	{
		typename T::Desc desc;
		return m_gameObject->AddComponent<T>(&desc);
	}
public:
	virtual void SetActive(bool _active);
	bool GetActive();
protected:
	GameObject* m_gameObject;
	Transform* m_transform;
public:
	void SetPosition(const Vector3& _pos);
	void SetScale(const Vector3& _scale);

	void SetGameObject(GameObject* _obj) { assert("Object is nullptr" && _obj); m_gameObject = _obj; }
	virtual void SetTransform(Transform* _transform) { assert("Transform is nullptr" && _transform);  m_transform = _transform; }
public:
	GameObject* GetGameObject() { return m_gameObject; }
	Transform* GetTransform() { return m_transform; }
private:
	const char* m_name;
	bool m_active;
	bool m_dead;

};

END

#endif // !__COMPONENT_H__
