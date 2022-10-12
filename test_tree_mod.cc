// <Your name>
// Main file for Part2(b) of Homework 2.
// Code will compile and run after you have completed sequence_map.h.

#include "avl_tree_p2c.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <fstream>
#include <climits>
using namespace std;

namespace {

	// @in_line: the current line being read from the input stream/database.
	// @reco_seq: the recognition sequence to add to the avl tree.
	//				the recognition sequence updates to the latest sequence before the separator (pre-update).
	// @sep_pos: the position of the '/' separator.
	//				position updates to the next separator with each function call.
	// @end_pos: the end position ('//') of the current line.
	bool GetNextRecognitionSequence(const string& in_line, string& reco_seq, size_t& sep_pos, const size_t& end_pos)
	{
		// No more recognition sequences.
		if (sep_pos == end_pos)
			return false;

		size_t next_separator_position = in_line.find('/', sep_pos + 1);

		reco_seq = in_line.substr(sep_pos + 1, next_separator_position - sep_pos - 1);
		sep_pos = next_separator_position;

		return true;
	}

	// @db_filename: an input database filename.
	// @seq_filename: an input sequences filename.
	// @a_tree: an input tree of the type TreeType. It is assumed to be
	//  empty.
	template <typename TreeType>
	void TestTree(const string& db_filename, const string& seq_filename, TreeType& a_tree) {
		// Code for running Part2(b)

		ifstream database(db_filename);
		string db_line;

		// Skip header of database (10 lines).
		for (int i = 0; i < 10; i++)
			database.ignore(INT_MAX, '\n');

		// Fill a_tree with data from database.
		while (getline(database, db_line))
		{
			// end_position is used to determine the end of the line.
			// separator_position is used to aid in splitting the enzyme acronyms and recognition sequences.
			size_t end_position = db_line.find("//");
			size_t separator_position = db_line.find('/');

			string an_enz_acro = db_line.substr(0, separator_position);
			string a_reco_seq;

			while (GetNextRecognitionSequence(db_line, a_reco_seq, separator_position, end_position))
			{
				SequenceMap new_sequence_map(a_reco_seq, an_enz_acro);
				a_tree.insert(new_sequence_map);
			}
		}

		size_t number_of_nodes = a_tree.numberOfNodes();
		float average_depth = a_tree.averageDepth();
		cout << "2: " << number_of_nodes << endl;
		cout << "3a: " << a_tree.averageDepth() << endl;
		if (number_of_nodes != 0)
			cout << "3b: " << average_depth / number_of_nodes << endl;
		else
			cout << "3b: Cannot compute ratio, tree is empty." << endl;

		ifstream sequences(seq_filename);
		string query_sequence;

		size_t successful_queries = 0;

		while (getline(sequences, query_sequence) && !sequences.fail())
		{
			// a_tree only has comparison functions for SequenceMap objects.
			SequenceMap comparison_sequence_map(query_sequence);

			if (a_tree.find(comparison_sequence_map))
				successful_queries++;
		}


		cout << "4a: " << successful_queries << endl;
		if (successful_queries != 0)
			cout << "4b: " << a_tree.getTotalRecursionCalls() / (float)successful_queries << endl; ///////////////////////////////// not exact match, .02 off
		else
			cout << "4b: Cannot compute average number of recursion calls, no successful queries." << endl;

		sequences.close();

		// Start reading input file from the beginning.
		sequences.open(seq_filename);

		size_t successful_removes = 0;
		a_tree.resetRecursionCounter();

		while (getline(sequences, query_sequence) && !sequences.fail())
		{
			// a_tree only has comparison functions for SequenceMap objects.
			SequenceMap comparison_sequence_map(query_sequence);

			if (a_tree.remove(comparison_sequence_map))
				successful_removes++;

			// Skip every other line of the file.
			sequences.ignore(INT_MAX, '\n');
		}

		cout << "5a: " << successful_removes << endl;
		if (successful_removes != 0)
			cout << "5b: " << a_tree.getTotalRecursionCalls() / (float)successful_removes << endl; ////////////////////////////////////need to increment total_recursion_calls
		else
			cout << "5b: Cannot compute average number of recursion calls, no successful removes." << endl;

		number_of_nodes = a_tree.numberOfNodes();
		average_depth = a_tree.averageDepth();
		cout << "6a: " << number_of_nodes << endl;
		cout << "6b: " << average_depth << endl;
		if (number_of_nodes != 0)
			cout << "6c: " << average_depth / (float)number_of_nodes << endl;
		else
			cout << "6c: Cannot compute ratio, tree is empty." << endl;

	}

}  // namespace

/*
int
main(int argc, char** argv) {
	if (argc != 3) {
		cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename>" << endl;
		return 0;
	}
	const string db_filename(argv[1]);
	const string seq_filename(argv[2]);

	cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;

	AvlTree<SequenceMap> a_tree;
	TestTree(db_filename, seq_filename, a_tree);

	return 0;
}
*/
