#ifndef _FPS_H_
#define _FPS_H_

class FPS
{
public:
	FPS();
	FPS(const FPS&);
	~FPS();
	void Initialize();
	void Frame();
	int GetFPS();
private:
	int			  m_Fps, m_count;
	unsigned long m_startTime;
};
#endif