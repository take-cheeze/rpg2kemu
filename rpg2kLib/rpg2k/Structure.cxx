#include "Array1DWrapper.hxx"
#include "Debug.hxx"
#include "Element.hxx"
#include "Encode.hxx"
#include "Stream.hxx"

#include <cctype>


namespace rpg2k
{
	CharSet::Dir::Type toCharSetDir(EventDir::Type const dir)
	{
		switch(dir) {
			case EventDir::DOWN : return CharSet::Dir::DOWN ;
			case EventDir::LEFT : return CharSet::Dir::LEFT ;
			case EventDir::RIGHT: return CharSet::Dir::RIGHT;
			case EventDir::UP   : return CharSet::Dir::UP   ;
			default: return CharSet::Dir::DOWN;
		}
	}
	EventDir::Type toEventDir(CharSet::Dir::Type const key)
	{
		switch(key) {
			case CharSet::Dir::UP   : return EventDir::UP   ;
			case CharSet::Dir::LEFT : return EventDir::LEFT ;
			case CharSet::Dir::RIGHT: return EventDir::RIGHT;
			case CharSet::Dir::DOWN : return EventDir::DOWN ;
			default: return EventDir::DOWN;
		}
	}

	/*
	 * xor shift random number generator
	 * from http://ja.wikipedia.org/wiki/Xorshift
	 */
	unsigned random()
	{
		static unsigned x=123456789, y=362436069, z=521288629, w=88675123;

		unsigned t = ( x^(x << 11) );
		x=y; y=z; z=w;
		return ( w = ( w^(w >> 19) ) ^ ( t^(t >> 8) ) );
	}
	unsigned random(unsigned const max)
	{
		return ( random() % max );
	}
	int random(int const min, int const max)
	{
		return ( random(max - min + 1) + min );
	}

	SystemString String::toSystem() const
	{
		return Encode::instance().toSystem(*this);
	}
	std::ostream& String::serialize(std::ostream& os) const
	{
		return os.write( this->c_str(), this->size() );
	}
	String SystemString::toRPG2k () const
	{
		return Encode::instance().toRPG2k (*this);
	}

	namespace structure
	{
		unsigned berSize(uint32_t num)
		{
			unsigned ret = 0;
			do {
				ret++;
				num >>= BER_BIT;
			} while(num);
			return ret;
		}
	} // namespace structure

	bool Binary::isBER() const
	{
		if( !size() || ( ( size() > ( sizeof(uint32_t) * CHAR_BIT ) / structure::BER_BIT + 1) ) ) return false;

		const_reverse_iterator it = std::vector<uint8_t>::rbegin();
		if( *it > structure::BER_SIGN ) return false;

		while( ++it < std::vector<uint8_t>::rend() ) if( *it < structure::BER_SIGN ) return false;

		return true;
	}
	bool Binary::isString() const
	{
		for(const_iterator i = begin(); i < end(); i++) if( std::iscntrl(*i) ) return false;
		try {
			static_cast<String>(*this).toSystem();
			return true;
		} catch(debug::AnalyzeException const&) { return false; }
	}

	Binary::operator String() const
	{
		// rpg2k_assert( isString() ); // will be so slow if enabled
		return String( (char*)pointer(), size() );
	}
	Binary::operator int() const
	{
		rpg2k_assert( isBER() );

		std::istringstream iss( static_cast<std::string>(*this), structure::INPUT_FLAG );
		return int32_t( structure::readBER(iss) );
	}
	Binary::operator bool() const
	{
		rpg2k_assert( size() == sizeof(bool) );
		switch( static_cast<int>(*this) ) {
			case false: return false;
			case true : return true ;
			default: rpg2k_assert(false);
		}
		return false;
	}
	Binary::operator double() const
	{
		rpg2k_assert( size() == sizeof(double) );
		return *( (double*)this->data() );
	}

	Binary& Binary::operator =(String const& str)
	{
		resize( str.size() );
		std::memcpy( this->data(), str.c_str(), str.size() );
		return *this;
	}
	Binary& Binary::operator =(int const num)
	{
		std::ostringstream s;
		structure::writeBER(s, int32_t(num) );
		this->assign( s.str() );
		return *this;
	}
	Binary& Binary::operator =(bool const b)
	{
		resize( sizeof(bool) );
		(*this)[0] = b;
		return *this;
	}
	Binary& Binary::operator =(double const d)
	{
		resize( sizeof(double) );
		*( (double*)this->data() ) = d;
		return *this;
	}

	unsigned Binary::serializedSize() const { return this->size(); }
	void Binary::serialize(std::ostream& s) const
	{
		structure::write(s, *this);
	}
} // namespace rpg2k
