// Demo of sending data via temporary files.  The default is to send data to gnuplot directly
// through stdin.
//
// Compile it with:
//   g++ -o example-tmpfile example-tmpfile.cc -lboost_iostreams -lboost_system -lboost_filesystem

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;


class Pitch_data
{

const char* input_file_name;
vector < pair<double,double> > pitchList;

public: 
    Pitch_data(string filenm)
    {
        input_file_name = filenm.c_str();
    }

    void create_view(const char* out_file,int t_init, int t_final)
    {
        ofstream ofs(out_file);

        for(int i = 0; i < pitchList.size() ; i++)
        {
            pair<double,double > tmp = pitchList.at(i);
            if( tmp.first > t_init && tmp.first < t_final)
            {
                ofs<<tmp.first<<"\t"<<tmp.second<<"\n";
            }  
        }

        ofs.close();
    }

    void read_pitch()
    {
        ifstream ifs(input_file_name);
        
        double time_inst=0.00,pitch_inst=0.00;
        char tmp;
        string pitch;    
        while(!ifs.eof())
        {      
            
            ifs>>time_inst;

            ifs>>tmp; 
            
            if(tmp!=',') 
                throw std::runtime_error("not proper record");

            getline(ifs,pitch);
            
            if(pitch != "--undefined--")
                pitch_inst = stod(pitch);
            else
                pitch_inst = -1.00;
                
            pitchList.push_back(make_pair(time_inst,pitch_inst));
        }
        ifs.close();
    }
};

int main(int argc, const char** argv) {

Pitch_data obj("pitch_list.txt");
obj.read_pitch();
obj.create_view("test_view.txt", stoi(argv[1]), stoi(argv[2]) );

return 0;
}