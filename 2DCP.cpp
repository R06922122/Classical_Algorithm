	#include <bits/stdc++.h>
	#define ll long long

	using namespace std;
	bool WhatsUp;
	struct point{
		ll x, y;
		int order;
	};

	int n;
	set<pair<int, int>> ClosestPairs;
	std::vector<point> Points; 
	vector<vector<point> :: iterator> XPoints, YPoints;
	ll ans;

	// ---------------------------------
	bool cmpx(vector<point> :: iterator &a, vector<point> :: iterator &b)
	{
		if(a->x <= b->x ) return true;
		else return false;
	}

	bool cmpy(vector<point> :: iterator &a, vector<point> :: iterator &b)
	{
		if(a->y <= b->y ) return true;
		else return false;
	}

	//-----------------------------

	ll pp(ll num){
		ll n = num*num;
		return n;
	}

	inline ll llmin(ll a, ll b){
		return a > b? b: a;
	}

	ll pos(ll num){
		if(num > 0) return num;
		else return num*(-1);
	}

	// ll sq()

	//--------------------------------------

	// Distance Calculate
	inline ll dis(const point &a, const point &b)
	{
		ll distance;
		ll x_diff = a.x - b.x, y_diff = a.y - b.y;
		distance = x_diff*x_diff + y_diff*y_diff;
		if(WhatsUp) 
		{
			if(distance == ans)
			{
				if(a.order < b.order)
					ClosestPairs.insert({a.order+1,b.order+1});
					else
					ClosestPairs.insert({b.order+1,a.order+1});
			}
		}
		return distance;
	}

	ll Bcase(int head, int end)
	{	
		ll DD = LLONG_MAX;
			for(int i = head; i < end; i ++)
				for(int j = i + 1; j < end; j++)
				{
					ll parisDis = dis(*XPoints.at(i), *XPoints.at(j)); 
					int a = XPoints.at(i)->order, b = XPoints.at(j)->order; 
					if(parisDis < DD)
					{
						DD = parisDis;
					}
				}		
		return DD;
	}

	ll IntersecDis(const vector<vector<point>::iterator> &InterD, const ll &d)
	{
		ll answer = LLONG_MAX;
		int size = InterD.size();
			for(int i = 0 ; i < size; i++)
				for(int j = i+1; j < size && pp(InterD.at(i)->y - InterD.at(j)->y) < d; j++)
				{
					ll DD = dis(*InterD.at(i), *InterD.at(j));
					if(DD <= answer)
						answer = DD;
				}
		return answer;
	}

	ll TCLP(const int &head, const int &end, vector<vector<point>::iterator> &py)
	{	
		int size = end - head;
		vector<vector<point>::iterator> lyp, ryp;
		ll ans = LLONG_MAX;
		//base case, i.e. conquer
		if(size <= 450){
			ans = Bcase(head, end);
			return ans;
		}

		//devide part each X sorted vector mached with a Y sorted vector
		int mid = size/2 + head;
		point Mpoint = *XPoints.at(mid);
		for(int i = 0; i < YPoints.size(); i++)
		{
			if(YPoints.at(i)->x < Mpoint.x) lyp.push_back(YPoints.at(i));
			else ryp.push_back(YPoints[i]);
		}
		ll leftDD = TCLP(head, mid+1, lyp);
		ll rightDD = TCLP(mid+1, end, ryp);
		ll minDD = llmin(leftDD, rightDD);


		//combine part where we need to calculate 
		vector<vector<point>::iterator> intersection;
		int j = 0;
		for(auto i = py.begin(); i < py.end(); i++)
			if(pp((*i)->x - Mpoint.x) <= minDD)
				intersection.push_back(*i);



		return llmin(minDD, IntersecDis(intersection, minDD));

	}



	int main(int argc, char const *argv[])
	{
		cin >> n;
		for(int i = 0; i < n; i++){
			point p;
			cin >> p.x >> p.y;
			p.order = i;
			Points.push_back(p);
		}
		// YPoints = XPoints = Points;
		for(auto it = Points.begin(); it < Points.end(); it++)
		{
			YPoints.push_back(it);
			XPoints.push_back(it);
		}
		sort(XPoints.begin(), XPoints.end(), cmpx);
		sort(YPoints.begin(), YPoints.end(), cmpy);
		WhatsUp = false;
		ans = TCLP(0, n, YPoints);
		WhatsUp = true;
		ll nobodycares = TCLP(0, Points.size(), YPoints);

		cout << ans << " ";
		cout << ClosestPairs.size() << endl;
		for(auto ele: ClosestPairs)
			cout << ele.first << " " << ele.second << '\n';

		return 0;
	}