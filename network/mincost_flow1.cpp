/*
 *  最小费用流 O(V * E * f)
 *  INIT: network g; g.build(v, e);
 *  CALL: g.mincost(s, t); flow=g.flow; cost=g.cost;
 *  注意: SPFA增广, 实际复杂度远远小于O(V * E);
 */
#define typef int               //  type of flow
#define typec int               //  type of dis
const typef inff = 0x3f3f3f3f;  //  max of flow
const typec infc = 0x3f3f3f3f;  //  max of dis
const int E = 10010;
const int N = 1010;

struct network
{
    int nv, ne, pnt[E], nxt[E];
    int vis[N], que[N], head[N], pv[N], pe[N];
    typef flow, cap[E];
    typec cost, dis[E], d[N];
    void addedge(int u, int v, typef c, typec w)
    {
        pnt[ne] = v;
        cap[ne] = c;
        dis[ne] = +w;
        nxt[ne] = head[u];
        head[u] = (ne++);
        pnt[ne] = u;
        cap[ne] = 0;
        dis[ne] = -w;
        nxt[ne] = head[v];
        head[v] = (ne++);
    }
    int mincost(int src, int sink)
    {
        int i, k, f, r;
        typef mxf;
        for (flow = 0, cost = 0; ;)
        {
            memset(pv, -1, sizeof(pv));
            memset(vis, 0, sizeof(vis));
            for (i = 0; i < nv; ++i)
            {
                d[i] = infc;
            }
            d[src] = 0;
            pv[src] = src;
            vis[src] = 1;
            for (f = 0, r = 1, que[0] = src; r != f;)
            {
                i = que[f++];
                vis[i] = 0;
                if (N == f)
                {
                    f = 0;
                }
                for (k = head[i]; k != -1; k = nxt[k])
                {
                    if(cap[k] && dis[k]+d[i] < d[pnt[k]])
                    {
                        d[pnt[k]] = dis[k] + d[i];
                        if (0 == vis[pnt[k]])
                        {
                            vis[pnt[k]] = 1;
                            que[r++] = pnt[k];
                            if (N == r)
                            {
                                r = 0;
                            }
                        }
                        pv[pnt[k]] = i;
                        pe[pnt[k]] = k;
                    }
                }
            }
            if (-1 == pv[sink])
            {
                break;
            }
            for (k = sink, mxf = inff; k != src; k = pv[k])
            {
                if (cap[pe[k]] < mxf)
                {
                    mxf = cap[pe[k]];
                }
            }
            flow += mxf;
            cost += d[sink] * mxf;
            for (k = sink; k != src; k = pv[k])
            {
                cap[pe[k]] -= mxf;
                cap[pe[k] ^ 1] += mxf;
            }
        }
        return cost;
    }

    void build(int v, int e)
    {
        nv = v;
        ne = 0;
        memset(head, -1, sizeof(head));
        int x, y;
        typef f;
        typec w;
        for (int i = 0; i < e; ++i)
        {
            cin >> x >> y >> f >> w;    //  vertex: 0 ~ n-1
            addedge(x, y, f, w);        //  add arc (u->v, f, w)
        }
    }
} g;