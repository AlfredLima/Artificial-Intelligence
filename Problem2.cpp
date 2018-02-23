/*
    Código desenvolvido para disciplina de Inteligência Artifical
    Autor: Alfredo Lima
    Data: 22/02/2018
*/

#include<bits/stdc++.h>
using namespace std;

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
}

double avaliacao( string from , string target ){
    return table[from][target]/30.0;
}

void aStar( string from , string target ){
    map< string , double > dist;
    priority_queue< tuple<double,double,string,string> > pq;
    for ( auto l : lines ){
        pq.push( make_tuple( avaliacao(from,target) , 0 , l , from ) );
    }
}

int main(){
    init();
}