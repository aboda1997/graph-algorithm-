#include<iostream>
#include<vector>
#include<time.h>
using namespace std ;


const long  INT_MAX = 20000000 ;

float  prob(){

return (float) rand()/RAND_MAX  ;
}
inline int getnumber (int h  ){ return (rand() % h + 1); }

struct node {
    /*  represent node in graph
     that have value and index
     also have queue index that help me in priority queue  class heap
     to make min heap */
node():value (INT_MAX), index( 10 ) , queue_indx(-1){}
node(int index): queue_indx(-1), value(INT_MAX), index(index ){}

int index ;
int value ;
int queue_indx ;
};

struct edge{
    /* represent edge in graph
     that have node x ,y and  positive weight
    and bool t to check connection between  two nodes in graph */
edge(): x(0) , y(0) , w(0) ,t(false) {}
edge(node *x , node *y , int w): x(x) , y(y) , w(w), t{t}{}
node* x ;
node*y;
int w ;
bool t ;

};
class pq{

private:
    vector<node*> q ;
    int parent(int i ){
    return (i-1 )/2 ;
    }
    int left_(int i ){
    return  (2*i +1 ) ;

    }
    int right_(int i ){
    return  (2*i + 2);
    }
    void heapify_down(int i)
	{
		// get left and right child of node at index i
		int left = left_(i);
		int right = right_(i);

		int smallest = i;

		// compare A[i] with its left and right child
		// and find largest value
		if (left < size() && q[left]->value <q[i]->value)
			smallest = left;

		if (right < size() && q[right]->value < q[smallest]->value)
			smallest = right;

		// swap with child having greater value and
		// call heapify-down on the child
		if (smallest != i) {
                q[i]->queue_indx = smallest;
		    q[smallest]->queue_indx = i ;
			swap(q[i], q[smallest]);
			heapify_down(smallest);
		}
	}
	void heapify_up(int i)
	{



		// check if node at index i and its parent violates
		// the heap property
		if (i && q[parent(i)]->value > q[i]->value)
		{
		    q[i]->queue_indx = parent(i);
		    q[parent(i)]->queue_indx = i ;

			// swap the two if heap property is violated
			swap(q[i], q[parent(i)]);


			// call Heapify-up on the parent
			heapify_up(parent(i));
		}
	}





public:
    pq( ){}
    void add_with_priority( node*x );
    void decrease_priority( node*x  ,   int v) ;
    node* extract_min() ;
    int size() ;
    void print() ;



};
int  pq::size(){
return  q.size() ;
}

void pq::add_with_priority(node*x){
    q.push_back(  x ) ;
    int index  =  size() -1 ;
    //cout<< index<< "\n" ;
    x->queue_indx = index ;
    heapify_up(index );




}

void pq::decrease_priority(node*x ,  int v) {
    x->value = v ;
    int index  = x->queue_indx ;

        heapify_up(index );
        heapify_down(index );



}

node* pq::extract_min(){
node *s =  q.at(0) ;
q[0] = q.back();
q.pop_back();
heapify_up(1);

heapify_down(0) ;
return  s ;


}
void pq::print(){
for(node* i : q){
    cout<<i->value  << ","<< i->queue_indx<<endl ;
}
}
class graph {
    // build graph
private :
    int size_{0};
    edge**adj_matrix  ;

public:
    graph(int size_):size_(size_) {
     adj_matrix = new edge*[size_];

 for(int i = 0 ;i<size_; ++i){
    adj_matrix[i] = new edge[size_];



 }
 for(int i=0 ; i<size_; i++){
    for(int j=0; j<size_; j++){
            adj_matrix[i][j] = edge();
        }
    }

    }

    void add_edge(int x , int y , int w ) ;
    void rempve_edg(int x, int y ) ;
    bool adjacent ( int x, int y) ;
    vector<node*> neighbors( node*  x );
    int get_node_value ( node* x);
    node*get_node(int x);
    void set_node_value( node* x, int a);
    int get_edge_value(  node* x, node* y);
    void set_edge_value ( int x, int y, int v);
    int get_size();
    vector<node*> nodes();





};



void graph::add_edge(int x, int y , int w){
    if ( adj_matrix[x][x].x == nullptr)
        {adj_matrix[x][x].x = adj_matrix[x][x].y =  new node (x);}
    if ( adj_matrix[y][y].x == nullptr)
    {adj_matrix[y][y].x = adj_matrix[y][y].y =  new node (y);}
    adj_matrix[x][y].t = adj_matrix[y][x].t = true;
    adj_matrix[x][y].x = adj_matrix[y][x].y  = adj_matrix[x][x].x ;
    adj_matrix[x][y].y = adj_matrix[y][x].x = adj_matrix[y][y].x ;
    adj_matrix[x][y].w = adj_matrix[y][x].w = w ;





}
void graph::rempve_edg(int x , int y){
    adj_matrix[x][y].t =   adj_matrix[y][x].t  = false ;
    adj_matrix[x][y].w =  adj_matrix[y][x].w =  0 ;
    adj_matrix[y][x].x = adj_matrix[x][y].y = 0 ;
    adj_matrix[y][x].y = adj_matrix[x][y].x  =0;




}
bool graph::adjacent(int x , int y){
    //  check connection between two nodes in graph
    return(adj_matrix[x][y].t == true) ;



}
int graph::get_node_value(node* k ){
    // return node value
  int x  = k->index;
return (adj_matrix[x][x].x->value);
}
void graph::set_node_value(node* k , int a ){
    int x  = k->index;

adj_matrix[x][x].x->value = adj_matrix[x][x].y->value = a ;
}
int graph::get_edge_value(node *k  , node*l ){
    // return  edge weight
    int x  = k->index ;
    int y =  l->index ;
     return(adj_matrix[x][y].w);

}
void graph::set_edge_value(int x ,int y, int v){

adj_matrix[x][y].w = adj_matrix[y][x].w = v ;
}

vector<node*>graph:: neighbors(node* x  ){
    // get neighbors nodes  of node in graph
         int q  = x->index ;
         vector<node*> adj ;
         int j =0 ;
for(int i=0; i< get_size(); i++){


      if(adjacent(q,i)){

    adj.push_back(adj_matrix[i][i].x);

      }


}
return adj  ;
}
int graph::get_size(){
return size_;
}
vector<node*> graph::nodes(){
    /// check the graph is all connect and return  all nodes
    /// or return  empty vector that graph not connected
    int r  =  get_size();
vector<node*> nodes = {};
vector<node*> help = {};

for(int i = 0 ; i<r; i++){
        node*f = adj_matrix[i][i].x ;
if (f== nullptr){
    return help ;

}
else{
    nodes.push_back(f);
    }
}
return nodes ;
}

node*graph::get_node(int s ){

return adj_matrix[s][s].x;
}






void  digikstra(graph g ,  node* s){
pq set_;
vector<node*> f = g.nodes();
if (f.size() == 0){
    cout<< "graph is not connected "<<"\n"  ;
    return  ;
}
for(auto i : f ){
        // add node to priority queue to built min heap
set_.add_with_priority(i);


}
set_.decrease_priority( s , 0 );
while(set_.size() != 0){
   node *u = set_.extract_min();

   for (node* i: g.neighbors(u)){
       // relaxation  on  nodes value in graph
       // and return  shortest path  from  source node
       if (i->value > u->value + g.get_edge_value(u ,  i)){
        set_.decrease_priority(i ,  u->value + g.get_edge_value(u ,  i)) ;

       }


}


}
vector<node*> o = g.nodes();
cout<< "node " << "   " << "distance from source: "<<endl ;
int sum  = 0;
int avg = 0;
for(node* i : o){
        avg+= i->value ;
    cout<< i->index << "         "<<i->value << endl ;
}
cout<< endl ;
cout << "The  average shortest path is    " << avg / o.size() << endl ;   ;
}




int main(){

graph r  = graph(50);
int  c = r.get_size();
for(int i=0 ; i<c ; i++){
    for(int j=0; j< c ; j++){
        if ((prob() <0.1) ){
            int x = getnumber(10);
            r.add_edge(i ,j , x) ;

            }
        }
    }
node* s = r.get_node(0);
digikstra(r   ,  s );


return  0 ;

}
