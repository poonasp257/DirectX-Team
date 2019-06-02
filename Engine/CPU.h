#ifndef _CPU_H_
#define _CPU_H_

class CPU
{
public:
	CPU();
	CPU(const CPU&);
	~CPU();
	void Initialize();
	void Shutdown();
	void Frame();
	int GetCPUPercentage();
private:
	bool m_canReadCpu;
	HQUERY m_queryHandle;
	HCOUNTER m_counterHandle;
	unsigned long m_lastSampleTime;
	long m_cpuUsage;
};
#endif