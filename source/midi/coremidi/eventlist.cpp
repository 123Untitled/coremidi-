#include "coremidi++/eventlist.hpp"

#if defined(COREMIDI_PLUS_PLUS)

/* default constructor */
coremidi::eventlist::eventlist(void)
: _buffer{}, _list{nullptr}, _packet{nullptr} {

	// reserve default buffer size
	_buffer.resize(BUFFER_SIZE);

	// initialize the event list
	_list = reinterpret_cast<MIDIEventList*>(_buffer.data());

	// initialize the event packet
	_packet = ::MIDIEventListInit(_list, kMIDIProtocol_1_0);
}


auto coremidi::eventlist::send(const coremidi::endpoint& source) -> void {

	// check packet validity
	if (_packet == nullptr)
		return;

	// WARNING: need to check if the source is valid

	// send midi to source device
	const ::OSStatus err = ::MIDIReceivedEventList(source.id(), _list);

	// check if the midi was sent. INFO: not implemented
	_packet = ::MIDIEventListInit(_list, kMIDIProtocol_1_0);
}


/* note on */
auto coremidi::eventlist::note_on(const coremidi::u8 channel,
								  const coremidi::u8 note,
								  const coremidi::u8 velocity) -> void {

	___self::_add(::MIDI1UPNoteOn(0U, channel, note, velocity));
}

/* note off */
auto coremidi::eventlist::note_off(const coremidi::u8 channel,
								   const coremidi::u8 note) -> void {

	___self::_add(::MIDI1UPNoteOff(0U, channel, note, 0U));
}


// -- private methods ---------------------------------------------------------

/* add */
auto coremidi::eventlist::_add(const coremidi::m32& msg) -> void {

	// check packet validity
	if (_packet == nullptr)
		return;

	addmsg:

	// add the midi message to the packet
	_packet = ::MIDIEventListAdd(_list,
								 _buffer.size(),
								 _packet,
								 0U,
								 1U,
								 &msg);

	// check packet validity
	if (!_packet) {
		std::cout << "resize buffer" << std::endl;
		// check if the buffer can be resized
		if (_resize() == false) {
			std::cout << "\x1b[32m" << "buffer full" << "\x1b[0m" << std::endl;
			exit(1);
			return;
		}
		// try again
		goto addmsg;
	}
}

/* resize */
auto coremidi::eventlist::_resize(void) -> bool {

	if (_buffer.size() == MAX_EVENT)
		return false;

	auto size = _buffer.size() * 2U;

	// check if the max number of events has been reached
	if (size > MAX_EVENT)
		size = MAX_EVENT;

	// else resize the buffer
	_buffer.resize(size);

	// update the list and packet pointers
	_list = reinterpret_cast<MIDIEventList*>(_buffer.data());

	// update the packet pointer
	const unsigned i = _list->numPackets ? (_list->numPackets - 1U) : 0U;

	_packet = &(_list->packet[i]);

	return true;
}

#endif // MSH_COREMIDI
