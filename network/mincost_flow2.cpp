/*
 *  最小费用流 O(V^2 * f)
 *  INIT: network g; g.build(nv, ne);
 *  CALL: g.mincost(s, t); flow=g.flow; cost=g.cost;
 *  注意: 网络中弧的cost需为非负. 若存在负权, 进行如下转化: 
 *  首先如果原图有负环, 则不存在最小费用流. 那么可以用Johnson
 *  重标号技术把所有边变成正权，以后每次增广后进行维护，算法如下：
 *  1、用bellman-ford求s到各点的距离phi[];
 *  2、以后每求一次最短路，设s到各点的最短距离为dis[];
 *      for i = 1 to v do
 *          phi[v] += dis[v];
 *  下面的代码已经做了第二步，如果原图有负权，添加第一步即可。
 */
#define typef int               //  type of flow
#define typec int               //  type of cost
const typef inff = 0x3f3f3f3f;  //  max of flow
const typec infc = 0x3f3f3f3f;  //  max of cost
const int E = 10010;
const int N = 1010;

struct edge
{
    int u, v;
    typef cuv, cvu, flow;
    typec cost;
    edge (int x, int y, typef cu, typef cv, typec cc) :u(x), v(y), cuv(cu), cvu(cv), flow(0), cost(cc){}
    int other(int p)
    {
        return p == u ? v : u;
    }
    typef cap(int p)
    {
        return p == u ? cuv-flow : cvu+flow;
    }
    typec ecost(int p)
    {
        if (flow == 0)
        {
            return cost;
        }
        else if (flow > 0)
        {
            return p == u ? cost : -cost;
        }
        else
        {
            return p == u ? -cost : cost;
        }
    }
    void addFlow(int p, typef f)
    {
        flow += (p == u ? f : -f);
    }
};

struct network
{
    vector<edge> eg;
    vector<edge*> net[N];
    edge *prev[N];
    int v, s, t, pre[N], vis[N];
    typef flow;
    typec cost, dis[N], phi[N];
    bool dijkstra();
    void build(int nv, int ne);
    typec mincost(int, int);
};

bool network::dijkstra()
{
    //  使用O(E * logV)的Dij可降低整体复杂度至 O(E * logV * f)
    int i, j, p, u = 0;
    typec md, cw;
    for (i = 0; i < v; i++)
    {
        dis[i] = infc;
    }
    dis[s] = 0;
    prev[s] = 0;
    pre[s] = -1;
    memset(vis, 0, v * sizeof(int));
    for (i = 1; i < v; i++)
    {
        for (md = infc, j = 0; j < v; j++)
        {
            if (!vis[j] && md > dis[j])
            {
                md = dis[j];
                u = j;
            }
        }
        if (md == infc)
        {
            break;
        }
        for (vis[u] = 1, j = (int)net[u].size() - 1; j >= 0; j--)
        {
            edge *ce = net[u][j];
            if (ce->cap(u) > 0)
            {
                p = ce->other(u);
                cw = ce->ecost(u) + phi[u] - phi[p];
                //  !!  assert(cw >= 0);
                if (dis[p] > dis[u] + cw)
                {
                    dis[p] = dis[u] + cw;
                    prev[p] = ce;
                    pre[p] = u;
                }
            }
        }
    }
    return infc != dis[t];
}

typec network::mincost(int ss, int tt)
{
    s = ss;
    t = tt;
    int i, c;
    typef ex;
    flow = cost = 0;
    memset(phi, 0, sizeof(phi));
    //  !!  若原图含有负消费的边, 在此处运行Bellmanford
    //  将phi[i](0 <= i <= n - 1)置为mindist(s, i).
    for (i = 0; i < v; i++)
    {
        net[i].clear();
    }
    for (i = (int)eg.size() - 1; i >= 0; i--)
    {
        net[eg[i].u].push_back(&eg[i]);
        net[eg[i].v].push_back(&eg[i]);
    }
    while (dijkstra())
    {
        for (ex = inff, c = t; c != s; c = pre[c])
        {
            if (ex > prev[c]->cap(pre[c]))
            {
                ex = prev[c]->cap(pre[c]);
            }
        }
        for (c = t; c != s; c = pre[c])
        {
            prev[c]->addFlow(pre[c], ex);
        }
        flow += ex;
        cost += ex * (dis[t] + phi[t]);
        for (i = 0; i < v; i++)
        {
            phi[i] += dis[i];}
    }
    return cost;
}

void network::build(int nv, int ne)
{
    eg.clear();
    v = nv;
    int x, y;
    typef f;
    typec c;
    for (int i = 0; i < ne; ++i)
    {
        cin >> x >> y >> f >> c;
        eg.push_back(edge(x, y, f, 0, c));
    }
    return ;
}