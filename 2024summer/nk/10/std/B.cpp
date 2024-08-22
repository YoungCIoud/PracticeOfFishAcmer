#include <bits/stdc++.h>

using namespace std;

struct node {
	string type;
	vector <node> sons;
};

node check(string s) {
	if (s == "double" || s == "int") return {s, {}};
	size_t i = 0;
	auto check = [&] (string x) {
		if (s.substr(i, x.size()) != x) return false;
		i += x.size();
		return true;
	};
	vector <int> sta;
	vector <node> expr;
	sta.push_back(1);
	expr.push_back({"", {}});
	while (i != s.size()) {
		if (check("pair<")) {
			sta.push_back(2);
			expr.push_back({"", {}});
			continue;
		}
		if (check(">")) {
			assert(sta.size() > 1 && sta.back() == 0);
			sta.pop_back();
			expr[expr.size() - 2].sons.push_back(move(expr.back()));
			expr.pop_back();
			assert(sta.back() > 0);
			sta.back()--;
		} else {
			auto current = check("int") ? (string)"int" : (check("double") ? (string)"double" : string());
			assert(current != "");
			assert(!sta.empty());
			expr.back().sons.push_back({current, {}});
			assert(sta.back() > 0);
			sta.back()--;
		}
		if (sta.back() == 1) assert(check(","));
	}
	assert (i == s.size() && sta.size() == 1 && sta.back() == 0);
	return expr.back().sons[0];
}

void print(node *x) {
	if (x->type == "") {
		cout << "pair<";
		print(&x->sons[0]);
		cout << ",";
		print(&x->sons[1]);
		cout << ">";
	} else cout << x->type;
}

int main() {
	int n, q;
	cin >> n >> q;
    map<string, node> types;

    // Validate type declarations
    for (int i = 0; i < n; ++i) {
    	string typeName, varName;
    	cin >> typeName >> varName;
        varName.pop_back();
        types[varName] = check(typeName);
    }

    // Validate the structure of queries
    for (int i = 0; i < q; ++i) { 
        string query;
        cin >> query;
        stringstream ss(query);
        string segment;
        vector<string> seglist;
        while (getline(ss, segment, '.')) {
            seglist.push_back(segment);
        }
        auto *node = &types[seglist[0]];
        for (int i = 1; i < seglist.size(); i++) {
			assert (node->type == "");
        	if (seglist[i] == "first") {
        		node = &node->sons[0];
			} else {
				assert(seglist[i] == "second");
        		node = &node->sons[1];
			}
		}
		print(node);
		cout << endl;
    }
}

