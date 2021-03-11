
#include "TimeManager.h"
#include "AudioClip.h"
#include "Nalmak_Struct.h"
#include "SoundManager.h"
#include "ResourceManager.h"

IMPLEMENT_SINGLETON(SoundManager)

SoundManager::SoundManager()
	:m_volumeRatio(1), m_b3DSound(false)
{
}
SoundManager::~SoundManager()
{
	Release();
}
void SoundManager::Initialize()
{


	m_resourceManager = ResourceManager::GetInstance();

	for (int i = 0; i < SOUND_CHANNEL_COUNT_MAX; ++i)
	{
		m_pChannelArr[i].first = true;
		m_pChannelArr[i].second = nullptr;
	}

	FMOD_RESULT eRes;
	eRes = FMOD_System_Create(&m_pSystem);
	if (eRes != FMOD_OK)
	{
		assert(L"Failed to FMod System Create! " && 0);
	}

	eRes = FMOD_System_Init(m_pSystem, SOUND_CHANNEL_COUNT_MAX, FMOD_INIT_NORMAL, NULL);
	if (eRes != FMOD_OK)
	{
		assert(L"Failed to FMod Initialize! " && 0);
	}


	//if (m_b3DSound)
	//{
	//	// Set Listner Position
	//	eRes = FMOD_System_Set3DListenerAttributes(m_pSystem, 0, 0, 0, 0, 0);
	//	if (eRes != FMOD_OK)
	//	{
	//		assert(L"Failed to Create 3D Listener Attribute! " && 0);
	//	}

	//	for (auto& c : m_pChannelArr)
	//	{
	//		c.position = new Vector3(0, 0, 0);
	//	}
	//}


}

void SoundManager::Update()
{
	FMOD_System_Update(m_pSystem);

	//PrintInfo();

}

void SoundManager::Release()
{
	FMOD_System_Close(m_pSystem);
	FMOD_System_Release(m_pSystem);
}

void SoundManager::Play(AudioSource * _source, const _SOUND_CHANNEL & _channel)
{
	auto audioClip = _source->GetAudioClip();

	FMOD_Channel_Stop(m_pChannelArr[_channel].second);

	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, audioClip->m_audio, FALSE, &m_pChannelArr[_channel].second);

	FMOD_Channel_SetVolume(m_pChannelArr[_channel].second, audioClip->volume * m_volumeRatio);

	if (audioClip->loop)
		FMOD_Channel_SetMode(m_pChannelArr[_channel].second, FMOD_LOOP_NORMAL);
	else
		FMOD_Channel_SetMode(m_pChannelArr[_channel].second, FMOD_LOOP_OFF);

	FMOD_System_Update(m_pSystem);
}

void SoundManager::PlayOneShot(AudioSource * _source, AudioClip * _audioClip)
{
	int availAbleIndex = GetAvailableChannel();
	if (availAbleIndex == -1)
		return;

	m_pChannelArr[availAbleIndex].first = true;

	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, _audioClip->m_audio, FALSE, &m_pChannelArr[availAbleIndex].second);

	FMOD_Channel_SetVolume(m_pChannelArr[availAbleIndex].second, _audioClip->volume * m_volumeRatio);

	FMOD_Channel_SetMode(m_pChannelArr[availAbleIndex].second, FMOD_LOOP_OFF);
		
}



void SoundManager::PlayOneShot(AudioSource * _clip, const wstring & _clipName)
{
	int availAbleIndex = GetAvailableChannel();
	if (availAbleIndex == -1)
		return;
	auto audioclip = m_resourceManager->GetResource<AudioClip>(_clipName);

	m_pChannelArr[availAbleIndex].first = true;

	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, audioclip->m_audio, FALSE, &m_pChannelArr[availAbleIndex].second);

	FMOD_Channel_SetVolume(m_pChannelArr[availAbleIndex].second, audioclip->volume * m_volumeRatio);

	FMOD_Channel_SetMode(m_pChannelArr[availAbleIndex].second, FMOD_LOOP_OFF);
}

bool SoundManager::IsPlay(const _SOUND_CHANNEL & _channel)
{
	if (_channel == -1)
		return false;

	FMOD_BOOL isPlay = false;
	FMOD_Channel_IsPlaying(m_pChannelArr[_channel].second, &isPlay);

	if (isPlay == 1)
		return true;
	return false;
}

//void SoundManager::Play(AudioClip * _clip, const int& _channel)
//{
//	AudioClip* pAudioClip = _clip;
//	FMOD_Channel_Stop(m_pChannelArr[_channel].channel);
//
//
//	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, pAudioClip->m_audio, FALSE, &m_pChannelArr[_channel].channel);
//	m_pChannelArr[_channel].currentClip = pAudioClip;
//
//	//if (m_b3DSound)
//	//{
//	//	FMOD_Channel_Set3DSpread(m_pChannelArr[_channel].channel, 360);
//	//	// Set Audio Speaker Position
//	//	//m_pChannelArr[eChannel].position->x = CycleMove;
//	//	FMOD_VECTOR vec;
//	//	vec.x = m_pChannelArr[_channel].position->x;
//	//	vec.y = m_pChannelArr[_channel].position->y;
//	//	vec.z = m_pChannelArr[_channel].position->z;
//
//	//	FMOD_Channel_Set3DAttributes(m_pChannelArr[_channel].channel, &vec, 0);
//	//}
//	FMOD_Channel_SetVolume(m_pChannelArr[_channel].channel, m_pChannelArr[_channel].currentClip->volume * m_volumeRatio);
//
//	if (pAudioClip->loop)
//		FMOD_Channel_SetMode(m_pChannelArr[_channel].channel, FMOD_LOOP_NORMAL);
//	else
//		FMOD_Channel_SetMode(m_pChannelArr[_channel].channel, FMOD_LOOP_OFF);
//	FMOD_System_Update(m_pSystem);
//}
//
//
//void SoundManager::Play(const wstring& _clip, const int & _channel)
//{
//	AudioClip* pAudioClip = m_resourceManager->GetResource<AudioClip>(_clip);
//	FMOD_Channel_Stop(m_pChannelArr[_channel].channel);
//
//
//	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, pAudioClip->m_audio, FALSE, &m_pChannelArr[_channel].channel);
//
//	m_pChannelArr[_channel].currentClip = pAudioClip;
//
//	if (m_b3DSound)
//	{
//		FMOD_Channel_Set3DSpread(m_pChannelArr[_channel].channel, 360);
//		// Set Audio Speaker Position
//		//m_pChannelArr[eChannel].position->x = CycleMove;
//		FMOD_VECTOR vec;
//		vec.x = m_pChannelArr[_channel].position->x;
//		vec.y = m_pChannelArr[_channel].position->y;
//		vec.z = m_pChannelArr[_channel].position->z;
//
//		FMOD_Channel_Set3DAttributes(m_pChannelArr[_channel].channel, &vec, 0);
//	}
//	FMOD_Channel_SetVolume(m_pChannelArr[_channel].channel, m_pChannelArr[_channel].currentClip->volume * m_volumeRatio);
//
//	if (pAudioClip->loop)
//		FMOD_Channel_SetMode(m_pChannelArr[_channel].channel, FMOD_LOOP_NORMAL);
//	else
//		FMOD_Channel_SetMode(m_pChannelArr[_channel].channel, FMOD_LOOP_OFF);
//	FMOD_System_Update(m_pSystem);
//}

//void SoundManager::Play(const wstring& _pSoundKey)
//{
//	auto pAudioClip = m_resourceManager->GetResource<AudioClip>(_pSoundKey);
//
//	int eChannel = pAudioClip->channel;
//	Play(pAudioClip, eChannel);
//}
//
//
//bool SoundManager::IsPlay(_SOUND_CHANNEL _channel)
//{
//	FMOD_BOOL isPlay = false;
//	FMOD_Channel_IsPlaying(m_pChannelArr[_channel].channel, &isPlay);
//
//	if (isPlay == 1)
//		return true;
//	return false;
//}
//
//void SoundManager::PlayEffect(const wstring& _pSoundKey)
//{
//	auto pAudioClip = m_resourceManager->GetResource<AudioClip>(_pSoundKey);
//	if (pAudioClip == nullptr)
//		return;
//
//	int eChannel = GetAvailableChannel(pAudioClip->channel);
//	Play(pAudioClip, eChannel);
//
//}
//
//void SoundManager::PlayEffect(AudioClip * _clip)
//{
//	int eChannel = GetAvailableChannel(_clip->channel);
//	Play(_clip, eChannel);
//}
//
//
//void SoundManager::Pause(_SOUND_CHANNEL _channel)
//{
//	FMOD_Channel_SetPaused(m_pChannelArr[_channel].channel, true);
//}
//
//void SoundManager::Resume(_SOUND_CHANNEL _channel)
//{
//	FMOD_Channel_SetPaused(m_pChannelArr[_channel].channel, false);
//}
//
//void SoundManager::Pause()
//{
//	for (auto& c : m_pChannelArr)
//	{
//		FMOD_Channel_SetPaused(c.channel, true);
//	}
//}
//
//void SoundManager::Resume()
//{
//	for (auto& c : m_pChannelArr)
//	{
//		FMOD_Channel_SetPaused(c.channel, false);
//	}
//}
//
//
//
//void SoundManager::Stop(_SOUND_CHANNEL  _channel)
//{
//	FMOD_Channel_Stop(m_pChannelArr[_channel].channel);
//}
//
//
//void SoundManager::SetVolumeRatio(_SOUND_CHANNEL _channel, float _ratio)
//{
//	FMOD_Channel_SetVolume(m_pChannelArr[_channel].channel, m_pChannelArr[_channel].currentClip->volume * _ratio);
//}
//
//void SoundManager::SetVolume(_SOUND_CHANNEL _channel, float _volume)
//{
//	FMOD_Channel_SetVolume(m_pChannelArr[_channel].channel, _volume);
//}
//
//void SoundManager::Stop()
//{
//	for (auto& c : m_pChannelArr)
//	{
//		FMOD_Channel_Stop(c.channel);
//	}
//}

//void SoundManager::SetMaterVolume(float _v)
//{
//	m_volumeRatio = _v;
//
//
//	/*for (auto& c : m_pChannelArr)
//	{
//		FMOD_Channel_SetVolume(c.channel, c.currentClip->volume * m_volumeRatio);
//	}*/
//}

//bool SoundManager::CompareCurrentClip(_SOUND_CHANNEL _channel, const wstring& pSoundKey)
//{
//	auto pAudioClip = m_resourceManager->GetResource<AudioClip>(pSoundKey); 
//	assert("Clip isn't exist" && pAudioClip);
//
//	if (m_pChannelArr[_channel].currentClip == pAudioClip)
//		return true;
//
//	return false;
//}

int SoundManager::GetAvailableChannel()
{
	for (int i = 0; i < SOUND_CHANNEL_COUNT_MAX; ++i)
	{
		if (m_pChannelArr[i].first)
		{
			m_pChannelArr[i].first = false;
			return i;
		}
	}
	return -1;
	//FMOD_BOOL isPlay;
	//// Find empty Channel 
	//// if exist empty channel then return index
	//for (unsigned int i = m_NumOfChannel_ExcludingEffects; i < m_pChannelArr.size(); ++i)
	//{
	//	if (!FMOD_Channel_IsPlaying(m_pChannelArr[i].channel, &isPlay))
	//	{
	//		continue;
	//	}
	//	else
	//	{
	//		m_publicSoundPriority.remove(i);
	//		m_publicSoundPriority.emplace_back(i);
	//		return i;
	//	}
	//}

	//int index = *m_publicSoundPriority.begin();
	//m_publicSoundPriority.pop_front();
	//m_publicSoundPriority.emplace_back(index);
	//return index;
}





_SOUND_CHANNEL SoundManager::AllocChannel()
{
	return GetAvailableChannel();
}

void SoundManager::DeAllocChannel(_SOUND_CHANNEL _channel)
{
	if(_channel != -1)
		m_pChannelArr[_channel].first = true;
}


//AudioClip * SoundManager::GetAudioClip(const wstring& _pSoundKey)
//{
//	if (m_SoundList.empty())
//		return nullptr;
//
//	auto iter = find_if(m_SoundList.begin(), m_SoundList.end(), [&](auto& Pair)->bool { return lstrcmp(_pSoundKey, Pair.first) == 0; });
//	if (m_SoundList.end() == iter)
//		return nullptr;
//
//	return iter->second;
//}

void SoundManager::SetListenerPosition(float _x, float _y, float _z)
{
	FMOD_VECTOR* vec = new FMOD_VECTOR{ _x,_y,_z };
	FMOD_System_Set3DListenerAttributes(m_pSystem, 0, vec, 0, 0, 0);
}
