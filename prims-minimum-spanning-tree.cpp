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
node():value (INT_MAX), index( 10 ) , queue_indx(-1),prev(0),visited{false} {}
node(int index): queue_indx(-1), value(INT_MAX), index(index ), prev(0), visited(false){}
node*prev;
bool visited   ;
int index ;
int value ;
int queue_indx ;
};

struct edge{
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
	    //cout<< q[0]->value<< endl;


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
    return(adj_matrix[x][y].t == true) ;



}
int graph::get_node_value(node* k ){
  int x  = k->index;
return (adj_matrix[x][x].x->value);
}
void graph::set_node_value(node* k , int a ){
    int x  = k->index;

adj_matrix[x][x].x->value = adj_matrix[x][x].y->value = a ;
}
int graph::get_edge_value(node *k  , node*l ){
    int x  = k->index ;
    int y =  l->index ;
     return(adj_matrix[x][y].w);

}
void graph::set_edge_value(int x ,int y, int v){

adj_matrix[x][y].w = adj_matrix[y][x].w = v ;
}

vector<node*>graph:: neighbors(node* x  ){
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






void  prim (graph g ,  node* s){
pq set_;
int c = g.get_size() ;
vector<node*> o;
vector<node*> f = g.nodes();
if (f.size() == 0){
    cout<< "graph is not connected "<<"\n"  ;
    return  ;
}
for(auto i : f ){
set_.add_with_priority(i);


}
set_.decrease_priority( s , 0 );
while(set_.size() != 0){
   node *u = set_.extract_min();
   o.push_back(u) ;
   u->visited = true ;
   //cout<<u->index<< endl ;
   for (node* i: g.neighbors(u)){
        if(i->visited == 0 && i->value > g.get_edge_value(u ,  i)){

        set_.decrease_priority(i , g.get_edge_value(u ,  i)) ;
        i->prev = u;


        }


}


}
//cout<< "node " << " " << "distance from source: "<<endl ;
//cout<<o.size()<<endl ;
for(int i= 1; i<o.size(); i++){
    cout<<o[i]->prev->index<<  "   "<< o[i]->index <<  "   "  <<endl ;
}

}




int main(){

graph r  = graph(9);
//int  c = r.get_size();
//for(int i=0 ; i<c ; i++){
//    for(int j=0; j< c ; j++){
//        if ((prob() <0.19) ){
//            int x = getnumber(100);
//            r.add_edge(i ,j , x) ;
//
//            }
//        }
//    }
r.add_edge(0,1,4);
r.add_edge(0,2,8);
r.add_edge(1,2,14);
r.add_edge(1,4,8);
r.add_edge(2,3,7);
r.add_edge(3,4,2);
r.add_edge(2,5,1);
r.add_edge(5,3,6);
r.add_edge(5,6,2);
r.add_edge(4,6,4);
r.add_edge(4,7,7);
r.add_edge(7,6,14);
r.add_edge(7,8,9);
r.add_edge(6,8,10);

node* s = r.get_node(0);

prim (r   ,  s );



return  0 ;

}
