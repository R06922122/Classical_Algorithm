#include <bits/stdc++.h>


using namespace std;
string s1, s2;
vector<vector<pair<int, bool>>> board;
vector<string> Strset;
int length;



/*open up if s1[n-1] == s2[m-1]*/
void flip(int n, int m)
{
	// cout << n << " " << m <<endl;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			board[i][j].second = true;
}



void lcs(int n, int m)
{
	for(int i = 1; i <= n ; i++)
	{
		for(int j = 1; j <= m; j++)
		{
			if(s1[i-1] == s2[j-1]) board[i][j].first = board[i-1][j-1].first +1;
			else board[i][j].first = board[i-1][j].first > board[i][j-1].first ? board[i-1][j].first : board[i][j-1].first;
		}
	}
	length = board[n][m].first;
}

void findall(int n , int m, string cs)
{
	// cout << cs << "\t" << "[" << n << ", " << m << "]" << " ";
	// cout << s1[n-1] << " " << s2[m-1] << endl;

	int self = board[n][m].first;
	if(self == 0)
	{
		Strset.push_back(cs);
		return;
	}
	int up = board[n-1][m].first;
	int left =  board[n][m-1].first;
	


	/* visited mark */
	board[n][m].second = false;

	if(s1[n-1] == s2[m-1] )
	{
		flip(n, m);
		findall(n-1, m-1, s1[n-1]+cs);
	}

	if(up == self && board[n-1][m].second) 		findall(n-1, m, cs);
	if(left == self && board[n][m-1].second) 	findall(n, m-1, cs);
	return;
}


int main(int argc, char const *argv[])
{
	cin >> s1 >> s2;
	int size1 = s1.size();
	int size2 = s2.size();
	vector<pair<int, bool>> tmp(size2+1, {0, true});
	for(int i = 0; i <= size1; i++)
		board.push_back(tmp);
	lcs(size1, size2);
cout << length << " " ;

/*cout board*/
	// int q = 1, p = 1;
	// auto beg = s1.begin();

	// cout << "Board" << endl;
	// cout << "    ";
	// for(auto ele: s2) cout << ele << " ";
	// cout << endl;
	// for(auto line: board)
	// {
	// 	if(q++ != 1) cout << *beg++ << " ";
	// 	else cout << "  ";
	// 	for(auto ele: line)
	// 		cout << ele.first << " ";
	// 	cout << endl;
	// }
	// cout << endl;



/*find strings*/

	findall(size1, size2, " ");
	sort(Strset.begin(), Strset.end());
	cout << Strset.size() << '\n';
	for(auto ele: Strset)
		cout << ele<< '\n';

	return 0; 
}