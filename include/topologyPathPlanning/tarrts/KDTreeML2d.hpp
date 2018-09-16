#ifndef TOPOLOGYPATHPLANNING_TARRTS_KDTREEML2D_HPP
#define TOPOLOGYPATHPLANNING_TARRTS_KDTREEML2D_HPP

#define KDTREE_DEFINE_OSTREAM_OPERATORS

#include <functional>
#include <iostream>
#include <vector>
#include "topologyPathPlanning/harrts/kdtree++/kdtree.hpp"

namespace topologyPathPlanning {

namespace tarrts {

  class MLRRTNode;

  class POS2D {
  public:
    typedef int value_type;

    POS2D() {
        d[0] = 0;
        d[1] = 1;
    }

    POS2D(value_type x, value_type y) {
        d[0] = x;
        d[1] = y;
    }

    POS2D(const POS2D & x) {
        d[0] = x.d[0];
        d[1] = x.d[1];
    }

    ~POS2D(){}

    double distance_to(POS2D const& x) const {
      double dist = 0;
      for (int i = 0; i != 2; ++i)
        dist += (d[i]-x.d[i])*(d[i]-x.d[i]);
      return sqrt(dist);
    }

    value_type operator[](size_t const N) { return d[N]; }

    void setX(value_type x) { d[0] = x; }
    void setY(value_type y) { d[1] = y; }

    bool operator==(const POS2D &other) const {
      return d[0] == other.d[0] && d[1] == other.d[1];
    }

    value_type d[2];
  };

  class KDNode2D : public POS2D {
  public:
    KDNode2D(value_type x, value_type y) : POS2D(x, y) { mp_pri_mlrrtnode = NULL; mp_mlrrtnodes.clear(); }
    KDNode2D(POS2D & pos) : POS2D(pos) { mp_pri_mlrrtnode = NULL; mp_mlrrtnodes.clear(); }
    void set_pri_mlrrtnode(MLRRTNode* p_node) { mp_pri_mlrrtnode = p_node; }
    MLRRTNode* get_pri_mlrrtnode() { return mp_pri_mlrrtnode; }
    void add_mlrrtnode( MLRRTNode* p_node ) { mp_mlrrtnodes.push_back( p_node ); }
    std::vector<MLRRTNode*>& get_mlrrtnodes() { return mp_mlrrtnodes; }
  protected:
    MLRRTNode*              mp_pri_mlrrtnode;
    std::vector<MLRRTNode*> mp_mlrrtnodes;
  };


  inline std::ostream& operator<<(std::ostream& out, POS2D const& T) {
    return out << '(' << T.d[0] << ',' << T.d[1] << ')';
  }


  inline std::ostream& operator<<(std::ostream& out, KDNode2D const& T) {
    return out << '(' << T.d[0] << ',' << T.d[1] << ')';
  }

  inline double tac( KDNode2D t, size_t k ) { return t[k]; }

  typedef KDTree::KDTree<2, KDNode2D, std::pointer_to_binary_function<KDNode2D,size_t,double> > KDTree2D;

} // tarrts

} // topologyPathPlanning

#endif // TOPOLOGYPATHPLANNING_TARRTS_KDTREEML2D_HPP