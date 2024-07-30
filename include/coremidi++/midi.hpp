#ifndef ___MSH_MIDI_HPP___
#define ___MSH_MIDI_HPP___

#include "msh/config/os.hpp"

// preprocessor check for operating system
#if defined(MSH_APPLE)

#	include "msh/midi/coremidi/server.hpp"

#	include "msh/midi/coremidi/client.hpp"
#	include "msh/midi/coremidi/eventlist.hpp"
#	include "msh/midi/coremidi/endpoint.hpp"
//#	include "msh/midi/coremidi/port.hpp"

#elif defined(MSH_LINUX)

#	warning "linux is not implemented yet"

#else

#	error "operating system not supported"

#endif



#endif // ___MSH_MIDI_HPP___
