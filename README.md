# miditypewriter

This Linux application uses typing keyboard to generate MIDI notes. Notes assigned to keys in config file: [kbdmap.txt](kbdmap.txt). Key press and release events generate separate note ON and note OFF messages. Notes velocity is fixed.
It also creates MIDI IN and OUT ports. Optionally it connects to another MIDI port for sending notes.
In Linux reading keyboard events requires root access so this should be run using sudo:

sudo pimidikeys -k kbdmap.txt

I use it to debug MIDI applications making a MIDI controller out of computer keyboard.
