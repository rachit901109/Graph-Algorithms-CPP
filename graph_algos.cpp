#include<bits/stdc++.h>
using namespace std;
typedef std::multimap<int,std::pair<int,int>>::iterator MMPIT;
#define max 50

// to initialise arrays use "memset" rather than int arr[r][c]={0} but https://www.quora.com/Why-memset-in-c++-work-only-for-1-and-0   
// Better use std::fill instead

class Graph
{
    public:
    int no_nodes;
    int adj_mat[max][max];
    multimap<int,pair<int,int>> edge_list;
    Graph(int n)
    {
        no_nodes = n;
        memset(adj_mat,0,sizeof(adj_mat));
        // for(int i =0;i<no_nodes;i++)
        // {
        //     for(int j=0;j<no_nodes;j++)
        //     {
        //         adj_mat[i][j]=0;
        //     }
        // }   
    }

    void add_edge(int src,int des,int weight,bool dir)
    {
        adj_mat[src][des] = weight;
        edge_list.insert({src,{des,weight}});
        if(dir)
        {adj_mat[des][src] = weight;edge_list.insert({des,{src,weight}});}
    }

    void show_graph() 
    {
        cout << "Adjacency Matrix:" << endl;
        cout <<"\t";
        for (int i = 0; i < no_nodes; i++) {
            cout << " " << i<<"\t";
        }
        cout << endl;
        for (int i = 0; i < no_nodes; i++) {
            cout << " " << i << "\t";
            for (int j = 0; j < no_nodes; j++) {
                cout << " " << adj_mat[i][j]<<"\t";
            }
            cout << endl;
        }
        cout<<"--------------------------------------------------------------------------------------------------------------------------------\n";
    }

    void show_edgelist()
    {
        cout<<"Edgelist:-\n";
        MMPIT lit;
        lit=edge_list.begin();
        cout<<"Src\tDes\tCost\n";
        while(lit!=edge_list.end())
        {
            cout<<lit->first<<"\t"<<lit->second.first<<"\t"<<lit->second.second<<"\n";
            lit++;
        }
        cout<<"--------------------------------------------------------------------------------------------------------------------------------\n";
    }

    void bfs(int s)
    {
        cout<<"BFS traversal from node "<<s<<" :-\n"; 
        int visited[no_nodes]={0};
        vector<int> bfs_queue;
        visited[s]=1;
        bfs_queue.push_back(s);
        while (bfs_queue.size()!=0)
        {        
            for(int i =0;i<no_nodes;i++)
            {
                if(adj_mat[s][i]!=0 && visited[i]==0)
                {bfs_queue.push_back(i);visited[i]=1;}
            }
            cout<<bfs_queue[0]<<" ";
            bfs_queue.erase(bfs_queue.begin());
            s=bfs_queue[0];
        }
        cout<<endl;
        cout<<"--------------------------------------------------------------------------------------------------------------------------------\n";
    }

    void dfs_traversal(int s,int* visited)
    {
        cout<<s<<" ";
        visited[s]=1;
        for(int i=0;i<no_nodes;i++)
        {
            if(adj_mat[s][i]!=0 && visited[i]==0)
            {visited[i]=1;dfs_traversal(i,visited);}
        }
    }

    void dfs(int s)
    {
        cout<<"DFS Traversal from "<<s<<" :-\n";
        int visited[no_nodes]={0};
        dfs_traversal(s,visited);
        cout<<endl;
        cout<<"--------------------------------------------------------------------------------------------------------------------------------\n";
    }

    bool bfs_search(int s,int d,vector<int> &bfs_path)
    {
        int visited[no_nodes]={0};
        visited[s]=1;
        vector<int> bfs_queue;
        bfs_queue.push_back(s);
        bfs_path.push_back(s);
        while (bfs_queue.size()!=0)
        {        
            for(int i =0;i<no_nodes;i++)
            {
                if(visited[d]==1)
                {return true;}
                if(adj_mat[s][i]!=0 && visited[i]==0)
                {bfs_queue.push_back(i);bfs_path.push_back(i);visited[i]=1;}
            }
            bfs_queue.erase(bfs_queue.begin());
            s=bfs_queue[0];
        }
        return false;
    }

    bool dfs_limited(int s,int d,int limit,int* visited)
    {
        if(s == d)
        {return true;}
        if(limit<=0)
        {return false;}
        visited[s]=1;
        for(int i=0;i<no_nodes;i++)
        {
            if(adj_mat[s][i]!=0 && visited[i]==0)
            {
                visited[i]=1;
                if(dfs_limited(i,d,limit-1,visited) == true)
                {return true;}
            }
        }    
        return false;
    }

    // Iterative deepning search IDS https://en.wikipedia.org/wiki/Iterative_deepening_depth-first_search
    bool ids(int s,int d,int limit)
    {
        int visited[no_nodes];
        for(int i =0;i<=limit;i++)
        {
            fill(visited,visited+no_nodes,0);
            if(dfs_limited(s,d,i,visited) == true)
            {return true;}
        }
        return false;
    }

    void prims()
    {
        int vistited[no_nodes]={0};
        set<int> nodes;
        multimap<int,pair<int,int>> prims_edgelist;
        int prims_mat[no_nodes][no_nodes];
        // int prims_mat[no_nodes][no_nodes]={0};
        memset(prims_mat,0,sizeof(prims_mat));
        int minw = INT_MAX;
        int s,d;
        int mincost=0;
        for(int i=0;i<no_nodes;i++)
        {
            for(int j=0;j<no_nodes;j++)
            {
                if(minw>adj_mat[i][j] && adj_mat[i][j]!=0)
                {minw=adj_mat[i][j];s=i;d=j;}
            }
        }
        prims_edgelist.insert({s,{d,minw}});
        prims_mat[s][d]=minw;prims_mat[d][s]=minw;
        vistited[s]=1;vistited[d]=1;
        nodes.insert(s);nodes.insert(d);
        mincost+=minw;
        while(nodes.size()!=no_nodes)
        {
            minw=INT_MAX;
            for(int i=0;i<no_nodes;i++)
            {
                for(int c=0;c<no_nodes;c++)
                {
                    if(vistited[i]==1 && minw>adj_mat[i][c] && adj_mat[i][c]!=0 && nodes.find(c)==nodes.end())
                    {minw=adj_mat[i][c];s=i;d=c;}
                }
            }
        prims_edgelist.insert({s,{d,minw}});
        prims_mat[s][d]=minw;prims_mat[d][s]=minw;
        vistited[s]=1;vistited[d]=1;
        nodes.insert(s);nodes.insert(d);
        mincost+=minw;
        }

    
    cout<<"MST - Edgelist:-\n";
    MMPIT lit;
    lit=prims_edgelist.begin();
    cout<<"Src\tDes\tCost\n";
    while(lit!=prims_edgelist.end())
    {
        cout<<lit->first<<"\t"<<lit->second.first<<"\t"<<lit->second.second<<"\n";
        lit++;
    }

    cout<<"MST - Adjacency Matrix:-\n";
    cout <<"\t";
    for (int i = 0; i < no_nodes; i++) {
        cout << " " << i<<"\t";
    }
    cout << endl;
    for (int i = 0; i < no_nodes; i++) {
        cout << " " << i << "\t";
        for (int j = 0; j < no_nodes; j++) {
            cout << " " << prims_mat[i][j]<<"\t";
        }
        cout << endl;
    }

    cout<<"Cost of MST:- "<<mincost<<" \n";
    cout<<"--------------------------------------------------------------------------------------------------------------------------------\n";
    }

    void dijkstras(int s)
    {
        multimap<int,pair<int,int>> dj_edgelist;
        int visited[no_nodes]={0};
        int mincost[no_nodes];
        fill(mincost,mincost+no_nodes,INT_MAX);
        mincost[s]=0;
        int src = s;
        for(int i=0;i<no_nodes;i++)
        {
            int cost=INT_MAX;
            for(int j=0;j<no_nodes;j++)
            {
                if(adj_mat[s][j]!=0 && mincost[j]>mincost[s]+adj_mat[s][j])
                {mincost[j]=mincost[s]+adj_mat[s][j];}
            }
            visited[s]=1;
            for(int k =0;k<no_nodes;k++)
            {
                if(visited[k]==0 && mincost[k]<cost)
                {cost=mincost[k];s=k;}
            }
        }

        for(int i=0;i<no_nodes;i++)
        {
            dj_edgelist.insert({src,{i,mincost[i]}});
        }

    cout<<"Dijkstras algorithm from source "<<src<<":-\n";
    MMPIT lit;
    lit=dj_edgelist.begin();
    cout<<"Src\tDes\tCost\n";
    while(lit!=dj_edgelist.end())
    {
        cout<<lit->first<<"\t"<<lit->second.first<<"\t"<<lit->second.second<<"\n";
        lit++;
    }
    cout<<"--------------------------------------------------------------------------------------------------------------------------------\n";
    }

    void warshalls()
    {
        cout<<"All source shortest path Floyd-Warshalls Algorithm:-\n";
        int warshall_mat[no_nodes][no_nodes];
        for(int i=0;i<no_nodes;i++)
        {
            for(int j=0;j<no_nodes;j++)
            {
                if(i!=j and adj_mat[i][j]==0)
                {warshall_mat[i][j]=INT16_MAX;}
                else{warshall_mat[i][j]=adj_mat[i][j];}
            }
        }

        for(int k=0;k<no_nodes;k++)
        {
            for(int i=0;i<no_nodes;i++)
            {
                for(int j=0;j<no_nodes;j++)
                {
                    if(i!=k && j!=k && warshall_mat[i][j]!=0 && warshall_mat[i][j]>warshall_mat[i][k]+warshall_mat[k][j])
                    {warshall_mat[i][j] = warshall_mat[i][k]+warshall_mat[k][j];}
                }
            }
        }

    cout <<"\t";
    for (int i = 0; i < no_nodes; i++) {
        cout << " " << i<<"\t";
    }
    cout << endl;
    for (int i = 0; i < no_nodes; i++) {
        cout << " " << i << "\t";
        for (int j = 0; j < no_nodes; j++) {
            cout << " " << warshall_mat[i][j]<<"\t";
        }
        cout << endl;
    }
        cout<<"--------------------------------------------------------------------------------------------------------------------------------\n";
    }
    /*
    1.call check cycle for every node 2.which basically runs dfs for each node.
    3.by travelling depth first if we visited parent again we detected a cycle
    */
    bool check_cycle_undir(int s,int parent,int* visited)
    {
        visited[s]=1;
        for(int i =0;i<no_nodes;i++)
        {
            if(adj_mat[s][i]!=0 && visited[i]==0)
            {
                if(check_cycle_undir(i,s,visited))
                {return true;}
            }
            // base cond. if graph has cycle then visited adj node of current node is not its parent - https://www.youtube.com/watch?v=zQ3zgFypzX4
            else if(adj_mat[s][i]!=0 && visited[i]==1 && i!=parent)
            {return true;}
        }
    return false;
    }

    bool has_cycle(bool dir)
    {
        int visited[no_nodes];
        fill(visited,visited+no_nodes,0);
        bool ans;
        if(dir)
        {

        }
        else
        {
            for(int i =0;i<no_nodes;i++)
            {
                if(visited[i]==0)
                {
                    if(check_cycle_undir(i,-1,visited))
                    {return true;}
                }
            }
        }
    return false;
    }
};




int main()
{
    cout<<"--------------------------------------------------------------------------------------------------------------------------------\n\n";
    Graph mygraph(9);
    mygraph.add_edge(0,1,4,true);
    mygraph.add_edge(0,7,8,true);
    mygraph.add_edge(1,7,11,true);
    mygraph.add_edge(1,2,8,true);
    mygraph.add_edge(7,8,7,true);
    mygraph.add_edge(7,6,1,true);
    mygraph.add_edge(2,8,2,true);
    mygraph.add_edge(2,3,7,true);
    mygraph.add_edge(2,5,4,true);
    mygraph.add_edge(8,6,6,true);
    mygraph.add_edge(6,5,2,true);
    mygraph.add_edge(3,5,14,true);
    mygraph.add_edge(3,4,9,true);
    mygraph.add_edge(5,4,10,true);

    // Graph mygraph(5);
    // mygraph.add_edge(0,1,2,true);
    // mygraph.add_edge(0,3,6,true);
    // mygraph.add_edge(1,2,3,true);
    // mygraph.add_edge(1,3,8,true);
    // mygraph.add_edge(1,4,5,true);
    // mygraph.add_edge(2,4,7,true);
    // mygraph.add_edge(3,4,9,true);

    // no cycle undir
    // Graph mygraph(4);
    // mygraph.add_edge(0,1,1,true);
    // mygraph.add_edge(1,2,1,true);
    // mygraph.add_edge(2,3,1,true);

    mygraph.show_graph();
    // mygraph.show_edgelist();
    // mygraph.bfs(3);
    // mygraph.dfs(3);
    // mygraph.prims();
    // mygraph.dijkstras(0);
    // if(mygraph.ids(0,3,3))
    // {cout<<"Destination is reachable from source at given depth."<<endl;}
    // else{cout<<"Destination is not reachable from source at given depth."<<endl;}
    // cout<<"--------------------------------------------------------------------------------------------------------------------------------\n\n";

    // vector<int> bfs_path;
    // if(mygraph.bfs_search(0,1,bfs_path))
    // {
    //     cout<<"Destination found from source.\nPath:- ";
    //     for(auto& itv:bfs_path)
    //     {cout<<itv<<" ";}
    //     cout<<endl;
    // }
    // else{cout<<"Destination not found."<<endl;}
    // cout<<"--------------------------------------------------------------------------------------------------------------------------------\n\n";

    // mygraph.warshalls();

    cout<<mygraph.has_cycle(false)<<endl;
    return 0;
}