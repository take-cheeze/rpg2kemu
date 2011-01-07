#ifndef _INC_RPG2K__COMMAND_HXX_
#define _INC_RPG2K__COMMAND_HXX_

#include "Context.hxx"


namespace rpg2k
{
	namespace model
	{
		#define PP_enumAllContextCommand(FUNC) \
			FUNC( 0) \
			FUNC(10) \
			\
			FUNC(11210) \
			\
			FUNC(11310) \
			FUNC(11320) \
			FUNC(11330) \

		#define PP_contextCommandProto(CODE) \
			template<> void Context::command<CODE>(structure::Instruction const& inst);
		PP_enumAllContextCommand(PP_contextCommandProto)
		#undef PP_contextCommandProto
	} // namespace model
} // namespace rpg2k

#endif
