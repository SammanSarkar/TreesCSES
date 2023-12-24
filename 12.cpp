#include "bits/stdc++.h"
using namespace std;

const int SIZE = 2e5 + 5;
const int DEPTH = 19;
const int SEGMENT = (1 << DEPTH);

int nodes, queries, values[SIZE];
vector<int> edges[SIZE];

int subtree_size[SIZE], parent[SIZE], depth[SIZE];
int segment_tree[SEGMENT], node_id[SIZE], head_node[SIZE];

void update_segment_tree(int index, int value) {
	segment_tree[index += nodes] = value;

	for (index /= 2; index; index /= 2) {
		segment_tree[index] = max(segment_tree[2 * index], segment_tree[2 * index + 1]);
	}
}

int query_segment_tree(int a, int b) {
	a += nodes, b += nodes;
	int result = 0;

	while (a <= b) {
		if (a & 1) {
			result = max(result, segment_tree[a]);
			a++;
		}
		if (~b & 1) {
			result = max(result, segment_tree[b]);
			b--;
		}
		a /= 2, b /= 2;
	}
	return result;
}

int dfs_subtree(int node, int parent_node) {
	subtree_size[node] = 1;
	parent[node] = parent_node;

	for (int child : edges[node]) {
		if (child == parent_node) continue;

		depth[child] = depth[node] + 1;
		parent[child] = node;
		subtree_size[node] += dfs_subtree(child, node);
	}
	return subtree_size[node];
}

int counter = 1;		

void dfs_head(int node, int parent_node, int top) {
	node_id[node] = counter++;
	head_node[node] = top;

	update_segment_tree(node_id[node], values[node]);

	int heavy_child = -1, heavy_size = -1;

	for (int child : edges[node]) {
		if (child == parent_node) continue;

		if (subtree_size[child] > heavy_size) {
			heavy_size = subtree_size[child];
			heavy_child = child;
		}
	}
	if (heavy_child == -1) return;

	dfs_head(heavy_child, node, top);

	for (int child : edges[node]) {
		if (child == parent_node || child == heavy_child) continue;

		dfs_head(child, node, child);
	}
}

int find_path(int x, int y) {
	int answer = 0;
	while (head_node[x] != head_node[y]) {
		if (depth[head_node[x]] < depth[head_node[y]]) {
			swap(x, y);
		}
		answer = max(answer, query_segment_tree(node_id[head_node[x]], node_id[x]));
		x = parent[head_node[x]];
	}
	if (depth[x] > depth[y]) {
		swap(x, y);
	}
	answer = max(answer, query_segment_tree(node_id[x], node_id[y]));
	return answer;
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

	cin >> nodes >> queries;

	for (int i = 1; i <= nodes; i++) {
		cin >> values[i];
	}
	for (int i = 2; i <= nodes; i++) {
		int a, b;
		cin >> a >> b;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}

	dfs_subtree(1, 0);
	dfs_head(1, 0, 1);

	while (queries--) {
		int type;
		cin >> type;
		if (type == 1) {
			int s, x;
			cin >> s >> x;
			values[s] = x;
			update_segment_tree(node_id[s], values[s]);
		} else {
			int a, b;
			cin >> a >> b;

			int result = find_path(a, b);
			cout << result << " ";
		}
	}
}
