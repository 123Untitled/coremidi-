#include "coremidi++/source.hpp"

#if defined(COREMIDI_PLUS_PLUS)

#include "coremidi++/string.hpp"


// -- S O U R C E -------------------------------------------------------------


// -- public lifecycle --------------------------------------------------------


/* name constructor */
coremidi::source::source(const coremidi::client& client, const char* name) {

	// create cfstring
	corefoundation::string cstr{name};

	// create a new source
	const ::OSStatus err = ::MIDISourceCreateWithProtocol(client.id(),
														  cstr,
														  kMIDIProtocol_1_0,
														  &_ref);

	// check if there was an error
	if (err != noErr)
		throw coremidi::exception{err, "MIDISourceCreateWithProtocol"};
}

/* move constructor */
coremidi::source::source(___self&& other) noexcept
: coremidi::object{other._ref} {
	other._ref = 0U;
}

/* destructor */
coremidi::source::~source(void) noexcept {
	// dispose source
	___self::_dispose();
}


// -- public assignment operators ---------------------------------------------

/* move assignment operator */
auto coremidi::source::operator=(___self&& other) noexcept -> ___self& {

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
auto coremidi::source::_dispose(void) noexcept -> void {

	// check source validity
	if (_ref == 0U)
		return;

	// dispose endpoint
	static_cast<void>(
		::MIDIEndpointDispose(_ref)
		);
}

#endif // COREMIDI_PLUS_PLUS
