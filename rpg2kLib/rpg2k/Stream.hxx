#ifndef _INC__RPG2K__FILE_HPP
#define _INC__RPG2K__FILE_HPP

#include "Structure.hxx"

#include <istream>
#include <ostream>
#include <sstream>


namespace rpg2k
{
	namespace structure
	{
		bool checkHeader(std::istream& is, RPG2kString const& header);
		RPG2kString readHeader(std::istream& is);
		std::ostream& writeHeader(std::ostream& os, RPG2kString const& header);

		template<class T>
		Binary serialize(T const& src)
		{
			std::ostringstream s;
			src.serialize(s);

			return Binary( s.str() );
		}

		unsigned readBER(std::istream& is);
		std::ostream& writeBER(std::ostream& os, unsigned val);

		std::istream& readWithSize(std::istream& is, Binary& dst);
		std::ostream& writeWithSize(std::ostream& os, Binary const& b);

		std::istream& read(std::istream& is, Binary& dst);
		std::ostream& write(std::ostream& os, Binary const& b);
	} // namespace structure
} // namespace rpg2k

#endif
