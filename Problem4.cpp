/*
    Código desenvolvido para disciplina de Inteligência Artifical
    Autor: Alfredo Lima
    Data: 13/03/2018
*/

#include<bits/stdc++.h>
using namespace std;

map< int , char > translate;

void print( string &s )
{
	for (int i = 0; i < 3 ; ++i)
	{
		if( i ) cout << "------------" << endl;
		for (int j = 0; j < 3 ; ++j)
		{
			if( j ) cout << " |";
			cout << " " << s[ 3*i + j ];
		}
		cout << endl;
	}
}

int finish( string &s ){
	for (int i = 0; i < 3; ++i)
	{
		if( s[3*i] == s[3*i+1] and s[3*i+1] == s[3*i+2] and s[3*i] != ' ' )	{
			if( s[3*i] == 'X' )	return 1;
			else return -1;
		}
		if( s[i] == s[i+3] and s[i+3] == s[i+6] and s[i] != ' ' )	{
			if( s[i] == 'X' )	return 1;
			else return -1;
		}
	}
	if( s[0] == s[4] and s[4] == s[8] and s[4] != ' ' ){
		if( s[4] == 'X' )	return 1;
		else return -1;
	}
	if( s[2] == s[4] and s[4] == s[6] and s[4] != ' ' ){
		if( s[4] == 'X' )	return 1;
		else return -1;
	}
	return 0;
}

tuple<int,int> minMax( string s , int id , int deph , int alfa , int beta )	{
	
	int v = finish( s );
	if( v )	return make_tuple( v * ( 20 - deph ) , -1 );
	v = 20 * ( id ? 1 : - 1 );
	int mov = -1;
	for (int i = 0; i < 9 ; ++i) {
		if( s[i] == ' ' ){
			s[i] = translate[id];
			auto q = minMax( s , 1 - id , deph + 1 , alfa , beta );
			s[i] = ' ';
			if( id ){ // Min
				if( get<0>(q) < v ) mov = i;
				v = min(get<0>(q),v);
				if( v <= alfa ) return make_tuple( v , mov );
				beta = min( beta , v );
			}
			else { // Max
				if( get<0>(q) > v ) mov = i;
				v = max(get<0>(q),v);
				if( v >= beta ) return make_tuple( v , mov );
				alfa = max( alfa , v );
			}
		}
	}
	return make_tuple( v , mov );
}

void init(){
	translate[0] = 'X';
	translate[1] = 'O';
}

int main(int argc, char const *argv[])
{
	init();
	int player = 0;
	string input, game;
	string play;
	int v;
	int alfa, beta;
	do {
		for( int i = 0 ; i < 2 ; ++i ) {
			cout << "Jogo novo!" << endl << endl;
			game = "         ";
			player = i;
			print( game );
			while( !finish(game) ){
				if( player ){
					alfa = -(1<<20);
					beta = 1<<20;
					auto j = minMax( game , player , 0 , alfa , beta );
					v = get<1>(j) + 1;
					if( v == -1 ) break;
					cout << "Máquina Jogando:" << endl;
					for (int i = 0; i < 50000000; ++i);
				}
				else {
					cout << "Sua vez: ";
					cin >> v;
				}
				if( game[v-1] == ' ' ) { 
					game[ v-1 ] = translate[ player ];
					player = 1 - player; 
				}
				else {
					cout << "Jogada inválida!" << endl;
				}
				print( game );
			} 
			cout << "Fim de jogo!" << endl;
			cout << "Continuar jogando S ou N?";
			cin >> play;
			if( play != "S" ) break;
		}
	} while( play == "S" );
	return 0;
}