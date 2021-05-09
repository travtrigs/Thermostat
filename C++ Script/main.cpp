#include <iostream>
#include <fstream>

using namespace std;

int main()
{begin:
    
    string fileName;
    fstream dummyFile;
    
    //opens a file
    cout << "\nPlease key in file name: ";
    cin >> fileName;
    dummyFile.open(fileName.c_str());
    
    //repeats if it can't find
    if(!dummyFile.is_open())
    {
        cout << "\nFile not found. Key in file name: ";
        cin >> fileName;
        dummyFile.open(fileName.c_str());
    }
    
    string textLine;
    
    //gives tL
    float tL;
    getline(dummyFile, textLine);
    tL=stof(textLine.substr(8,13));
    cout << "\ntL is: " << tL << "\n";
    
    //gives tH
    float tH;
    getline(dummyFile, textLine);
    tH=stof(textLine.substr(8,13));
    cout << "tH is: " << tH << "\n\n";
    
    //skips the next three lines
    for(int i=0; i<3; i++) getline(dummyFile, textLine);
    
    //stores temperature, status, and time values
    int index=0;
    float temp[5000];
    bool stat[5000];
    int time[5000];
    int counter=1;
    for(int i=0; i<5000; i++)
    {
        getline(dummyFile, textLine);
        temp[i] = stof(textLine.substr(0,5));
        stat[i] = stoi(textLine.substr(15,16));
        time[i] = stoi(textLine.substr(26,31))-60000;
        if(!dummyFile.eof()) index++;
    }
    
    //offers to show data
    char noyes;
    cout << "Would you like to see the data? [N/Y]: ";
    cin >> noyes;
    while(noyes!='Y' && noyes!='N')
    {
        cout << "You must key in either N or Y\n";
        cout << "Would you like to see the data? [N/Y]: ";
        cin >> noyes;
    }
    if(noyes=='Y' )
    {
        cout << "        temp(c)      status       time(ms)\n";
        for(int i=0 ; i<=index ; i++)
        {
            cout << "Entry " << counter << ": ";
            cout << temp[i] << "          ";
            cout << stat[i] << "          ";
            cout << time[i] << "\n";
            ++counter;
        }
    }
    
    //if more than 5,000 entries, terminates
    if(!dummyFile.eof())
    {
        cout << "The data file has more than 5,000 entries!";
        cout << "Terminating...";
        exit(1);
    }
    
    //calculates first stability
    int i=0;
    int transCounter=0;
    for(; i<index; i++)
    {
        if(stat[i]==1 && stat[i+1]==0)
        {
            ++transCounter;
            if(transCounter==2)
            {
                cout << "\nThe system becomes stable at entry: ";
                cout << i << "\n";
                break;
            }
        }
    }
    
    //calculates on and off states after stability reached
    int j=i;
    double onCounter = 0;
    int offCounter = 0;
    for(; i<=index; i++)
    {
        if(stat[i]==1) ++onCounter;
        else ++offCounter;
    }
    cout << "Number of on states: " << onCounter << "\n";
    cout << "Number of off states: " << offCounter << "\n";
    
    //calculates total time on after stability reached
    double timeOn;
    double on = onCounter + offCounter;
    float percent = (onCounter)/(on);
    float timeStablems=(time[index]-time[j]);
    float timeStable=timeStablems/1000;
    timeOn=percent*timeStable;
    cout << "Total time on: " << timeOn << " seconds\n";
    
    //calculates average power after stabilty reached
    double power=(5*timeOn)/timeStable;
    cout << "Average power used: " << power << " watts\n";
    
    //calculates average temperature after stability reached
    float heat=0;
    int entries=index-j;
    for(; j < index; j++)
    {
        heat=heat+temp[j];
    }
    float avgHeat=heat/entries;
    cout << "Average temperature: " << avgHeat << " degrees celcius\n";
    
    //writes average power and temperature to a file
    dummyFile.close();
    ofstream file;
    file.open("/Users/travtrigs/Documents/MATLAB/Final Project/avg_pvt.txt",ios::app);
    string space="            ";
    file << power;
    file << space;
    file << avgHeat << "\n";
    file.close();
    dummyFile.open(fileName.c_str());
    
    //offers to proccess another file
    char yesno;
    cout << "Would you like to process another file? [Y/N]: ";
    cin >> yesno;
    while(yesno!='Y' && yesno!='N')
    {
        cout << "You must key in either Y or N\n";
        cout << "Would you like to process another file? [Y/N]: ";
        cin >> yesno;
    }
    if(yesno=='Y')
    {
        goto begin;
    }
}