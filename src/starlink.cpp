#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std; 
#include <nlohmann/json.hpp>
using json = nlohmann::json;

// SpaceX Starlink V4.0

struct Sat_info {
    string sat_id;
    string version;
    string sat_name;
    string launch_date;
    double velocity;
    double longitude;
    double latitude;
    double height;
} starlink1;

void api_request(string satellite_id) {
	
  	string merge = "curl https://api.spacexdata.com/v4/starlink/" + satellite_id + " >> starlink.json";
	// line above redirects and stores system command into the starlink.json file

	system(merge.c_str());// c_str converts the string into an array of characters
	//basic linux command will return the get command for a single satellite
}

void reading_json(string file_name) {
	std::ifstream f(file_name);
	json data = json::parse(f);
	
	string sat_id1 = data["id"].dump();
	starlink1.sat_id = sat_id1;
	
	string version1 = data["version"].dump();
	starlink1.version = version1;
	
	string sat_name1 = data["spaceTrack"]["OBJECT_NAME"].dump();
	starlink1.sat_name = sat_name1;
	
	string launch_date1 = data["spaceTrack"]["LAUNCH_DATE"].dump();
	starlink1.launch_date = launch_date1;
	
	starlink1.velocity = data["velocity_kms"];
	starlink1.longitude = data["longitude"];
	starlink1.latitude = data["latitude"];
	starlink1.height = data["height_km"];
	
}

int main() {
	string satellite_id;
	cout << "Please type the Spacex Satellite Id Below\n";
	cin >> satellite_id; // input statement 628ea116a8973c1694df189b
	
	std::ofstream ofs;
	ofs.open("starlink.json", std::ofstream::out | std::ofstream::trunc); // clears the json file for new data
	ofs.close();
	
	api_request(satellite_id); //function that takes api request
	
	reading_json("starlink.json");
	cout << "Satellite Id: "<< starlink1.sat_id << endl;
	cout << "Version: "<< starlink1.version << endl;
	cout << "Satellite Name: "<< starlink1.sat_name << endl;
	cout << "Launch Date: "<< starlink1.launch_date << endl;
	cout << "Velocity: "<< starlink1.velocity << endl;
	cout << "Longitude: "<< starlink1.longitude << endl;
	cout << "Latitude: "<< starlink1.latitude << endl;
	cout << "Height: "<< starlink1.height << endl;

}

