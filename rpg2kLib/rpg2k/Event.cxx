#include "Event.hxx"
#include "Stream.hxx"


namespace rpg2k
{
	namespace structure
	{
		Instruction::Instruction()
		: code_(-1)
		{
		}
		Instruction::Instruction(std::istream& s)
		{
			code_ = readBER(s);
			nest_ = readBER(s);

			Binary b;
			readWithSize(s, b);
			stringArgument_ = static_cast<String>(b);

			int argNum = readBER(s);

			argument_.resize(argNum, VAR_DEF_VAL);
			for(int i = 0; i < argNum; i++) argument_[i] = readBER(s);
		}

		int32_t Instruction::at(unsigned index) const
		{ rpg2k_assert( index < argument_.size() ); return argument_[index]; }
		int32_t Instruction::operator [](unsigned index) const
		{ rpg2k_assert( index < argument_.size() ); return argument_[index]; }
		int32_t& Instruction::at(unsigned index)
		{ rpg2k_assert( index < argument_.size() ); return argument_[index]; }
		int32_t& Instruction::operator [](unsigned index)
		{ rpg2k_assert( index < argument_.size() ); return argument_[index]; }

		unsigned Instruction::serializedSize() const
		{
			unsigned ret =
				berSize(code_) + berSize(nest_) +
				berSize( stringArgument_.size() ) + stringArgument_.size() +
				berSize( argument_.size() );
			for(unsigned i = 0; i < argument_.size(); i++) ret += berSize(argument_[i]);
			return ret;
		}
		std::ostream& Instruction::serialize(std::ostream& s) const
		{
			writeBER(s, code_);
			writeBER(s, nest_);
			writeWithSize(s, stringArgument_);
			writeBER( s, argument_.size() );
			for(unsigned i = 0; i < argument_.size(); i++) writeBER(s, argument_[i]);
			return s;
		}

		Event::Event(Binary const& b)
		{
			std::istringstream s( static_cast<std::string>(b), INPUT_FLAG );
			init(s);
		}

		void Event::init(std::istream& s)
		{
			while( !s.eof() ) {
				data_.push_back( Instruction(s) );
				if(data_.back().code() == 12110) { // check for label
					if( !label_.insert( std::make_pair(data_.back()[0], data_.size() - 1) ).second ) {
						rpg2k_assert(false);
					}
				}
			}
		}

		unsigned Event::serializedSize() const
		{
			return this->serializedSize(0);
		}
		unsigned Event::serializedSize(unsigned const offset) const
		{
			unsigned ret = 0;
			for(Data::const_iterator i = data_.begin() + offset; i < data_.end(); ++i) {
				ret += i->serializedSize();
			}
			return ret;
		}
		std::ostream& Event::serialize(std::ostream& s) const
		{
			for(Data::const_iterator i = data_.begin(); i < data_.end(); ++i) {
				i->serialize(s);
			}
			return s;
		}

		void Event::resize(unsigned size)
		{
			data_.resize(size);
		}
	} // namespace structure
} // namespace rpg2k
