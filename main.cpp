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
		listNode* findSpot(listNode *head,string s){
			listNode *spot= head;
			while(spot->next!=NULL && compare(spot->next->data,s)<=0){
				spot=spot->next;
			}
			if(spot->data.compare(s)==0){
			spot->count++;
			return NULL;
			}
			return spot;
		}

		void listinsert(listNode *spot, listNode *newnode){
			newnode->next=spot->next;
			spot->next=newnode;
		}
		void debugPrint(ostream &os,listNode *head){
			listNode *current=head;
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
	bool iscommonWord(listNode *head, string text){
	    listNode *current=head;
	    while(current!=NULL){
            if(compare(current->data,text)==0)
                return true;
            current=current->next;
	    }
	    return false;
	}

	void printSortedList(ostream &out, listNode *head){
	    listNode *current=head->next;
	    while(current!=NULL){
            out<<current->data<<" "<<current->count<<endl;
            current=current->next;
	    }
	}

	listNode* getlistHead(){
	    return listhead;
	}
};

int main(int argc, char* argv[]){
	if(argc<3){
		cout<<"no file";
		exit(-1);
	}
	fstream infile;
	linkedList commonWordlist("dummy");
	linkedList textWordlist("dummy");
	infile.open(argv[1]);
	ofstream outfile(argv[3]);
	fstream infile2;
	infile2.open(argv[2]);
	ofstream outfile2(argv[4]);
	string s;
	while(infile>>s){
            listNode *n= new listNode(s);
           listNode *spot= commonWordlist.findSpot(commonWordlist.getlistHead(),s);
            commonWordlist.listinsert(spot,n);
            outfile<<"inserted data ("<<s<<")"<<endl;
            commonWordlist.debugPrint(outfile,commonWordlist.getlistHead());
    }
    string j;
    int insertCount=0;
    while(infile2>> j){
            if(commonWordlist.iscommonWord(commonWordlist.getlistHead(), j)==true){
                    continue;
            }
            else if(commonWordlist.iscommonWord(commonWordlist.getlistHead(), j)==false){
                listNode *Spot= textWordlist.findSpot(textWordlist.getlistHead(),j);
                if(Spot!=NULL){
                    listNode *newNode= new listNode(j);
                    textWordlist.listinsert(Spot, newNode);
                    insertCount++;
                    if(insertCount>=5){
                        commonWordlist.debugPrint(outfile,commonWordlist.getlistHead());
                        insertCount=0;
                    }
                }
            }
        }
    textWordlist.printSortedList(outfile2,textWordlist.getlistHead());
    infile.close();
    outfile.close();
    infile2.close();
    outfile2.close();
    return 0;
}
