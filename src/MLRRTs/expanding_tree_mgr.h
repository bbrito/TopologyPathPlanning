#ifndef EXPANDING_TREE_MGR_H_
#define EXPANDING_TREE_MGR_H_

#include <vector>
#include "expanding_tree.h"
#include "worldmap.h"

namespace mlrrts {

  class Path;

  class SubRegionMgr {
  public:
    SubRegionMgr( homotopy::SubRegion* p_subregion );
    virtual ~SubRegionMgr();

    void add_node( ExpandingNode* p_node );
    ExpandingNode* find_node( std::string name);

    homotopy::SubRegion*        mp_subregion;
    std::vector<ExpandingNode*> mp_nodes;
  };

  class LineSubSegmentMgr{
  public:
    LineSubSegmentMgr( homotopy::LineSubSegment* p_line_subsegment );
    virtual ~LineSubSegmentMgr();

    void add_edge( ExpandingEdge* p_edge );
    ExpandingEdge* find_edge( std::string name);

    homotopy::LineSubSegment*   mp_line_subsegment;
    std::vector<ExpandingEdge*> mp_edges;
  };
  
  class StringClass {
  public:
    StringClass( std::vector< std::string > string );
    virtual ~StringClass();
    std::string get_name();
  
    std::vector< std::string > m_string;
    double m_cost;
    Path*  mp_path;  
  };

  class ExpandingTreeMgr {
  public:
    ExpandingTreeMgr();
    virtual ~ExpandingTreeMgr();

    void init( homotopy::StringGrammar* p_grammar, homotopy::WorldMap* p_worldmap );
    
    SubRegionMgr* find_subregion_mgr( homotopy::SubRegion* p_subregion );
    LineSubSegmentMgr* find_line_subsegment_mgr( homotopy::LineSubSegment* p_line_subsegment );
    std::vector<StringClass*>& get_string_classes() { return mp_string_classes; };


    ExpandingTree*                  mp_expanding_tree;
    homotopy::StringGrammar*        mp_string_grammar;
    std::vector<StringClass*>       mp_string_classes;
    std::vector<SubRegionMgr*>      mp_subregion_mgrs;
    std::vector<LineSubSegmentMgr*> mp_line_subsegment_mgrs; 
  };

}

#endif /* EXPANDING_TREE_MGR_H_ */
