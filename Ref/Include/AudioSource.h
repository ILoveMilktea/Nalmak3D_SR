#pragma once
#include "Component.h"
class NALMAK_DLL AudioSource :
	public Component
{
public:
	struct Desc
	{
		wstring audioClipName = L"";
	};
public:
	AudioSource(Desc* _desc);
	~AudioSource();
private:
	// Component을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;
public:
	void SetAudioClip(const wstring& _audioClip);
	void Play();
	void PlayOneShot(const wstring& _audioClip);
	bool IsPlay();
	void Stop();
	AudioClip* GetAudioClip() { return m_audioClip; }
private:
	AudioClip* m_audioClip = nullptr;
	class SoundManager* m_soundManager = nullptr;
	_SOUND_CHANNEL m_channelIndex;
	bool m_isPlay;
};

