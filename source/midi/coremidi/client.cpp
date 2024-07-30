#include "coremidi++/client.hpp"

#if defined(COREMIDI_PLUS_PLUS)

#include "coremidi++/string.hpp"

#include <unistd.h>


// -- public lifecycle --------------------------------------------------------

/* default constructor */
coremidi::client::client(void) noexcept
: _client{0U} {
}

/* name constructor */
coremidi::client::client(const char* name)
: _client{0U} {

	// create cfstring
	corefoundation::string cstr{name};

	// create client
	::OSStatus status = ::MIDIClientCreate(cstr, _notification, this, &_client);

	// check if there was an error
	if (status != noErr)
		throw "error creating midi client";
}

/* move constructor */
coremidi::client::client(___self&& other) noexcept
: _client{other._client} {
	other._client = 0U;
}

/* destructor */
coremidi::client::~client(void) noexcept {

	// dispose client
	___self::_dispose();
}


// -- public assignment operators ---------------------------------------------

/* move assignment operator */
auto coremidi::client::operator=(___self&& other) noexcept -> ___self& {

	// check self assignment
	if (this == &other)
		return *this;

	// dispose client
	___self::_dispose();

	// move client
	_client       = other._client;
	other._client = 0U;

	return *this;
}


// -- public accessors --------------------------------------------------------

/* id */
auto coremidi::client::id(void) const noexcept -> ::MIDIClientRef {
	return _client;
}


// -- public boolean operators ------------------------------------------------

/* boolean operator */
coremidi::client::operator bool(void) const noexcept {
	return _client != 0U;
}

/* not operator */
auto coremidi::client::operator!(void) const noexcept -> bool {
	return _client == 0U;
}


// -- private methods ---------------------------------------------------------

/* dispose */
auto coremidi::client::_dispose(void) noexcept -> void {

	// check client validity
	if (_client == 0)
		return;

	return; // no need to dispose client

	// dispose client
	if (::MIDIClientDispose(_client) != noErr)
		;
}





/* notification */
auto coremidi::client::_notification(const MIDINotification *message, void* data) noexcept -> void {

	// get client reference
	___self& client = *static_cast<___self*>(data);

	switch (message->messageID) {

		// Some aspect of the current MIDI setup changed.
		case kMIDIMsgSetupChanged:
			::write(STDIN_FILENO, "setup changed", 13);
			break;

		// The system added a device, entity, or endpoint.
		case kMIDIMsgObjectAdded:
			::write(STDIN_FILENO, "object added", 12);
			break;

		// The system removed a device, entity, or endpoint.
		case kMIDIMsgObjectRemoved:
			::write(STDIN_FILENO, "object removed", 14);
			break;

		// An object’s property value changed.
		case kMIDIMsgPropertyChanged:
			::write(STDIN_FILENO, "property changed", 16);
			break;

		// The system created or disposed of a persistent MIDI Thru connection.
		case kMIDIMsgThruConnectionsChanged:
			::write(STDIN_FILENO, "thru connection changed", 23);
			break;

		// The system changed a serial port owner.
		case kMIDIMsgSerialPortOwnerChanged:
			::write(STDIN_FILENO, "serial port owner changed", 25);
			break;

		// An I/O error occurred.
		case kMIDIMsgIOError:
			::write(STDIN_FILENO, "io error", 8);
			break;

		default:
			::write(STDIN_FILENO, "unknown notification", 20);
	}
}



#endif // MSH_COREMIDI




	//midi::set_string_property(_client, kMIDIPropertyName, name);
	//midi::set_string_property(_client, kMIDIPropertyModel, "model_1.0");
	//midi::set_string_property(_client, kMIDIPropertyManufacturer, "TMS_Industry");
	//
	//// capabilities
	//
	//midi::set_integer_property(_client, kMIDIPropertySupportsMMC, 0);
	//midi::set_integer_property(_client, kMIDIPropertySupportsGeneralMIDI, 0);
	//midi::set_integer_property(_client, kMIDIPropertySupportsShowControl, 0);
	//
	//// banks
	//
	//midi::set_integer_property(_client, kMIDIPropertyReceivesBankSelectLSB, 0);
	//midi::set_integer_property(_client, kMIDIPropertyTransmitsBankSelectLSB, 0);
	//midi::set_integer_property(_client, kMIDIPropertyReceivesBankSelectMSB, 0);
	//midi::set_integer_property(_client, kMIDIPropertyTransmitsBankSelectMSB, 0);
	//
	//// notes
	//
	//midi::set_integer_property(_client, kMIDIPropertyReceivesNotes, 1);
	//midi::set_integer_property(_client, kMIDIPropertyTransmitsNotes, 1);
	//
	//
	//// program changes
	//
	//midi::set_integer_property(_client, kMIDIPropertyReceivesProgramChanges, 0);
	//midi::set_integer_property(_client, kMIDIPropertyTransmitsProgramChanges, 0);
	//
	//// channels
	//
	//// The maximum number of MIDI channels on which a device may simultaneously receive channel messages.
	//midi::set_integer_property(_client, kMIDIPropertyMaxReceiveChannels, 0x7F);
	//// The maximum number of MIDI channels on which a device may simultaneously transmit channel messages.
	//midi::set_integer_property(_client, kMIDIPropertyMaxTransmitChannels, 0x7F);
	//// The bitmap of channels on which the object receives messages.
	//midi::set_integer_property(_client, kMIDIPropertyReceiveChannels, 0x7F);
	//// The bitmap of channels on which the object transmits messages.
	//midi::set_integer_property(_client, kMIDIPropertyTransmitChannels, 0x7F);
	//
	//
	//// connections
	//
	//// A Boolean value that indicates whether the device or entity can route messages to or from external MIDI devices.
	//midi::set_integer_property(_client, kMIDIPropertyCanRoute, 0);
	//// A Boolean value that indicates whether the endpoint broadcasts messages to all of the other endpoints in the device.
	//midi::set_integer_property(_client, kMIDIPropertyIsBroadcast, 0);
	//// The unique identifier of an external device attached to this connection.
	//midi::set_integer_property(_client, kMIDIPropertyConnectionUniqueID, 0);
	//// A Boolean value that indicates whether this entity or endpoint has external MIDI connections.
	//midi::set_integer_property(_client, kMIDIPropertyIsEmbeddedEntity, 0);
	//// The 0-based index of the entity on which incoming real-time messages from the device appear to have originated.
	//midi::set_integer_property(_client, kMIDIPropertySingleRealtimeEntity, 0);
	//
