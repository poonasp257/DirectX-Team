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
	
	bool Initialize(HWND, const char* fileName);
	void Shutdown();

	bool PlayWaveFile(long volume, bool loop);
	bool StopWaveFile();

private:
	bool InitializeDirectSound(HWND);
	void ShutdownDirectSound();
	bool LoadWaveFile(const char*, IDirectSoundBuffer8**);
	void ShutdownWaveFile(IDirectSoundBuffer8**);
private:
	IDirectSound8		*m_DirectSound;
	IDirectSoundBuffer	*m_primaryBuffer;
	IDirectSoundBuffer8	*m_secondaryBuffer1;
};
#endif