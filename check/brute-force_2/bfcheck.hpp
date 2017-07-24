#ifndef _BFCHECK_HPP
#define _BFCHECK_HPP

#include <deque>
#include <vector>

using std::deque;
using std::vector;

class BF_Checker {
  
public:
  BF_Checker(vector< vector < int > > graph, 
	     vector< vector< double > > cl_constraints,
	     vector< vector< double > > ml_constraints,
	     int k, double gamma);
  bool is_feasible(void);
  double get_best(void);
  vector< vector< int > > get_clusters(void);
  
private:
    
  vector< vector< int > > _graph;
  vector< vector< double > > _cl_constraints;
  vector< vector< double > > _ml_constraints;
  vector< bool > _visited;
  vector< vector< int > > _clusters;
  int _k;
  double _gamma;
  double _cl_sum;
  double _ml_sum;
  bool _feasible;
  double _best;
  bool _first;
  
  void bf(int n, int k);
  bool is_connected(const vector< bool >& cluster);
  double get_penalty(const deque< int >& clusters);
  void update_clusters(deque< int >& clusters);

};

#endif //_BFCHECK_HPP