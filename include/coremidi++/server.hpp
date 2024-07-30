#ifndef ___MSH_MIDI_SERVER_HPP___
#define ___MSH_MIDI_SERVER_HPP___

#include "coremidi++/os.hpp"

#if defined(COREMIDI_PLUS_PLUS)

#include "coremidi++/client.hpp"
#include "coremidi++/endpoint.hpp"
#include "coremidi++/eventlist.hpp"
#include "coremidi++/output_port.hpp"

#include <CoreMIDI/CoreMIDI.h>
#include <cstdint>

#include <iostream>


// -- M S H  N A M E S P A C E ------------------------------------------------

namespace msh {


	// -- M I D I  N A M E S P A C E ------------------------------------------

	namespace midi {


		// -- S E R V E R -----------------------------------------------------

		class server final {


			private:

				// -- private types -------------------------------------------

				/* self type */
				using ___self = msh::midi::server;

				/* timestamp type */
				using timestamp = ::MIDITimeStamp;


			public:

				// -- public lifecycle ----------------------------------------

				/* deleted copy constructor */
				server(const ___self&) = delete;

				/* deleted move constructor */
				server(___self&&) = delete;

				/* destructor */
				~server(void) noexcept = default;


				// -- public assignment operators -----------------------------

				/* deleted copy assignment operator */
				auto operator=(const ___self&) -> ___self& = delete;

				/* deleted move assignment operator */
				auto operator=(___self&&) -> ___self& = delete;


				// -- public static methods -----------------------------------

				/* note on */
				static auto note_on(const coremidi::u8,
									const coremidi::u8,
									const coremidi::u8 = 100U) -> void;

				/* note off */
				static auto note_off(const coremidi::u8,
									 const coremidi::u8) -> void;

				/* send */
				static auto send(void) -> void;


				static auto start(void) -> void {

					___self::shared();
					//return;
					std::cout << "press enter to disconnect" << std::endl;
					//CFRunLoopRun();
					while (true) {

						note_on(0, 60, 100);
						send();
						sleep(1);
						note_off(0, 60);
						send();
						sleep(1);


						//int c = std::getchar();
						//if (c == 'q') { break; }
					}
				}

				static auto overall_info(void) -> void;
				static auto source_info(void) -> void;

			private:

				// -- private lifecycle ---------------------------------------

				/* default constructor */
				server(void);


				// -- private static methods ----------------------------------

				/* shared */
				static auto shared(void) -> ___self&;


				// -- private methods ---------------------------------------------

				/* setup midi */
				auto setup_server(void) -> void;


				// -- private members ---------------------------------------------

				/* client */
				coremidi::client _client;

				/* source */
				coremidi::endpoint _source;

				/* port */
				coremidi::port::output _port;

				/* event list */
				coremidi::eventlist _eventlist;


				///* destination */
				//msh::midi::endpoint<"destination"> _destination;
				//
				///* packet */
				//msh::midi::packet _packet;

		}; // class server

	} // namespace midi

} // namespace msh

#endif // MSH_APPLE

#endif // ___MSH_MIDI_SERVER_HPP___





//UInt32 msg = MIDICLOCKTICK;
/*
msg = on ? 0x20900000 : 0x20800000; // note on or off
msg = msg | ((note & 0x7F) << 8); // note
msg = msg | 127; // velocity
*/



//#if defined(XNS_APPLE)
//
//// -- M I D I  N A M E S P A C E ----------------------------------------------
//
//namespace midi {
//
//	/* common midi messages */
//	enum : xns::u32 {
//		CLOCK = 0x10F80000,
//		START = 0x10FA0000, STOP  = 0x10FC0000,
//		ON    = 0x20900000, OFF   = 0x20800000
//	};
//
//
//
//
//
//
//
//
//
//
//
//
//class Devicelist final {
//	public:
//		Devicelist(void);
//		~Devicelist(void);
//	private:
//		class Device;
//		Device** _devices;
//		class Device final {
//			public:
//				Device(void);
//				~Device(void);
//			private:
//				class Entity;
//				MIDIDeviceRef _device;
//				UInt64        _index;
//				Entity**      _entities;
//				class Entity final {
//					public:
//						Entity(void);
//						~Entity(void);
//					private:
//						class Source;
//						MIDIEntityRef _entity;
//						UInt64        _index;
//						Source**      _sources;
//						class Source final {
//							public:
//								Source(void);
//								~Source(void);
//							private:
//								MIDIEndpointRef _source;
//								UInt64          _index;
//						};
//				};
//		};
//};
//
//#endif


