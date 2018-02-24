/*
    Código desenvolvido para disciplina de Inteligência Artifical
    Autor: Alfredo Lima
    Data: 22/02/2018
*/

#include<bits/stdc++.h>
using namespace std;
#define DEBUG if(0)

map< string , map< string , double> > table;
vector< string > lines;

struct node {
    string name;
    map< string , vector<string> > edges;

    node(){

    }

    node(string name){
        this->name = name;
    }

};

map< string , node > nodes;

// Criação dos nós
void createNodes(){
    for (int i = 1; i < 15 ; ++i) {
        string name = "E" + to_string(i);
        nodes[ name ] = node(name);
    }
}

// Criação das conexões
void createConnections(){
    // Nós da linha azul
    int blue[] = {1,2,3,4,5,6};
    vector<int> vblue ( blue , blue + sizeof(blue)/ sizeof(int) );

    // Nós da linha amarela
    int yellow[] = {10,2,9,8,5,7};
    vector<int> vyellow ( yellow , yellow + sizeof(yellow)/ sizeof(int) );

    // Nós da linha vermelha
    int red[] = {11,9,3,13};
    vector<int> vred ( red , red + sizeof(red)/ sizeof(int) );

    // Nós da linha verde
    int green[] = {12,8,4,13,14};
    vector<int> vgreen ( green , green + sizeof(green)/ sizeof(int) );

    // Conexões da linha azul
    for (int i = 1; i < vblue.size() ; ++i) {
        string n1 = "E" + to_string( vblue[i-1] );
        string n2 = "E" + to_string( vblue[i] );
        nodes[ n1 ].edges["blue"].push_back( n2 );
        nodes[ n2 ].edges["blue"].push_back( n1 );
    }

    // Conexões da linha amarela
    for (int i = 1; i < vyellow.size() ; ++i) {
        string n1 = "E" + to_string( vyellow[i-1] );
        string n2 = "E" + to_string( vyellow[i] );
        nodes[ n1 ].edges["yellow"].push_back( n2 );
        nodes[ n2 ].edges["yellow"].push_back( n1 );
    }

    // Conexões da linha vermelha
    for (int i = 1; i < vred.size() ; ++i) {
        string n1 = "E" + to_string( vred[i-1] );
        string n2 = "E" + to_string( vred[i] );
        nodes[ n1 ].edges["red"].push_back( n2 );
        nodes[ n2 ].edges["red"].push_back( n1 );
    }

    // Conexões da linha verde
    for (int i = 1; i < vgreen.size() ; ++i) {
        string n1 = "E" + to_string( vgreen[i-1] );
        string n2 = "E" + to_string( vgreen[i] );
        nodes[ n1 ].edges["green"].push_back( n2 );
        nodes[ n2 ].edges["green"].push_back( n1 );
    }

}

// Leitura da tabela
void readFile(){
    FILE *fp;
    fp = fopen("Problem2.in", "r+");
    int c;
    for (int i = 0; i < 14; ++i) {
        for (int j = 0; j < 14; ++j) {
            fscanf(fp , "%d", &c );
            table[ "E" + to_string(i+1) ][ "E" + to_string(j+1) ] = c;
        }
    }
}

// Criação das linhas
void createLines(){
    lines.push_back( "blue" );
    lines.push_back( "red" );
    lines.push_back( "yellow" );
    lines.push_back( "green" );
}

void init(){
    readFile();
    createNodes();
    createConnections();
    createLines();
}

double rate( string from , string target ){
    return table[from][target]/30.0;
}

void aStar( string from , string target ){
    DEBUG cout << "Chamou! " << lines.size() << endl;
    map< string , map< string , double > > dist;
    map< string , map< string , tuple<string,string> > > path;
    priority_queue< tuple< double , double , string , string , string , string > > pq;

    for ( auto l : lines ){
        DEBUG cout << l << " - " << nodes[ from ].edges[l].size() << endl;
        if( nodes[ from ].edges[l].size() ) {
            pq.push( make_tuple( rate(from,target) , 0 , l , from, "" , "" ) );
            path[ from ][ l ] = make_tuple("","");
        }
    }

    string line_target = "";
    while ( !pq.empty() ){
        auto top = pq.top(); pq.pop();
        double cost_rate = get<0>(top), cost_real = get<1>(top);
        string line = get<2>(top) , node = get<3>(top);
        string father = get<4>(top), line_father = get<5>(top);

        cout << "Analisando " << node << " - " << line << " - " << cost_rate << endl;

        if( dist[node].count(line) ) {
            continue;
        }

        dist[ node ][ line ] = cost_real;
        path[ node ][ line ] = make_tuple( father, line_father );
        if( node == target ){
            cout << "Encontrei a resposta" << endl;
            line_target = line;
            break;
        }

        // Continuar na mesma linha
        for ( auto v : nodes[node].edges[line] ) {
            double cost = cost_real + table[ node ][ v ]/30.0;
            pq.push( make_tuple( cost + rate(v,target) , cost , line , v , node, line ) );
        }

        // Mudar de linha
        for( auto l : lines ){
            if( l == line ) continue;
            pq.push( make_tuple( cost_rate + 4 , cost_real + 4 , l , node, node, l ) );
        }
    }

    cout << "#################################################" << endl;

    // Caminho até o objetivo
    string s = target;
    vector< tuple<string,string> > paths;
    while ( s != from ){
        cout << s << " - " << line_target << endl;
        paths.push_back( make_tuple(s,line_target) );
        auto t = path[s][line_target];
        s = get<0>(t); line_target = get<1>(t);
    }


}

int main(){
    init();
    aStar( "E1", "E3" );
}