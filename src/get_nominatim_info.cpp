/* Copyright 2015 - Marco Di Cristina, Alessandro Fabbri, Mattia Guidetti, Stefano Sinigardi */

/***************************************************************************
This file is part of get_nominatim_info.

get_nominatim_info is free software : you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

get_nominatim_info is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with get_nominatim_info. If not, see <http://www.gnu.org/licenses/>.
***************************************************************************/

#include "jsoncons/json.hpp"

#define MAJOR_VERSION           1
#define MINOR_VERSION           0

int main(int narg, char** argv) {
	// Usage
	std::cout << "Get_Nominatim_Info - v" << MAJOR_VERSION << "." << MINOR_VERSION << std::endl;
	std::cout << "Usage: " << argv[0] << " -i [input.json] -o [output.json] -f [output format specifier]" << std::endl;
	std::cout << "\t- [input.json] UNIBO style GPS .json file to parse" << std::endl;
	std::cout << "\t- [output.json] improved .json with geolocalization data" << std::endl;
	std::cout << "\t- [format specifier] use 'a' (without quotes) for array json, 'o' for object json" << std::endl;
	std::cout << "\t- -f is optional, if omitted the output format will reflect the input file" << std::endl;


	// Parsing command line
	std::string input_name, output_name, outjson_type{};
	if(narg > 2) { /* Parse arguments, if there are arguments supplied */
		for(int i = 1; i < narg; i++) {
			if(argv[i][0] == '-' || argv[i][0] == '/') {       // switches or options...
				switch(tolower(argv[i][1])) {
				case 'i':
					input_name = argv[++i];
					break;
				case 'o':
					output_name = argv[++i];
					break;
				case 'f':
					outjson_type = argv[++i];
					break;
				default:    // no match...
					std::cout << "Flag \"" << argv[i] << "\" not recognized. Quitting..." << std::endl;
					exit(1);
				}
			} else {
				std::cout << "Flag \"" << argv[i] << "\" not recognized. Quitting..." << std::endl;
				exit(11);
			}
		}
	} else { std::cout << "No flags specified. Read usage and relaunch properly." << std::endl; exit(111); }

	// Safety checks for file manipulations 
	if(input_name.size() > 5) {
		if(input_name.substr(input_name.size() - 5, 5) != ".json") {
			std::cout << input_name << " is not a valid .json file. Quitting..." << std::endl;
			exit(2);
		}
	} else {
		std::cout << input_name << " is not a valid .json file. Quitting..." << std::endl;
		exit(22);
	}

	// Parsing of input.json and building of output.json
	jsoncons::json gps_records = jsoncons::json::parse_file(input_name);


	jsoncons::json outjson;


	//decide output type
	if(outjson_type == "a") //array
		outjson = jsoncons::json(jsoncons::json::an_array);
	else if(outjson_type == "o") {} //object
	else if(outjson_type == "") { //omitted
		if(gps_records.type() == 2) outjson = jsoncons::json(jsoncons::json::an_array);
	}

	else {
		std::cout << "Output type not recognized. Quitting..." << std::endl;
		exit(4);
	}

	if(gps_records.type() == 2) //array type
		for(size_t i = 0; i < gps_records.size(); ++i) {
			try {
				std::string url = R"("http://osmino.bo.infn.it/nominatim/search.php?q=)"
					+ gps_records[i]["lat"].as<std::string>()
					+ "%2C+"
					+ gps_records[i]["lon"].as<std::string>()
					+ "&format=jsonv2\"";

				std::string outname = "wget_out.json";
				std::string command = "wget --output-document=" + outname + " " + url;

				system(command.c_str());

				jsoncons::json wget_out = jsoncons::json::parse_file("wget_out.json");

				jsoncons::json ijson(gps_records[i]);
				ijson["display_name"] = wget_out[0]["display_name"].as<std::string>();

				if(outjson.is_array()) outjson.add(ijson);
				else {
					std::ostringstream ostr; ostr << "gps_record_" << std::setfill('0') << std::setw(7) << i;
					outjson[ostr.str()] = ijson;
				}
			} catch(const std::exception& e) {
				std::cerr << e.what() << std::endl;
			}
		}

	else if(gps_records.type() == 1) //object type
		for(auto rec = gps_records.begin_members(); rec != gps_records.end_members(); ++rec) {
			try {
				std::string url = R"("http://osmino.bo.infn.it/nominatim/search.php?q=)"
					+ rec->value()["lat"].as<std::string>()
					+ "%2C+"
					+ rec->value()["lon"].as<std::string>()
					+ "&format=jsonv2\"";

				std::string outname = "wget_out.json";
				std::string command = "wget --output-document=" + outname + " " + url;

				system(command.c_str());

				jsoncons::json wget_out = jsoncons::json::parse_file("wget_out.json");

				jsoncons::json ijson(rec->value());
				ijson["display_name"] = wget_out[0]["display_name"].as<std::string>();

				if(outjson.is_array()) outjson.add(ijson);
				else {
					outjson[rec->name()] = ijson;
				}
			} catch(const std::exception& e) {
				std::cerr << e.what() << std::endl;
			}
		}

	std::ofstream output_file;

	output_file.open(output_name);
	if(!output_file.is_open()) {
		std::cout << "FAILED: Output file " << output_name << " could not be opened." << std::endl;
		std::cout << "Hit ENTER to close.\n"; std::cin.get();
		exit(333);
	} else { std::cout << "SUCCESS: file " << output_name << " opened!" << std::endl; }

	output_file << jsoncons::pretty_print(outjson) << std::endl;
	output_file.close();

	return 0;
}