#include "Tabu.h"
//vector<vector <int> > ivec(m ,vector<int>(n,0)); //m*n�Ķ�άvector������Ԫ�س�ʼ��Ϊ0
using namespace std;
Tabu::Tabu(){}
Tabu::Tabu(vector <Nodes> &Node)
{

	Sc = 0;
	numNode = Node.size();
    

    vector <vector <int>> Table (numNode,vector<int >(numNode,0));//���ɱ��ʼ��
    /* Table.resize(numNode);
    for (int i = 0; i != numNode; i++) {
        Table[i].resize(numNode) ;
    }*/
    vector <vector <int>> F(2, vector<int>(numNode, 0));
    vector <vector <int>> D(2, vector<int>(numNode, 0));
   
    adjDic=distance;
	for (int j = 0; j != 2; j++) {
		for (int i = 0; i !=Node.size(); i++) {
			F[j].push_back(0);
			D[j].push_back(0);//P��D���ʼ��
		}
	}
	
}
void Tabu::compDic(vector <Nodes> &Node, int &numNode) {//�������
    vector <vector <double>> distance(numNode, vector <double>(numNode, 0));
   // distance[numNode][numNode];
    for (int i = 0; i != Node.size() - 1; i++) {
        for (int j = i + 1; j != Node.size(); j++) {
            distance[Node[i].id][Node[j].id] = sqrt(double(abs(Node[i].x - Node[j].x) + abs(Node[i].y - Node[j].y)));
            distance[Node[j].id][Node[i].id] = distance[Node[i].id][Node[j].id];
            if (i == j) {
                distance[Node[i].id][Node[j].id] = 0;
            }
        }
    }
}
void Tabu::init(vector <Nodes> &Node) {
    pcenter.push_back(rand() % numNode - 1);
	//pcenter[0]=rand()% numNode-1;
	int longestN;
	//for (int i = 0; i != numNode; i++) {
	//	if(pcenter[0]!=i)
	//		PtoNode[0].push_back = Node[i].id;//1��Ӧ�����ĵ���p[1]
	//}
	longestN = initfuncation(Node,pcenter);
	for (int i = 1; i !=numPcenter; i++) {
		int tempP=findP(Node,longestN);
        initDandFtable(Node, tempP);
		//updatePtoNode(Node,tempP);
        pcenter.push_back(tempP);
       // pcenter[i] = tempP;
		longestN = initfuncation(Node, pcenter);

	}
}

//void Tabu::updatePtoNode(vector <Nodes> &Node,int nextP) {
//	for(int j=0;j!=pcenter.size();j++)
//		for (int i = 0; i != numNode; i++) {
//			if (adjDic[pcenter[j]][Node[i].id] > adjDic[nextP][Node[i].id])
//				PtoNode[pcenter.size() + 1][i] = Node[i].id;
//			else PtoNode[pcenter.size() + 1][i] = -1;
//		}
//}

int Tabu::findP(vector <Nodes> &Node, int longestN) {
	vector <int> id;
	int tempP;
	for (int i = 0; i != numNode; i++) {
		if (adjDic[longestN][Node[i].id] < Sc) {
			id.push_back(Node[i].id);
		}
	}
	srand(time(0));
	int tempi = rand() % id.size() - 1;
	tempP = id[tempi];
	return tempP;
}

void Tabu::initDandFtable(vector <Nodes> &Node,int tempP) {

    for (int j = 0; j != numNode; j++) {
        if (pcenter.size() == 1) {
            if (adjDic[pcenter[0]][Node[j].id] < adjDic[tempP][Node[j].id]) {
                D[Node[j].id][0] = adjDic[pcenter[0]][Node[j].id];
                F[Node[j].id][0] = pcenter[0];
                D[Node[j].id][1] = adjDic[tempP][Node[j].id];
                F[Node[j].id][1] = tempP;
            } else {
                D[Node[j].id][0] = adjDic[tempP][Node[j].id];
                F[Node[j].id][0] = tempP;
                D[Node[j].id][1] = adjDic[pcenter[0]][Node[j].id];
                F[Node[j].id][1] = pcenter[0];
            }
        } else {

            if (adjDic[tempP][Node[j].id] < D[Node[j].id][0]) {
                D[Node[j].id][1] = D[Node[j].id][0];
                F[Node[j].id][1] = F[Node[j].id][0];
                D[Node[j].id][0] = adjDic[tempP][Node[j].id];
                F[Node[j].id][0] = tempP;

            } else if (adjDic[tempP][Node[j].id] < D[Node[j].id][1]) {
                D[Node[j].id][1] = adjDic[tempP][Node[j].id];
                F[Node[j].id][1] = tempP;
            }

        }
    }
}

int Tabu::initfuncation(vector <Nodes> &Node,vector <int> pcenter) {
	int tempid1 = 0;//��¼Ѱ�ҹ�����Ŀ�꺯����
	int tempid2 = 0;
	double tempSc = 0;
	for (int i = 0; i != pcenter.size(); i++) {
		for (int j = 0; j != numNode; j++) {
			if (pcenter[i] !=Node[j].id && tempSc< adjDic[pcenter[i]][Node[j].id]) {
				tempSc = adjDic[pcenter[i]][Node[j].id];
				tempid1 = pcenter[i];
				tempid2 = Node[j].id;
			}
		}
	}
	Sc = tempSc;
    ScPoint.Noden = tempid2;
    ScPoint.Nodep = tempid1;
	return tempid2;
}


void Tabu::tabusearch(vector <Nodes> &Node) {
    int longestN;
    init(Node);//��ʼ��
    int iter;//��������
    longestN = initfuncation(Node, pcenter);
    while (iter<10000)//��������
    {
    }
   

}
//int Tabu::fine_move(vector <Nodes> &Node) {
//	int f;
//    int delt = 0;
//	return f;//�����ķ����
//}

int Tabu::findadd_facility(vector <Nodes> &Node) {
    int f=ScPoint.Noden;
    vector <int > Newf;
    for (int i = 0; i != numNode; i++) {
        if (adjDic[f][Node[i].id] < Sc) {
            Newf.push_back(Node[i].id);
        }
    }
    
}


void Tabu::add_facility(vector <Nodes> &Node,int f) {//������,f�����
    for (int i = 0; i != numNode; i++) {
        if (D[Node[i].id][0] > adjDic[f][Node[i].id]) {
            D[Node[i].id][1] = D[Node[i].id][0];
            F[Node[i].id][1] = F[Node[i].id][0];
            D[Node[i].id][0] = adjDic[f][i];
            F[Node[i].id][0] = f;

        }
        else if (D[Node[i].id][1] > adjDic[f][i]) {
            D[Node[i].id][1] = adjDic[f][Node[i].id];
            F[Node[i].id][1] = f;
        }

    }
    pcenter.push_back(f);
    //pcenter[numPcenter + 1] = f;
}

int Tabu::findremove_facility(vector <Nodes> &Node,int f) {//ǰp����������ҵ�һ��ɾ������������������С�ĵ�ɾ(���ɲ����ҽ�����<f,i>��
    vector <int> Mf(numPcenter,0);
    double tempSc=0;
    int tempScid;
    for (int j = 0; j != numPcenter; j++) {
        for (int i = 0; i != numNode; i++) {
            if (F[Node[i].id][0] == pcenter[j]&& Mf[j] < D[Node[i].id][1]) {
                Mf[j] = D[Node[i].id][1];
            }
        }
    }   
    tempSc = Mf[0];
    for (int j = 1; j != numPcenter; j++) {
        if (tempSc>Mf[j]) {
            tempSc = Mf[j];
            tempScid = j;
        }
        else if(tempSc == Mf[j]) {
            if (rand() % 2 == 0) {//���ʱ�����ѡ��
                tempSc = Mf[j];
                tempScid = j;
            }
        }
    }
    int i = pcenter[tempScid];
    //����Sc
    if (tempSc > Sc) Sc = tempSc;
    return i;
    //return tempScid;//�ҵ�ɾ�����������е�λ��
}

void Tabu::remove_facility(vector <Nodes> &Node,int f) {
    int tempPlace;
    for (int j = 0; j != pcenter.size(); j++) {
        if (pcenter[j] == f) tempPlace = j;
    }
    //int f = pcenter[tempPlace];
    
    for (int i = 0; i != numNode; i++) {
        if (F[Node[i].id][0] = f) {
            D[Node[i].id][0] = D[Node[i].id][1];
            F[Node[i].id][0] = F[Node[i].id][1];
            int nextp=find_next(Node,Node[i].id,tempPlace);
            D[Node[i].id][1] = adjDic[nextp][i];
            F[Node[i].id][1] = nextp;
            
        }
        else if (F[Node[i].id][1] = f) {
            int nextp=find_next(Node, Node[i].id,tempPlace);
            D[Node[i].id][1] = adjDic[nextp][i];
            F[Node[i].id][1] = nextp;
        }
    }
    pcenter[tempPlace] = pcenter[numPcenter + 1];
    pcenter[numPcenter + 1] = -1;
}
/*MfΪɾ���ڵ�f������������߾��루���ǵ�ǰ��ʷ����룩��
�Ա����з����ɾ���������Mf��ѡ����С��ɾ�����Ӧ�ĵ�,
����F��D�����
*/


int Tabu::find_next(vector <Nodes> &Node, int v,int fplace) {
    double tempsecondmax = max;
    int tempsecondmaxP;
    for (int j = 0; j != numPcenter+1; j++) {
        if (j != fplace && pcenter[j]!=F[v][pcenter[j]]&&tempsecondmax<adjDic[pcenter[j]][v]) {
            tempsecondmax = adjDic[pcenter[j]][v];
            tempsecondmaxP = pcenter[j];
        }
    }
    return tempsecondmaxP;
}


void Tabu::find_pair(vector <Nodes> &Node,int f) {
    
	add_facility(Node,f);//fΪ��ӵķ����
    int i=findremove_facility(Node,f);
	remove_facility(Node,i);//iΪɾ���ķ����
}

Tabu::~Tabu()
{

}
