#ifndef _INC_RPG2K__COMMAND_HXX_
#define _INC_RPG2K__COMMAND_HXX_

#include "Context.hxx"


namespace rpg2k
{
	namespace model
	{
		#define PP_contextCommandProto(CODE) \
			template<> void Context::command<CODE>(structure::Instruction const& inst)

		PP_contextCommandProto( 0); // event terminater
		PP_contextCommandProto(10); // branch terminater

		PP_contextCommandProto(11210); // render battle animation on field

		PP_contextCommandProto(11310); // change party's transparancy state
		PP_contextCommandProto(11320); // flash effect to event
		PP_contextCommandProto(11330); // set event action
	} // namespace model
} // namespace rpg2k

#endif
