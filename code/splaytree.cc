struct KNode
{
    int Value;
    int Size;
    KNode *P, *L, *R;
};
using QNode = KNode *;
KNode No_thing_here;
QNode nil = &No_thing_here, root;
 
void Link(QNode par, QNode child, bool Right)
{
    child->P = par;
    if (Right)
        par->R = child;
    else
        par->L = child;
}
 
void Update(QNode &a)
{
    a->Size = a->L->Size + a->R->Size + 1;
}
 
void Init()
{
    nil->Size = 0;
    nil->P = nil->L = nil->R = nil;
    root = nil;
    for (int i = 1; i <= n; ++i)
    {
        QNode cur = new KNode;
        cur->P = cur->L = cur->R = nil;
        cur->Value = i;
        Link(cur, root, false);
        root = cur;
        Update(root);
    }
}
 
void Rotate(QNode x)
{
    QNode y = x->P;
    QNode z = y->P;
    if (x == y->L)
    {
        Link(y, x->R, false);
        Link(x, y, true);
    }
    else
    {
        Link(y, x->L, true);
        Link(x, y, false);
    }
    Update(y);
    Update(x);
    x->P = nil;
    if (z != nil)
        Link(z, x, z->R == y);
}
 
void Up_to_Root(QNode x)
{
    while (1){
        QNode y = x->P;
        QNode z = y->P;
        if(y == nil)
            break;
        if(z != nil){
            if((x == y->L) == (y == z->L))
                Rotate(y);
            else
                Rotate(x);
        }
        Rotate(x);
    }
}
 
QNode The_kth(QNode x, int k)
{
    while (true)
    {
        if (x->L->Size == k - 1)
            return x;
        if (x->L->Size >= k)
            x = x->L;
        else
        {
            k -= x->L->Size + 1;
            x = x->R;
        }
    }
    return nil;
}
 
void Split(QNode x, int k, QNode &a, QNode &b)
{
    if (k == 0)
    {
        a = nil;
        b = x;
        return;
    }
    QNode cur = The_kth(x, k);
    Up_to_Root(cur);
    a = cur;
    b = a->R;
    a->R = nil;
    b->P = nil;
    Update(a);
}
 
QNode Join(QNode a, QNode b)
{
    if (a == nil)
        return b;
    while (a->R != nil)
        a = a->R;
    Up_to_Root(a);
    Link(a, b, true);
    Update(a);
    return a;
}
 
void Print(QNode &a)
{
    if (a->L != nil)
        Print(a->L);
    cout << (a->Value) << " ";
    if (a->R != nil)
        Print(a->R);
}
