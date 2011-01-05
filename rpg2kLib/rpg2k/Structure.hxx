#ifndef _INC__RPG2K__STRUCTURE_HPP
#define _INC__RPG2K__STRUCTURE_HPP

#include "Define.hxx"

#include <boost/array.hpp>
#include <climits>
#include <vector>
#include <set>


namespace rpg2k
{
	namespace structure
	{
		enum {
			BER_BIT  = (CHAR_BIT-1),
			BER_SIGN = 0x01 << BER_BIT,
			BER_MASK = BER_SIGN - 1,
		};
		unsigned berSize(unsigned num);
	} // namespace structure

	class Binary : public std::vector<uint8_t>
	{
	private:
		template<class SrcT>
		static void exchangeEndianIfNeed(uint8_t* dst, SrcT const& src)
		{
			for(typename SrcT::const_iterator srcIt = src.begin(); srcIt != src.end(); ++srcIt) {
				uint8_t const* srcCur = reinterpret_cast<uint8_t const*>( &(*srcIt) );
				for(unsigned i = 0; i < sizeof(typename SrcT::value_type); i++) {
				#if RPG2K_IS_BIG_ENDIAN
					*(dst++) = srcCur[sizeof(typename SrcT::value_type)-i-1];
				#elif RPG2K_IS_LITTLE_ENDIAN
					*(dst++) = srcCur[i];
				#else
					#error unsupported endian
				#endif
				}
			}
		}
		template<class DstT>
		static void exchangeEndianIfNeed(DstT& dst, uint8_t const* src)
		{
			for(typename DstT::iterator dstIt = dst.begin(); dstIt != dst.end(); ++dstIt) {
				uint8_t* dstCur = reinterpret_cast<uint8_t*>( &(*dstIt) );
				for(unsigned i = 0; i < sizeof(typename DstT::value_type); i++) {
				#if RPG2K_IS_BIG_ENDIAN
					dstCur[sizeof(typename SrcT::value_type)-i-1] = *(src++);
				#elif RPG2K_IS_LITTLE_ENDIAN
					dstCur[i] = *(src++);
				#else
					#error unsupported endian
				#endif
				}
			}
		}
	public:
		Binary() {}
		explicit Binary(unsigned size) : std::vector<uint8_t>(size) {}
		explicit Binary(uint8_t* data, unsigned size) : std::vector<uint8_t>(data, data + size) {}
		Binary(Binary const& b) : std::vector<uint8_t>(b) {}
		Binary(std::string const& str) : std::vector<uint8_t>(str.begin(), str.end()) {}

		uint8_t const* data(unsigned index = 0) const { return &((*this)[index]); }
		uint8_t* data(unsigned index = 0) { return &((*this)[index]); }

		bool isBER() const;
		bool isString() const;
	// operator wrap of converter
		operator RPG2kString() const;
		operator int   () const;
		operator bool  () const;
		operator double() const;
	// operator wrap of setter
		Binary& operator =(RPG2kString const& src);
		Binary& operator =(int    src);
		Binary& operator =(bool   src);
		Binary& operator =(double src);

		unsigned serializedSize() const;
		void serialize(std::ostream& s) const;

		template<class T>
		std::vector<T> convert() const
		{
			rpg2k_assert( ( this->size() % sizeof(T) ) == 0 );

			std::vector<T> output( this->size() / sizeof(T) );
			exchangeEndianIfNeed( output, this->data() );
			return output;
		}
		template<class T, size_t S>
		boost::array<T, S> convert() const
		{
			rpg2k_assert( ( this->size() % sizeof(T) ) == 0 );
			rpg2k_assert( (this->size() / sizeof(T)) == S );

			boost::array<T, S> output;
			exchangeEndianIfNeed( output, this->data() );
			return output;
		}
		template<class T>
		Binary& assign(T const& src)
		{
			this->resize( sizeof(typename T::value_type) * src.size() );
			exchangeEndianIfNeed( this->data(), src );
			return *this;
		}

		template<class T>
		Binary(T const& src) { assign(src); }
		template<class T>
		Binary& operator =(T const& src) { return assign(src); }
		template<typename T>
		operator std::vector<T>() const { return convert<T>(); }
		template<typename T, size_t S>
		operator boost::array<T, S>() const { return convert<T, S>(); }
		template<class T>
		operator std::set<T>() const
		{
			std::vector<T> const& output = convert<T>();
			return std::set<T>( output.begin(), output.end() );
		}
	}; // class Binary
} // namespace rpg2k

#endif // _INC__RPG2K__STRUCTURE_HPP
