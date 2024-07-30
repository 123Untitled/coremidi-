#ifndef ___MSH_COREMIDI_OUTPUT_PORT_HPP___
#define ___MSH_COREMIDI_OUTPUT_PORT_HPP___


#include "coremidi++/os.hpp"

#if defined(COREMIDI_PLUS_PLUS)

#include "coremidi++/string.hpp"
#include "coremidi++/client.hpp"
#include "coremidi++/endpoint.hpp"


// -- C O R E M I D I  N A M E S P A C E --------------------------------------

namespace coremidi {


	// -- P O R T  N A M E S P A C E ------------------------------------------

	namespace port {


		// -- I N P U T -------------------------------------------------------

		class input final {


			private:

				// -- private types -------------------------------------------

				/* self type */
				using ___self = coremidi::port::input;


				// -- private members -----------------------------------------

				/* port */
				::MIDIPortRef _port;


			public:

				// -- public lifecycle ----------------------------------------

				/* default constructor */
				input(void) noexcept
				: _port{0U} {
				}

				/* client constructor */
				input(const coremidi::client& client, const char* name)
				: _port{0U} {

					// create cfstring
					corefoundation::string cstr{name};

					// create input port
					const ::OSStatus result = ::MIDIInputPortCreateWithProtocol(
												client.id(),
												cstr,
												kMIDIProtocol_1_0,
												&_port,
												^(const MIDIEventList*, void*) {
												}
							);

					// check if port was created
					if (result != noErr)
						throw "error creating input port";
				}

				/* deleted copy constructor */
				input(const ___self&) = delete;

				/* move constructor */
				input(___self&& other) noexcept
				: _port{other._port} {

					// reset other
					other._port = 0U;
				}

				/* destructor */
				~input(void) noexcept {

					// dispose port
					___self::_dispose();
				}


				// -- public assignment operators -----------------------------

				/* deleted copy assignment operator */
				auto operator=(const ___self&) -> ___self& = delete;

				/* move assignment operator */
				auto operator=(___self&& other) noexcept -> ___self& {

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


				// -- public modifiers ----------------------------------------

				/* connect */
				auto connect(const coremidi::endpoint& ep) -> void {

					// connect endpoint to port
					::OSStatus status = ::MIDIPortConnectSource(_port, ep.id(), nullptr);

					if (status != noErr)
						throw "error connecting midi endpoint to port";
				}

				/* disconnect */
				auto disconnect(const coremidi::endpoint& ep) -> void {

					// disconnect endpoint from port
					::OSStatus status = ::MIDIPortDisconnectSource(_port, ep.id());

					if (status != noErr)
						throw "error disconnecting midi endpoint from port";
				}


			private:

				// -- private methods -----------------------------------------

				/* dispose */
				auto _dispose(void) noexcept -> void {

					// check port validity
					if (_port == 0U)
						return;

					// dispose port
					static_cast<void>(
						::MIDIPortDispose(_port)
						);
				}

		}; // class input


		// -- O U T P U T -----------------------------------------------------

		class output final {


			private:

				// -- private types -------------------------------------------

				/* self type */
				using ___self = coremidi::port::output;


				// -- private members -----------------------------------------

				/* port */
				::MIDIPortRef _port;


			public:

				// -- public lifecycle ----------------------------------------

				/* default constructor */
				output(void) noexcept
				: _port{0U} {
				}

				/* client constructor */
				output(const coremidi::client& client, const char* name)
				: _port{0U} {

					// create cfstring
					corefoundation::string cstr{name};

					// create output port
					::OSStatus result = ::MIDIOutputPortCreate(client.id(), cstr, &_port);

					// check if port was created
					if (result != noErr)
						throw "error creating output port";
				}

				/* deleted copy constructor */
				output(const ___self&) = delete;

				/* move constructor */
				output(___self&& other) noexcept
				: _port{other._port} {

					// reset other
					other._port = 0U;
				}

				/* destructor */
				~output(void) noexcept {

					// dispose port
					___self::_dispose();
				}


				// -- public assignment operators -----------------------------

				/* deleted copy assignment operator */
				auto operator=(const ___self&) -> ___self& = delete;

				/* move assignment operator */
				auto operator=(___self&& other) noexcept -> ___self& {

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


			private:

				// -- private methods -----------------------------------------

				/* dispose */
				auto _dispose(void) noexcept -> void {

					// check port validity
					if (_port == 0U)
						return;

					// dispose port
					static_cast<void>(
						::MIDIPortDispose(_port)
						);
				}


		}; // class output

	} // namespace port

} // namespace coremidi

#endif // MSH_COREMIDI

#endif // ___MSH_COREMIDI_OUTPUT_PORT_HPP___
