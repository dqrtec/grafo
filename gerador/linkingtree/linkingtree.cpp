#include <bits/stdc++.h>

using namespace std;

int       n, m, v, d, nt, prob;
string               path, out;
map <int, string>        label;
map <string, int>       ilabel;
vector< vector<int> >      adj;
vector< vector<int> >     tree;
map< pair<int,int>, int> edges;
vector< vector< int > >   dist;

bool inset(int x, set<int> y){
	return y.find(x) != y.end();
}

bool inmap(string x, map<string, int> y){
	return y.find(x) != y.end();
}

void importEQuery(){
	
	char spath[path.size() + 1];
	for(int i = 0; i < path.size(); i++){
		spath[i] = path[i];
	}
	spath[path.size()] = '\0';
	
	FILE *arq = fopen(spath, "r");
	
	if(arq == NULL){
		printf("Error: not possible to open file.\n");
	}else{
		fscanf(arq, "%d %d %d\n", &v, &n, &m);
		adj.resize(n);
		for(int i = 0; i < n; i++){
			char s[10];
			fscanf(arq,"%s", s);
			
			string l = "";
			int j = 0;
			while(s[j] != '\0'){
				l += s[j];
				j++;
			}
			
			label[i]  = l;
			ilabel[l] = i;
		}
		for(int i = 0; i < m; i++){
			int a, b;
			fscanf(arq,"%d %d\n",&a,&b);
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
	}
	
	fclose(arq);
}

void exportAndGenerateADJ(){
	char spath[out.size() + 1];
	for(int i = 0; i < out.size(); i++){
		spath[i] = out[i];
	}
	spath[out.size()] = '\0';
	
	FILE *arq = fopen(spath, "a");

	for(int i = 0; i < nt; i++){
		int x = rand() % (n + i);
		fprintf(arq, "%d %d\n", n + i, x);
	}
	
	fclose(arq);
}

void exportTop(){
	char spath[out.size() + 1];
	for(int i = 0; i < out.size(); i++){
		spath[i] = out[i];
	}
	spath[out.size()] = '\0';
	
	FILE *arq = fopen(spath, "w");
	
	if(arq == NULL){
		printf("Error: not possible to open file.\n");
	}else{
		fprintf(arq, "%d %d\n", n + nt, m + nt);
		for(int i = 0; i < n; i++){
			string lbl = label[i];
			char rsp[lbl.size() + 1];
			for(int j = 0; j < lbl.size(); j++){
				rsp[j] = lbl[j];
			}
			rsp[lbl.size()] = '\0';
			fprintf(arq, "%s\n", rsp);
		}
	}
	
	fclose(arq);
}

void generateLabels(){
	string let = "ABCDEFGHIJKLMOPQRSTUVXWYZ0123456789";
	
	char spath[out.size() + 1];
	for(int i = 0; i < out.size(); i++){
		spath[i] = out[i];
	}
	spath[out.size()] = '\0';
	
	FILE *arq = fopen(spath, "a");
	
	for(int i = 0; i < nt; i++){
		string lb;
		do{
			lb = "";
			for(int j = 0; j < 8; j++){
				lb += let[rand() % let.size()];
			}		
		}while(inmap(lb,ilabel));
		
		char rsp[lb.size() + 1];
		for(int j = 0; j < lb.size(); j++){
			rsp[j] = lb[j];
		}
		rsp[lb.size()] = '\0';
			
		fprintf(arq, "%s\n", rsp);
	}
	
	fclose(arq);
}

void exportEQADJ(){
	char spath[out.size() + 1];
	for(int i = 0; i < out.size(); i++){
		spath[i] = out[i];
	}
	spath[out.size()] = '\0';
	
	FILE *arq = fopen(spath, "a");
	
	for(int i = 0; i < n; i++){
		for(int j : adj[i]){
			if(i < j)
				fprintf(arq, "%d %d\n", i, j);
		}
	}
	
	fclose(arq);
}

int stringToInt(string value){
	int x = 0;
	reverse(value.begin(), value.end());
	for(int i = 0; i < value.size(); i++){
		x += ((int) value[i] - '0') * pow(10, i);
	}
	return x;
}

int main(int argc, char** argv){
	// N = MAX 10000000
	
    srand(time(NULL));

	nt =   stringToInt(argv[1]);
    path =              argv[2];
    out =               argv[3];
    
    cout << "Generating Linking Tree from " << path << " to " << out << " with N = " << nt << endl;
    
	importEQuery();
	cout << "Imported" << endl;
	exportTop();
	cout << "Exported Top" << endl;
	generateLabels();
	cout << "Labels Generated" << endl;
	exportEQADJ();
	cout << "Exported Adj List" << endl;
	exportAndGenerateADJ();
	cout << "Exported Rest Tree Adj List" << endl;
    
    return 0;
}
