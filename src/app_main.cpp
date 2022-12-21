#include "pch.hpp"
#include "lib/log.hpp"

#include "MidiKeysClient.hpp"

void help();

int main(int argc, char *argv[])
{

	const char *clientName = nullptr;
	const char *kbdMapFile = nullptr;
	LOG::ReportingLevel() = LogLvl::ERROR;

	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-n") == 0 && i + 1 < argc)
		{
			clientName = argv[i + 1];
		}
		else if (strcmp(argv[i], "-k") == 0 && i + 1 < argc)
		{
			kbdMapFile = argv[i + 1];
		}
		else if (strcmp(argv[i], "-v") == 0)
		{
			LOG::ReportingLevel() = LogLvl::WARN;
		}
		else if (strcmp(argv[i], "-vv") == 0)
		{
			LOG::ReportingLevel() = LogLvl::INFO;
		}
		else if (strcmp(argv[i], "-vvv") == 0)
		{
			LOG::ReportingLevel() = LogLvl::DEBUG;
		}
		else if (strcmp(argv[i], "-h") == 0)
		{
			help();
			return 0;
		}
	}

	if (clientName == nullptr)
		clientName = "pimidikeys";

	LOG(LogLvl::INFO) << "MIDI client name: " << clientName;

	try
	{

		MidiKeysClient midiKeysClient(kbdMapFile, clientName, nullptr);
		LOG(LogLvl::INFO) << "Using typing keyboard as source with map: " << kbdMapFile;
		LOG(LogLvl::INFO) << "Starting MIDI messages processing";
		midiKeysClient.run();
	}
	catch (std::exception &e)
	{
		LOG(LogLvl::ERROR) << "Completed with error: " << e.what();
		return 1;
	}
}

void help()
{
	cout << "Usage: sudo ./pimidikeys -k <kbdMapFile> [options] \n"
			"  -n [name] output MIDI port name to create\n"
			"  -d [dstName] name of destination MIDI port to connect\n"
			"  -v verbose output\n"
			"  -vv more verbose\n"
			"  -vvv even more verbose\n"
			"  -h displays this info\n";
}
