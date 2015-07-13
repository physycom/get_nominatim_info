/* Copyright 2015 - Marco Di Cristina, Alessandro Fabbri, Mattia Guidetti, Stefano Sinigardi */

/***************************************************************************
This file is part of json_to_html.

json_to_html is free software : you can redistribute it and / or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

json_to_html is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with json_to_html. If not, see <http://www.gnu.org/licenses/>.
***************************************************************************/

#include "jsoncons/json.hpp"

int main(int narg, char** argv) {
  std::string input_name, output_name;
  if (narg > 2){ /* Parse arguments, if there are arguments supplied */
    for (int i = 1; i < narg; i++){
      if ((argv[i][0] == '-') || (argv[i][0] == '/')){       // switches or options...
        switch (tolower(argv[i][1])){
        case 'i':
          input_name = argv[++i];
          break;
        case 'o':
          output_name = argv[++i];
          break;
        default:    // no match...
          std::cout << "Flag \"" << argv[i] << "\" not recognized. Quitting..." << std::endl;
          exit(1);
        }
      }
      else {
        std::cout << "Flag \"" << argv[i] << "\" not recognized. Quitting..." << std::endl;
        exit(11);
      }
    }
  }
  else { std::cout << "No flags specified. Read usage and relaunch properly." << std::endl; exit(111); }
		
	
	if( input_name.size() > 5 ){
    if( input_name.substr(input_name.size()-5,5)!=".json" ){
      std::cout << input_name << " is not a valid .json file. Quitting..." << std::endl;
      exit(2);
    }
  }
  else{
    std::cout << input_name << " is not a valid .json file. Quitting..." << std::endl;
    exit(22);
  }

	jsoncons::json gps_records = jsoncons::json::parse_file(input_name);

	jsoncons::json outjson(jsoncons::json::an_array);

	for (size_t i = 0; i < gps_records.size(); ++i) {
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

			outjson.add(ijson);
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
	}
	
	std::ofstream output_file;

	output_file.open(output_name);
  if (!output_file.is_open()) {
    std::cout << "FAILED: Output file " << output_name << " could not be opened." << std::endl;
    std::cout << "Hit ENTER to close.\n"; std::cin.get();
    exit(333);
  }
  else { std::cout << "SUCCESS: file " << output_name << " opened!"<< std::endl; }

	output_file << jsoncons::pretty_print(outjson) << std::endl;
	output_file.close();

	return 0;
}