#include "coremidi++/port.hpp"

#if defined(COREMIDI_PLUS_PLUS)


// -- P O R T -----------------------------------------------------------------


// -- public lifecycle --------------------------------------------------------

/* default constructor */
coremidi::port::port(void) noexcept
: _port{0U} {
}

/* client constructor */
coremidi::port::port(const coremidi::client& client)
: _port{0U} {

	::OSStatus status = ::MIDIInputPortCreateWithProtocol(client.id(),
														  CFSTR("MIDI port"),
														  kMIDIProtocol_1_0,
														  &_port,
														  ^(const MIDIEventList* evtlist, void* data) {
																___self::read_midi(evtlist, data);
														  });

	if (status != noErr)
		throw "error creating midi input port";
}

/* move constructor */
coremidi::port::port(___self&& other) noexcept
: _port{other._port} {
	other._port = 0U;
}

/* destructor */
coremidi::port::~port(void) noexcept {

	// dispose port
	___self::_dispose();
}


// -- public assignment operators ---------------------------------------------

/* move assignment operator */
auto coremidi::port::operator=(___self&& other) -> ___self& {

	// check self assignment
	if (this == &other)
		return *this;

	// dispose port
	___self::_dispose();

	// move port
	_port       = other._port;
	other._port = 0U;

	return *this;
}


// -- public methods ----------------------------------------------------------

/* connect */
auto coremidi::port::connect(const coremidi::endpoint& ep) -> void {

	// connect endpoint to port
	::OSStatus status = ::MIDIPortConnectSource(_port, ep.id(), nullptr);

	if (status != noErr)
		throw "error connecting midi endpoint to port";
}

/* disconnect */
auto coremidi::port::disconnect(const coremidi::endpoint& ep) -> void {

	// disconnect endpoint from port
	::OSStatus status = ::MIDIPortDisconnectSource(_port, ep.id());

	if (status != noErr)
		throw "error disconnecting midi endpoint from port";
}


// -- private methods ---------------------------------------------------------

/* dispose */
auto coremidi::port::_dispose(void) noexcept -> void {

	// check port validity
	if (_port == 0U)
		return;

	// dispose port
	::OSStatus status = ::MIDIPortDispose(_port);

	static_cast<void>(status);
}


#endif // MSH_COREMIDI
