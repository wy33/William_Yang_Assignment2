// William Yang
// QueryTree
// Main file for Part2(a) of Homework 2.

#include "avl_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <fstream>
#include <climits>
using namespace std;

namespace {
	
	// Helper function.
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

		return true;	// More recognition sequences.
	}

	// @db_filename: an input filename.
	// @a_tree: an input tree of the type TreeType. It is assumed to be
	//  empty.
	template <typename TreeType>
	void QueryTree(const string& db_filename, TreeType& a_tree) {
		// Code for running Part2(a)
		// Parse input file @db_filename and fill tree @a_tree.

		ifstream database(db_filename);
		if (!database.is_open())
		{
			cerr << "Failed to read database." << endl;
			exit(1);
		}

		// Skip header of database (10 lines).
		for(int i = 0; i < 10; i++)
			database.ignore(INT_MAX, '\n');

		string db_line;
		// Fill a_tree with data from database.
		while (getline(database, db_line))
		{
			// end_position is used to determine the end of the line.
			// separator_position is used to aid in splitting the enzyme acronyms and recognition sequences.
			size_t end_position = db_line.find("//");
			size_t separator_position = db_line.find('/');

			string an_enz_acro = db_line.substr(0, separator_position);
			string a_reco_seq;

			// Insert to tree.
			while (GetNextRecognitionSequence(db_line, a_reco_seq, separator_position, end_position))
			{
				SequenceMap new_sequence_map(a_reco_seq, an_enz_acro);
				a_tree.insert(new_sequence_map);
			}
		}	// Tree insert finished.
		database.close();

		string query_sequence;
		// Querying tree.
		while (getline(cin, query_sequence) && !cin.fail())
		{
			// a_tree only has comparison functions for SequenceMap objects.
			SequenceMap comparison_sequence_map(query_sequence);

			if (a_tree.contains(comparison_sequence_map))
				a_tree.getElement(comparison_sequence_map).PrintEnzymeAcronyms();
			else
				cout << "Not Found" << endl;
		}
	}

}  // namespace

/*
int
main(int argc, char** argv) {
	if (argc != 2) {
		cout << "Usage: " << argv[0] << " <databasefilename>" << endl;
		return 0;
	}
	const string db_filename(argv[1]);

	cout << "Input filename is " << db_filename << endl;
	AvlTree<SequenceMap> a_tree;
	QueryTree(db_filename, a_tree);

	return 0;
}
*/