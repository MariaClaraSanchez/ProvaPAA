#include <iostream>
#include <list>
#include <queue>
#define INFINITO 10000000

using namespace std;

class Grafo
{
private:
	int V; // número de vértices

	// ponteiro para um array contendo as listas de adjacências
	list<pair<int, int> > * adj;

public:

	// construtor
	Grafo(int V)
	{
		this->V = V; // atribui o número de vértices

		/*
			cria as listas onde cada lista é uma lista de pairs
			onde cada pair é formado pelo vértice destino e o custo
		*/
		adj = new list<pair<int, int> >[V];
	}

	// adiciona uma aresta ao grafo de v1 à v2
	void addAresta(int v1, int v2, int custo)
	{
		adj[v1].push_back(make_pair(v2, custo));
	}

	// algoritmo de Dijkstra
	int dijkstra(int orig, int dest)
	{
		// vetor de distâncias
		int dist[V];

		/*
		   vetor de visitados serve para caso o vértice já tenha sido
		   expandido (visitado), não expandir mais
		*/
		int visitados[V];

		// fila de prioridades de pair (distancia, vértice)
		priority_queue < pair<int, int>,
					   vector<pair<int, int> >, greater<pair<int, int> > > pq;

		// inicia o vetor de distâncias e visitados
		for(int i = 0; i < V; i++)
		{
			dist[i] = INFINITO;
			visitados[i] = false;
		}

		// a distância de orig para orig é 0
		dist[orig] = 0;

		// insere na fila
		pq.push(make_pair(dist[orig], orig));

		// loop do algoritmo
		while(!pq.empty())
		{
			pair<int, int> p = pq.top(); // extrai o pair do topo
			int u = p.second; // obtém o vértice do pair
			pq.pop(); // remove da fila

			// verifica se o vértice não foi expandido
			if(visitados[u] == false)
			{
				// marca como visitado
				visitados[u] = true;

				list<pair<int, int> >::iterator it;

				// percorre os vértices "v" adjacentes de "u"
				for(it = adj[u].begin(); it != adj[u].end(); it++)
				{
					// obtém o vértice adjacente e o custo da aresta
					int v = it->first;
					int custo_aresta = it->second;

					// relaxamento (u, v)
					if(dist[v] > (dist[u] + custo_aresta))
					{
						// atualiza a distância de "v" e insere na fila
						dist[v] = dist[u] + custo_aresta;
						pq.push(make_pair(dist[v], v));
					}
				}
			}
		}

		// retorna a distância mínima até o destino
		return dist[dest];
	}
};

int main(int argc, char *argv[])
{
	Grafo g(7);
    g.addAresta(1, 1, 0); // São paulo -> São Paulo
    cout << "\n De 1 a 1 (Ou de Sao Paulo -> Sao Paulo) : (Nao Existe)" << endl;
    cout << " Custo = " << g.dijkstra(1, 1)  << " , Ou seja nao existe!"<< endl; 

    /*CALCULCULA A MENOR DISTÂNCIA PARA IR DE SÃO PAULO PARA RIBERÃO PRETO*/
	g.addAresta(1, 2, 2); // Saindo de São paulo -> Ribeirão Preto Direto
    g.addAresta(1, 2,10); // Indo por São Paulo -> Campinas -> Riberão Preto
    g.addAresta(1, 2, 9); //Indo por São Paulo -> Poços de Caldas -> Riberão Preto
    g.addAresta(1, 2, 14); //Indo por São Paulo -> Rio de Janeiro -> Poços de Caldas -> Riberão Preto

    switch (g.dijkstra(1, 2))
      {
        case 2:
            cout << "\n De 1 a 2(Ou de Sao Paulo -> Ribeirao Preto) : Sao Paulo -> Ribeirao Preto" << endl;
            cout << " Custo = " << g.dijkstra(1, 2) << "\n"<< endl;
            break;
        case 10:
            cout << "\n De 1 a 2(Ou Sao Paulo Campinas-> Ribeirao Preto) : Sao Paulo -> Campinas -> Riberao Preto " << endl;
            cout << " Custo = " << g.dijkstra(1, 2) << "\n"<< endl;
            break;
        case 9:
            cout << "\n De 1 a 2(Ou Sao Paulo Campinas-> Ribeirao Preto) : Sao Paulo -> Pocos de Caldas -> Riberao Preto " << endl;
            cout << " Custo = " << g.dijkstra(1, 2) << "\n"<< endl;
            break;

        case 14:
            cout << "\n De 1 a 2(Ou Sao Paulo Campinas-> Ribeirao Preto) : Sao Paulo -> Rio de Janeiro -> Pocos de Caldas -> Riberao Preto " << endl;
            cout << " Custo = " << g.dijkstra(1, 2) << "\n"<< endl;
            break;
         default:
             cout << " Nenhum caminho encontrado \n"<< endl;
      }

    /*CALCULCULA A MENOR DISTÂNCIA PARA IR DE SÃO PAULO PARA POÇOS DE CALDAS*/
	g.addAresta(1, 3, 5); // Saindo de São paulo -> Poços de Caldas
    g.addAresta(1, 3,14); // Indo por São Paulo -> Campinas -> Riberão Preto -> Poços de Caldas
    g.addAresta(1, 3, 6); //Indo por São Paulo -> Ribeirão Preto -> Poços de Caldas
    g.addAresta(1, 3, 10); //Indo por São Paulo -> Rio de Janeiro -> Poços de Caldas

    switch (g.dijkstra(1, 3))
      {
        case 5:
            cout << "\n De 1 a 3(Ou de Sao Paulo -> Pocos de Caldas) : Sao Paulo -> Pocos de Caldas" << endl;
            cout << " Custo = " << g.dijkstra(1, 3) << "\n"<< endl;
            break;
        case 14:
            cout << "\n De 1 a 3(Ou de Sao Paulo -> Pocos de Caldas) : Sao Paulo -> Campinas -> Riberao Preto -> Poços de Caldas " << endl;
            cout << " Custo = " << g.dijkstra(1, 3) << "\n"<< endl;
            break;
        case 6:
            cout << "\n De 1 a 3(Ou de Sao Paulo -> Pocos de Caldas) : Sao Paulo -> Riberao Preto -> Pocos de Caldas" << endl;
            cout << " Custo = " << g.dijkstra(1, 3) << "\n"<< endl;
            break;

        case 10:
            cout << "\n De 1 a 3(Ou de Sao Paulo -> Pocos de Caldas) : Sao Paulo -> Rio de Janeiro -> Pocos de Caldas" << endl;
            cout << " Custo = " << g.dijkstra(1, 3) << "\n"<< endl;
            break;
         default:
             cout << " Nenhum caminho encontrado \n"<< endl;
      }

    /*CALCULCULA A MENOR DISTÂNCIA PARA IR DE SÃO PAULO PARA CAMPINAS*/
	g.addAresta(1, 4, 7); // Saindo de São paulo -> Campinas
    g.addAresta(1, 4, 6); // Indo por São Paulo -> Riberão Preto -> Campinas
    g.addAresta(1, 4, 12); //Indo por São Paulo -> Poços de Caldas -> Riberão Preto -> Campinas
    g.addAresta(1, 4, 17); //Indo por São Paulo -> Rio de Janeiro -> Poços de Caldas -> Riberão Preto -> Campinas

    switch (g.dijkstra(1, 4))
      {
        case 7:
            cout << "\n De 1 a 4(Ou de Sao Paulo -> Campinas) : Sao Paulo -> Campinas" << endl;
            cout << " Custo = " << g.dijkstra(1, 4) << "\n"<< endl;
            break;
        case 6:
            cout << "\n De 1 a 4(Ou de Sao Paulo -> Campinas) : Sao Paulo -> Riberao Preto -> Campinas" << endl;
            cout << " Custo = " << g.dijkstra(1, 4) << "\n"<< endl;
            break;
        case 12:
            cout << "\n De 1 a 4(Ou de Sao Paulo -> PCampinas) : Sao Paulo -> Riberao Preto -> Pocos de Caldas" << endl;
            cout << " Custo = " << g.dijkstra(1, 4) << "\n"<< endl;
            break;

        case 17:
            cout << "\n De 1 a 4(Ou de Sao Paulo ->Campinas) : Sao Paulo -> Rio de Janeiro -> Pocos de Caldas -> Riberao Preto -> Campinas" << endl;
            cout << " Custo = " << g.dijkstra(1, 4) << "\n"<< endl;
            break;
         default:
             cout << " Nenhum caminho encontrado \n"<< endl;
      }

    /*CALCULCULA A MENOR DISTÂNCIA PARA IR DE SÃO PAULO PARA Rio de Janeiro*/
	g.addAresta(1, 5, 4); // Saindo de São paulo -> Rio de Janeiro
    g.addAresta(1, 5, 20); // Indo por São Paulo -> Campinas -> Riberão Preto -> Poços de Caldas -> Rio de Janeiro
    g.addAresta(1, 5, 12); //Indo por São Paulo -> Riberão Preto -> Poços de Caldas -> Rio de Janeiro
    g.addAresta(1, 5, 11); //Indo por São Paulo -> Poços de Caldas -> Rio de Janeiro

    switch (g.dijkstra(1, 5))
      {
        case 4:
            cout << "\n De 1 a 5(Ou de Sao Paulo -> Rio de Janeiro) : Sao Paulo -> Rio de Janeiro" << endl;
            cout << " Custo = " << g.dijkstra(1, 5) << "\n"<< endl;
            break;
        case 20:
            cout << "\n De 1 a 5(Ou de Sao Paulo -> Rio de Janeiro) : Sao Paulo -> Campinas -> Riberao Preto -> Pocos de Caldas -> Rio de Janeiro " << endl;
            cout << " Custo = " << g.dijkstra(1, 5) << "\n"<< endl;
            break;
        case 12:
            cout << "\n De 1 a 5(Ou de Sao Paulo -> Rio de Janeiro) : Sao Paulo -> Riberao Preto -> Pocos de Caldas -> Rio de Janeiro" << endl;
            cout << " Custo = " << g.dijkstra(1, 5) << "\n"<< endl;
            break;

        case 11:
            cout << "\n De 1 a 5(Ou de Sao Paulo ->Rio de Janeiro) : Sao Paulo -> Pocos de Caldas -> Rio de Janeiro" << endl;
            cout << " Custo = " << g.dijkstra(1, 5) << "\n"<< endl;
            break;
         default:
             cout << " Nenhum caminho encontrado \n"<< endl;
      }

	return 0;
}