#ifndef SEQUENCE_MAP_H
#define SEQUENCE_MAP_H

#include <string>
#include <vector>
#include <iostream>
#include <climits>

class SequenceMap
{
public:
	// Zero-parameter constructor.
	SequenceMap() = default;
	// Copy constructor.
	SequenceMap(const SequenceMap& rhs) = default;
	// Copy assignment.
	SequenceMap& operator=(const SequenceMap& rhs) = default;
	// Move constructor.
	SequenceMap(SequenceMap&& rhs) = default;
	// Move assignment.
	SequenceMap& operator=(SequenceMap&& rhs) = default;
	// Destructor.
	~SequenceMap() = default;

	// End of big-five.

	// One-parameter constructor.
	// @a_rec_seq: a recognition sequence.
	// Result is a SequenceMap object with only recognition_sequence_ initialized.
	SequenceMap(const std::string& a_rec_seq) : recognition_sequence_(a_rec_seq)
	{
	}

	// Two-parameter constructor.
	// @a_rec_seq: a recognition sequence.
	// @an_enz_acro: an enzyme acronym.
	// Result is a SequenceMap object with one enzyme acronym.
	SequenceMap(const std::string& a_rec_seq, const std::string& an_enz_acro) : recognition_sequence_(a_rec_seq)
	{
		enzyme_acronyms_.push_back(an_enz_acro);
	}

	// Overloaded < operator.
	// @return true if current recognition sequence is shorter or smaller than rhs,
	//         else false.
	bool operator<(const SequenceMap& rhs) const
	{
		return recognition_sequence_ < rhs.recognition_sequence_ ? true : false;
	}

	// Overloaded > operator.
	// @return true if current recognition sequence is longer or bigger than rhs,
	//         else false.
	bool operator>(const SequenceMap& rhs) const
	{
		return recognition_sequence_ > rhs.recognition_sequence_ ? true : false;
	}

	// @other_sequence: other sequence to be merged.
	// Appends enzyme_acronyms_ member of other_sequence to current sequence's enzyme_acronyms_ member.
	// Assumes data structure doesn't have/allow duplicates 
	// (as in, same enzyme acronym associated with the same recognition sequence appearing twice).
	void Merge(const SequenceMap &other_sequence)
	{
		if (other_sequence.enzyme_acronyms_.size() > 0)
		{
			enzyme_acronyms_.insert(enzyme_acronyms_.end(), other_sequence.enzyme_acronyms_.begin(), other_sequence.enzyme_acronyms_.end());
		}
	}

	// Prints out the enzyme acronyms.
	// Output format: AanI PsiI etc.
	void PrintEnzymeAcronyms() const
	{
		size_t number_of_enzyme_acronyms = enzyme_acronyms_.size();
		if (number_of_enzyme_acronyms != 0)
		{
			for (size_t i = 0; i < number_of_enzyme_acronyms; i++)
			{
				std::cout << enzyme_acronyms_[i];
				if (i < number_of_enzyme_acronyms - 1)
					std::cout << ' ';
			}
			std::cout << std::endl;
		}
		else
		{
			std::cout << "(No enzyme acronyms correspond to recognition sequence)" << std::endl;
		}
	}

	void PrintRecognitionSequence() const
	{
		std::cout << recognition_sequence_ << std::endl;
	}

	friend std::ostream& operator<<(std::ostream& out, const SequenceMap& sequence)
	{
//		out << sequence.recognition_sequence_ << ':';

		if (sequence.enzyme_acronyms_.size() != 0)
		{
			for (size_t i = 0; i < sequence.enzyme_acronyms_.size(); i++)
			{
//				out << ' ' << sequence.enzyme_acronyms_[i];
				out << sequence.enzyme_acronyms_[i];
				if (i < sequence.enzyme_acronyms_.size() - 1)
					out << ' ';
			}
		}
		else
		{
			out << " (No Enzyme Acronyms)";
		}

		return out;
	}
	
	// Overloading >> operator.
	// Reads enzyme acronyms in a list format (1 acronym each line).
	// Assumes the input format is similar to input_part2a.txt.
	// Ex:	Absi
	//		AanI
	//		...
	//		etc.
	friend std::istream& operator>>(std::istream& in, SequenceMap& sequence)
	{
		std::string enzyme;
		while (in >> enzyme)
		{
			in.ignore(INT_MAX, '\n');
			sequence.enzyme_acronyms_.push_back(enzyme);
		}

		return in;
	}
private:
	// Recognition sequence.
	std::string recognition_sequence_;
	// Enzyme acronyms.
	std::vector<std::string> enzyme_acronyms_;
};

#endif
