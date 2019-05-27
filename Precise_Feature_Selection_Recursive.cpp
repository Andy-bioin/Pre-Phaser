#include <array>
#include <random>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <string>
#include <map>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include "boost/lexical_cast.hpp"
#include<numeric>  // inner_product, iota
#include<cmath>    // sqrt
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;
using namespace std;


int main(int argc, char *argv[])
{
	vector<int> available_train_gene_indeces;
	string train_file_prefix = argv[1];	
	int k = stoi(argv[2]);
	for (int i = 3; i < argc; ++i){
		int gene_index = stoi(argv[i]);
		available_train_gene_indeces.push_back(gene_index);
	}

	// read in train gene names
	vector<string> canonical_train_gene_names;
	ifstream file(train_file_prefix + "_genes.csv");
	string line = "";
	getline(file, line);
	boost::algorithm::split(canonical_train_gene_names, line, boost::is_any_of(","));
	file.close();


	// read in the train angles 
	vector<double> train_cell_angles;
	vector<string> read;
	ifstream file2(train_file_prefix + "_angles.csv");
	getline(file2, line);
	stringstream tokenStream2(line);
	string token2;
	while (getline(tokenStream2, token2, ',')){
		train_cell_angles.push_back(stod(token2)); 
	}
	file2.close();


	// read in train cell names
	vector<string> train_cell_names;
	ifstream file3(train_file_prefix + "_cells.csv");
	//ifstream file3("SC_df_z_train_cells.csv");
	getline(file3, line);
	boost::algorithm::split(train_cell_names, line, boost::is_any_of(","));
	file3.close();
	

	// read in the train data matrix
	vector<vector<double>> trainDataMatrix;
	ifstream file4(train_file_prefix + "_array.csv");		
	while (getline(file4, line))
	{
		vector<double> row;
		stringstream tokenStream(line);
		string token;
		int counter = 0;
		while (getline(tokenStream, token, ' ')){
			if (token == "nan") {
				row.push_back(0.0);
				available_train_gene_indeces.erase(remove(available_train_gene_indeces.begin(),\
				available_train_gene_indeces.end(), counter), available_train_gene_indeces.end());
			} else {	
				row.push_back(stod(token));
			}
			counter += 1;
		}
		trainDataMatrix.push_back(row);
	}
	file4.close();


	int gene_indeces_size = available_train_gene_indeces.size();
	if (available_train_gene_indeces.size() == 0) {
		cout<<0.0;
		return 0;
	}


	srand(time(NULL));
	// go through all the test cells one by one 	
	double total_error = 0.0;
	int num_g1 = 0;
	int num_g2 = 0;
	int num_s = 0;
	double total_pvalue = 0.0;
	vector<string> predicted_angles;
	for(int i = 0; i < train_cell_names.size(); i++) {
		vector<tuple<double, double> > dist_names_list;
		vector<double> test_cell = trainDataMatrix[i];
		// go through all the train cells one by one
		// train cells are all cells not identical to the test cell
		for(int j = 0; j < train_cell_names.size(); j++){
			if (i == j)
				continue;
			vector<double> train_cell = trainDataMatrix[j];

			// select two vectors with distance
			vector<double> test_vector(gene_indeces_size, 0);	
			vector<double> train_vector(gene_indeces_size, 0);	

			transform(available_train_gene_indeces.begin(), available_train_gene_indeces.end(), \
				test_vector.begin(), [test_cell](size_t pos) {return test_cell[pos];});
			transform(available_train_gene_indeces.begin(), available_train_gene_indeces.end(),  \
				train_vector.begin(), [train_cell](size_t pos) {return train_cell[pos];});

			// euclidean distance	
			vector<double>	auxiliary;
			transform(test_vector.begin(), test_vector.end(), train_vector.begin(), back_inserter(auxiliary),//
			[](double element1, double element2) {return pow((element1-element2),2);});
			double distance = sqrt(accumulate(auxiliary.begin(), auxiliary.end(), 0.0));

			// record distance 
			dist_names_list.push_back(make_tuple(distance, train_cell_angles[j]));
				
			//break;
		}
		// sort the training cells based on distances, get the best one for now
		sort(dist_names_list.begin(), dist_names_list.end());
	
		double sine_sum = 0.0;
		double cos_sum = 0.0;
		for (int idx = 0; idx <k; idx++) {
			sine_sum += sin(get<1>(dist_names_list[idx]));
			cos_sum += cos(get<1>(dist_names_list[idx]));
		}
		double avg_angle = atan2(sine_sum, cos_sum);
		if (avg_angle < 0)
			avg_angle = 2 * M_PI + avg_angle;
		double test_error = (M_PI - abs(abs(train_cell_angles[i] - avg_angle) - M_PI))/M_PI;
		total_error += test_error;
		
		// add to predicted labels
		predicted_angles.push_back(to_string(avg_angle));
	
	}
	cout<<1-total_error/(train_cell_names.size()-1);

	//ofstream outfile(train_file_prefix + "_predicted_angles.csv");
	//string joined_output = boost::algorithm::join(predicted_angles, ",");
	//outfile<<joined_output<<"\n";
	//outfile.close();
}


