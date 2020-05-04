#include "Node.h"

int Node::node_count = 0;

/*! sets accept and final to false */
Node::Node() {

	accept = false; /* final status */
	initial = false; /* start status */

	// stuff below just relates to make displays
	// and can be ignored
	node_count++;

	// uses a fail-safe way to convert anything cout-able to string
	// ostringstream ss;
        // ss << node_count;
        // identifier = ss.str();

	// uses 'recent' library function convert numbers to stringd
	identifier = to_string(node_count);

}

/*! \param label is a label on an arc 
 *  \return either node ptr that matches with l or NULL
 */
NodePtr Node::match(string label) {
  NodePtr n;
  Arc arc;
  n = NULL;
  
  for(int i=0; i<arcs.size(); i++) {
    arc = arcs[i];
    if (arc.label == label) {
      n = arc.next;
      break;
    }
  }
  return n;

}

/*! adds a pair (label,n) to the arcs of the node
 *  where n is newly allocated Node object
 */
NodePtr Node::update(string label) {

  NodePtr n2;

  n2 = new Node;
  Arc p;
  p.label = label;
  p.next = n2;
  arcs.push_back(p);

  return n2;
}

/*! displays information about the node
 *  and recursively invokes show on all the destination nodes
 */
void Node::show() {
  cout << identifier << " accept:" << accept << " initial:" << initial << endl;
  for(int i = 0; i < arcs.size();  i++) {
    cout << identifier << " -- " << arcs[i].label << " --> ";
    cout << arcs[i].next->identifier << endl;
  }

  for(int j = 0; j < arcs.size(); j++) {
    arcs[j].next->show();
  }

}

/*! sends lines to a file stream in the notation understood
 *  by the dot program as part of generationg a postscript 
 *  picture of the network 
 */
void Node::show(ostream& f) {
  f << identifier << " ";
  if (accept) { f << "[color=red];" << endl;}
  if (initial) { f << "[color=green];" << endl;}
  //f << identifier << " [label=\"" << identifier << " " << ios::hex << this << "\"];" << endl;
  for(int i = 0; i < arcs.size();  i++) {
    f << identifier << " -> " << arcs[i].next->identifier << " ";
    f << "[label = \""; f << arcs[i].label; f << "\"];"; f << endl;
  }
  for(int j = 0; j < arcs.size(); j++) {
    arcs[j].next->show(f);
  }

}



