#ifndef ___MSH_COREMIDI_PORT_HPP___
#define ___MSH_COREMIDI_PORT_HPP___

#include "coremidi++/os.hpp"

#if defined(COREMIDI_PLUS_PLUS)

#include "coremidi++/client.hpp"
#include "coremidi++/endpoint.hpp"


// -- C O R E M I D I  N A M E S P A C E --------------------------------------

namespace coremidi {


	// -- P O R T -------------------------------------------------------------

	class port final {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = coremidi::port;


		public:
			
			// -- public lifecycle --------------------------------------------

			/* default constructor */
			port(void) noexcept;

			/* client constructor */
			port(const coremidi::client&);

			/* deleted copy constructor */
			port(const ___self&) = delete;

			/* move constructor */
			port(___self&&) noexcept;

			/* destructor */
			~port(void) noexcept;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&&) -> ___self&;


			// -- public methods ----------------------------------------------

			/* connect */
			auto connect(const coremidi::endpoint&) -> void;

			/* disconnect */
			auto disconnect(const coremidi::endpoint&) -> void;


		private:

			// -- private methods ---------------------------------------------

			/* dispose */
			auto _dispose(void) noexcept -> void;




			static auto read_midi(const MIDIEventList* evtlist, void* data) -> void {
				std::cout << "read midi" << std::endl;

				if (evtlist == nullptr) { return; }


				for (std::size_t i = 0; i < evtlist->numPackets; ++i) {

					const MIDIEventPacket* packet = evtlist->packet + i;

					for (std::size_t j = 0; j < packet->wordCount; ++j) {

						const UInt32 word = packet->words[j];

						const UInt8 status = word & 0xFF;
						const UInt8 data1 = (word >> 8) & 0xFF;
						const UInt8 data2 = (word >> 16) & 0xFF;

						std::cout << "status: " << static_cast<int>(status) << std::endl;

						std::cout << "data1: " << static_cast<int>(data1) << std::endl;

						std::cout << "data2: " << static_cast<int>(data2) << std::endl;

					}

				}


			}

			// -- private members ---------------------------------------------

			/* port */
			::MIDIPortRef _port;

	}; // class port

} // namespace coremidi

#endif // MSH_COREMIDI

#endif // ___MSH_COREMIDI_PORT_HPP___
