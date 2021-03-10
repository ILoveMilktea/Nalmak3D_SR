#include "..\Include\AudioSource.h"
#include "SoundManager.h"




AudioSource::AudioSource(Desc * _desc)
{
	if(_desc->audioClipName != L"")
		m_audioClip = ResourceManager::GetInstance()->GetResource<AudioClip>(_desc->audioClipName);
}

AudioSource::~AudioSource()
{
}

void AudioSource::Initialize()
{
	m_soundManager = SoundManager::GetInstance();

}

void AudioSource::Update()
{
	DEBUG_LOG(L"Playing ", IsPlay());
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_C))
	{
		Play();
	}
	if (InputManager::GetInstance()->GetKeyDown(KEY_STATE_D))
	{
		PlayOneShot(L"sfx_titleToStage");
	}


	if (m_isPlay)
	{
		if (!IsPlay())
		{
			m_isPlay = false;
			m_soundManager->DeAllocChannel(m_channelIndex);
		}
	}
	
}

void AudioSource::Release()
{
}

void AudioSource::SetAudioClip(const wstring & _audioClip)
{
	m_audioClip = ResourceManager::GetInstance()->GetResource<AudioClip>(_audioClip);
}

void AudioSource::Play()
{
	assert(L"Audio clip is null! " && m_audioClip);

	if (m_isPlay)
	{
		m_soundManager->Play(this, m_channelIndex); 
	}
	else
	{
		m_soundManager->DeAllocChannel(m_channelIndex);

		m_channelIndex = m_soundManager->AllocChannel();
		if (-1 == m_channelIndex)
			return;
		m_soundManager->Play(this, m_channelIndex);

		m_isPlay = true;
	}
	
}

void AudioSource::PlayOneShot(const wstring & _audioClip)
{
	m_soundManager->PlayOneShot(this, _audioClip);
}

bool AudioSource::IsPlay()
{
	return m_soundManager->IsPlay(m_channelIndex);
}

void AudioSource::Stop()
{
}
