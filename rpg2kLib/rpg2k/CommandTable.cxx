#include <utility>

#include "CommandTable.hxx"


namespace rpg2k
{
	namespace model
	{
		CommandTable::CommandTable()
		{
			#define PP_insert(CODE) \
				table_.insert( std::make_pair( CODE, &Context::command<CODE> ) );

			#undef PP_insert
		}

		Context::Command CommandTable::operator [](size_t const code) const
		{
			Table::const_iterator it = table_.find(code);
			rpg2k_assert( it != table_.end() );
			return it ->second;
		}
	} // namespace model
} // namespace rpg2k
