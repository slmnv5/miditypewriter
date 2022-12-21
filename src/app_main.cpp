#include "pch.hpp"
#include "lib/log.hpp"

#include "MidiKeysClient.hpp"

using namespace std;

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
		clientName = "mimap";

	LOG(LogLvl::INFO) << "MIDI client name: " << clientName;
	MidiClient *midiClient = nullptr;

	try
	{

		MidiKeysClient midiKeysClient(kbdMapFile, clientName, nullptr);
		LOG(LogLvl::INFO) << "Using typing keyboard as source with map: " << kbdMapFile;

		LOG(LogLvl::INFO) << "Starting MIDI messages processing";
	}
	catch (exception &e)
	{
		LOG(LogLvl::ERROR) << "Completed with error: " << e.what();
		return 1;
	}
}

void help()
{
	cout << "Usage: mimap5 -r <file> [options] \n"
			"  -k <kbdMapFile> use typing keyboard for MIDI notes, needs sudo\n"
			"  -n [name] output MIDI port name to create\n"
			"  -v verbose output\n"
			"  -vv more verbose\n"
			"  -vvv even more verbose\n"
			"  -h displays this info\n";
}
