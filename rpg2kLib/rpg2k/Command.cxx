#include "Command.hxx"


namespace rpg2k
{
	namespace model
	{
		#define PP_contextCommandProto(CODE) \
			template<> void Context::command<CODE>(structure::Instruction const& inst)

		PP_contextCommandProto(0) // event terminater
		{
			this->ret();
		}
		PP_contextCommandProto(10) // branch terminater
		{
		}

		PP_contextCommandProto(11210) // render battle animation on field
		{
			// TODO
		}

		PP_contextCommandProto(11310) // change party's transparancy state
		{
			// TODO
		}
		PP_contextCommandProto(11320) // flash effect to event
		{
			// TODO
		}
		PP_contextCommandProto(11330) // set event action
		{
			// TODO
		}

		#undef PP_contextCommandProto
	} // namespace model
} // namespace rpg2k
