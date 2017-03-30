#include "Interface.h"
#include "FileHandlers.h"

int originCPoint(vector<CPoint> &pontos, size_t &origin_ind) {
	size_t ans=-1;

	while(ans < 1 || ans > pontos.size()){
		cout << "\nWhich collection point are you in?";
		for (size_t i = 0; i < pontos.size(); i++) {
			cout << endl;
			cout << i+1 << " - " << pontos.at(i).getName();
		}
		cout << endl;
		while(ans < 1 || ans > pontos.size()){
			cin >> ans;
		}
	}

	return ans-1;
}

void showGraph(Graph<Node> *grafo, vector<CPoint> *pontos)
{
	GraphViewer *gv = new GraphViewer(450, 600, false);

	gv->setBackground("Limits.PNG");
	gv->createWindow(450, 600);
	gv->defineEdgeColor("blue");
	gv->defineVertexColor("yellow");
	gv->defineEdgeCurved(false);
	gv->defineVertexSize(1);

	for(size_t i=0; i<grafo->getVertexSet().size(); i++)
	{
		long id=grafo->getVertexSet()[i]->getInfo()->getId();
		float lat=0-grafo->getVertexSet()[i]->getInfo()->getRadCoords().getLat();
		float lon=grafo->getVertexSet()[i]->getInfo()->getRadCoords().getLon();

		int y = 600-(lon-GeoCoordinate::lonMin)*600.0/(GeoCoordinate::lonMax-GeoCoordinate::lonMin);
		int x = 450-(lat+GeoCoordinate::latMax)*450.0/(GeoCoordinate::latMax-GeoCoordinate::latMin);

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

void searchForRent(size_t &origin_ind, vector<CPoint> &pontos, Graph<Node> &grafo) {
	int min = INT_MAX;
	size_t ans=-1;
	int new_ind=origin_ind;
	CPoint* ponto = NULL;
	for (size_t i = 0; i < pontos.size(); i++) {
		if (pontos.at(i).getBikes() > 0
				&& grafo.getVertex(pontos.at(i).getColNode())->getDist()
				< min && i!=origin_ind) {
			min = grafo.getVertex(pontos.at(i).getColNode())->getDist();
			ponto = &(pontos.at(i));
			new_ind=i;
		}
	}

	cout << "\nThe nearest point ("<< grafo.getVertex(ponto->getColNode())->getDist() <<" m) with bikes for rental is " << ponto->getName() << endl;
	cout << "\nDo you want to rent a bike on there? (Y/N)";

	while (ans < 1 || ans > 2) {
		cout << "\n1 - Yes\n2 - No\n";
		cin >> ans;
	}

	vector<Node> path;

	switch(ans)
	{
	case 1:
		ponto->rentBike();
		origin_ind=new_ind;
		break;
	case 2:
		cout << "\nSo where do you want to do it?\n";
		for (unsigned int i = 0, a=0; i < pontos.size(); i++)
		{
			if(a!=origin_ind)
				cout << a+1 << " - " << pontos.at(i).getName() << " ("<< grafo.getVertex(pontos.at(i).getColNode())->getDist() <<" m)"<< endl;
			a++;
		}

		while(ans < 1 || ans > pontos.size() || ans==(origin_ind+1)){
				cin >> ans;
		}
		pontos.at(ans-1).rentBike();
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
void searchForReturn(size_t &origin_ind, vector<CPoint> &pontos, Graph<Node> &grafo) {
	int min = INT_MAX;
	int new_ind=origin_ind;
	size_t ans=-1;
	CPoint* ponto = NULL;
	for (unsigned int i = 0; i < pontos.size(); i++) {
		if (pontos.at(i).getPlaces() > 0
				&& grafo.getVertex(pontos.at(i).getColNode())->getDist()
				< min && i!=origin_ind) {
			min = grafo.getVertex(pontos.at(i).getColNode())->getDist();
			ponto = &(pontos.at(i));
			new_ind=i;
		}
	}
	cout << "\nThe nearest point with places for return is ("<< grafo.getVertex(ponto->getColNode())->getDist() <<" m | " << 8-0.11*ponto->getAltitude() << " euros) " << ponto->getName()<< endl;
	cout << "Do you want to return a bike on there? (Y/N)";

	while (ans < 1 || ans > 2) {
		cout << "\n1 - Yes\n2 - No\n";
		cin >> ans;
	}

	switch(ans)
	{
	case 1:
		if(ponto->getPlaces() > 0){
			ponto->returnBike();
			origin_ind=new_ind;
		}
		else{
		}
		break;
	case 2:
		cout << "\nSo where do you want to do it?\n";
		for (unsigned int i = 0, a=0; i < pontos.size(); i++)
		{
			if(a!=origin_ind)
				cout << a+1 << " - " << pontos.at(i).getName() << " ("<< grafo.getVertex(pontos.at(i).getColNode())->getDist() <<" m | " << 8-0.11*pontos.at(i).getAltitude() << " euros)" << endl;
			a++;
		}
		while(ans < 1 || ans > pontos.size() || ans==(origin_ind+1)){
				cin >> ans;
		}
		pontos.at(ans-1).returnBike();
		origin_ind=ans;
		break;
	default:
		break;
	}

	return;

}

void clientInit(size_t &origin_ind, vector<User*> &utils, vector<CPoint> &pontos) {
	int ans = 0;
	string name;
	string password;
	fstream file;
	bool exists = false;
	bool valid = false;

	while (ans < 1 || ans > 2) {
		cout << "\n1 - Login\n2 - Register\n";
		cin >> ans;
	}

	if (ans == 1) {
		cout << "\nLOGIN\n";
		cout << "Username: ";
		cin >> name;
		file.open(USERS_TXT);
		while (!file.eof()) {
			printf("NAO DEVIA ACONTECER\n");
			string read_name, read_password, read_index, read_paymet, read_no, line;
			getline(file, read_name, ';');
			getline(file, read_password, ';');
			getline(file, read_index, ';');
			getline(file, read_paymet, ';');
			getline(file, read_no, '\n');
			utils.push_back(new User(read_name, read_password, (size_t) atoi(read_index.c_str()), atoi(read_paymet.c_str()), atoi(read_no.c_str())));
			if (read_name == name) {
				exists = true;
				while (!valid) {
					cout << "PASSWORD: ";
					cin >> password;
					if (read_password == password)
						{
						file.close();
						return;
						}
				}
			}
		}printf("OK\n");
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
		utils.push_back(new User(name,password,origin_ind,pay_met,pay_no));
	}
}

void menu(size_t &origin_ind, vector<CPoint> &pontos, Graph<Node> &grafo){
	size_t ans=-1;
	cout << "\nWhat do you want to do?";
	while (ans != 1 || ans != 2) {
		cout << "\n1 - Rent\n2 - Return\n";
		cin >> ans;
	}

	while(1){
		grafo.dijkstraShortestPath(pontos.at(origin_ind).getColNode());

		if (ans == 1){
			searchForRent(origin_ind,pontos,grafo);
			ans=2;
		}
		else{
			searchForReturn(origin_ind,pontos,grafo);
			ans=1;
		}

		char exit = 'a';

		while(exit != 'Y' || exit != 'N'){
			cout<<"\nDo you want to exit? (Y/N)\n";
			exit = getchar();
			exit = toupper(exit);

			if(exit == 'Y')
				return;
			if(exit == 'N')
				break;
		}
	}
}
