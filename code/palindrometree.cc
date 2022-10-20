// base on idea odd palindrome, even palindrome
// 0-odd is the root of tree
struct node
{
    int len;
    node *child[26], *sufflink;
    node()
    {
        len = 0;
        for (int i = 0; i < 26; ++i)
            child[i] = NULL;
        sufflink = NULL;
    }
};
struct PalindromeTree
{
    node odd, even;
    PalindromeTree()
    {
        odd.len = -1;
        odd.sufflink = &odd;
        even.len = 0;
        even.sufflink = &odd;
    }
    void Assign(string &s)
    {
        node *last = &even;
        for (int i = 0; i < (int)s.size(); ++i)
        {
            node *tmp = last;
            while (s[i - tmp->len - 1] != s[i])
                tmp = tmp->sufflink;
            if (tmp->child[s[i] - 'a'])
            {
                last = tmp->child[s[i] - 'a'];
                continue;
            }
            tmp->child[s[i] - 'a'] = new node;
            last = tmp->child[s[i] - 'a'];
            last->len = tmp->len + 2;
            if (last->len == 1)
            {
                last->sufflink = &even;
                continue;
            }
            tmp = tmp->sufflink;
            while (s[i - tmp->len - 1] != s[i])
                tmp = tmp->sufflink;
            last->sufflink = tmp->child[s[i] - 'a'];
        }
    }
};