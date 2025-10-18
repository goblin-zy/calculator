#ifndef NODE_POLY_H
#define NODE_POLY_H


//类的定义
class Node{
    public:
    double xishu=0;
    int cishu=-1;
    Node* next=nullptr;
    
    //函数 
    Node()=default;
    Node(double ci,int ei):xishu(ci),cishu(ei){
        this->next=nullptr;
    };
};


class Polynomial{
    public:
    int length=0;
    Node *head=nullptr;   //头节点储存实际最高次数,规定
    Node *tail=nullptr;
    //函数
    Polynomial()=default;
   /* Polynomial(int n,const  map<int,double,greater<int>>& pp){  //pp输入窗口产生的动态分配
        this->length=n;
        head=new Node();
        head->next=nullptr;
       
        Node *head1=head;
        for(auto it=pp.begin();it!=pp.end();pp++){
            Node* p=new Node(it->second,it->first);

            head1->next=p;
            head1=head1->next;
            head1->next=nullptr;
        }

        head->cishu=head->next->cishu;//head记录最高次数
    }*/

    Polynomial(Node* p){  //  p 指的是什么？是头节点吗？
      this->head=p;
      this->tail=p;
      this->length=0;

      if(p->next!=nullptr){
      this->head->cishu=this->head->next->cishu;
      while(p->next){
        this->length++;
        p=p->next;
        if(p->next==nullptr) this->tail=p;
      }
    }

    }
//拷贝构造（深拷贝）
Polynomial(const Polynomial& other) {
    // 与 operator= 逻辑类似，深拷贝链表
    this->length = other.length;
    this->head = new Node();
    this->tail=this->head;
    this->head->cishu = other.head->cishu;

    Node *this_floop = this->head;
    Node* other_floop = other.head->next;
    while (other_floop) {
        this_floop->next = new Node(other_floop->xishu, other_floop->cishu);
        this_floop = this_floop->next;
        other_floop = other_floop->next;
        if(other_floop==nullptr){this->tail=this_floop;} //与上一个构造函数确定tail不同
    }
 
}

    ~Polynomial(){
        Node *l=head;
        while(l){
            Node* p_delete=l;
            l=l->next;
            delete p_delete; 
        }
    }

   Polynomial operator+(Polynomial& other);
   Polynomial operator-(Polynomial& other); 
   Polynomial& operator=(const Polynomial& other);
};







  #endif
