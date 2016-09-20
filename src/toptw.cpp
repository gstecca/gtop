#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include "Node.h"

using namespace std;

struct coord {
  float x;
  float y;
};


int load_data(vector<int> * profits, vector<coord>* coords, int* n, int* m, float* tau, string filename );

int main(){
  int n, m = 0;
  float tau = .0;
  vector<int> profits;
  vector<coord> coords;
  vector<Node> nodes;

  load_data(&profits, &coords, &n, &m, &tau, "p4.2.a.txt");

  float t[n][n];
  for(int r=0; r<n; r++){
    for (int c=0; c<n; c++){
      t[r][c] = sqrt(pow(coords[r].x - coords[c].x, 2) + pow(coords[r].y - coords[c].y, 2));
    }
    Node aNode(r);
    //aNode.id = r;
    nodes.push_back(aNode);

  }
  for(Node n : nodes)
    cout << n.id << "\n";
}


int load_data(vector<int> * profits, vector<coord>* coords, int* n, int* m, float*tau, string filename ){
     ifstream myfile(filename);

  string line;
  if(myfile){
    getline(myfile, line);
    string ns = line.substr(2, sizeof(line)-2);
    *n = std::stoi(ns);
    getline(myfile, line);
    string ms = line.substr(2, sizeof(line)-2);
    *m = stoi(ms);
    getline(myfile, line);
    string ts = line.substr(5, sizeof(line)-5);
    *tau = stof(ts);
    cout << "n: " << *n << endl;
    cout << "m: " << *m << endl;
    cout << "tau: " << *tau << endl;
    string delimiter = "\t";
    string token;
    int i = 0;
    while(getline(myfile, line)){
      coord* c = new coord();
      int startsub = 0;
      size_t pos = line.find(delimiter);
      // x coord
      token = line.substr(startsub, pos);
      //coords[i][0] = stof(token);
      c->x = stof(token);

      //cout << "x coord: " << token << endl;
      // y coord
      startsub = pos+1;
      pos = line.find(delimiter, startsub);
      token = line.substr(startsub, pos-startsub);
      //coords[i][1] = stof(token);
      c->y = stof(token);
      //cout << "y coord: " << token << endl;
      // profit
      startsub = pos;
      token = line.substr(pos+1, sizeof(line)- pos+1);
      //profits[i] = stoi(token);
      profits->push_back(stoi(token));
      coords->push_back(*c);
      //i++;

    }

  }
  else cout << "error opening file\n";

  return 0;

}
