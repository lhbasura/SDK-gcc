#include "deploy.h"
#include "lib/lib_io.h"
#include<string.h>
#include<iostream>
using namespace std;

struct Edge
{
    int width;
    int cost;
    bool is_connect= false;
};
struct Cost_Edge
{
    int need;
    int net_id;
};
//你要完成的功能总入口
void deploy_server(char * topo[MAX_EDGE_NUM], int line_num,char * filename) {

    int vex_num;//网络节点数量
    int edge_num;//网络链路数量
    int consume_num;//消费节点数量
    int one_sever_cost;//一台视频内容服务器部署成本
    Edge **net_matrix;  //邻接矩阵
    Cost_Edge *need;        //需要的带宽

    char *p;
    vex_num = atoi(strtok_r(topo[0], " ", &p));
    edge_num = atoi(strtok_r(p, " ", &p));
    consume_num = atoi(p);
    one_sever_cost = atoi(topo[2]);
   /* cout << vex_num << endl;
    cout << edge_num << endl;
    cout << consume_num << endl;
    cout << one_sever_cost<<endl;*/
    net_matrix = new Edge *[edge_num];
    need=new Cost_Edge[consume_num];
    for(int i=0;i<vex_num;i++)
    {
        net_matrix[i]=new Edge[vex_num];
    }
    for(int i=4;i<edge_num+4;i++)
    {
        int begin=atoi(strtok_r(topo[i]," ",&p));
        int end=atoi(strtok_r(p," ",&p));
        int width=atoi(strtok_r(p," ",&p));
        int cost=atoi(p);
       // cout<<begin<<" "<<end<<endl;
        net_matrix[begin][end].width=width;
        net_matrix[begin][end].cost=cost;
        net_matrix[begin][end].is_connect= true;

        net_matrix[end][begin].width=width;
        net_matrix[end][begin].cost=cost;
        net_matrix[end][begin].is_connect= true;
    }
    for(int i=edge_num+5;i<consume_num+edge_num+5;i++)
    {
        int consume_id=atoi(strtok_r(topo[i]," ",&p));
        int net_id=atoi(strtok_r(p," ",&p));
        int width=atoi(p);
        need[consume_id].net_id=net_id;
        need[consume_id].need=width;
    }

    string output=to_string(consume_num);
    output+="\n\n";
    for(int i=0;i<consume_num;i++)
    {
        output+=to_string(need[i].net_id)+" "+to_string(i)+" "+to_string(need[i].need)+"\n";
    }

    cout<< output;
    const char *topo_file = output.c_str();
            // 需要输出的内容
   // char *topo_file = (char *) "17\n\n0 8 0 20\n21 8 0 20\n9 11 1 13\n21 22 2 20\n23 22 2 8\n1 3 3 11\n24 3 3 17\n27 3 3 26\n24 3 3 10\n18 17 4 11\n1 19 5 26\n1 16 6 15\n15 13 7 13\n4 5 8 18\n2 25 9 15\n0 7 10 10\n23 24 11 23";

    // 直接调用输出文件的方法输出到指定文件中(ps请注意格式的正确性，如果有解，第一行只有一个数据；第二行为空；第三行开始才是具体的数据，数据之间用一个空格分隔开)
    write_result(topo_file, filename);
}
/*
int main() {
    char *topo[MAX_EDGE_NUM];
    char *topo_file="/home/cust/Desktop/case0.txt";
  //  cout << "enter input file" << endl;
  //  cin >> topo_file;
   // cout << "eter result file" << endl;
  //  cin >> result_file;
    int line_num = read_file(topo, MAX_EDGE_NUM, topo_file);
    deploy_server(topo, line_num, "/home/cust/Desktop/resut.txt");
    return 0;
}*/