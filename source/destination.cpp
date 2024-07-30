#include "coremidi++/destination.hpp"

#if defined(COREMIDI_PLUS_PLUS)

#include "coremidi++/string.hpp"


// -- D E S T I N A T I O N ---------------------------------------------------


// -- public lifecycle --------------------------------------------------------

/* name constructor */
coremidi::destination::destination(const coremidi::client& client, const char* name) {

	// create cfstring
	corefoundation::string cstr{name};

	// create a new destination
	const ::OSStatus err = ::MIDIDestinationCreateWithProtocol(client.id(),
															   cstr,
															   kMIDIProtocol_1_0,
															   &_ref,
															   ^(const ::MIDIEventList* evtlist, void*) {
																	coremidi::destination::_read_midi(*evtlist);
															   });

	// check if there was an error
	if (err != noErr)
		throw coremidi::exception{err, "MIDIDestinationCreateWithProtocol"};
}

/* move constructor */
coremidi::destination::destination(___self&& other) noexcept
: coremidi::object{other._ref} {
	other._ref = 0U;
}

/* destructor */
coremidi::destination::~destination(void) noexcept {
	// dispose endpoint
	___self::_dispose();
}


// -- public assignment operators ---------------------------------------------

/* move assignment operator */
auto coremidi::destination::operator=(___self&& other) noexcept -> ___self& {

	// check self assignment
	if (this == &other)
		return *this;

	// dispose endpoint
	___self::_dispose();

	// move source
	_ref       = other._ref;
	other._ref = 0U;

	// return self
	return *this;
}

// -- private methods ---------------------------------------------------------

/* dispose */
auto coremidi::destination::_dispose(void) noexcept -> void {

	// check endpoint validity
	if (_ref == 0U)
		return;

	// dispose endpoint
	static_cast<void>(
			::MIDIEndpointDispose(_ref)
		);
}


// -- private static methods --------------------------------------------------

/* read midi */
auto coremidi::destination::_read_midi(const ::MIDIEventList& evtlist) -> void {
	//static_cast<void>(evtlist);
	//if (evtlist == nullptr) { return; }

	std::cout << "numPackets: " << evtlist.numPackets << std::endl;

	for (std::size_t i = 0; i < evtlist.numPackets; ++i) {

		const MIDIEventPacket& packet = evtlist.packet[i];

		std::cout << "wordCount: " << packet.wordCount << std::endl;

		for (std::size_t j = 0; j < packet.wordCount; ++j) {

			const UInt32 word = packet.words[j];

			const UInt8 status = word & 0xFF;
			const UInt8 data1 = (word >> 8) & 0xFF;
			const UInt8 data2 = (word >> 16) & 0xFF;

			std::cout << "status: " << static_cast<int>(status) << std::endl;

			std::cout << "data1: " << static_cast<int>(data1) << std::endl;

			std::cout << "data2: " << static_cast<int>(data2) << std::endl;

		}
	}

}


#endif // COREMIDI_PLUS_PLUS
