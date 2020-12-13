#include <iostream>
#include <memory>
#include <vector>

using namespace std;

int N; // the number of nodes
int M; // the number of edges
int T; // allowed time
int C; // the number of cars in the fleet
int S; // initial points of all cars

struct Edge
{
    int direction;
    int src, dst;
    int cost;
    int length;
    double score;

    void CalcScore()
    {
        double length2 = static_cast<double>(length);
        score = length2 * length2 / cost;
        if (length2 < 0.0)
        {
            score *= -1.0;
        }
    }

    void Visit()
    {
        if (length > 0)
        {
            length = 0;
        }
        else
        {
            --length;
        }
    }

    bool IsVisited() const
    {
        return length <= 0;
    }
};

struct Node
{
    Node(float lat_, float long_) : lat_(lat_), long_(long_) {}
    float lat_;
    float long_;
    vector<pair<shared_ptr<Edge>, shared_ptr<Node>>> adj;
};

vector<shared_ptr<Node>> nodes;
vector<shared_ptr<Edge>> edges;

int64_t total_score;

void Run(const int curr_i, const int T)
{
    shared_ptr<Node> curr = nodes.at(curr_i);
    shared_ptr<Edge> max_edge;
    for (const auto &a : curr->adj)
    {
        if (T < a.first->cost)
        {
            continue;
        }
        if (max_edge)
        {
            if (max_edge->score < a.first->score)
            {
                max_edge = a.first;
            }
        }
        else
        {
            max_edge = a.first;
        }
    }

    if (!max_edge)
    {
        return;
    }

    if (!max_edge->IsVisited())
    {
        total_score += max_edge->length;
    }

    max_edge->Visit();
    max_edge->CalcScore();

    Run(max_edge->dst, T - max_edge->cost);
}

int main(int argc, char const *argv[])
{
    cin >> N >> M >> T >> C >> S;

    // N개 nodes
    for (int i = 0; i < N; ++i)
    {
        float lat_, long_;
        cin >> lat_ >> long_;
        nodes.push_back(make_shared<Node>(lat_, long_));
    }

    // M개 edges
    for (int i = 0; i < M; ++i)
    {
        auto e = make_shared<Edge>();
        cin >> e->src >> e->dst >> e->direction >> e->cost >> e->length;
        edges.push_back(e);

        e->CalcScore();

        nodes.at(e->src)->adj.emplace_back(e, nodes.at(e->dst));

        if (e->direction == 2)
        {
            nodes.at(e->dst)->adj.emplace_back(e, nodes.at(e->src));
        }
    }

    for (int i = 0; i < C; ++i)
    {
        Run(S, T);
    }

    cout << total_score << '\n';

    return 0;
}
