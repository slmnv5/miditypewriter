#ifndef MIDIKEYSCLIENT_H
#define MIDIKEYSCLIENT_H

#include "pch.hpp"
#include "MidiClient.hpp"

class MidiKeysClient : public MidiClient
{
private:
	std::map<int, int> mKbdMap;
	int mFdKbd;

public:
	MidiKeysClient(const char *kbdMapFile, const char *clientName, const char *dstName);
	virtual ~MidiKeysClient()
	{
	}
	void run();

private:
	void parse_string(const std::string &s);
	void parse_file(const char *kbdMapFile);
};

#endif
