#ifndef ___MSH_MIDI_CLIENT_HPP___
#define ___MSH_MIDI_CLIENT_HPP___

#include "coremidi++/os.hpp"

#if defined(COREMIDI_PLUS_PLUS)

#include <string_view>

#include <CoreMIDI/CoreMIDI.h>




// -- C O R E M I D I  N A M E S P A C E --------------------------------------

namespace coremidi {


	// -- C L I E N T ---------------------------------------------------------

	class client final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = coremidi::client;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			client(void) noexcept;

			/* name constructor */
			client(const char*);

			/* deleted copy constructor */
			client(const ___self&) = delete;

			/* move constructor */
			client(___self&&) noexcept;

			/* destructor */
			~client(void) noexcept;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&&) noexcept -> ___self&;


			// -- public accessors --------------------------------------------

			/* id */
			auto id(void) const noexcept -> ::MIDIClientRef;


			// -- public boolean operators ------------------------------------

			/* boolean operator */
			explicit operator bool(void) const noexcept;

			/* not operator */
			auto operator!(void) const noexcept -> bool;


		private:

			// -- private methods ---------------------------------------------

			/* dispose */
			auto _dispose(void) noexcept -> void;


			// -- private static methods --------------------------------------

			/* _notification */
			static auto _notification(const ::MIDINotification*, void*) noexcept -> void;


			// -- private members ---------------------------------------------

			/* client */
			::MIDIClientRef _client;

	}; // class client

} // namespace coremidi

#endif // MSH_APPLE

#endif // ___MSH_MIDI_CLIENT_HPP___






	//inline auto set_string_property(const MIDIObjectRef& obj,
	//								const CFStringRef& property,
	//								const xns::string& name) -> void {
	//
	//	CFStringRef cstr = ::CFStringCreateWithCString( kCFAllocatorDefault,
	//													name.data(),
	//													kCFStringEncodingASCII);
	//
	//	if (cstr == nullptr) {
	//		std::cerr << "error creating cfstring" << std::endl;
	//		return;
	//	}
	//
	//	// set name
	//	OSStatus status = ::MIDIObjectSetStringProperty(obj, property, cstr);
	//
	//	// check if there was an error
	//	if (status != noErr) {
	//		std::cerr << "error setting name: " << status << std::endl;
	//	}
	//
	//	// release cfstring
	//	::CFRelease(cstr);
	//}
	//
	//inline auto set_integer_property(const MIDIObjectRef& obj,
	//								 const CFStringRef& property,
	//								 const SInt32& value) -> void {
	//
	//	// set value
	//	OSStatus status = ::MIDIObjectSetIntegerProperty(obj, property, value);
	//
	//	// check if there was an error
	//	if (status != noErr) {
	//		std::cerr << "error setting name: " << status << std::endl;
	//	}
	//}
	//
	//
