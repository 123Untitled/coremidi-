#ifndef ___COREMIDI_PLUS_PLUS_SOURCE_HPP___
#define ___COREMIDI_PLUS_PLUS_SOURCE_HPP___

#include "coremidi++/os.hpp"

#if defined(COREMIDI_PLUS_PLUS)

#include "coremidi++/object.hpp"
#include "coremidi++/client.hpp"
#include "coremidi++/types.hpp"

#include <iostream>



// -- C O R E M I D I  N A M E S P A C E --------------------------------------

namespace coremidi {


	// -- S O U R C E ---------------------------------------------------------

	class source final : public coremidi::object {


		private:

			// -- private types -----------------------------------------------

			/* self type */
			using ___self = coremidi::source;


		public:

			// -- public lifecycle --------------------------------------------

			/* default constructor */
			source(void) noexcept = default;

			/* name constructor */
			source(const coremidi::client&, const char*);

			/* deleted copy constructor */
			source(const ___self&) = delete;

			/* move constructor */
			source(___self&&) noexcept;

			/* destructor */
			~source(void) noexcept;


			// -- public assignment operators ---------------------------------

			/* deleted copy assignment operator */
			auto operator=(const ___self&) -> ___self& = delete;

			/* move assignment operator */
			auto operator=(___self&& other) noexcept -> ___self&;


		private:

			// -- private methods ---------------------------------------------

			/* dispose */
			auto _dispose(void) noexcept -> void;

	}; // class source

} // namespace coremidi

#endif // COREMIDI_PLUS_PLUS

#endif // ___COREMIDI_PLUS_PLUS_SOURCE_HPP___
