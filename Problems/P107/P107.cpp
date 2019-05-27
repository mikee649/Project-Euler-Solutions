#include <iostream>
#include <fstream>
#include "Weighted_graph.h"
using namespace std;

//Michael Rokas
//May 27th 2019

int main() 
{
    int total_edge_sum;
    Weighted_graph graph(40);

    ifstream file;
    file.open("network.txt");

    char line[200];
    if (file.is_open()) {
        int row = 0;

        //This loop character by character parses the matrix and adds the graph edges to the graph object
        while (!file.eof()) {
            file >> line;

            int temp = 0;
            int col = 0;
            int i = 0;
            while(col < row && line[i] != '\0') {   //This ensures that edges are not recorded twice,
                switch(line[i]) {                   //as they will appear twice in the matrix
                    case ',':
                        if(temp != 0) {
                            graph.insert_edge(row, col, (double)temp);
                            total_edge_sum += temp;
                        }
                        col++;
                        temp = 0;
                        break;
                    case '-':
                        break;
                    default:
                        temp *= 10;
                        temp += line[i] - 48;
                        break;
                }
                i++;
            }
            if(temp != 0) {
                graph.insert_edge(row, col, (double)temp);
                total_edge_sum += temp;
            }

            row++;
        }
    }
    file.close();

    cout << total_edge_sum - graph.minimum_spanning_tree().first << endl;

    return 0;
}
