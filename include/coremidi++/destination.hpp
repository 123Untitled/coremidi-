#ifndef ___COREMIDI_PLUS_PLUS_DESTINATION_HPP___
#define ___COREMIDI_PLUS_PLUS_DESTINATION_HPP___

#include "coremidi++/os.hpp"

#if defined(COREMIDI_PLUS_PLUS)

#include "coremidi++/object.hpp"
#include "coremidi++/client.hpp"
#include "coremidi++/types.hpp"

#include <iostream>



// -- C O R E M I D I  N A M E S P A C E --------------------------------------

namespace coremidi {


	// -- D E S T I N A T I O N -----------------------------------------------

	class destination final : public coremidi::object {


		private:


			// -- private types -----------------------------------------------

			/* self type */
			using ___self = coremidi::destination;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			destination(void) noexcept = default;

			/* name constructor */
			destination(const coremidi::client&, const char*);

			/* deleted copy constructor */
			destination(const ___self&) = delete;

			/* move constructor */
			destination(___self&&) noexcept;

			/* destructor */
			~destination(void) noexcept;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&& other) noexcept -> ___self&;


		private:

			// -- private methods ---------------------------------------------

			/* dispose */
			auto _dispose(void) noexcept -> void;


			// -- private static methods --------------------------------------

			/* read midi */
			static auto _read_midi(const ::MIDIEventList&) -> void;

	}; // class destination

} // namespace coremidi

#endif // COREMIDI_PLUS_PLUS

#endif // ___COREMIDI_PLUS_PLUS_DESTINATION_HPP___
