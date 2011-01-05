#include "Debug.hxx"
#include "Stream.hxx"


namespace rpg2k
{
	namespace structure
	{
		RPG2kString readHeader(std::istream& is)
		{
			is.seekg(0, std::ios_base::beg);
			Binary buf;
			readWithSize(is, buf);
			return static_cast<RPG2kString>(buf);
		}
		std::ostream& writeHeader(std::ostream& os, RPG2kString const& header)
		{
			os.seekp(0, std::ios_base::beg);
			writeWithSize(os, header);
			return os;
		}

		bool checkHeader(std::istream& is,  RPG2kString const& header)
		{
			return( readHeader(is) == header );
		}

		std::ostream& writeBER(std::ostream& os, unsigned num)
		{
			// BER output buffer
			uint8_t buff[ ( sizeof(num) * CHAR_BIT ) / BER_BIT + 1];
			unsigned size = berSize(num), index = size;
			// unsigned numBack = num;
		// set data
			buff[--index] = num & BER_MASK; // BER terminator
			num >>= BER_BIT;
			while(num) {
				buff[--index] = (num & BER_MASK) | BER_SIGN;
				num >>= BER_BIT;
			}
			/*
			clog << numBack << " = " << size << " :";
			clog << std::setfill('0') << std::hex;
			for(unsigned i = 0; i < size; i++) { clog << " " << std::setw(2) << (buff[i] & 0xff); }
			clog << std::setfill(' ') << std::dec;
			clog << ";" << endl;
			 */
		// write data
			os.write( reinterpret_cast<char const*>(buff), size);
			return os;
		}
		unsigned readBER(std::istream& is)
		{
			unsigned ret = 0;
			uint8_t data;
		// extract
			do {
				data = is.get();
				ret = (ret << BER_BIT) | (data & BER_MASK);
			} while(data > BER_SIGN);
		// result
			return ret;
		}

		std::ostream& writeWithSize(std::ostream& os, Binary const& b)
		{
			writeBER( os, b.size() );
			os.write( reinterpret_cast<char const*>( b.data() ), b.size() );
			return os;
		}
		std::istream& readWithSize(std::istream& is, Binary& dst)
		{
			dst.resize( readBER(is) );
			is.read( reinterpret_cast<char*>( dst.data() ), dst.size() );
			return is;
		}

		std::ostream& write(std::ostream& os, Binary const& b)
		{
			os.write( reinterpret_cast<char const*>( b.data() ), b.size() );
			return os;
		}
		std::istream& read(std::istream& is, Binary& dst)
		{
			is.read( reinterpret_cast<char*>( dst.data() ), dst.size() );
			return is;
		}
	} // namespace structure
} // namespace rpg2k
