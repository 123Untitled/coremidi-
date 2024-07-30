#ifndef ___MSH_COREMIDI_ENDPOINT_HPP___
#define ___MSH_COREMIDI_ENDPOINT_HPP___

#include "coremidi++/os.hpp"

#if defined(COREMIDI_PLUS_PLUS)

#include "coremidi++/client.hpp"
#include "coremidi++/types.hpp"

#include <iostream>



// -- C O R E M I D I  N A M E S P A C E --------------------------------------

namespace coremidi {


	// -- E N D P O I N T -----------------------------------------------------

	class endpoint final {


		private:


			// -- private types -----------------------------------------------

			/* self type */
			using ___self = coremidi::endpoint;


			// -- friends ---------------------------------------------------------

			/* make source as friend */
			friend auto make_source(const coremidi::client&,
									const char*) -> ___self;

			/* make destination as friend */
			friend auto make_destination(const coremidi::client&,
										 const char*) -> ___self;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			endpoint(void) noexcept;

			/* deleted copy constructor */
			endpoint(const ___self&) = delete;

			/* move constructor */
			endpoint(___self&&) noexcept;

			/* destructor */
			~endpoint(void) noexcept;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&& other) noexcept -> ___self&;


			// -- public modifiers --------------------------------------------

			/* model */
			auto model(const char*) -> void;

			/* manufacturer */
			auto manufacturer(const char*) -> void;


			// -- public accessors --------------------------------------------

			/* id */
			auto id(void) const noexcept -> ::MIDIEndpointRef;


			// -- public boolean operators ------------------------------------

			/* boolean operator */
			explicit operator bool(void) const noexcept;

			/* not operator */
			auto operator!(void) const noexcept -> bool;


			// -- public static methods ---------------------------------------

			/* sources */
			static auto sources(void) -> coremidi::u32;


		private:

			// -- privatel lifecycle ------------------------------------------

			/* id constructor */
			endpoint(const ::MIDIEndpointRef&) noexcept;


			// -- private methods ---------------------------------------------

			/* dispose */
			auto _dispose(void) noexcept -> void;


			// -- private static methods --------------------------------------

			/* read midi */
			static auto _read_midi(const ::MIDIEventList&) -> void;


			// -- private members ---------------------------------------------

			/* source */
			::MIDIEndpointRef _endpoint;

	}; // class endpoint


	// -- non-member functions ------------------------------------------------

	/* make source */
	auto make_source(const coremidi::client&, const char*) -> coremidi::endpoint;

	/* make destination */
	auto make_destination(const coremidi::client&, const char*) -> coremidi::endpoint;

} // namespace coremidi

#endif // MSH_COREMIDI

#endif // ___MSH_MIDI_SOURCE_HPP___







			// -- private static methods --------------------------------------

			/* read midi */
//static auto read_midi(const MIDIEventList* evtlist) -> void requires (type == "destination") {
//
//	if (evtlist == nullptr) { return; }
//
//	std::cout << "numPackets: " << evtlist->numPackets << std::endl;
//	for (xns::size_t i = 0; i < evtlist->numPackets; ++i) {
//
//		const MIDIEventPacket* packet = evtlist->packet + i;
//
//		std::cout << "wordCount: " << packet->wordCount << std::endl;
//		for (xns::size_t j = 0; j < packet->wordCount; ++j) {
//
//			const UInt32 word = packet->words[j];
//
//			const UInt8 status = word & 0xFF;
//			const UInt8 data1 = (word >> 8) & 0xFF;
//			const UInt8 data2 = (word >> 16) & 0xFF;
//
//			std::cout << "status: " << static_cast<int>(status) << std::endl;
//
//			std::cout << "data1: " << static_cast<int>(data1) << std::endl;
//
//			std::cout << "data2: " << static_cast<int>(data2) << std::endl;
//
//		}
//	}
//
//}
