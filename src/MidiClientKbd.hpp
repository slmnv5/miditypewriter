#ifndef MIDICLIENTKBD_H
#define MIDICLIENTKBD_H
#include "pch.hpp"

#include "MidiClientKbd.hpp"

class MidiClientKbd : public MidiClient
{
private:
	std::map<int, int> kbdMap;
	int fd;

public:
	MidiClientKbd(const char *clientName, const char *sourceName);
	virtual ~MidiClientKbd()
	{
	}
	void run();

private:
	void parse_string(const std::string &s);
	void parse_file(const char *kbdMapFile);
};

#endif
