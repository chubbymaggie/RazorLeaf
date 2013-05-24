#ifndef SDG_PASS_H_RAZORLEAF
#define SDG_PASS_H_RAZORLEAF

#include <llvm/Pass.h>
#include <llvm/Module.h>
#include <llvm/CallGraphSCCPass.h>
#include <llvm/ADT/DenseSet.h>
#include <llvm/ADT/DenseMap.h>
#include <llvm/Support/raw_ostream.h>

#include <utility>
#include <vector>

using namespace llvm;
using std::pair;
using std::vector;

namespace razorleaf {
  struct SDGNode;
  struct ProcEntryNode;
  class SDGPass : public ModulePass {
    public:
      typedef DenseSet<Function*> FunctionSet;
      typedef DenseMap<Function*,
              ProcEntryNode*> FunctionMap;
      typedef pair<
        Function*, 
        vector<Function*> 
      > LinkageGrammar;
      typedef vector<LinkageGrammar>
        LinkageGrammarList;

      static char ID;
      SDGPass();

      /**
       * 1.Construct the linkage grammar via cg
       * 2.Gets the functions' information
       * 3.Calculates the dependence equation
       * 4.Build the SubCGraphs 
       */
      virtual bool runOnModule(Module&);

      void getAnalysisUsage(AnalysisUsage&) const;

      virtual bool doFinalization(Module&);

    private:
      FunctionSet functionSet;
      FunctionMap functionMap;
      LinkageGrammarList linkageGrammarList;
      SDGNode *root;

      void buildSDG();

  };

} /* razorleaf */

#endif