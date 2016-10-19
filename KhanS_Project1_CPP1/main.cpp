//Name:Shameer Khan
//cs-323 project 1.1

#include<iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

class listNode{
	friend class linkedList;

	private:
		string data;
		int count;
		listNode *next;

	public:
		listNode(){};
		listNode(string d){
			data=d;
			count=0;
			next=NULL;
		}

};

class linkedList{
	private:
		listNode *listhead;
	public:
		linkedList(string s){
			listhead=new listNode(s);
		}
		listNode* findSpot(string s){
			listNode *spot= listhead;
			while(spot->next!=NULL && compare(spot->next->data,s)<0){
				spot=spot->next;
			}
			return spot;
		}

		void listinsert(listNode *n, listNode *p){
			p->next=n->next;
			n->next=p;
		}
		void print(ostream &os,string s){
			listNode *current=listhead;
			os<<"Data Inserted("<<s << "):"<<endl;
			os<<"ListHead -->";
			while(current!=NULL){
				if(current->next==NULL)
				os<<"("<<current->data<<", NULL)-->NULL";
			else
				os<<"("<<current->data<<","<<current->next->data<<")-->";
			current=current->next;
			}
			os<<endl<<endl;
		}
		int compare(string prev, string next){
			string temp1=prev;
			string temp2 =next;

			for(int i=0; i<prev.size();i++)
				temp1[i]=tolower(temp1[i]);
			for(int i=0;i<next.size();i++)
				temp2[i]=tolower(temp2[i]);
			return (temp1.compare(temp2));
	}
};

int main(int argc, char* argv[]){
	if(argc<3){
		cout<<"no file";
		exit(-1);
	}
	fstream infile;
	linkedList L("dummy");
	infile.open(argv[1]);
	ofstream outfile(argv[2]);
	string s;
	while(infile>>s){
            listNode *n= new listNode(s);
            L.listinsert(L.findSpot(s),n);
            L.print(outfile,s);
    }
    infile.close();
    outfile.close();
}
