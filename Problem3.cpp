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

int factorial( int n )
{
    int answer = 1;
    for (int i = 2; i <= n ; ++i)
        answer *= i;
    return answer;
}

vector<string> kthperm( vector<string> S, int k )
{
    vector<string> P;
    while( S.size() )
    {
        int f = factorial( S.size() - 1 );
        int i = k/f;
        P.push_back( S[i] );
        k = k%f;
        S.erase( S.begin() + i );
    }
    return P;
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

bool valid( vector<string> &s ){

    for (int i = 1; i < s.size() ; ++i)
        if( !table[ s[i-1] ][ s[i] ] ) return false;

    return true;
}

void print( vector<string> &s ){
    for (int i = 0; i < s.size() ; ++i) {
        if( i ) cout << " -> ";
        cout << s[i];
    }
    cout << endl;
}

void generatePath( int life ){
    srand(time(NULL));
    // Condições iniciais
    double min_answer = 1<<20;
    vector<string> answer_path, path, temp_path;
    vector<string> base;
    for (int i = 2; i <= 10; ++i)
        base.push_back( "C" + to_string(i) );
    int size = factorial( base.size() );


    for (int k = 0; k < life; ++k)
    {
        // Reinicio aleatório
        do {
            path = kthperm( base , rand()%size );
            path.insert( path.begin() , "C1" );
            path.push_back( "C1" );
        } while( !valid(path) );
        int c = cost(path);
        cout << "--------------######--------------" << endl;
        cout << "Reinicio: " << c << " => "; print( path );
        cout << "--------------######--------------" << endl;
        if( c < min_answer ){
            answer_path = path;
            min_answer = c;
            cout << "Trocou no reinicio:" << endl;
            cout << c << " => "; print( answer_path );
        }
        // Subida da encosta
        // Trocando duas posições
        
        bool up;
        temp_path = path;
        int cost_temp = c;
        
        do {
            up = false;
            for (int i = 1; i < 9 ; ++i) {
                for (int j = i+1; j < 10 ; ++j) {
                    swap( path[i], path[j] );
                    if( valid(path) ){
                        c = cost(path);
                        if( c < cost_temp ){
                            temp_path = path;
                            cost_temp = c;
                            cout << "Trocou subindo:" << endl;
                            cout << c << " => "; print( temp_path );
                        }
                    }
                    swap( path[i], path[j] );
                }
            }
        } while( up );
        if( cost_temp < min_answer ) {
            answer_path = temp_path;
            min_answer = cost_temp;
            cout << "Trocou no topo:" << endl;
            cout << min_answer << " => "; print( answer_path );
        }
    }

    cout << "--------------######--------------" << endl;
    cout << "Resposta:" << endl;
    cout << min_answer << " => "; print( answer_path );
}

void allAnswer(){
    // Gerar todas as respostas
    int min_answer = 1<<20;
    vector< string > path;
    for (int i = 1; i < 11; ++i)
        path.push_back( "C" + to_string(i) );
    path.push_back("C1");

    do {
        if( valid(path) ){
            int t = cost(path);
            min_answer = min(t,min_answer);
            cout << "# " << t << " # ";
            print(path);
        }
    } while ( next_permutation( path.begin()+1 , path.begin() + 10 ) );

    cout << min_answer << endl;

}

int main(int argc, char const *argv[])
{
    init();
    cout << "Digite a quantidade de reinicios aleatórios: ";
    int t;
    cin >> t;
    generatePath(t);

    //allAnswer();
    return 0;
}