#include "asd-cli.h"

const string VERSION = "1.0.0";

const string ARG_CALC_IBS = "--ibs";
const bool DEFAULT_CALC_IBS = false;
const string HELP_CALC_IBS = "Set to output all IBS sharing matrices too.";

const string ARG_OUTFILE = "--out";
const string DEFAULT_OUTFILE = "outfile";
const string HELP_OUTFILE = "Basename for output files.";

const string ARG_FILENAME = "--stru";
const string DEFAULT_FILENAME = "__none";
const string HELP_FILENAME = "The input data filename (stru format). Change missing data code with\
\n--missing-stru.";

const string ARG_TPED_FILENAME = "--tped";
const string DEFAULT_TPED_FILENAME = "__none";
const string HELP_TPED_FILENAME = "The input data filename (tped format). Requires a .tfam file (--tfam).\
\nChange missing data code with --missing-tped.";

const string ARG_TFAM_FILENAME = "--tfam";
const string DEFAULT_TFAM_FILENAME = "__none";
const string HELP_TFAM_FILENAME = "The input data filename (tfam format), also requires a .tped file (--tped).";

const string ARG_SORT = "--id";
const int DEFAULT_SORT = 1;
const string HELP_SORT = "Column where individual IDs are. (stru files only)";

const string ARG_THREAD = "--threads";
const int DEFAULT_THREAD = 1;
const string HELP_THREAD = "Number of threads to spawn for faster calculation.";

const string ARG_PARTIAL = "--partial";
const bool DEFAULT_PARTIAL = false;
const string HELP_PARTIAL =
 "If set, outputs two nind x nind matrices. The first is the number of loci used\
\nfor each pairwise comparison, and the second is the untransformed dist/IBS\
\nmatrix. Useful for splitting up very large jobs. Can combine with --combine.";

const string ARG_LOG = "--log";
const bool DEFAULT_LOG = false;
const string HELP_LOG = "Transforms allele sharing distance by -ln(ps) instead of 1-(ps).";

const string ARG_STRU_MISSING = "--missing-stru";
const string DEFAULT_STRU_MISSING = "-9";
const string HELP_STRU_MISSING = "For stru files, set the missing data value.";

const string ARG_TPED_MISSING = "--missing-tped";
const string DEFAULT_TPED_MISSING = "0";
const string HELP_TPED_MISSING = "For stru files, set the missing data value.";

const string ARG_BIALLELIC = "--biallelic";
const bool DEFAULT_BIALLELIC = false;
const string HELP_BIALLELIC = "Set for more efficient computations when all loci are biallelic.";

const string ARG_COMBINE = "--combine";
const string DEFAULT_COMBINE = "__none";
const string HELP_COMBINE = "Combine several files generated with --partial.";

const string ARG_LONG_FORMAT = "--long";
const bool DEFAULT_LONG_FORMAT = false;
const string HELP_LONG_FORMAT = "Instead of printing a matrix, print allele sharing distances one\
\nper row. Formatted <ID1> <ID2> <allele sharing distance>.\
\nNot compatible with --partial.";

const string ARG_IBS_LONG = "--long-ibs";
const bool DEFAULT_IBS_LONG = false;
const string HELP_IBS_LONG = "Instead of printing a matrix, print IBS calculations one\
\nper row. Formatted <ID1> <ID2> <IBS0/1/2>.\
\nNot compatible with --partial.";

string getCommandLineString(int argc, char *argv[])
{
	string str = argv[0];
	for (int i = 1; i < argc; i++) {
		str += " " + string(argv[i]);
	}
	return str;
}

param_t *getCLI(int argc, char *argv[])
{
	param_t *params = new param_t;
	params->addFlag(ARG_THREAD, DEFAULT_THREAD, "", HELP_THREAD);
	params->addFlag(ARG_CALC_IBS, DEFAULT_CALC_IBS, "", HELP_CALC_IBS);
	params->addFlag(ARG_OUTFILE, DEFAULT_OUTFILE, "", HELP_OUTFILE);
	params->addFlag(ARG_FILENAME, DEFAULT_FILENAME, "", HELP_FILENAME);
	params->addFlag(ARG_TPED_FILENAME, DEFAULT_TPED_FILENAME, "", HELP_TPED_FILENAME);
	params->addFlag(ARG_TFAM_FILENAME, DEFAULT_TFAM_FILENAME, "", HELP_TFAM_FILENAME);
	params->addFlag(ARG_SORT, DEFAULT_SORT, "", HELP_SORT);
	params->addFlag(ARG_PARTIAL, DEFAULT_PARTIAL, "", HELP_PARTIAL);
	params->addFlag(ARG_LOG, DEFAULT_LOG, "", HELP_LOG);
	params->addFlag(ARG_STRU_MISSING, DEFAULT_STRU_MISSING, "", HELP_STRU_MISSING);
	params->addFlag(ARG_TPED_MISSING, DEFAULT_TPED_MISSING, "", HELP_TPED_MISSING);
	params->addFlag(ARG_BIALLELIC, DEFAULT_BIALLELIC, "", HELP_BIALLELIC);
	params->addListFlag(ARG_COMBINE, DEFAULT_COMBINE, "", HELP_COMBINE);
	params->addFlag(ARG_LONG_FORMAT, DEFAULT_LONG_FORMAT, "", HELP_LONG_FORMAT);
	params->addFlag(ARG_IBS_LONG, DEFAULT_IBS_LONG, "", HELP_IBS_LONG);

	params->setPreamble("asd v" + VERSION);

	if (!params->parseCommandLine(argc, argv))
	{
		delete params;
		return NULL;
	}
	return params;
}


bool check_int_gt_0(int n) {
	return (n > 0);
}
bool check_int_ge_0(int n) {
	return (n >= 0);
}
bool check_sort(int sort, int ndcols) {
	return (sort <= ndcols && sort >= 1);
}
bool check_file_type(bool STRU, bool TPED, bool TFAM) {
	return ((STRU && !TPED && !TFAM) || (!STRU && TFAM && TPED));
}
