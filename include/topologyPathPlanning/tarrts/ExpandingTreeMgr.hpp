#ifndef TOPOLOGYPATHPLANNING_TARRTS_EXPANDINGTREEMGR_HPP
#define TOPOLOGYPATHPLANNING_TARRTS_EXPANDINGTREEMGR_HPP

#include <vector>
#include "topologyPathPlanning/homotopy/ReferenceFrames.hpp"
#include "topologyPathPlanning/tarrts/KDTreeML2d.hpp"
#include "topologyPathPlanning/tarrts/ExpandingTree.hpp"

namespace topologyPathPlanning {

namespace tarrts {


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
  
  class ExpandingTreeMgr {
  public:
    ExpandingTreeMgr();
    virtual ~ExpandingTreeMgr();

    void init( homotopy::StringGrammar* p_grammar, homotopy::ReferenceFrameSet* p_reference_frame_set );
    
    SubRegionMgr* find_subregion_mgr( homotopy::SubRegion* p_subregion );
    LineSubSegmentMgr* find_line_subsegment_mgr( homotopy::LineSubSegment* p_line_subsegment );
    std::vector<StringClass*>& get_string_classes() { return mp_string_classes; };
    ExpandingTree* get_expanding_tree() { return mp_expanding_tree; };
    
    void export_subregion_mgrs( std::string filename );

    void dump_historical_data( std::string filename );
    void record();

  protected:
    ExpandingTree*                  mp_expanding_tree;
    homotopy::StringGrammar*        mp_string_grammar;
    std::vector<StringClass*>       mp_string_classes;
    std::vector<SubRegionMgr*>      mp_subregion_mgrs;
    std::vector<LineSubSegmentMgr*> mp_line_subsegment_mgrs; 
  };

} // tarrts

} // topologyPathPlanning

#endif // TOPOLOGYPATHPLANNING_TARRTS_EXPANDINGTREEMGR_HPP