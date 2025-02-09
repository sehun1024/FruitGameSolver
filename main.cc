#include <iostream>

class coord
{
public:
    int x;
    int y;
};

class box
{
public:
    coord s;
    coord e;
    bool is_val()
    {
        return (s.x!=-1);
    }
    void print()
    {
        std::cout<<"{{"<<s.x+1<<","<<s.y+1<<"},{"<<e.x+1<<","<<e.y+1<<"}}"<<std::endl;
    }
};

class board
{
public:
    int** bd;
    int row,column;
    board(int rowt,int columnt)
    {
        row=rowt;
        column=columnt;
        int i;
        
        bd=new int* [row];
        for(int i=0;i<row;i++)
        {
            bd[i]=new int[column];
        }
    }
    board(std::string str)
    {
        
        int r=0;
        int c=0;
        std::string::iterator it;
        it=str.begin();
        

        while(it!= str.end() && *it!='}')
        {
            if(isdigit(*it))
            {
                c++;
            };
            ++it;
        }
        ++it;
        r++;
        while(it!= str.end() && *it!='}')
        {
            if(*it=='{')
            {
                r++;
                while(*it!='}')
                {
                    ++it;
                }
            };
            ++it;
        }
            

        
        row=r;
        column=c;

        bd=new int* [r];
        for(int i=0;i<r;i++)
        {
            bd[i]=new int[c];
        }



        it=str.begin();
        int i,j;
        for(i=0;i<r;i++)
        {
            for(j=0;j<c;j++)
            {
                while(true)
                {
                    if(it!= str.end())
                    {
                        if(isdigit(*it))
                        {
                            bd[i][j]=(*it)-'0';
                            ++it;
                            break;
                        }else{
                            ++it;
                        }
                    }else{
                        bd[i][j]=0;
                        break;
                    }
                }
            }
        }
        


    }
    
    void set_val(int i,int j,int v)
    {
        bd[i][j]=v;
    }
    void print()
    {
        int i,j;
        for(int i=0;i<row;i++)
        {
            for(int j=0;j<column;j++)
            {
                std::cout<<bd[i][j]<<" ";
            }
            std::cout<<std::endl;
        }

    }
    void print(box b)
    {
        int i,j;
        for(int i=0;i<row;i++)
        {
            for(int j=0;j<column;j++)
            {
                if(i>=b.s.x && i<=b.e.x && j>=b.s.y && j<=b.e.y )
                {
                    std::cout<<"* ";
                }else{
                    std::cout<<bd[i][j]<<" ";
                }
                
            }
            std::cout<<std::endl;
        }
    }
    box check(int x,int y)
    {
        int i,j,k,sum;
        for(int i=0;i<row-x;i++)
        {
            sum=0;
            for(int j=0;j<column-y;j++)
            {
                for(k=0;k<=i;k++)
                {
                    sum=sum+bd[x+k][y+j];
                }
                if(sum==10)
                {
                    return {{x,y},{x+i,y+j}};
                }
                else if
                (sum>10)
                {
                    break;
                }
            }
            
        }
        return {{-1,-1},{-1,-1}};

    }
    bool reduction (box b)
    {
        int i,j;
        int sum=0;
        for(i=b.s.x;i<=b.e.x;i++)
        {
            for(j=b.s.y;j<=b.e.y;j++)
            {
                sum=sum+bd[i][j];
            }
        }
        if(sum==10)
        {
            for(i=b.s.x;i<=b.e.x;i++)
            {
                for(j=b.s.y;j<=b.e.y;j++)
                {
                    bd[i][j]=0;
                }
            }
            return true;
        }
        else{
            return false;
        }
    }
    box reduction_step()
    {
        int i,j;
        for(i=0;i<row;i++)
        {
            for(j=0;j<column;j++)
            {
                box b=check(i,j);
                if(b.is_val())
                {
                    reduction(b);
                    return b;
                }
            }
        }
        return {{-1,-1},{-1,-1}};
    }

};



int main()
{
    int i,j;
    /*
    int r=10;
    int c=17;
    int dat[r][c]={
        {9,1,7,4,3,8,1,7,4,2,8,4,3,8,4,9,6},
        {8,5,3,4,9,8,1,5,7,2,3,9,9,1,9,4,2},
        {9,7,6,6,2,4,8,7,1,1,4,3,9,9,8,4,7},
        {8,2,4,4,5,5,6,4,2,3,7,1,1,2,5,5,2},
        {7,8,5,6,6,3,1,5,4,2,7,2,9,6,8,3,8},
        {3,1,6,2,7,3,9,6,7,7,9,3,6,3,3,7,7},
        {4,7,1,9,9,4,7,6,6,5,8,1,2,3,4,9,5},
        {3,5,1,2,8,6,6,6,5,8,1,2,6,4,9,8,5},
        {2,9,2,8,3,3,9,5,3,4,1,9,3,5,2,4,5},
        {6,7,9,8,4,1,9,3,4,2,3,3,3,1,8,5,8}
    };
    board input_board=board(r,c);
    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            input_board.set_val(i,j,dat[i][j]);
        }
    }
        */
    std::string str="";
    std::string input;
    std::string::iterator it;
    int count=0;
    while(true)
    {
        std::cin>>input;
        str=str+input;
        for(it=input.begin();it!=input.end();++it)
        {
            if(*it=='{')
            {
                count++;
            }
            if(*it=='}')
            {
                count--;
            }
        }
        if(count==0)
        {
            
            break;
        }
    }
    
    

    board input_board=board(str);
    while(true)
    {
        box b=input_board.reduction_step();
        if(b.is_val())
        {
            input_board.print(b);
            b.print();
        }
        else
        {
            input_board.print();
            std::cout<<"Nothing to reduce."<<std::endl;
            break;
        }
        
    }

    
    return 0;
}