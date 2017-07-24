#include <deque>
#include <vector>

#include "bfcheck.hpp"

using std::deque;
using std::vector;

  BF_Checker::BF_Checker(vector< vector < int > > graph, 
	     vector< vector< double > > cl_constraints, 
	     vector< vector< double > > ml_constraints,
	     int k, double gamma): _graph(graph), 
	     _cl_constraints(cl_constraints), 
	     _ml_constraints(ml_constraints),
	     _k(k), _gamma(gamma) {
	       
	     _cl_sum = 0;
	     for (int i=0, sz=cl_constraints.size(); i<sz; i++)
	       _cl_sum += cl_constraints[i][2];
	     _ml_sum = 0;
	     for (int i=0, sz=ml_constraints.size(); i<sz; i++)
	       _ml_sum += ml_constraints[i][2];
	       
	       this->_feasible = false;
	       this->_first = true;
	       int n = graph.size();
	       this->bf(n, k);
  }
  
  bool BF_Checker::is_feasible(void) {
    return this->_feasible;
  }
  
  double BF_Checker::get_best(void) {
    return this->_best;
  }

  void BF_Checker::bf(int n, int k) {
    
    deque<int> s;
    vector< vector< bool > > clusters(k, vector< bool >(n));

    do {

      while(s.size() < n)
	s.push_back(0);
      
      // s is the current solution
      for(int i=0; i<k; i++)
	for (int j=0; j<n; j++)
	  if(s[j] == i) 
	    clusters[i][j] = true;
	  else 
	    clusters[i][j] = false;
	  
      bool all_connected = true;
      for (int i=0; all_connected && i<k; i++)
	all_connected &= is_connected(clusters[i]);
      
      if(all_connected) {
	double value = get_penalty(s);
	if (_first) {
	  _best = value;
	  _feasible = true;
	  _first = false;
	  update_clusters(s);
	}
	else if (value < _best) {
	  _best = value;
	  update_clusters(s);
	}
      }
      
      int t = s.back();
      s.pop_back();
      while (!s.empty() && t == k-1) {
	t = s.back();
	s.pop_back();
      }
      
      if (t<k-1)
	s.push_back(t + 1);
    } while (!s.empty());
  }

  bool BF_Checker::is_connected(const vector< bool >& cluster) {
    int n = cluster.size();
    _visited.assign(n, false);
    
    deque<int> s;
    for(int i=0; s.empty() && i<n; i++)
      if (cluster[i]) {
	s.push_back(i);
	_visited[i] = true;
       }
    
    while(!s.empty()){
      int u = s.back();
      s.pop_back();
      for (int i=0, sz=_graph[u].size(); i<sz; i++) {
        int v  = _graph[u][i];
	if (cluster[v] and !_visited[v]) {
	  s.push_back(v);
	  _visited[v] = true;
	}
      }
    }
    
    bool connected = true;
    for(int i=0; connected && i<n; i++)
      if(cluster[i] && !_visited[i])
	connected = false;
      
    return connected;
  }
  
  double BF_Checker::get_penalty(const deque<int>& clusters) {

    double cl_penalty = 0;
    for (int i=0, sz=_cl_constraints.size(); i<sz; i++) {
      int first = _cl_constraints[i][0];
      int second = _cl_constraints[i][1];
      double weight = _cl_constraints[i][2];
      if (clusters[first] == clusters[second])
	cl_penalty += weight;
    }
    
    double ml_penalty = 0;
    for (int i=0, sz=_ml_constraints.size(); i<sz; i++) {
      int first = _ml_constraints[i][0];
      int second = _ml_constraints[i][1];
      double weight = _ml_constraints[i][2];
      if (clusters[first] != clusters[second])
	ml_penalty += weight;
    }
    
    double penalty = 0;
    if (_cl_sum > 0)
      penalty += _gamma * cl_penalty / _cl_sum;
    if (_ml_sum > 0)
      penalty += (1-_gamma) * ml_penalty / _ml_sum;
      
    return  penalty;
  }
  
  void BF_Checker::update_clusters(deque< int >& clusters) {
    _clusters.assign(_k, vector< int >());
    for (int i=0; i<clusters.size(); i++)
      _clusters[clusters[i]].push_back(i);
  }
  
vector< vector< int > > BF_Checker::get_clusters(void)
{
  return _clusters;
}


  
  