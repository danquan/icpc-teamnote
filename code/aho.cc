constexpr int ALPHABET_SIZE = 26;
constexpr int firstCharacter = 'a';

struct Node
{
    Node *to[ALPHABET_SIZE];
    Node *suflink;
    int ending_length; // 0 if is not ending

    Node()
    {
        for (int i = 0; i < ALPHABET_SIZE; ++i)
            to[i] = NULL;
        suflink = NULL;
        ending_length = false;
    }
};

struct AhoCorasick
{
    Node *root;

    AhoCorasick()
    {
        root = new Node();
    }

    void add(const string &s)
    {
        Node *cur_node = root;

        for (char c : s)
        {
            int v = c - firstCharacter;

            if (!cur_node->to[v])
                cur_node->to[v] = new Node();

            cur_node = cur_node->to[v];
        }

        cur_node->ending_length = s.size();
    }

    // if a->to[v] == NULL
    // for convinient a->to[v] = root
    // root -> suflink = root

    void build()
    {
        queue<Node *> Q;
        root->suflink = root;
        Q.push(root);

        while (!Q.empty())
        {
            Node *par = Q.front();
            Q.pop();
            for (int c = 0; c < ALPHABET_SIZE; ++c)
            {
                if (par->to[c])
                {
                    par->to[c]->suflink = par == root ? root : par->suflink->to[c];
                    Q.push(par->to[c]);
                }
                else
                {
                    par->to[c] = par == root ? root : par->suflink->to[c];
                }
            }
        }
    }
};
