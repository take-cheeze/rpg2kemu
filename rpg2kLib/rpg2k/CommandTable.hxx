#ifndef _INC_RPG2K__COMMAND_TABLE_HXX_
#define _INC_RPG2K__COMMAND_TABLE_HXX_

#include "Context.hxx"
#include "Singleton.hxx"

#include <boost/unordered_map.hpp>


namespace rpg2k
{
	namespace model
	{
		class CommandTable : public ConstSingleton<CommandTable>
		{
			friend class ConstSingleton<CommandTable>;
		protected:
			CommandTable();
		public:
			Context::Command operator [](size_t code) const;
		private:
			typedef boost::unordered_map<size_t, Context::Command> Table;
			Table table_;
		}; // class CommandTable
	} // namespace model
} // namespace rpg2k

#endif // _INC_RPG2K__COMMAND_TABLE_HXX_
