#ifndef __j1PERFTIMER_H__
#define __j1PERFTIMER_H__

#include "p2Defs.h"

class j1PerfTimer
{
public:

	// Constructor
	j1PerfTimer();

	void Start();
	double ReadMs() const;
	Uint64 ReadTicks() const;

private:
	Uint64	started_at;
	static Uint64 frequency;
};

#endif //__j1PERFTIMER_H__