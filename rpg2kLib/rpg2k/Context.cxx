#include "Context.hxx"
#include "Project.hxx"


namespace rpg2k
{
	namespace model
	{
		Context::Context(Project& p, unsigned evID, EventStart::Type t)
		: owner_(p)
		, eventID_(evID), type_(t)
		{
		}
	}
}
