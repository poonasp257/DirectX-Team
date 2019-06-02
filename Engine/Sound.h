#ifndef _SOUND_H_
#define _SOUND_H_

class Sound
{
private:
	struct WaveHeaderType
	{
		char chunkId[4];
		unsigned long chunkSize;
		char format[4];
		char subChunkId[4];
		unsigned long subChunkSize;
		unsigned short audioFormat;
		unsigned short numChannels;
		unsigned long sampleRate;
		unsigned long bytesPerSecond;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		char dataChunkId[4];
		unsigned long dataSize;
	};
public:
	Sound();
	Sound(const Sound&);
	~Sound();
	bool Initialize(HWND);
	void Shutdown();
private:
	bool InitializeDirectSound(HWND);
	void ShutdownDirectSound();
	bool LoadWaveFile(char*, IDirectSoundBuffer8**);
	void ShutdownWaveFile(IDirectSoundBuffer8**);
	bool PlayWaveFile();
private:
	IDirectSound8		*m_DirectSound;
	IDirectSoundBuffer	*m_primaryBuffer;
	IDirectSoundBuffer8	*m_secondaryBuffer1;
};
#endif