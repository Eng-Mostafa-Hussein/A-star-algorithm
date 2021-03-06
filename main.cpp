    #include <stdlib.h>
    #include <iostream>
    #include <stdio.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <string.h>
    #include <arpa/inet.h>
//    #include <unistd.h>
    #define PORT 4000
    using namespace std;

    struct link
    {
        int id;
        int f;
        int g;
        int h;
        int x;
        int y;
        link* next;
        link* prev;
        link* parent;

    };
    class linklist
    {
        private:
            link * first;
            link * end;

        public:

            int count;
            linklist()
            {
                first = NULL;
                end =NULL;
                count=0;
            }

            link* get (int id)
            {
                link* current=first;
                while (current!=NULL) {
                    if (current->id == id) {
                        return current;
                    }
                    current = current->next;
                    break;
                }
            }

            void getpath(int path[][3])
            {
                int c=0;
                link* current=first;
                path[0][0]=c;
                while(current !=NULL )
                {
                    path[0][0]= ++c ;
                    path[c][0]=current->x;
                    path[c][1]=current->y;

                    cout<<path[c][0]<<"\t"<<path[c][1]<<endl;
                    current=current->parent;
                }

            }

            void check1 (int child[][5])   //open list 3
            {
                for (int i = 1; i <=child[0][0] ; ++i) {
                    link* current = first;
                    while (current!=NULL)
                    {
                        if( child[i][0]==current->x  && child[i][1]==current->y &&  current->f < child[i][2] )
                            child[i][3]=0;
                        else
                            child[i][3]=1;

                        current=current->next;
                    }

                }

            }

            void check2 (int child[][5])   //closed list 4
            {
                for (int i = 1; i <=child[0][0] ; ++i) {
                    link* current = first;
                    while (current!=NULL)
                    {
                        if( child[i][0]==current->x  && child[i][1]==current->y &&  current->f <child[i][2] )
                            child[i][4]=0;
                        else
                            child[i][4]=1;

                        current=current->next;
                    }

                }

            }

            void additem(int g,int h,int x,int y,link* p)
            {
                count++;

                if ( first == NULL && end==NULL )
                {
                    link* newlink = new link;
                    newlink->id= count;
                    newlink->x = x;
                    newlink->y = y;
                    newlink->g = g;
                    newlink->h = h;
                    newlink->parent=p;
                    newlink->f=g+h;
                    newlink->next = NULL;
                    newlink->prev=NULL;
                    first = newlink;
                    end=newlink;
                }
                else
                {
                    int d=g+h;
                    if (d <= first->f )
                    {
                        link* newlink = new link;
                        newlink->id= count;
                        newlink->g = g;
                        newlink->h = h;
                        newlink->parent=p;
                        newlink->x = x;
                        newlink->y = y;
                        newlink->f=g+h;
                        newlink->next=first;
                        newlink->prev=NULL;

                        first->prev=newlink;

                        first =newlink;
                    }
                    else if ( d >= end->f )
                    {
                        link* newlink = new link;
                        newlink->id= count;
                        newlink->g = g;
                        newlink->h = h;
                        newlink->parent=p;
                        newlink->x = x;
                        newlink->y = y;
                        newlink->f=g+h;
                        newlink->next=NULL;
                        newlink->prev=end;
                        end->next=newlink;
                        end=newlink;
                    }
                    else
                    {
                        link* current = first;
                        while( current != NULL )
                        {
                            if( d<current->f || (d==current->f && g<=current->g))
                            {
                                link* newlink = new link;
                                newlink->id= count;
                                newlink->g = g;
                                newlink->h = h;
                                newlink->parent=p;
                                newlink->x = x;
                                newlink->y = y;
                                newlink->f=g+h;
                                newlink->next=current;
                                newlink->prev=current->prev;
                                current->prev->next=newlink;
                                current->prev=newlink;
                                break;
                            }
                            if( d==current->f && g>current->g)
                            {
                                current=current->next;
                                link* newlink = new link;
                                newlink->id= count;
                                newlink->g = g;
                                newlink->parent=p;
                                newlink->x = x;
                                newlink->y = y;
                                newlink->h = h;
                                newlink->f=g+h;
                                newlink->next=current;
                                newlink->prev=current->prev;
                                current->prev->next=newlink;
                                current->prev=newlink;
                                break;
                            }
                            current = current->next;
                        }

                    }

                }
                arrange();
            }
            void display()
            {
                link* current = first;
                while( current != NULL )
                {
                    cout<<current <<"\t"<<current->id<<"\t"<< current->f<<"\t" <<current->x <<"\t"<<current->y <<"\t"<<current->parent <<endl;
                    current = current->next;
                }
            }

            void arrange()
            {
                link* current = first;
                for(int i=0 ; i<count ; i++)
                {
                    current->id=i+1;
                    current = current->next;
                }
            }

            void remove(int i)
            {
                if (count==1)
                {
                    first=end=NULL;
                }
                else if (i==1)
                {
                    first=first->next;
                    first->prev=NULL;
                }
                else if (i==count)
                {
                    end=end->prev;
                    end->next=NULL;
                }
                else
                {
                    link* current = first;
                    while( current != NULL )
                    {
                        if(i==current->id)
                        {
                            current->prev->next=current->next;
                            current->next->prev=current->prev;
                            break;
                        }
                        current = current->next;
                    }

                }
                count--;
                this->arrange();
            }
    };


    void display(int path[][3],char path_letter[],int startx, int starty,int goalx,int goaly,int staticop[][2],int dynamicop[][2],int sizex,
                 int sizey,int n_of_st,int n_of_dy);
    void sethuristic (int huristic[][6],int goalx, int goaly,int staticop[][2],int n_of_st);
    int dist(int sx,int sy,int gx , int gy);
    void genrate (int px, int py ,int child[][5]);
    void path_convereter(int path[][3],char tmp[]);
    void a_star (int startx, int starty,int goalx,int goaly,int staticop[][2],int dynamicop[][2],int sizex,
                 int sizey,int path[][3],int n_of_st,int n_of_dy);


    void setprob (int n_hist ,int history[][2] ,int size ,int prob [][3]);

    int main()
    {

        int startx=0 , starty=4 , goalx=5 , goaly=5;
        int sizex=6;
        int sizey=6;
        int n_of_st=2;
        int n_of_dy=2;
        int staticop[2][2]={{0,5},{1,5}};
        int dynamicop[2][2]={{0,5},{1,5}};

        int path[50][3];

        a_star(startx,starty,goalx,goaly,staticop,dynamicop,sizex,sizey,path,n_of_st,n_of_dy);
        char path_letter[path[0][0]];
        path_convereter(path,path_letter);
        display(path,path_letter,startx,starty,goalx,goaly,staticop,dynamicop,sizex,sizey,n_of_st,n_of_dy);

        for (int i = 1; i <=path[0][0] ; ++i) {

            cout<<path[i][0]<<"\t"<<path[i][1]<<endl;

        }

        return 0;
    }

    void setprob (int n_hist ,int history[][2] ,int size ,int prob [][3])
    {

    }


    void a_star (int startx, int starty,int goalx,int goaly,int staticop[][2],int dynamicop[][2],int sizex,
                 int sizey,int path[][3],int n_of_st,int n_of_dy)
    {
        const int x=6,y=6;
        bool solved= 0;
        int child[x-1][y-1];
        linklist openlist,closedlist;
        int huristic [x][y];


        sethuristic(huristic,goalx,goaly,staticop,n_of_st);

        openlist.additem(0,huristic[startx][starty],startx,starty,NULL);
        int c=1;
        while (openlist.count>0 && !solved && c)
        {
            //c--;
            openlist.arrange();
            link* node=openlist.get(1);
            openlist.remove(1);
            genrate(node->x,node->y,child);

            for (int i = 1; i <= child[0][0] ; ++i)
            {

                if(child[i][0]==goalx && child[i][1]==goaly)
                {
                    cout<<"Goal reached \n";
                    solved=1;
                    break;
                }
                child[i][2]=node->g+1+huristic[child[i][0]][child[i][1]];
                openlist.check1(child);
                closedlist.check2(child);
            }
            for (int i = 1; i <= child[0][0] ; ++i)
            {
                if(child[i][3]==1 && child[i][4]==1)
                    openlist.additem(node->g+1,huristic[child[i][0]][child[i][1]],child[i][0],child[i][1],node);
            }
            closedlist.additem(node->g,node->h,node->x,node->y,node->parent);
            cout <<"openlist \n";
            openlist.display();

            cout <<"closedlist \n";
            closedlist.display();
        }
    openlist.getpath(path);
    }

    void path_convereter(int path[][3],char tmp[])
    {
        int count=-1;

        for (int i = path[0][0]; i >0; --i)
        {
            count++;
            if(path[i][0]==path[i-1][0] && path[i-1][1]-path[i][1]>0)
                tmp[count]='r';
            if(path[i][0]==path[i-1][0] && path[i-1][1]-path[i][1]<0)
                tmp[count]='l';
            if(path[i][1]==path[i-1][1] && path[i-1][0]-path[i][0]>0)
                tmp[count]='d';
            if(path[i][1]==path[i-1][1] && path[i-1][0]-path[i][0]<0)
                tmp[count]='u';
        }
        tmp[count]='G';
    }

    void genrate (int px, int py ,int child[][5])
    {
        int id;
        for (int i = 0; i <5 ; ++i)
            for (int j = 0; j <5 ; ++j)
                child[i][j]=1;

        child[0][0]=0;
        if(px+1>=0 && px+1 <=5) {
            id=++child[0][0];
            child[id][0] = px + 1;
            child[id][1] = py;
        }

        if(px-1>=0 && px-1 <=5) {
            id=++child[0][0];
            child[id][0] = px - 1;
            child[id][1] = py;
        }
        if(py+1>=0 && py+1 <=5) {
            id=++child[0][0];
            child[id][0] = px;
            child[id][1] = py+1;
        }
        if(py-1>=0 && py-1 <=5) {
            id=++child[0][0];
            child[id][0] = px;
            child[id][1] = py-1;
        }
    }
    void sethuristic (int huristic[][6],int goalx, int goaly,int staticop[][2],int n_of_st)
    {

        for (int i = 0; i <6 ; ++i) {
            for (int j = 0; j <6; ++j) {
                huristic[i][j]=dist(i,j,goalx,goaly)+10;
            }
        }
        huristic[goalx][goaly]=0;
        for (int k = 0; k <n_of_st; ++k) {
            huristic[staticop[k][0]][staticop[k][1]]=1000;
        }

        /*for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 6 ; ++j) {
                cout<<huristic[i][j]<<"\t";
             }
            cout<<endl;
        }*/

    }

    int dist(int sx,int sy,int gx , int gy)
    {
        return abs(gy-sy)+abs(gx-sx);
    }

    void display(int path[][3],char path_letter[],int startx, int starty,int goalx,int goaly,int staticop[][2],int dynamicop[][2],int sizex,
                 int sizey,int n_of_st,int n_of_dy)
    {
        char map[6][6];

        for (int i = 0; i <sizex; ++i)
            for (int j = 0; j <sizey; ++j)
                map[i][j]='-';

        for (int i =path[0][0]; i >0 ; --i)
            map[path[i][0]][path[i][1]]='*';

        for (int i =0; i <n_of_st ; ++i)
            map[staticop[i][0]][staticop[i][1]]='#';

        map[startx][starty]='S';
        map[goalx][goaly]='G';

        cout<<"Path from the start to goal \n";

        for (int i = 0; i <sizex; ++i) {
            for (int j = 0; j < sizey; ++j)
                cout << map[i][j] << "\t";
            cout << endl;
        }


        cout<<"Full path in letters ---->";
        for (int j = 0; j < path[0][0]; ++j)
            cout<<path_letter[j];



        for (int i = 0; i <sizex; ++i)
            for (int j = 0; j <sizey; ++j)
                map[i][j]='-';
        map[startx][starty]='S';
        map[goalx][goaly]='G';

        int t=0;
        for (int i =path[0][0]; i >0 ; --i)
        {
            map[path[i][0]][path[i][1]] = path_letter[t];
            t++;
        }
        for (int i =0; i <n_of_st ; ++i)
            map[staticop[i][0]][staticop[i][1]]='#';



        cout<<"\npath from the start to goal wirh direcions \n";

        for (int i = 0; i <sizex; ++i) {
            for (int j = 0; j < sizey; ++j)
                cout << map[i][j] << "\t";
            cout << endl;
        }
    }
