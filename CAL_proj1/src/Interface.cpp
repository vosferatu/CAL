#include "Interface.h"
#include "FileHandlers.h"

#define RENT false
#define RETURN true

int originCPoint(vector<CPoint> &pontos, size_t &origin_ind) {
	size_t ans = -1;

	while (ans < 1 || ans > pontos.size()) {
		cout << "\nWhich collection point are you in?";
		for (size_t i = 0; i < pontos.size(); i++) {
			cout << endl;
			cout << i + 1 << " - " << pontos.at(i).getName();
		}
		cout << endl;
		while (ans < 1 || ans > pontos.size()) {
			cin >> ans;
		}
	}

	return ans - 1;
}

void showRoute(Graph<Node> *grafo, vector<CPoint> *pontos, vector<Node> *path, bool type)
{
	GraphViewer *gv = new GraphViewer(450, 600, false);

	gv->setBackground("Limits.PNG");
	gv->createWindow(450, 600);
	gv->defineEdgeColor("blue");
	gv->defineVertexColor("yellow");
	gv->defineEdgeCurved(false);

	for(size_t i=0; i<path->size(); i++)
	{
		long id=path->at(i).getId();
		float lat=0-path->at(i).getRadCoords().getLat();
		float lon=path->at(i).getRadCoords().getLon();

		int y = 600-(lon-GeoCoordinate::lonMin)*600.0/(GeoCoordinate::lonMax-GeoCoordinate::lonMin);
		int x = 450-(lat+GeoCoordinate::latMax)*450.0/(GeoCoordinate::latMax-GeoCoordinate::latMin);

		gv->setVertexColor(id,BLUE);

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

		int y = 600-(lon-GeoCoordinate::lonMin)*600.0/(GeoCoordinate::lonMax-GeoCoordinate::lonMin);
		int x = 450-(lat+GeoCoordinate::latMax)*450.0/(GeoCoordinate::latMax-GeoCoordinate::latMin);

		switch(type)
		{
		case RENT:
			if(pontos->at(a).getBikes()==0)
				gv->setVertexColor(id,RED);
			else
				gv->setVertexColor(id,GREEN);
			break;
		case RETURN:
			if(pontos->at(a).getPlaces()==0)
				gv->setVertexColor(id,RED);
			else
				gv->setVertexColor(id,GREEN);
			break;
		}

		gv->addNode(id, x, y);
		gv->setVertexLabel(id, ".");
	}

	int a=0;

	for(size_t i=0; i<path->size()-1; i++)
	{
		gv->defineEdgeColor("pink");
		gv->addEdge(a, path->at(i).getId(), path->at(i+1).getId(), EdgeType::DIRECTED);
		gv->setEdgeThickness(a,8);
		a++;
	}

	gv->rearrange();
}

void showGraph(Graph<Node> *grafo, vector<CPoint> *pontos) {
	GraphViewer *gv = new GraphViewer(450, 600, false);

	gv->setBackground("Limits.PNG");
	gv->createWindow(450, 600);
	gv->defineEdgeColor("blue");
	gv->defineVertexColor("yellow");
	gv->defineEdgeCurved(false);
	gv->defineVertexSize(1);

	for (size_t i = 0; i < grafo->getVertexSet().size(); i++) {
		long id = grafo->getVertexSet()[i]->getInfo()->getId();
		float lat = 0
				- grafo->getVertexSet()[i]->getInfo()->getRadCoords().getLat();
		float lon =
				grafo->getVertexSet()[i]->getInfo()->getRadCoords().getLon();

		int y = 600
				- (lon - GeoCoordinate::lonMin) * 600.0
				/ (GeoCoordinate::lonMax - GeoCoordinate::lonMin);
		int x = 450
				- (lat + GeoCoordinate::latMax) * 450.0
				/ (GeoCoordinate::latMax - GeoCoordinate::latMin);

		{
			gv->addNode(id, x, y);
			gv->setVertexLabel(id, ".");
		}
	}

	for (size_t a = 0; a < pontos->size(); a++) {
		long id = pontos->at(a).getColNode()->getId();
		float lat = 0 - pontos->at(a).getColNode()->getRadCoords().getLat();
		float lon = pontos->at(a).getColNode()->getRadCoords().getLon();

		int y = 600
				- (lon - GeoCoordinate::lonMin) * 600.0
				/ (GeoCoordinate::lonMax - GeoCoordinate::lonMin);
		int x = 450
				- (lat + GeoCoordinate::latMax) * 450.0
				/ (GeoCoordinate::latMax - GeoCoordinate::latMin);

		gv->addNode(id, x, y);
		gv->setVertexColor(id, RED);
	}

	int a = 0;

	for (size_t i = 0; i < grafo->getVertexSet().size(); i++)
		for (size_t j = 0; j < grafo->getVertexSet()[i]->getAdj().size();
				j++, a++) {
			gv->addEdge(a, grafo->getVertexSet()[i]->getInfo()->getId(),
					grafo->getVertexSet()[i]->getAdj()[j].getDest()->getInfo()->getId(),
					EdgeType::DIRECTED);
		}

	gv->rearrange();
}

void searchForRent(size_t &origin_ind, vector<CPoint> &pontos,
		Graph<Node> &grafo) {
	int min = INT_MAX;
	size_t ans = -1;
	int new_ind = origin_ind;
	CPoint* ponto = NULL;
	for (size_t i = 0; i < pontos.size(); i++) {
		if (pontos.at(i).getBikes() > 0
				&& grafo.getVertex(pontos.at(i).getColNode())->getDist() < min
				&& i != origin_ind) {
			min = grafo.getVertex(pontos.at(i).getColNode())->getDist();
			ponto = &(pontos.at(i));
			new_ind = i;
		}
	}

	cout << "\nThe nearest point ("
			<< grafo.getVertex(ponto->getColNode())->getDist()
			<< " m) with bikes for rental is " << ponto->getName() << endl;
	cout << "\nDo you want to rent a bike on there? (Y/N)";

	while (ans != 1 && ans != 2) {
		cout << "\n1 - Yes\n2 - No\n";
		cin >> ans;
	}

	vector<Node> path;

	switch(ans)
	{
	case 1:
		path=grafo.getPath(*pontos.at(origin_ind).getColNode(), *pontos.at(new_ind).getColNode());
		showRoute(&grafo,&pontos,&path,RENT);
		ponto->rentBike();
		origin_ind=new_ind;
		break;
	case 2:
		cout << "\nSo where do you want to do it?\n";
		for (unsigned int i = 0; i < pontos.size(); i++)
		{
			if(i!=origin_ind && pontos.at(i).getBikes()>0)
				cout << i+1 << " - " << pontos.at(i).getName() << " ("<< grafo.getVertex(pontos.at(i).getColNode())->getDist() <<" m)"<< endl;
		}

		while(ans < 1 || ans > pontos.size() || ans==(origin_ind+1) || pontos.at(ans-1).getBikes()==0){
			cin >> ans;
		}
		pontos.at(ans-1).rentBike();
		path=grafo.getPath(*pontos.at(origin_ind).getColNode(), *pontos.at(ans-1).getColNode());
		showRoute(&grafo,&pontos,&path,RENT);
		origin_ind=ans;
		break;
	default:
		break;
	}

	return;


}

/*
 * @brief Search for a place to return a bike
 */
void searchForReturn(size_t &origin_ind, vector<CPoint> &pontos,
		Graph<Node> &grafo) {
	int min = INT_MAX;
	int new_ind = origin_ind;
	size_t ans = -1;
	CPoint* ponto = NULL;
	for (unsigned int i = 0; i < pontos.size(); i++) {
		if (pontos.at(i).getPlaces() > 0
				&& grafo.getVertex(pontos.at(i).getColNode())->getDist() < min
				&& i != origin_ind) {
			min = grafo.getVertex(pontos.at(i).getColNode())->getDist();
			ponto = &(pontos.at(i));
			new_ind = i;
		}
	}
	cout << "\nThe nearest point with places for return is ("
			<< grafo.getVertex(ponto->getColNode())->getDist() << " m | "
			<< 8 - 0.11 * ponto->getAltitude() << " euros) " << ponto->getName()
			<< endl;
	cout << "Do you want to return a bike on there? (Y/N)";

	while (ans != 1 && ans != 2) {
		cout << "\n1 - Yes\n2 - No\n";
		cin >> ans;
	}

	vector<Node> path;

	switch(ans)
	{
	case 1:
		path=grafo.getPath(*pontos.at(origin_ind).getColNode(), *pontos.at(new_ind).getColNode());
		showRoute(&grafo,&pontos,&path,RETURN);
		ponto->returnBike();
		origin_ind = new_ind;
		break;
	case 2:
		cout << "\nSo where do you want to do it?\n";
		for (unsigned int i = 0; i < pontos.size(); i++) {
			if (i != origin_ind && pontos.at(i).getPlaces()!=0)
				cout << i + 1 << " - " << pontos.at(i).getName() << " ("
				<< grafo.getVertex(pontos.at(i).getColNode())->getDist()
				<< " m | " << 8 - 0.11 * pontos.at(i).getAltitude()
				<< " euros)" << endl;
		}
		while (ans < 1 || ans > pontos.size() || ans == (origin_ind + 1) || pontos.at(ans-1).getPlaces()==0) {
			cin >> ans;
		}
		pontos.at(ans - 1).returnBike();
		path=grafo.getPath(*pontos.at(origin_ind).getColNode(), *pontos.at(ans-1).getColNode());
		showRoute(&grafo,&pontos,&path,RETURN);
		origin_ind = ans;
		break;
	default:
		break;
	}

	return;

}

void clientInit(size_t &origin_ind, vector<User*> &utils,
		vector<CPoint> &pontos, User* current_user) {
	int ans = 0;
	string name;
	string password;
	fstream file;
	bool exists = false;
	bool valid = false;

	while (ans != 1 && ans != 2) {
		cout << "\n1 - Login\n2 - Register\n";
		cin >> ans;
	}

	if (ans == 1) {
		cout << "\nLOGIN\n";
		cout << "Username: ";
		while (name == "" || name == "\n"){
			cin >> name;
		}

		for(size_t i = 0; utils.size() < 0 && !exists ; i++){
			if(utils[i]->getName() == name){
				cout << "Password: ";
				while (!valid){
					cin >> password;
					if(utils[i]->getPassword() == password){
						exists = true;
						valid = true;
						current_user = utils[i];
						break;
					}
				}
			}
		}

	}

	if (!exists || ans == 2) {
		int pay_met, pay_no;
		cout << "\nREGISTRATION";
		cout << "\nUsername: ";
		cin.ignore();
		getline(cin, name);
		cout << "Password: ";
		cin >> password;
		cout << "Payment method?\n1 - Paypal\n2 - Credit Card\n";
		cin >> pay_met;
		cout << "Payment method number: ";
		cin >> pay_no;
		originCPoint(pontos, origin_ind);
		User* novo = new User(name, password, origin_ind, pay_met, pay_no);
		utils.push_back(novo);
		current_user = novo;
	}
}

void menu(size_t &origin_ind, vector<CPoint> &pontos, Graph<Node> &grafo) {
	size_t ans = -1;
	cout << "\nWhat do you want to do?";
	while (ans != 1 && ans != 2) {
		cout << "\n1 - Rent\n2 - Return\n";
		cin >> ans;
	}

	while (1) {
		grafo.dijkstraShortestPath(pontos.at(origin_ind).getColNode());

		if (ans == 1) {
			searchForRent(origin_ind, pontos, grafo);
			ans = 2;
		} else {
			searchForReturn(origin_ind, pontos, grafo);
			ans = 1;
		}

		char exit = 'a';

		while (exit != 'Y' && exit != 'N') {
			cout << "\nDo you want to exit? (Y/N)\n";
			cin.ignore();
			exit = getchar();
			exit = toupper(exit);

			if (exit == 'Y')
				return;
			if (exit == 'N')
				break;
		}
	}
}
