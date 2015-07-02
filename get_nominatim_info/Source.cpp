#include "jsoncons/json.hpp"

int main() {

	jsoncons::json gps_records = jsoncons::json::parse_file("records.json");

	jsoncons::json outjson(jsoncons::json::an_array);

	for (size_t i = 0; i < gps_records.size(); ++i) {
		try {
			std::string url = R"("http://osmino.bo.infn.it/nominatim/search.php?q=)"
				+ gps_records[i]["lat"].as<std::string>()
				+ "%2C+"
				+ gps_records[i]["lon"].as<std::string>()
				+ "&format=jsonv2";
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
	
	std::ofstream outfile("output.json");
	outfile << jsoncons::pretty_print(outjson) << std::endl;
	outfile.close();

	return 0;
}