#include <fstream>
#include <iostream>
#include <math.h>
#include <cstring>
using namespace std;
int main(int argc, char const *argv[])
{
	ifstream ifs;
	ofstream ofs;
	string inputFileName(argv[1]);
	string outputFileName;

	if(inputFileName.find("List") != string::npos)
	{
		 outputFileName.append( inputFileName.substr( 0,inputFileName.find("List")));
		 outputFileName.append("FinalList.txt"); 
	}
	cout<<"\nReading from "<<inputFileName<<endl;
	ifs.open(inputFileName.c_str(),ifstream::in);
	

	ofs.open(outputFileName.c_str(),ofstream::out);
	cout<<"\nWriting to "<<outputFileName<<endl;

	double recordBeg,recordEnd;

	double prevEnd = 0,prevBeg = 0;

	double duration;		//added later . Please keep in mind 
	ofs<<"thresh 0.5 sec";
	while(!ifs.eof())
	{	
		ifs>>recordBeg>>recordEnd>>duration;

		//cout<<recordBeg<<"  "<<recordEnd<<endl;

		if( (recordBeg - prevEnd) < 0.15 )
		{
			prevEnd = recordEnd;
			//cout<<"*\n";
		}
		else
		{
			if(prevEnd != 0 && (prevEnd-prevBeg)>0.5 )
			{	
				int BeginValue = (int)floor(prevBeg);
				int EndValue = (int)ceil(prevEnd); 
									
				//ofs<<prevBeg<<"\t\t\t"<<prevEnd<<endl;
				ofs<<BeginValue/60<<":"<<BeginValue%60<<"\t\t\t"<<EndValue/60<<":"<<EndValue%60<<"\t\t\t"<<duration<<endl;
				//cout<<prevBeg<<"  "<<prevEnd<<" rec written\n";
				cout<<BeginValue/60<<":"<<BeginValue%60<<"\t\t\t"<<EndValue/60<<":"<<EndValue%60<<"\t\t\t"<<duration<<endl;
			}
				prevBeg = recordBeg;	prevEnd = recordEnd;
			
		}	
	}	

	if(prevEnd != 0 || (prevEnd-prevBeg)>0.15 )
			{	
				ofs<<prevBeg<<prevEnd<<endl;
			}

	ifs.close();
	ofs.close();
	return 0;
}
