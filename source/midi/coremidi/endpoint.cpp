#include "coremidi++/endpoint.hpp"

#if defined(COREMIDI_PLUS_PLUS)

#include "coremidi++/string.hpp"


// -- E N D P O I N T ---------------------------------------------------------


// -- public lifecycle --------------------------------------------------------

/* default constructor */
coremidi::endpoint::endpoint(void) noexcept
: _endpoint{0U} {
}

/* move constructor */
coremidi::endpoint::endpoint(___self&& other) noexcept
: _endpoint{other._endpoint} {
	other._endpoint = 0U;
}

/* destructor */
coremidi::endpoint::~endpoint(void) noexcept {
	// dispose endpoint
	_dispose();
}


// -- public assignment operators ---------------------------------------------

/* move assignment operator */
auto coremidi::endpoint::operator=(___self&& other) noexcept -> ___self& {

	// check self assignment
	if (this == &other)
		return *this;

	// dispose endpoint
	_dispose();

	// move source
	_endpoint       = other._endpoint;
	other._endpoint = 0U;

	// return self
	return *this;
}

// -- public modifiers --------------------------------------------------------

/* model */
auto coremidi::endpoint::model(const char* m) -> void {

	// create cfstring
	corefoundation::string cstr{m};

	// set model
	::MIDIObjectSetStringProperty(_endpoint, kMIDIPropertyModel, cstr);
}

/* manufacturer */
auto coremidi::endpoint::manufacturer(const char* m) -> void {

	// create cfstring
	corefoundation::string cstr{m};

	// set manufacturer
	::MIDIObjectSetStringProperty(_endpoint, kMIDIPropertyManufacturer, cstr);
}


// -- public accessors --------------------------------------------------------

/* id */
auto coremidi::endpoint::id(void) const noexcept -> ::MIDIEndpointRef {
	return _endpoint;
}


// -- public boolean operators ------------------------------------------------

/* boolean operator */
coremidi::endpoint::operator bool(void) const noexcept {
	return _endpoint != 0U;
}

/* not operator */
auto coremidi::endpoint::operator!(void) const noexcept -> bool {
	return _endpoint == 0U;
}


// -- public static methods ---------------------------------------------------

/* sources */
auto coremidi::endpoint::sources(void) -> coremidi::u32 {
	return static_cast<coremidi::u32>(::MIDIGetNumberOfSources());
}


// -- private lifecycle -------------------------------------------------------

/* id constructor */
coremidi::endpoint::endpoint(const ::MIDIEndpointRef& ep) noexcept
: _endpoint{ep} {
}


// -- private methods ---------------------------------------------------------

/* dispose */
auto coremidi::endpoint::_dispose(void) noexcept -> void {

	// check endpoint validity
	if (_endpoint == 0U)
		return;

	// dispose endpoint
	static_cast<void>(
		::MIDIEndpointDispose(_endpoint)
		);
}


// -- private static methods --------------------------------------------------

/* read midi */
auto coremidi::endpoint::_read_midi(const ::MIDIEventList& evtlist) -> void {
	static_cast<void>(evtlist);
}


// -- non-member functions ----------------------------------------------------

/* make source */
auto coremidi::make_source(const coremidi::client& client, const char* name) -> coremidi::endpoint {

	::MIDIEndpointRef ep = 0U;

	// create cfstring
	corefoundation::string cstr{name};

	// create a new source
	const ::OSStatus err = ::MIDISourceCreateWithProtocol(client.id(),
														  cstr,
														  kMIDIProtocol_1_0,
														  &ep);

	// check if there was an error
	if (err != noErr)
		throw "error creating midi source";

	return coremidi::endpoint{ep};
}

/* make destination */
auto coremidi::make_destination(const coremidi::client& client, const char* name) -> coremidi::endpoint {

	::MIDIEndpointRef ep = 0U;

	// create cfstring
	corefoundation::string cstr{name};

	// create a new source
	const ::OSStatus err = ::MIDIDestinationCreateWithProtocol(client.id(),
															   cstr,
															   kMIDIProtocol_1_0,
															   &ep,
															   ^(const ::MIDIEventList* evtlist, void*) {
																	coremidi::endpoint::_read_midi(*evtlist);
															   });

	// check if there was an error
	if (err != noErr)
		throw "error creating midi destination";

	return coremidi::endpoint{ep};
}

#endif // MSH_COREMIDI
