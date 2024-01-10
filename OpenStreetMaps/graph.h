

#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
#include <set>
#include <map>

using namespace std;

template<typename VertexT, typename WeightT>
class graph {
 private:
  map<VertexT, map<VertexT, WeightT>> adjacencyList;

  //This function finds if the index is found in the adjacencyList, if not found returns -1, if found returns 1
  int _LookupVertex(VertexT v) const {
    //searches for the value in the map
    if (adjacencyList.find(v) == adjacencyList.end()) {
        return -1;
    } else {
        return 1;
    }
}


 public:
  //
  // constructor:
  //
  // Constructs an empty graph where n is the max # of vertices
  // you expect the graph to contain.
  //
  // NOTE: the graph is implemented using an adjacency matrix.
  // If n exceeds the dimensions of this matrix, an exception
  // will be thrown to let you know that this implementation
  // will not suffice.
  //
  graph() {  // default constructor
    return;
  }

  //
  // NumVertices
  //
  // Returns the # of vertices currently in the graph.
  //
  int NumVertices() const {
    return adjacencyList.size();
  }

  //
  // NumEdges
  //
  // Returns the # of edges currently in the graph.
  //
  int NumEdges() const {
    int count = 0;
    //
    // loop through the adjacency list and count how many
    // edges currently exist:
    //
    for (auto &vertex : adjacencyList) {
      count += vertex.second.size();
    }
    return count;
  }

  //
  // addVertex
  //
  // Adds the vertex v to the graph if there's room, and if so
  // returns true.  If the graph is full, or the vertex already
  // exists in the graph, then false is returned.
  //
  bool addVertex(VertexT v) {
    //
    // is the vertex already in the graph?  If so, we do not
    // insert again otherwise Vertices may fill with duplicates:
    //
    if (_LookupVertex(v) > 0) {
      return false;
    }

    //
    // if we get here, vertex does not exist so insert.
    //
    adjacencyList[v];
    return true;
  }

  //
  // addEdge
  //
  // Adds the edge (from, to, weight) to the graph, and returns
  // true.  If the vertices do not exist or for some reason the
  // graph is full, false is returned.
  //
  // NOTE: if the edge already exists, the existing edge weight
  // is overwritten with the new edge weight.
  //
    bool addEdge(VertexT from, VertexT to, WeightT weight) {
    //
    // we need to search the Vertices and find the position
    // of each vertex
    //
   if (_LookupVertex(from) < 0 || _LookupVertex(to) < 0) {
    return false;
}

    //
    // the vertices exist, so insert / update the edge:
    //
    adjacencyList[from][to] = weight; 
    return true;
  }
    

  //
  // getWeight
  //
  // Returns the weight associated with a given edge.  If
  // the edge exists, the weight is returned via the reference
  // parameter and true is returned.  If the edge does not
  // exist, the weight parameter is unchanged and false is
  // returned.
  //
   bool getWeight(VertexT from, VertexT to, WeightT& weight) const {
    auto it1 = this->adjacencyList.find(from);

    if (it1 == this->adjacencyList.end()) {  // not found:
        return false;
    }

    auto& e = it1->second;

    auto it2 = e.find(to);

    if (it2 == e.end()) {  // not found:
        return false;
    }

    weight = it2->second;

    return true;
}


  //
  // neighbors
  //
  // Returns a set containing the neighbors of v, i.e. all
  // vertices that can be reached from v along one edge.
  // Since a set is returned, the neighbors are returned in
  // sorted order; use foreach to iterate through the set.
  //
  set<VertexT> neighbors(VertexT v) const {
    //
    // we need to search the Vertices and find the position
    // of v, that will be the row we need in the adjacency
    // map:
    //
    set<VertexT> S;

    if (_LookupVertex(v) == -1) { //only returns if the vertext does not exist
      return S;
    }

    //If the vertex is found return the sets conatinaing the adjacent nodes
    for (auto &e : adjacencyList.at(v)) {
      S.insert(e.first);
    }
    return S;
  }

  //
  // getVertices
  //
  // Returns a vector containing all the vertices currently in
  // the graph.
  //
  vector<VertexT> getVertices() const {
    vector<VertexT> V;
    for (auto &v : adjacencyList) {
      V.push_back(v.first);
    }
    return V;  
  }

  //
  // dump
  //
  // Dumps the internal state of the graph for debugging purposes.
  //
  // Example:
  //    graph<string,int>  G(26);
  //    ...
  //    G.dump(cout);  // dump to console
  //
  void dump(ostream& output) const {
    output << "***************************************************" << endl;
    output << "********************* GRAPH ***********************" << endl;

    output << "**Num vertices: " << this->NumVertices() << endl;
    output << "**Num edges: " << this->NumEdges() << endl;

    output << endl;
    output << "**Vertices:" << endl;
    int count = 0;
    for (auto &v : adjacencyList) {
      output << " " << count << ". " << v.first << endl;
      count++;
    }

    output << endl;
    output << "**Edges:" << endl;
    for (auto &v : adjacencyList) {
      for (auto &e : v.second) {
        output << " (" << v.first << "," <<
          e.first << "," << e.second << ")";
      }
      output << endl;
    }
    output << "**************************************************" << endl;
  }
};