#ifndef _INC__RGP2K__ENCODE__ENCODE_HPP
#define _INC__RGP2K__ENCODE__ENCODE_HPP

#include "Define.hxx"
#include "Singleton.hxx"

#include <iconv.h>
#include <stdexcept>


namespace rpg2k
{
	class Encode : public Singleton<Encode>
	{
		friend class Singleton<Encode>;
	private:
		enum { BUFF_SIZE = 1024, };

		static std::string const SYSTEM_ENCODE;
		static std::string const RPG2K_ENCODE;

		::iconv_t toSystem_, toRPG2k_;
		std::string sysEncode_;
	protected:
		Encode();
		~Encode();

		static std::string convertString(std::string const& src, iconv_t cd);
		static iconv_t openConverter(std::string const& to, std::string const& from);
	public:
		SystemString toSystem( String const& src) const { return convertString(src, toSystem_); }
		 String toRPG2k (SystemString const& src) const { return convertString(src, toRPG2k_ ); }

		std::string const& systemEncoding() const { return sysEncode_; }
	}; // class Encode
} // namespace rpg2k

#endif
