#include "..\Include\AudioClip.h"
#include "SoundManager.h"

#include <fstream>

AudioClip::AudioClip()
{
}


AudioClip::~AudioClip()
{
}

void AudioClip::Initialize(wstring _fp)
{
	//FMOD_DEFAULT-> FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE

	string path;
	path.assign(_fp.begin(), _fp.end());

	ifstream file(path.c_str());

	string buffer;
	size_t length = 0;

	while (true)
	{
		getline(file, buffer);
		if ('#' == buffer[0] || "" == buffer)
			continue;

		// 항목 확인
		size_t firstWordEnd;
		for (firstWordEnd = 0; firstWordEnd < buffer.size(); ++firstWordEnd)
		{
			if (' ' == buffer[firstWordEnd])
				break;
		}

		string memberName = buffer.substr(0, firstWordEnd);

		// 다음 " 찾기
		while ('\"' != buffer[firstWordEnd])
		{
			++firstWordEnd;
		}
		++firstWordEnd;

		// 1. loop
		if (strcmp(memberName.c_str(), "loop") == 0)
		{
			// handle name
			size_t handleNameEnd;
			for (handleNameEnd = firstWordEnd; handleNameEnd < buffer.size(); ++handleNameEnd)
			{
				if ('\"' == buffer[handleNameEnd])
					break;
			}

			string handleName = buffer.substr(firstWordEnd, handleNameEnd - firstWordEnd);

			//// 다음 " 찾기
			//++handleNameEnd;
			//while ('\"' != buffer[handleNameEnd])
			//{
			//	++handleNameEnd;
			//}
			//++handleNameEnd;

			//// value
			//size_t valueEnd;
			//for (valueEnd = handleNameEnd; valueEnd < buffer.size(); ++valueEnd)
			//{
			//	if ('\"' == buffer[valueEnd])
			//		break;
			//}

			//string subBuffer = buffer.substr(handleNameEnd, valueEnd - handleNameEnd);

			if (strcmp(handleName.c_str(), "true") == 0)
				loop = true;
			else
				loop = false;
		}

		// 2. channel
		if (strcmp(memberName.c_str(), "channel") == 0)
		{
			size_t handleNameEnd;
			for (handleNameEnd = firstWordEnd; handleNameEnd < buffer.size(); ++handleNameEnd)
			{
				if ('\"' == buffer[handleNameEnd])
					break;
			}
			string handleName = buffer.substr(firstWordEnd, handleNameEnd - firstWordEnd);
			channel = atoi(handleName.c_str());
		}

		// 3. volume
		if (strcmp(memberName.c_str(), "volume") == 0)
		{
			// handle name
			size_t handleNameEnd;
			for (handleNameEnd = firstWordEnd; handleNameEnd < buffer.size(); ++handleNameEnd)
			{
				if ('\"' == buffer[handleNameEnd])
					break;
			}
			string handleName = buffer.substr(firstWordEnd, handleNameEnd - firstWordEnd);
			volume = (float)atof(handleName.c_str());
		}
		// 3. max distance
		if (strcmp(memberName.c_str(), "maxDistance") == 0)
		{
			// handle name
			size_t handleNameEnd;
			for (handleNameEnd = firstWordEnd; handleNameEnd < buffer.size(); ++handleNameEnd)
			{
				if ('\"' == buffer[handleNameEnd])
					break;
			}
			string handleName = buffer.substr(firstWordEnd, handleNameEnd - firstWordEnd);
			maxDistance = (float)atof(handleName.c_str());
			break;
		}
	}

	//string audioFilePath;
	//string extention[5] = { ".mp3",".mp4", ".wav", ".mkv", ".ogg" };
	////FMOD_3D
	//for (int i = 0; i < 5; ++i)
	//{
	//	audioFilePath = path + extention[i];
	//	FMOD_RESULT eRes = FMOD_System_CreateSound(SoundManager::GetInstance()->GetFModSystem(), audioFilePath.c_str(), FMOD_HARDWARE , 0, &pAudio);
	//	if (eRes == FMOD_OK)
	//	{
	//		break;
	//	}
	//}
	string extention[5] = { ".mp3",".mp4", ".wav", ".mkv", ".ogg" };


	//FMOD_3D
	size_t targetNum = path.find_last_of(".");
	string fileName = path.substr(0, targetNum);
	fileName = fileName + ".wav";

	auto fmodeSystem = SoundManager::GetInstance()->GetFModSystem();
	assert(L"fmode system is nullptr! " && fmodeSystem);
	FMOD_RESULT eRes = FMOD_System_CreateSound(fmodeSystem, fileName.c_str(), FMOD_HARDWARE, 0, &m_audio);
	if (eRes != FMOD_OK)
	{
		assert(L"Failed to Create AudioClip! " && 0);
	}
}

void AudioClip::Release()
{
	if (!m_audio)
		return;

	FMOD_Sound_Release(m_audio);
	m_audio = nullptr;
}
