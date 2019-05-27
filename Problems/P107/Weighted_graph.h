
/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  mebrokas @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Fall) 2017
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include "Disjoint_sets.h"

using namespace std;

struct Adjacency_node{
    int adjacent_node;
    double weight;
    Adjacency_node* next;
};

struct Node{
    Adjacency_node* adj_list;
    int degree;
};

struct Edge{
    int a;
    int b;
    double weight;
};

class Weighted_graph {
private:
    static const double INF;
    double** graph;
    int num_nodes;
    int num_edges;

    Node* nodes;

    // Do not implement these functions!
    // By making these private and not implementing them, any attempt
    // to make copies or assignments will result in errors
    Weighted_graph( Weighted_graph const & );
    Weighted_graph &operator=( Weighted_graph );

    void selectionSort(Edge* edges[], int size) const;
    void merge(Edge* edges[], int start, int end) const;
    void merge_sort(Edge* edges[], int start, int end) const;

    // your choice

public:
    Weighted_graph( int = 50 );
    ~Weighted_graph();

    int degree( int ) const;
    int edge_count() const;
    std::pair<double, int> minimum_spanning_tree() const;

    bool insert_edge( int, int, double );
    bool erase_edge( int, int );
    void clear_edges();

    void print();

    // Friends

    friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

Weighted_graph::Weighted_graph(int n ) {
    nodes = new Node[n];

    for(int i = 0; i < n; i++){
        nodes[i].degree = 0;
        nodes[i].adj_list = nullptr;
    }

    num_nodes = n;
    num_edges = 0;
}

Weighted_graph::~Weighted_graph() {
    clear_edges();
    delete[] nodes;
}

int Weighted_graph::degree(int u) const {
    return nodes[u].degree;
}

int Weighted_graph::edge_count() const {
    return num_edges;
}

bool Weighted_graph::erase_edge(int i, int j) {
    if(i == j)
        return true;

    Adjacency_node* traverse = nodes[i].adj_list;
    Adjacency_node* previous = nullptr;

    while(traverse != nullptr && traverse->adjacent_node != j){
        previous = traverse;
        traverse = traverse->next;
    }

    if(traverse == nullptr)
        return false;
    else if(previous == nullptr){
        nodes[i].adj_list = traverse->next;
        delete traverse;
    }
    else{
        previous->next = traverse->next;
        delete traverse;
    }
    nodes[i].degree--;

    traverse = nodes[j].adj_list;
    previous = nullptr;

    while(traverse != nullptr && traverse->adjacent_node != i){
        previous = traverse;
        traverse = traverse->next;
    }

    if(previous == nullptr){
        nodes[j].adj_list = traverse->next;
        delete traverse;
    }
    else{
        previous->next = traverse->next;
        delete traverse;
    }
    nodes[j].degree--;

    num_edges--;
    return true;
}

void Weighted_graph::clear_edges() {
    num_edges = 0;

    for(int i = 0; i < num_nodes; i++){
        nodes[i].degree = 0;

        Adjacency_node* traverse = nodes[i].adj_list;
        Adjacency_node* previous = nullptr;

        while(traverse != nullptr){
            delete previous;
            previous = traverse;
            traverse = traverse->next;
        }
        delete previous;

        nodes[i].adj_list = nullptr;
    }

    return;
}

bool Weighted_graph::insert_edge( int i, int j, double d ) {
    if(i == j)
        return false;

    if(nodes[i].adj_list == nullptr){
        Adjacency_node* temp = new Adjacency_node;

        temp->next = nullptr;
        temp->adjacent_node = j;
        temp->weight = d;

        nodes[i].adj_list = temp;
        nodes[i].degree++;
        num_edges++;
    }
    else{
        Adjacency_node* traverse = nodes[i].adj_list;
        Adjacency_node* previous;

        while(traverse != nullptr && traverse->adjacent_node != j) {
            previous = traverse;
            traverse = traverse->next;
        }

        if(traverse == nullptr) {
            Adjacency_node* temp = new Adjacency_node;

            temp->next = nullptr;
            temp->adjacent_node = j;
            temp->weight = d;

            previous->next = temp;
            nodes[i].degree++;
            num_edges++;
        }
        else
            traverse->weight = d;
    }

    if(nodes[j].adj_list == nullptr){
        Adjacency_node* temp = new Adjacency_node;

        temp->next = nullptr;
        temp->adjacent_node = i;
        temp->weight = d;

        nodes[j].adj_list = temp;
        nodes[j].degree++;
    }
    else{
        Adjacency_node* traverse = nodes[j].adj_list;
        Adjacency_node* previous;

        while(traverse != nullptr && traverse->adjacent_node != i) {
            previous = traverse;
            traverse = traverse->next;
        }

        if(traverse == nullptr) {
            Adjacency_node* temp = new Adjacency_node;

            temp->next = nullptr;
            temp->adjacent_node = i;
            temp->weight = d;

            previous->next = temp;
            nodes[j].degree++;
        }
        else
            traverse->weight = d;
    }

    return true;
}

void Weighted_graph::merge(Edge* edges[], int start, int end) const{
    int mid = start+(end-start)/2;

    Edge** left = new Edge*[mid-start+1];
    Edge** right  = new Edge*[end-mid];

    for(int i = 0; i < mid-start+1; i++)
        left[i] = edges[start+i];
    for(int i = 0; i < end-mid; i++)
        right[i] = edges[mid+1+i];

    int i = 0;
    int j = 0;
    int count = 0;

    while(count < end-start+1 ){
        if(j >= end-mid || (i < mid-start+1 && left[i]->weight < right[j]->weight))
            edges[start+count] = left[i++];
        else
            edges[start+count] = right[j++];
        count++;
    }

    delete[] left;
    delete[] right;
}

void Weighted_graph::merge_sort(Edge* edges[], int start, int end) const{
    if(start >= end)
        return;

    int mid = start + (end-start)/2;

    merge_sort(edges, start, mid);
    merge_sort(edges, mid+1, end);
    merge(edges, start, end);
}

std::pair<double, int> Weighted_graph::minimum_spanning_tree() const {
    Edge** edges = new Edge*[num_edges];
    int counter = 0;

    for(int i = 0; i < num_nodes; i++){
        Adjacency_node* traverse = nodes[i].adj_list;
        while(traverse != nullptr){
            if(traverse->adjacent_node < i){
                edges[counter] = new Edge;
                edges[counter]->a = i;
                edges[counter]->b = traverse->adjacent_node;
                edges[counter]->weight = traverse->weight;
                counter++;
            }
            traverse = traverse->next;
        }
    }

    merge_sort(edges, 0, num_edges-1);

    Disjoint_set s (num_nodes);

    int tree_edges = 0;
    int edges_checked = 0;
    double weight = 0;

    while(tree_edges < num_nodes-1 && edges_checked < num_edges){
        if(s.find_set(edges[edges_checked]->a) != s.find_set(edges[edges_checked]->b)){
            s.union_sets(edges[edges_checked]->a, edges[edges_checked]->b);
            weight += edges[edges_checked]->weight;
            tree_edges++;
        }
        edges_checked++;
    }

    for(int i = 0; i < num_edges; i++){
        delete edges[i];
    }

    delete[] edges;

    return std::pair<double, int>(weight,edges_checked);
}

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
    return out;
}

void Weighted_graph::print(){
    for(int i = 0; i < num_nodes; i++) {
        std::cout << i << "-degree:" << nodes[i].degree << "-adjacent nodes";
        Adjacency_node *traverse = nodes[i].adj_list;
        while (traverse != nullptr) {
            std::cout << ":" << "(" << traverse->adjacent_node << "," << traverse->weight << ")";
            traverse = traverse->next;
        }
        std::cout << endl;
    }
}

#endif