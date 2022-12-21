#include "pch.hpp"
#include "MidiClientKbd.hpp"
#include "utils.hpp"
#include <fcntl.h>
#include <linux/input.h>

MidiClientKbd::MidiClientKbd(const char *clientName, const char *sourceName) : MidiClient(clientName, nullptr)
{
	std::string tmp = "/dev/input/event" + findKbdEvent();
	fd = open(tmp.c_str(), O_RDONLY);
	if (fd == -1)
	{
		throw std::runtime_error("Cannot open typing keyboard file: " + tmp);
	}
	parse_file(sourceName);
}

void MidiClientKbd::run()
{
	ssize_t n;
	struct input_event kbd_ev;
	while (true)
	{
		n = read(fd, &kbd_ev, sizeof kbd_ev);
		if (n == (ssize_t)-1)
		{
			if (errno == EINTR)
			{
				continue;
			}
			throw std::runtime_error("Error reading typing keyboard");
		}
		if (n != sizeof kbd_ev)
			continue;
		if (kbd_ev.type != EV_KEY)
			continue;

		LOG(LogLvl::DEBUG) << "Typing keyboard: " << kbd_ev.value << " " << kbd_ev.code;

		if (kbd_ev.value < 0 || kbd_ev.value > 1)
			continue;
		if (kbdMap.find((int)kbd_ev.code) == kbdMap.end())
			continue;

		snd_seq_event_t event;
		snd_seq_ev_clear(&event);
		event.type = SND_SEQ_EVENT_NOTEON;
		event.data.note.channel = 0;
		event.data.note.note = kbdMap.at((int)kbd_ev.code);
		event.data.note.velocity = kbd_ev.value == 0 ? 0 : 100;

		LOG(LogLvl::DEBUG) << "Send ch:note:vel: " << event.data.note.channel << ":" << event.data.note.note << ":" << event.data.note.velocity;

		send_event(&event);
	}
}

void MidiClientKbd::parse_string(const std::string &s1)
{
	std::string s(s1);
	remove_spaces(s);
	if (s.empty())
		return;

	std::vector<std::string> parts = split_string(s, "=");
	if (parts.size() != 2)
	{
		throw std::runtime_error("Keyboard mapping must have 2 parts: " + s);
	}

	try
	{
		int n1 = std::stoi(parts[0]);
		int n2 = std::stoi(parts[1]);
		LOG(LogLvl::DEBUG) << "Mapping typing key code to note: " << n1 << "=" << n2;
		kbdMap.insert({n1, n2});
	}
	catch (std::exception &e)
	{
		throw std::runtime_error("Keyboard mapping must have numbers on both sides of '=': " + s);
	}
}

void MidiClientKbd::parse_file(const char *kbdMapFile)
{
	std::ifstream f(kbdMapFile);
	std::string s;
	int k = 0;
	while (getline(f, s))
	{
		try
		{
			k++;
			parse_string(s);
		}
		catch (std::exception &e)
		{
			LOG(LogLvl::ERROR) << "Line: " << k << " in " << kbdMapFile << " Error: "
							   << e.what();
		}
	}
}
