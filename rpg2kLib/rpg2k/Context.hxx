#ifndef _INC_RPG2K__CONTEXT__HXX
#define _INC_RPG2K__CONTEXT__HXX

#include <stack>

#include "Define.hxx"


namespace rpg2k
{
	namespace structure
	{
		class Event;
		class Instruction;
	}

	namespace model
	{
		class Project;

		class Waiter
		{
		public:
			Waiter() : count_(0) {}
			void update() { --count_; }
		private:
			size_t count_;
		};

		class Context
		{
		public:
			Context(Project& p, unsigned evID, EventStart::Type t);

			typedef void (Context::*Command)(structure::Instruction const&);
			template<unsigned Code>
			void command(structure::Instruction const& inst);
		protected:
			void ret(); // return

		private:
			Project& owner_;
			unsigned const eventID_;
			EventStart::Type const type_;
			Waiter waiter_;
			struct EventStream
			{
				structure::Event const* event;
				size_t pointer;
			};
			std::stack<EventStream> event_;
			struct LoopState
			{
				size_t nest, pointer;
			};
			std::stack<LoopState> loop_;
			
		}; // class Context
	} // namespace model
} // namespace rpg2k

#endif // _INC_RPG2K__CONTEXT__HXX
