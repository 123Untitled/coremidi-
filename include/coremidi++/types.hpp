#ifndef ___COREMIDI_PLUS_PLUS_TYPES_HPP___
#define ___COREMIDI_PLUS_PLUS_TYPES_HPP___


#include <CoreMIDI/CoreMIDI.h>


namespace coremidi {


	// -- midi messages -------------------------------------------------------

	/* midi message 32 */
	using m32 = ::MIDIMessage_32;

	/* midi message 64 */
	using m64 = ::MIDIMessage_64;

	/* midi message 96 */
	using m96 = ::MIDIMessage_96;

	/* midi message 128 */
	using m128 = ::MIDIMessage_128;



	/* timestamp */
	using timestamp = ::MIDITimeStamp;

	/* protocol id */
	using protocol_id = ::MIDIProtocolID;



	using u32 = UInt32;
	using s32 = SInt32;
	using u64 = UInt64;
	using s64 = SInt64;

	using u8 = UInt8;
	using s8 = SInt8;


} // namespace coremidi

#endif // ___COREMIDI_PLUS_PLUS_TYPES_HPP___
