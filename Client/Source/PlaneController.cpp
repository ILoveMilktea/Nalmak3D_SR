#include "stdafx.h"
#include "..\Include\PlaneController.h"
#include "PlaneInfo.h"


PlaneController::PlaneController(Desc * _desc)
{
}

PlaneController::~PlaneController()
{
}


void PlaneController::Initialize()
{
	m_rigidbody = GetComponent<Rigidbody>();
	m_input = InputManager::GetInstance();
}

void PlaneController::Update()
{
	//m_rigidbody->AddForce(m_planeInfo->GetDefaultForce());
	if (m_input->GetKeyPress(KEY_STATE::KEY_STATE_UP_ARROW))
	{
		m_rigidbody->SetVelocity(m_transform->GetForward() * 5);
	//	m_rigidbody->AddForce(* 50.f);

	}
	else if(m_input->GetKeyPress(KEY_STATE::KEY_STATE_DOWN_ARROW))
	{
		m_rigidbody->SetVelocity(-m_transform->GetForward() * 5);
	}
	else
	{
		m_rigidbody->SetVelocity(Vector3(0,0,0));
	}
	float zAngle = m_planeInfo->GetZAngle();

	if (m_input->GetKeyPress(KEY_STATE::KEY_STATE_LEFT_ARROW))
	{
		zAngle = Nalmak_Math::Lerp(zAngle, -50.f, dTime);
		//MoveLeft();
	}
	else if (m_input->GetKeyPress(KEY_STATE::KEY_STATE_RIGHT_ARROW))
	{
		zAngle = Nalmak_Math::Lerp(zAngle, 50.f, dTime);
	}
	else
	{
		zAngle = Nalmak_Math::Lerp(zAngle, 0.f, dTime * 3);
	}

	m_transform->RotateY(zAngle);
	//m_planeInfo->SetZAngle(zAngle);

	//D3DXQuaternionRotationYawPitchRoll(&m_transform->rotation, Deg2Rad * m_planeInfo->GetYAngle(), Deg2Rad *m_planeInfo->GetXAngle(), Deg2Rad * m_planeInfo->GetZAngle());
	////m_rigidbody->SetAngularVelocity(rotPower);

	//Vector3 currentVelocity = m_rigidbody->GetVelocity();
	//if (Nalmak_Math::Magnitude(currentVelocity) > 3)
	//{
	//	m_rigidbody->SetVelocity(Nalmak_Math::Normalize(currentVelocity) * 3);
	//}

	m_rigidbody->GetAngularVelocity();


	// 단순히 각도로 limit 거는게 아니라, 수평 상태의 축들이랑 현재 forward, up, right 방향을 비교해서 그 사이각을 재야할듯?
	/*CorrectRoll();
	CorrectPitch();
	CorrectYaw();*/

}

void PlaneController::LateUpdate()
{
}


void PlaneController::MoveLeft()
{
	Vector3 forward = m_transform->GetForward();
	Vector3 right = m_transform->GetRight();
	Vector3 up = m_transform->GetUp();

	// left move
	//m_rigidbody->AddForce(-right * 50.f);
	// roll, yaw rotation
	m_rigidbody->AddTorque(forward * 10.f);
	m_rigidbody->AddTorque(-up * 10.f);

}

void PlaneController::MoveRight()
{
	Vector3 forward = m_transform->GetForward();
	Vector3 right = m_transform->GetRight();
	Vector3 up = m_transform->GetUp();

	// right move
	//m_rigidbody->AddForce(right * 50.f);
	// roll, yaw rotation
	m_rigidbody->AddTorque(-forward * 10.f);
	//m_rigidbody->AddTorque(up * 50.f);
}

void PlaneController::MoveFront()
{
}

void PlaneController::MoveUp()
{
	Vector3 right = m_transform->GetRight();
	Vector3 up = m_transform->GetUp();

	// up move
	m_rigidbody->AddForce(up * 50.f);
	// pitch rotate
	m_rigidbody->AddTorque(-right * 50.f);
}

void PlaneController::MoveDown()
{
	Vector3 right = m_transform->GetRight();
	Vector3 up = m_transform->GetUp();

	// down move
	m_rigidbody->AddForce(-up * 50.f);
	// pitch rotate
	m_rigidbody->AddTorque(right * 50.f);
}

void PlaneController::RecoverRotateHorizotal()
{

}