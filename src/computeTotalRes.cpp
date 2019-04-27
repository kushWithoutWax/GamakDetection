#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    string label;
    ifstream ifs("result");
    int tp=0,fp=0,tn=0,fn=0;
    int totalSample=0;
    while(!ifs.eof())
    {    
        int a1,b1,a2,b2;
        ifs.ignore();
        getline(ifs,label);
        ifs>>a1>>b1>>a2>>b2;
        tp+=a1;
        fp+=b1;
        tn+=a2;
        fn+=b2;
    }
    cout<<"\n\nTotal gamak = "<<tp+fn<<"\nTotal samples "<<tp+fn+tn+fp<<endl;
    cout<<"\n\n truePositive = "<<tp*100.0/(tp+fn)<<"\n\n falsePositive = "<<fp*100.0/(tn+fp)<<"\n\n trueNegative = "<<tn*100.0/(tn+fp)<<"\n\n falseNegative = "<<fn*100.0/(tp+fn)<<endl;
    
    double prec = tp*100.0/(tp+fp) , rec = tp*100.0/(tp+fn);
    cout<<"\n\n precision = "<<prec<<"\n\n recall ="<<rec<<endl;
    cout<<"\n\n fmeasure = "<<(2*prec*rec)/(prec+rec)<<endl;
    
    return 0;
}