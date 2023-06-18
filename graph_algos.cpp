#include<bits/stdc++.h>
using namespace std;
typedef std::multimap<int,std::pair<int,int>>::iterator MMPIT;
#define max 50

// to initialise a 2d array of all zeros use "memset" rather than int arr[r][c]={0}

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
        // cout<<"Updated mat at "<<s<<" "<<d<<" to "<<minw<<endl;
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
        // cout<<"Updated mat"<<s<<" "<<d<<"to "<<minw<<endl;
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
    }
};




int main()
{
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

    mygraph.show_graph();
    mygraph.show_edgelist();
    mygraph.bfs(3);
    mygraph.dfs(3);
    mygraph.prims();
    return 0;
}