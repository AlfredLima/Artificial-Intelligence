#include<bits/stdc++.h>
using namespace std;

map< int , vector<int> > DP_moves;

vector<int> moves ( int p )
{
	if( DP_moves.count(p) ) return DP_moves[p];
	vector<int> mvs;
	if( p%3 != 0 ) mvs.push_back(-1);
	if( p/3 != 0 ) mvs.push_back(-3);
	if( p%3 != 2 ) mvs.push_back(+1);
	if( p/3 != 2 ) mvs.push_back(+3);

	return DP_moves[p] = mvs;
}

int position( string s )
{
	for (int i = 0; i < 9 ; ++i)
		if( s[i] == '0' ) return i;
}

// Resolvendo com BFS sem guadar que já passou pelo estado.
void solver1 ( string initial , string final )
{
	list< pair<string,string> > states;
	states.push_back( {initial , ""} );

	int count = 0;

	while( states.size() )
	{

		auto s = states.front(); states.pop_front();
		if( s.first == final )
		{
			cout << "Encontrei" << endl;
			break;
		}
		int p = position(s.first);
		vector<int> mvs = moves( p );
		for ( auto v : mvs )
		{
			string next = s.first;
			swap( next[p+v] , next[p] );
			if( s.first != s.second ) states.push_back( {next,s.first} );
		}
	}

}

// Resolvendo com BFS guardando que passou pelo estado
void solver2 ( string initial , string final )
{

	map< string, bool > marked;

	list< pair<string,string> > states;
	states.push_back( {initial , ""} );

	marked[initial] = 1;

	while( states.size() )
	{
		
		auto s = states.front(); states.pop_front();
		if( s.first == final )
		{
			cout << "Encontrei" << endl;
			break;
		}
		int p = position(s.first);
		vector<int> mvs = moves( p );
		for ( auto v : mvs )
		{
			string next = s.first;
			swap( next[p+v] , next[p] );
			if( !marked[next] ) states.push_back( {next,s.first} );
			marked[next] = 1;
		}
	}

}

int main(int argc, char const *argv[])
{
	int v;
	string tab;
	for (int i = 0; i < 3 ; ++i)
		for (int j = 0; j < 3 ; ++j)
		{
			cin >> v;
			tab += '0' + v;
		}
		
	solver2 ( tab , "123456780" );

	solver1 ( tab , "123456780" );

	return 0;
}