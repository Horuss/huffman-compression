#include "functions.h"

void preorder(node *act,string code,string bit,string* coding)
{
    if(act!=0)
    {
        act->code=code+bit;
        if(act->ch!=0) coding[(int)act->ch]=act->code;
        preorder(act->left,act->code,"0",coding);
        preorder(act->right,act->code,"1",coding);
    }
}

string code()
{
    priority_queue<node> pr_queue;
    fstream in_file;
    fstream out_file;
    string name,name2;
    string coding[128];
    for(int i=0;i<128;i++)
    {
        coding[i]="";
    }
    cout << "Input text file:\n";
    cin >> name;
    in_file.open(name.c_str(),ios::in| ios::binary);
    if(in_file.is_open()==false) return "Error opening file: \""+ name+"\" !\n";
    int tab[128];
    for(int i=0;i<128;i++)
    {
        tab[i]=0;
    }
    char c;
    while(in_file.get(c))
    {
        tab[(int)c]++;
    }
    in_file.close();
    char code_count=0;
    for(int i=0;i<128;i++)
    {
        if(tab[i]!=0)
        {
            code_count++;
            node *newNode=new node;
            newNode->count=tab[i];
            newNode->ch=i;
            newNode->code="";
            newNode->left=0;
            newNode->right=0;
            pr_queue.push(*newNode);
        }
    }
    node* root=NULL;
    while(pr_queue.size()>1)
    {
        node *newNode=new node;
        node *newNode1=new node;
        node *newNode2=new node;
        newNode1->ch=pr_queue.top().ch;
        newNode1->count=pr_queue.top().count;
        newNode1->code=pr_queue.top().code;
        newNode1->left=pr_queue.top().left;
        newNode1->right=pr_queue.top().right;
        pr_queue.pop();
        newNode2->ch=pr_queue.top().ch;
        newNode2->count=pr_queue.top().count;
        newNode2->code=pr_queue.top().code;
        newNode2->left=pr_queue.top().left;
        newNode2->right=pr_queue.top().right;
        pr_queue.pop();
        newNode->ch=0;
        newNode->count=newNode1->count+newNode2->count;
        newNode->left=newNode1;
        newNode->right=newNode2;
        newNode->code="";
        pr_queue.push(*newNode);
        root=newNode;
    }
    preorder(root,"","",coding);
    cout << "Output text file:\n";
    cin >> name2;
    out_file.open(name2.c_str(),ios::out | ios::trunc | ios::binary);
    if(out_file.is_open()==false) return "Error creating file: \""+name2+"\" !\n";
    out_file.put(code_count);
    byte b={0,0,0,0,0,0,0,0};
    for(int i=0;i<128;i++)
    {
        if(coding[i]!="")
        {
            char ch=i;
            out_file.put(ch);
            char length=coding[i].length();
            out_file.put(length);
            int counter_bit=1;
            for(unsigned int j=0;j<coding[i].length();j++)
            {
                switch(counter_bit)
                {
                    case 1: b.bit1= ((coding[i][j] == '1') ? 1 : 0);  break;
                    case 2: b.bit2= ((coding[i][j] == '1') ? 1 : 0);  break;
                    case 3: b.bit3= ((coding[i][j] == '1') ? 1 : 0);  break;
                    case 4: b.bit4= ((coding[i][j] == '1') ? 1 : 0);  break;
                    case 5: b.bit5= ((coding[i][j] == '1') ? 1 : 0);  break;
                    case 6: b.bit6= ((coding[i][j] == '1') ? 1 : 0);  break;
                    case 7: b.bit7= ((coding[i][j] == '1') ? 1 : 0);  break;
                    case 8: b.bit8= ((coding[i][j] == '1') ? 1 : 0);
                            out_file.write((char *) &b, 1);
                            counter_bit=0;
                            break;
                }
                counter_bit++;
            }
            if(counter_bit!=1) out_file.write((char *) &b, 1);
        }
    }
    int counter_bit=1;
    in_file.open(name.c_str(),ios::in| ios::binary);
    ifstream plik(name.c_str(), ifstream::ate);
    streampos size;
    if (!plik.fail())
    {
        size = plik.tellg();
        plik.close();
    }
    long size_long=static_cast<long>(size);
    out_file<<size_long;
    while(in_file.get(c))
    {
        for(unsigned int i=0;i<coding[(int)c].length();i++)
        {
            switch(counter_bit)
            {
                case 1: b.bit1= ((coding[(int)c][i] == '1') ? 1 : 0);  break;
                case 2: b.bit2= ((coding[(int)c][i] == '1') ? 1 : 0);  break;
                case 3: b.bit3= ((coding[(int)c][i] == '1') ? 1 : 0);  break;
                case 4: b.bit4= ((coding[(int)c][i] == '1') ? 1 : 0);  break;
                case 5: b.bit5= ((coding[(int)c][i] == '1') ? 1 : 0);  break;
                case 6: b.bit6= ((coding[(int)c][i] == '1') ? 1 : 0);  break;
                case 7: b.bit7= ((coding[(int)c][i] == '1') ? 1 : 0);  break;
                case 8: b.bit8= ((coding[(int)c][i] == '1') ? 1 : 0);
                        out_file.write((char *) &b, 1);
                        counter_bit=0;
                        break;
            }
            counter_bit++;
        }
    }
    switch(counter_bit)
    {
        case 2: b.bit2=0;b.bit3=0;b.bit4=0;b.bit5=0;b.bit6=0;b.bit7=0;b.bit8=0;break;
        case 3: b.bit3=0;b.bit4=0;b.bit5=0;b.bit6=0;b.bit7=0;b.bit8=0;break;
        case 4: b.bit4=0;b.bit5=0;b.bit6=0;b.bit7=0;b.bit8=0;break;
        case 5: b.bit5=0;b.bit6=0;b.bit7=0;b.bit8=0;break;
        case 6: b.bit6=0;b.bit7=0;b.bit8=0;break;
        case 7: b.bit7=0;b.bit8=0;break;
        case 8: b.bit8=0;break;
    }
    if(counter_bit!=1) out_file.write((char *) &b, 1);
    in_file.close();
    out_file.close();
    return "Compressed!\n";
}

string decode()
{
    fstream in_file;
    fstream out_file;
    map<string,char> coding_map;
    map<string,char>::iterator it;
    string name,name2;
    cout << "Compressed text file:\n";
    cin >> name;
    in_file.open(name.c_str(), ios::in | ios::binary);
    if(in_file.is_open()==false) return "Error opening file: \""+name+"\" !\n";
    char code_count=0;
    in_file.get(code_count);
    char c,length;
    string code;
    byte b;
    for(int i=0;i<code_count;i++)
    {
        in_file.get(c);
        in_file.get(length);
        int counter_bit=1;
        code="";
        for(int j=1;j<=length;j++)
        {
            if(counter_bit==1) in_file.read((char *) &b, 1);
            switch(counter_bit)
            {
                case 1: if(b.bit1!=0) code+='1'; else code+='0'; break;
                case 2: if(b.bit2!=0) code+='1'; else code+='0'; break;
                case 3: if(b.bit3!=0) code+='1'; else code+='0'; break;
                case 4: if(b.bit4!=0) code+='1'; else code+='0'; break;
                case 5: if(b.bit5!=0) code+='1'; else code+='0'; break;
                case 6: if(b.bit6!=0) code+='1'; else code+='0'; break;
                case 7: if(b.bit7!=0) code+='1'; else code+='0'; break;
                case 8: if(b.bit8!=0) code+='1'; else code+='0'; break;
            }
            counter_bit++;
            if(counter_bit>8) counter_bit=1;
        }
        coding_map[code]=c;
    }
    cout << "Output text file:\n";
    cin >> name2;
    out_file.open(name2.c_str(),ios::out | ios::trunc | ios::binary);
    if(out_file.is_open()==false) return "Error creating file: \""+name2+"\" !\n";
    long size_long=0;
    in_file>>size_long;
    code="";
    int counter_bit=1;
    int n=0;
    while(n!=size_long)
    {
        in_file.read((char *) &b, 1);
        for(int i=1;i<=8;i++)
        {
            if(n==size_long) break;
            switch(counter_bit)
            {
                case 1: if(b.bit1==1) code+='1'; else code+='0'; break;
                case 2: if(b.bit2==1) code+='1'; else code+='0'; break;
                case 3: if(b.bit3==1) code+='1'; else code+='0'; break;
                case 4: if(b.bit4==1) code+='1'; else code+='0'; break;
                case 5: if(b.bit5==1) code+='1'; else code+='0'; break;
                case 6: if(b.bit6==1) code+='1'; else code+='0'; break;
                case 7: if(b.bit7==1) code+='1'; else code+='0'; break;
                case 8: if(b.bit8==1) code+='1'; else code+='0'; break;
            }
            if(coding_map[code]!=0)
            {
                out_file.put(coding_map[code]);
                n++;
                code="";
            }
            counter_bit++;
            if(counter_bit>8) counter_bit=1;
        }
    }
    in_file.close();
    out_file.close();
    return "Decompressed!\n";
}
