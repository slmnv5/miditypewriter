# pimidikeys

This Linux application uses typing keyboard to generate MIDI notes. It assigns note to each key separately [kbdmap.txt](kbdmap.txt). Key press and release events generate separate note ON and OFF messages.
It also creates MIDI IN/OUT ports and optionally connects to another MIDI port for sending notes.
In Linux access to keyboard events requires root access so this should be run using sudo:

sudo pimidikeys -k kbdmap.txt