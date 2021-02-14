#include "..\Include\IResource.h"
#include "DeviceManager.h"
USING(Nalmak)

IResource::IResource()
{
	m_device = DeviceManager::GetInstance()->GetDevice();
}
