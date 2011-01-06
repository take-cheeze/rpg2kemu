#ifndef _INC__RPG2K__STRUCTURE__DESCRIPTOR_HPP
#define _INC__RPG2K__STRUCTURE__DESCRIPTOR_HPP

#include "Define.hxx"

#include <boost/bimap.hpp>
#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_unordered_map.hpp>


namespace rpg2k
{
	class Binary;

	namespace structure
	{
		class Array1D;
		class Array2D;
		class BerEnum;
		class Element;
		class Event;

		class EventState;
		class Music;
		class Sound;

		class Descriptor;
		typedef boost::ptr_unordered_map<unsigned, Descriptor> ArrayDefineType;
		typedef ArrayDefineType const& ArrayDefine;
		typedef std::auto_ptr<ArrayDefineType> ArrayDefinePointer;

		#define PP_basicTypes(func) \
			func(int) \
			func(bool) \
			func(double)
		#define PP_rpg2kTypes(func) \
			func(Array1D) \
			func(Array2D) \
			func(BerEnum) \
			func(Binary) \
			func(String) \
			func(Event) \

		class ElementType : boost::noncopyable
		{
		public:
			static ElementType const& instance();

			enum Enum {
				#define PP_enum(TYPE) TYPE##_,
				PP_basicTypes(PP_enum)
				PP_rpg2kTypes(PP_enum)
				#undef PP_enum
			};
			Enum toEnum(String const& name) const;
			String const& toString(Enum e) const;

			ElementType();
		private:
			typedef boost::bimap<Enum, String> Table;
			Table table_;
		}; // class ElementType
		class Descriptor
		{
		private:
			ElementType::Enum const type_;
			bool const hasDefault_;

			union {
				#define PP_enum(TYPE) TYPE TYPE##_;
				PP_basicTypes(PP_enum)
				#undef PP_enum
				String const* String_;
				boost::ptr_unordered_map<unsigned, Descriptor>* arrayDefine;
			} impl_;

			operator ArrayDefine() const;
		public:
			Descriptor(Descriptor const& src);
			Descriptor(String const& type);
			Descriptor(String const& type, String const& val);
			Descriptor(String const& type, ArrayDefinePointer def);

			~Descriptor();

			#define PP_castOperator(type) operator type const&() const;
			PP_basicTypes(PP_castOperator)
			#undef PP_castOperator
			operator String const&() const;
			ArrayDefine arrayDefine() const { return static_cast<ArrayDefine>(*this); }

			operator unsigned const&() const
			{
				return reinterpret_cast<unsigned const&>( static_cast<int const&>(*this) );
			}

			String const& typeName() const;
			ElementType::Enum type() const { return type_; }

			bool hasDefault() const { return hasDefault_; }
		}; // class Descriptor
	} // namespace structure
} // namespace rpg2k

#endif // _INC__RPG2K__STRUCTURE__DESCRIPTOR_HPP
