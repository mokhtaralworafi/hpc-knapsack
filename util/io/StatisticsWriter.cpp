#include "StatisticsWriter.h"



StatisticsWriter::StatisticsWriter(std::string filename, std::string algorithmname):
	filename(filename),
	algorithmname(algorithmname),
	durations()
{
}

StatisticsWriter::~StatisticsWriter() {
}

void StatisticsWriter::addDuration(const double seconds) {
	durations.insert(durations.end(), seconds);
}

void StatisticsWriter::clearDurations(){
	durations.clear();
}

//calculate avg duration
double StatisticsWriter::calcAvg() {
	const int n = durations.size();
	double sum = 0;
	for(int i=0; i<n; i++){
		sum += durations[i];
	}
	return sum / n;
}

//calculate root mean square
double StatisticsWriter::calcRms(const double avg) {
	const int n = durations.size();
	double sum = 0;
	for(int i=0; i<n; i++){
		sum += pow(durations[i] - avg, 2);
	}
	return sqrt(sum / n);
}


bool StatisticsWriter::writeToFile() {
	FILE* fp;
	fp = fopen(filename.c_str(), "w");

	if (fp == NULL)
		return false;

	const double avg = calcAvg();
	const double rms = calcRms(avg);

	fprintf(fp, "Alogrithmus;%s\n", algorithmname.c_str());
	fprintf(fp, "Anzahl Durchlaeufe;%d\n", durations.size());
	fprintf(fp, "Durchschnittliche Laufzeit;%.4f\n", avg);
	fprintf(fp, "Quadratisches Mittel;%.4f", rms);
	
	for (int i=0; i < durations.size() ;++i) {
		fprintf(fp, "%d;%.4f\n", i+1, durations[i]);
	}

	fclose(fp);

	return true;
}
