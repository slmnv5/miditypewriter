#ifndef MIDIKEYSCLIENT_H
#define MIDIKEYSCLIENT_H

#include "pch.hpp"
#include "MidiClient.hpp"

class MidiKeysClient : public MidiClient
{
private:
	std::map<int, int> kbdMap;
	int fd;

public:
	MidiKeysClient(const char *clientName, const char *sourceName);
	virtual ~MidiKeysClient()
	{
	}
	void run();

private:
	void parse_string(const std::string &s);
	void parse_file(const char *kbdMapFile);
};

#endif
