/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
using namespace std;

template <class T> class Edge;
template <class T> class Graph;

template <class T>
class Vertex {
	T info;
	vector<Edge<T>  > adj;
	bool visited;
	int indegree;
	bool processed;
	int dist;
public:
	Vertex<T> * path;
	Vertex(T in);
	friend class Graph<T>;
	int getIndegree() const;
	T* getInfo();
	void addEdge(Vertex<T> *dest, double w);
	bool removeEdgeTo(Vertex<T> *d);
};


template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
	typename vector<Edge<T> >::iterator it= adj.begin();
	typename vector<Edge<T> >::iterator ite= adj.end();
	while (it!=ite) {
		if (it->dest == d) {
			adj.erase(it);
			return true;
		}
		else it++;
	}
	return false;
}

template <class T>
Vertex<T>::Vertex(T in): info(in), visited(false), indegree(0), processed(false), path(NULL), dist(0){}

template <class T>
T* Vertex<T>::getInfo() {
	return &(this->info);
}


template <class T>
void Vertex<T>::addEdge(Vertex<T> *dest, double w) {
	Edge<T> edgeD(dest,w);
	adj.push_back(edgeD);
}

template <class T>
class Edge {
	Vertex<T> * dest;
	double weight;
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w){}

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;
	void dfs(Vertex<T> *v, vector<T> &res) const;
public:
	bool addVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	bool removeVertex(const T &in);
	bool removeEdge(const T &sourc, const T &dest);
	vector<T> dfs() const;
	vector<T> bfs(Vertex<T> *v) const;
	int maxNewChildren(Vertex<T> *v, T &inf) const;
	vector<Vertex<T> * > getVertexSet() const;
	int getNumVertex() const;
	vector<Vertex<T>*> getSources() const;
	void resetIndegrees();
	bool isDAG();
	void visitedReset();
	bool dsfVisit(Vertex<T>* v);
	vector<T> topologicalOrder();
	void unweightedShortestPath(const T &v);
	vector<T> getPath(const T &origin, const T &dest);
};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}
template <class T>
vector<Vertex<T> * > Graph<T>::getVertexSet() const {
	return vertexSet;
}

template <class T>
bool Graph<T>::addVertex(const T &in) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++)
		if ((*it)->info == in) return false;
	Vertex<T> *v1 = new Vertex<T>(in);
	vertexSet.push_back(v1);
	return true;
}

template <class T>
bool Graph<T>::removeVertex(const T &in) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++) {
		if ((*it)->info == in) {
			Vertex<T> * v= *it;
			vertexSet.erase(it);
			typename vector<Vertex<T>*>::iterator it1= vertexSet.begin();
			typename vector<Vertex<T>*>::iterator it1e= vertexSet.end();
			for (; it1!=it1e; it1++) {
				(*it1)->removeEdgeTo(v);
			}
			typename vector<Edge<T> >::iterator it2= v->adj.begin();
			typename vector<Edge<T> >::iterator it2e= v->adj.end();
			for (; it2!=it2e; it2++) {
				it2->dest->indegree--;
			}
			delete v;
			return true;
		}
	}
	return false;
}

template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	int found=0;
	Vertex<T> *vS, *vD;
	while (found!=2 && it!=ite ) {
		if ( (*it)->info == sourc )
		{ vS=*it; found++;}
		if ( (*it)->info == dest )
		{ vD=*it; found++;}
		it ++;
	}
	if (found!=2) return false;
	vD->indegree++;
	vS->addEdge(vD,w);
	return true;
}

template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	int found=0;
	Vertex<T> *vS, *vD;
	while (found!=2 && it!=ite ) {
		if ( (*it)->info == sourc )
		{ vS=*it; found++;}
		if ( (*it)->info == dest )
		{ vD=*it; found++;}
		it ++;
	}
	if (found!=2) return false;
	vD->indegree--;
	return vS->removeEdgeTo(vD);
}

template <class T>
vector<T> Graph<T>::dfs() const {
	typename vector<Vertex<T>*>::const_iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator ite= vertexSet.end();
	for (; it !=ite; it++)
		(*it)->visited=false;
	vector<T> res;
	it=vertexSet.begin();
	for (; it !=ite; it++)
		if ( (*it)->visited==false )
			dfs(*it,res);
	return res;
}

template <class T>
void Graph<T>::dfs(Vertex<T> *v,vector<T> &res) const {
	v->visited = true;
	res.push_back(v->info);
	typename vector<Edge<T> >::iterator it= (v->adj).begin();
	typename vector<Edge<T> >::iterator ite= (v->adj).end();
	for (; it !=ite; it++)
		if ( it->dest->visited == false )
			dfs(it->dest, res);
}

template <class T>
vector<T> Graph<T>::bfs(Vertex<T> *v) const {
	vector<T> res;
	queue<Vertex<T> *> q;
	q.push(v);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		typename vector<Edge<T> >::iterator it=v1->adj.begin();
		typename vector<Edge<T> >::iterator ite=v1->adj.end();
		for (; it!=ite; it++) {
			Vertex<T> *d = it->dest;
			if (d->visited==false) {
				d->visited=true;
				q.push(d);
			}
		}
	}
	return res;
}

template <class T>
int Graph<T>::maxNewChildren(Vertex<T> *v, T &inf) const {
	vector<T> res;
	queue<Vertex<T> *> q;
	queue<int> level;
	int maxChildren=0;
	inf =v->info;
	q.push(v);
	level.push(0);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		int l=level.front();
		level.pop(); l++;
		int nChildren=0;
		typename vector<Edge<T> >::iterator it=v1->adj.begin();
		typename vector<Edge<T> >::iterator ite=v1->adj.end();
		for (; it!=ite; it++) {
			Vertex<T> *d = it->dest;
			if (d->visited==false) {
				d->visited=true;
				q.push(d);
				level.push(l);
				nChildren++;
			}
		}
		if (nChildren>maxChildren) {
			maxChildren=nChildren;
			inf = v1->info;
		}
	}
	return maxChildren;
}

template<class T>
vector<Vertex<T>*> Graph<T>::getSources() const{
	vector<Vertex<T>*> ret;

	for(int i=0; i<vertexSet.size(); i++)
		if(vertexSet[i]->indegree==0)
			ret.push_back(vertexSet[i]);

	return ret;
}

template<class T>
int Vertex<T>::getIndegree() const{
	return indegree;
}

template<class T>
void Graph<T>::resetIndegrees(){
	for(int i=0; i<vertexSet.size(); i++)
		vertexSet[i]->indegree=0;

	for(int i=0; i<vertexSet.size(); i++)
		for(int n=0; n<vertexSet[i]->adj.size(); n++)
			vertexSet[i]->adj[n].dest->indegree++;
}

template<class T>
void Graph<T>::visitedReset(){
	for(int i=0; i<vertexSet.size(); i++)
	{
		vertexSet[i]->visited=false;
	}
}

template<class T>
bool Graph<T>::isDAG(){
	visitedReset();

	for(int i=0; i<vertexSet.size(); i++)
		if(vertexSet[i]->visited==false)
			if(bsfVisit(vertexSet[i]))
				return true;

	return false;
}


template<class T>
bool Graph<T>::dsfVisit(Vertex<T>* v){
	v->visited=true;
	v->processed=true;
	typename vector<Edge<T> >::iterator it=v->adj.begin();
	typename vector<Edge<T> >::iterator itr=v->adj.end();
	for(;it!=itr; it++)
	{
		if((*it).dest->processed==true)
			return true;
		if((*it).dest->visited==false)
			dsfVisit((*it).dest);
	}
}

template<class T>
vector<T> Graph<T>::topologicalOrder(){
	vector<T> ret;

	if(!isDAG())
		return ret;

	queue<Vertex<T>*> fila;
	for(int i=0; i<vertexSet.size(); i++)
		if(vertexSet[i]->indegree==0)
			fila.push(vertexSet[i]);

	while(!fila.empty()){
		Vertex<T> *v=fila.front();
		fila.pop();
		ret.push_back(v->info);
		typename vector<Edge<T> >::iterator it=v->adj.begin();
		typename vector<Edge<T> >::iterator itr=v->adj.end();
		for(;it!=itr; it++){
			(*it).dest->indegree--;
			if((*it).dest->indegree==0)
				fila.push((*it).dest);
		}
	}

	resetIndegrees();

	return ret;
}

template<class T>
void Graph<T>::unweightedShortestPath(const T &v){

	Vertex<T> * vert;
	for(int i=0; i<vertexSet.size(); i++)
	{
		if(vertexSet[i]->info==v)
			vert=vertexSet[i];
		vertexSet[i]->path=NULL;
		vertexSet[i]->dist=-1;
	}

	vert->dist=0;
	queue<Vertex<T>*> fila;
	fila.push(vert);
	while(!fila.empty())
	{
		vert=fila.front();
		fila.pop();
		typename vector<Edge<T> >::iterator it=vert->adj.begin();
		typename vector<Edge<T> >::iterator itr=vert->adj.end();
		for(;it!=itr; it++){
			Vertex<T> * vertD=(*it).dest;
			if(vertD->dist==-1){
				vertD->dist=vert->dist+1;
				vertD->path=vert;
				fila.push(vertD);
			}
		}
	}
}

template<class T>
vector<T> Graph<T>::getPath(const T &origin, const T &dest){
	vector<T> ret;
	Vertex<T> *d;

	this->unweightedShortestPath(origin);

	for(int i=0; i<vertexSet.size(); i++)
		if(vertexSet[i]->info==dest)
			d=vertexSet[i];

	ret.insert(ret.begin(),dest);
	while(d->path!=NULL && d->path->info!=origin)
	{
		d=d->path;
		ret.insert(ret.begin(),d->info);
	}
	if(d->path!=NULL)
		ret.insert(ret.begin(),d->path->info);

	return ret;
}

#endif /* GRAPH_H_ */
