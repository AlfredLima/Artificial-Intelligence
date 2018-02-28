/*
    Código desenvolvido para disciplina de Inteligência Artifical
    Autor: Alfredo Lima
    Data: 26/02/2018
*/

#include<bits/stdc++.h>
using namespace std;

// Representação do Grafo
map< string , vector< string > >graph;
map< string , map< string, double> > table;

// Leitura da tabela
void readFile(){
    FILE *fp;
    fp = fopen("Problem3.in", "r+");
    int c;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            fscanf(fp , "%d", &c );
            if( c ) graph[ "C" + to_string(i+1) ].push_back( "C" + to_string(j+1) );
            table[ "C" + to_string(i+1) ][ "C" + to_string(j+1) ] = c;
        }
    }
}

void init(){
    readFile();
}

double cost( vector<string> way ){
    double cost_way = 0;
    for (int i = 1; i < way.size() ; ++i)
        cost_way += table[ way[i-1] ][ way[i] ];
    return cost_way;
}

map< string, bool> vstd;
vector<string> path;

bool answer = false;

void dfs( string f , string t, int d ){

    if( answer ) return;

    if( d == 10 ){
        if( f == t )
            answer = true;
        return;
    }

    for ( auto v : graph[f] ){
        if( !vstd[v] ){
            vstd[v] = true;
            path.push_back( v );
            dfs( v , t , d + 1 );
            if( answer ) return;
            vstd[v] = false;
            path.pop_back();
        }
    }

}

bool valid( vector<string> &s , int i, int j ){
    return table[ s[i-1] ][ s[i] ] && table[ s[i] ][ s[i+1] ]
                                    &&
           table[ s[j-1] ][ s[j] ] && table[ s[j] ][ s[j+1] ];
}

void print( vector<string> &s ){
    for (int i = 0; i < s.size() ; ++i) {
        if( i ) cout << " -> ";
        cout << s[i];
    }
    cout << endl;
}

void generatePath(){

    // Condições iniciais
    answer = false;
    double min_answer = 1<<20;
    vector<string> answer_path;

    // Encontrar a primeira resposta
    path.push_back( "C1" );
    dfs( "C1" , "C1" , 0 );
    if( path.size() == 1 ){
        cout << "Não tem resposta!" << endl;
    }
    else {
        answer_path = path;
        min_answer = cost(answer_path);
        cout << "Primeira resposta: " << cost(answer_path) << endl;
        print(answer_path);
    }

    // Encontrar respostas melhores
    for (int k = 0; k < 5; ++k) {
        path = answer_path;
        for (int i = 1; i < answer_path.size() - 1; ++i) {
            for (int j = i + 1; j < answer_path.size() - 1; ++j) {
                swap(path[i], path[j]);
                if (valid(path, i, j)) {
                    double cost_temp = cost(path);
                    if (cost_temp < min_answer) {
                        answer_path = path;
                        min_answer = cost_temp;
                        cout << "Trocou: " << min_answer << endl;
                        print(answer_path);
                    }
                }
                swap(path[i], path[j]);
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    init();
    generatePath();
	return 0;
}