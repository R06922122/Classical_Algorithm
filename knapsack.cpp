#include <bits/stdc++.h>

using namespace std;

int S;
struct section;
vector<section> sections;
int maxVote;


struct section{
	float v, t, unit;
};

bool cmpUnit(section a, section b){
	return a.unit > b.unit;
}


void TeamKP(bool go, int i, int votes, int Time){

	int lowb = 0, upb = 0;
	auto sec = sections.begin() + i;
	if(go)
	{
		if(sec->t <= Time)
		{
			Time -= sec->t;
			votes += sec->v;
		}
		else
			return;
	}

	maxVote = max(maxVote,votes);

	if(Time == 0 || i+1 == S)	return;
	

	/* upb && lowb calculation*/
	int bTime = Time;
	for(auto next = sec + 1; next < sections.end(); next++)
	{
		if( bTime >= next->t)	
		{
			bTime -= next->t;
			upb += next->v;
		}
		else
		{
			lowb = upb;
			upb += next->unit*bTime;
			bTime = 0;
			break;
		}
	}

	lowb += votes;
	upb += votes;

	if(upb <= maxVote) return;
	maxVote = max(maxVote, lowb);
	TeamKP(1, i+1, votes, Time);
	TeamKP(0, i+1, votes, Time);
}




int main(int argc, char const *argv[])
{
	int T;
	cin >> T >> S;
	for(int i = 0; i < S; i++)
	{
		section tmp;
		cin >> tmp.v >> tmp.t;
		tmp.unit = tmp.v / tmp.t;
		sections.push_back(tmp);
	}
	sort(sections.begin(), sections.end(), cmpUnit);
	TeamKP(0, 0, 0, T);
	TeamKP(1, 0, 0, T);
	cout << maxVote;
	return 0;
}