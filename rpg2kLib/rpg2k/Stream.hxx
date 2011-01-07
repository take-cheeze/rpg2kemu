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
		std::ios_base::openmode const INPUT_FLAG = std::ios_base::in | std::ios_base::binary;
		std::ios_base::openmode const OUTPUT_FLAG = std::ios_base::out
			| std::ios_base::binary | std::ios_base::trunc;

		bool checkHeader(std::istream& is, String const& header);
		String readHeader(std::istream& is);
		std::ostream& writeHeader(std::ostream& os, String const& header);

		template<class T>
		Binary serialize(T const& src)
		{
			std::ostringstream s(OUTPUT_FLAG);
			src.serialize(s);

			return Binary( s.str() );
		}

		unsigned readBER(std::istream& is);
		std::ostream& writeBER(std::ostream& os, unsigned val);

		std::istream& readWithSize(std::istream& is, Binary& dst);
		template<class T>
		std::ostream& writeWithSize(std::ostream& os, T const& val)
		{
			return val.serialize( writeBER( os, val.serializedSize() ) );
		}
	} // namespace structure
} // namespace rpg2k

#endif
