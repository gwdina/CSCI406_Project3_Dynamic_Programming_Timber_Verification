#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string>
#include <iostream>
#include <random>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <iomanip>
#include <utility>


using namespace std;

int length;
int numbers;
vector<int> Log;

// opens the text file containing the number of nodes and coordinates and stores them 
void inputFile(string file_name){
    ifstream file;
    file.open(file_name);
    
    file >> length;

    for(int i=0;i < length; ++i){
        file >> numbers;
        Log.push_back(numbers);
    }

}


vector<vector<int>> table; //DP Table 



// fills in our table with the base cases and initializes the vectors for future use
void base_cases(int n){
    

    for(int l=0;l<n;++l){
        vector<int> inital;
        for(int k=0;k<n;++k){
        inital.push_back(0);
        }
        table.push_back(inital);
    }

    // if i = j
    for(int i=0;i< n; ++i){
        table[i][i] = Log[i];
    }

    // if i+1 = j
    for(int j=0;j<n;++j){
        int next = j+1;

        if(next == n){
            break;
        }
        table[j][next]=max(table[j][j],table[next][next]);
    }

}

//grabs the maximum sum of lengths that you can take
int DP_Log_Length(int i, int j){

    if (i > j){return 0;}

    if(table[i][j] != 0){return table[i][j];} 

    // left side of the tree
    int left = Log[i] + min(DP_Log_Length(i+2,j),DP_Log_Length(i+1,j-1));

    // right side of the tree
    int right = Log[j] + min(DP_Log_Length(i+1,j-1),DP_Log_Length(i,j-2));


    if (left == right){
        table[i][j] = left;
    }



    else{table[i][j] = max(left,right);}
    


    return table[i][j];
}


vector<int> order;
// the order in which the points are taken
void traceback(int i, int j){

    while (i != j){
    int ll = 0;
    int mid = 0;
    int rr = 0;
    
    if(i+2 >= table.size()){}
    else{
        ll = table[i+2][j];
        if(ll==0){ll = DP_Log_Length(i+2,j);}
    }

    mid = table[i+1][j-1];
    if(mid==0){mid = DP_Log_Length(i+1,j-1);}


    if(j-2 <= 0){}
    else{
        rr = table[i][j-2];
        if(rr==0){rr = DP_Log_Length(i,j-2);}
    }
    


    int left = Log[i] + min(ll,mid);
    int right = Log[j] + min(mid,rr);

    table[i][j] = max(left,right);

    if (left >= right){
        order.push_back(i);
        ++i;
    }
    else{
        order.push_back(j);
        --j;
    }

    }
    order.push_back(i);
}

int main(int argc, char* argv[]) {


    //inputFile("DP.txt");
    inputFile(argv[1]);

    // for(int i=0;i < length; ++i){
    //     cout << Log[i] << " ";
    // }

    base_cases(length);

     cout << DP_Log_Length(0, length-1);
    //inputFile(argv[1]);



    traceback(0,length-1);

    cout << endl;

    // for(int i = 0; i < table.size(); ++i){
    //     cout << i << ": ";
    //     for(int j = 0; j < table[i].size(); ++j){
    //         cout <<  table[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    for(int k = 0; k < order.size(); ++k){
        cout << order[k] + 1 << " ";

    }


}