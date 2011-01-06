#include "Debug.hxx"
#include "Stream.hxx"


namespace rpg2k
{
	namespace structure
	{
		String readHeader(std::istream& is)
		{
			is.seekg(0, std::ios_base::beg);
			Binary buf;
			readWithSize(is, buf);
			return static_cast<String>(buf);
		}
		std::ostream& writeHeader(std::ostream& os, String const& header)
		{
			os.seekp(0, std::ios_base::beg);
			return writeWithSize(os, header);
		}

		bool checkHeader(std::istream& is,  String const& header)
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
			return os.write( reinterpret_cast<char const*>(buff), size);
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
			return write(os, b);
		}
		std::istream& readWithSize(std::istream& is, Binary& dst)
		{
			dst.resize( readBER(is) );
			return read(is, dst);
		}

		std::ostream& write(std::ostream& os, Binary const& b)
		{
			return os.write( reinterpret_cast<char const*>( b.data() ), b.size() );
		}
		std::istream& read(std::istream& is, Binary& dst)
		{
			return is.read( reinterpret_cast<char*>( dst.data() ), dst.size() );
		}
	} // namespace structure
} // namespace rpg2k
