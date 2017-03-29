#include "Interface.h"

void showGraph(Graph<Node> *grafo, vector<CPoint> *pontos)
{
	GraphViewer *gv = new GraphViewer(600, 600, false);

	gv->createWindow(600, 600);

	gv->defineEdgeColor("blue");
	gv->defineVertexColor("yellow");
	gv->defineEdgeCurved(false);
	gv->defineVertexSize(0.000001);

	for(size_t i=0; i<grafo->getVertexSet().size(); i++)
	{
		long id=grafo->getVertexSet()[i]->getInfo()->getId();
		float lat=0-grafo->getVertexSet()[i]->getInfo()->getRadCoords().getLat();
		float lon=grafo->getVertexSet()[i]->getInfo()->getRadCoords().getLon();

		int x = (lon-GeoCoordinate::lonMin)*600.0/(GeoCoordinate::lonMax-GeoCoordinate::lonMin);
		int y = (lat+GeoCoordinate::latMax)*600.0/(GeoCoordinate::latMax-GeoCoordinate::latMin);

		{
			gv->addNode(id, x, y);
			gv->setVertexLabel(id, ".");
		}
	}

	for(size_t a=0; a<pontos->size(); a++)
	{
		long id=pontos->at(a).getColNode()->getId();
		float lat=0-pontos->at(a).getColNode()->getRadCoords().getLat();
		float lon=pontos->at(a).getColNode()->getRadCoords().getLon();

		int x = (lon-GeoCoordinate::lonMin)*600.0/(GeoCoordinate::lonMax-GeoCoordinate::lonMin);
		int y = (lat+GeoCoordinate::latMax)*600.0/(GeoCoordinate::latMax-GeoCoordinate::latMin);

		gv->addNode(id, x, y);
		gv->setVertexColor(id,RED);
	}

	int a=0;

	for(size_t i=0; i<grafo->getVertexSet().size(); i++)
		for(size_t j=0; j<grafo->getVertexSet()[i]->getAdj().size(); j++, a++)
		{
			gv->addEdge(a, grafo->getVertexSet()[i]->getInfo()->getId(), grafo->getVertexSet()[i]->getAdj()[j].getDest()->getInfo()->getId() , EdgeType::DIRECTED);
		}

	gv->rearrange();
}

int originCPoint(vector<CPoint> *pontos, size_t *origin_ind) {
	size_t ans=-1;

	while(ans < 1 || ans > pontos->size()){
		cout << "\nWhich collection point are you in?";
		for (size_t i = 0; i < pontos->size(); i++) {
			cout << endl;
			cout << i+1 << " - " << pontos->at(i).getName();
		}
		cout << endl;
		while(ans < 1 || ans > pontos->size()){
			cin >> ans;
		}
	}
	return ans-1;

}
