#ifndef _INC_RPG2K__SINGLETON_
#define _INC_RPG2K__SINGLETON_

#include <boost/noncopyable.hpp>


namespace rpg2k
{
	template<class T>
	class Singleton : boost::noncopyable
	{
	public:
		static T& instance()
		{
			static T theInstance;
			return theInstance;
		}
	}; // class Singleton
	template<class T>
	class ConstSingleton : boost::noncopyable
	{
	public:
		static T const& instance()
		{
			static T const theInstance;
			return theInstance;
		}
	}; // class Singleton
} // namespace rpg2k

#endif // _INC_RPG2K__SINGLETON_
