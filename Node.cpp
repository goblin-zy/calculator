#include"Node_Poly.h"
//加法函数

Polynomial Polynomial::operator+(Polynomial& other){   //这里的返回值若是Poli，那么需要重载拷贝构造函数
    Node* newhead;  // 用于第三种情况，否则就会提前析构
    //处理空多项式
    if(this->head->next==nullptr) {return other;}
    else if(other.head->next==nullptr){return *this;}

    else{
        int max_cishu=(this->head->cishu>other.head->cishu)? this->head->cishu :other.head->cishu;
        //寻找最小次数
        int min_cishu=(this->tail->cishu<other.tail->cishu)? this->tail->cishu :other.tail->cishu;

        //后续输入的时候要保证头节点的次数确实被正确记录了。
        newhead=new Node;
        // result.head->cishu=max_cishu;//最高项可能正负抵消
        newhead->next=nullptr;

        Node* plus1_head=this->head->next;
        Node* plus2_head=other.head->next;
        Node* sum_head=newhead;


        int cishu=max_cishu;
        while(cishu>=min_cishu){
            //ex1
            if(plus1_head!=nullptr&&plus2_head!=nullptr&&plus1_head->cishu==cishu&&plus2_head->cishu==cishu){

                if(plus1_head->xishu+plus2_head->xishu!=0){
                    Node *sum=new Node(plus1_head->xishu+plus2_head->xishu,cishu);  //这里默认sum->next=nullptr？？
                    sum_head->next=sum;
                    sum_head=sum_head->next;
                    plus1_head=plus1_head->next;
                    plus2_head=plus2_head->next;
                }
                else{
                    plus1_head=plus1_head->next;
                    plus2_head=plus2_head->next;
                }

            }
            //ex2
            if(plus1_head!=nullptr&&plus1_head->cishu==cishu&&(plus2_head==nullptr||plus2_head->cishu!=cishu)){
                if(plus1_head->xishu!=0){
                    Node *sum=new Node(plus1_head->xishu,cishu);
                    sum_head->next=sum;
                    sum_head=sum_head->next;
                    plus1_head=plus1_head->next;
                }
                else{
                    plus1_head=plus1_head->next;
                }

            }
            //ex3
            if(plus2_head!=nullptr&&plus2_head->cishu==cishu&&(plus1_head==nullptr||plus1_head->cishu!=cishu)){
                if(plus2_head->xishu!=0){
                    Node *sum=new Node(plus2_head->xishu,cishu);
                    sum_head->next=sum;
                    sum_head=sum_head->next;
                    plus2_head=plus2_head->next;
                }
                else{
                    plus2_head=plus2_head->next;
                }

            }

            cishu--;
        }
    }

    return Polynomial(newhead);
}



Polynomial Polynomial::operator-(Polynomial& other){
    Node* newhead;

    //如果返回值是Node*,那么使用Polynomial(Node*)并不是深拷贝（要求要提供一个新的链表），对于下面两种情况会导致二次释放内存。
    if(this->head->next==nullptr){  //返回负的的值
        Node* floop=other.head->next;
        while(floop){
            floop->xishu=0-floop->xishu;
            floop=floop->next;
        }
        return other;
    }
    else if(other.head->next==nullptr){return *this;}

    else{
        int max_cishu=(this->head->cishu>other.head->cishu)? this->head->cishu :other.head->cishu;
        //寻找最小次数
        int min_cishu=(this->tail->cishu<other.tail->cishu)? this->tail->cishu :other.tail->cishu;

        newhead=new Node;
        //result.head->cishu=max_cishu; //差的最高次数不能确定
        newhead->next=nullptr;

        Node* dimi_head=this->head->next;
        Node* sub_head=other.head->next;
        Node* cha_head=newhead;

        int cishu=max_cishu;
        while(cishu>=min_cishu){
            if(dimi_head!=nullptr&&sub_head!=nullptr&&dimi_head->cishu==cishu&&sub_head->cishu==cishu){
                if(dimi_head->xishu-sub_head->xishu!=0){
                    Node *cha=new Node(dimi_head->xishu-sub_head->xishu,cishu);
                    cha_head->next=cha;
                    cha_head=cha_head->next;
                    dimi_head=dimi_head->next;
                    sub_head=sub_head->next;
                }
                else{
                    dimi_head=dimi_head->next;
                    sub_head=sub_head->next;
                }
            }

            if(dimi_head!=nullptr&&dimi_head->cishu==cishu&&(sub_head==nullptr||sub_head->cishu!=cishu)){
                if(dimi_head->xishu!=0){
                    Node *cha=new Node(dimi_head->xishu,cishu);
                    cha_head->next=cha;
                    cha_head=cha_head->next;
                    dimi_head=dimi_head->next;
                }
                else{
                    dimi_head=dimi_head->next;
                }
            }

            if((dimi_head==nullptr||dimi_head->cishu!=cishu)&&sub_head!=nullptr&&sub_head->cishu==cishu){
                if(sub_head->xishu!=0){
                    Node *cha=new Node(-sub_head->xishu,cishu);
                    cha_head->next=cha;
                    cha_head=cha_head->next;
                    sub_head=sub_head->next;
                }
                else{
                    sub_head=sub_head->next;
                }
            }

            cishu--;
        }
    }


    return Polynomial(newhead);
}


Polynomial& Polynomial::operator=(const Polynomial& other){
    if(this!=&other){
        //首先删除this链表
        Node *l=head;
        while(l){
            Node* p_delete=l;
            l=l->next;
            delete p_delete;
        }
        //深拷贝
        this->length=other.length;

//处理特殊情况,即other连头节点都没有
        if(other.head==nullptr) {
            this->head=nullptr;
            this->tail=nullptr;
            this->length=0;
            return *this;
        }

        this->head=new Node;
        this->tail=this->head;
        //次数不一定有，可能是空项
        if(other.head->next!=nullptr) head->cishu=other.head->next->cishu;

        Node *this_floop=this->head;
        Node* other_floop=other.head->next;
        while(other_floop){
            Node* p=new Node(other_floop->xishu,other_floop->cishu);
            this_floop->next=p;

            this_floop=this_floop->next;
            other_floop=other_floop->next;

            if(other_floop==nullptr) this->tail=this_floop;
        }
    }
    return *this;
}
